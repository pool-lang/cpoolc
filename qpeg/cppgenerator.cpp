/**************************************************************************
**   QPeg, the PEG parser generator
**   Copyright 2010 Mohamed Samy Ali - samy2004@gmail.com
**   This project is released under the Apache License version 2.0
**   as described in the included license.txt file
**************************************************************************/

#include "cppgenerator.h"

QString CPPGenerator::genType(PegType *ast, GenContext *context)
{
    if(isa<PegTypeId *>(ast))
        return to<PegTypeId *>(ast)->id;
    if(isa<PegPointerType *>(ast))
        return genType(to<PegPointerType*>(ast)->baseType, context) + " *";
    if(isa<PegParametrizedType*>(ast))
    {
        PegParametrizedType *pt = to<PegParametrizedType *>(ast);
        QStringList typeArgs;
        for(int i=0; i<pt->params.count(); i++)
            typeArgs.append(genType(pt->params[i], context));
        return QString("%1 <%2>").arg(genType(pt->baseType, context))
                                 .arg(typeArgs.join(", "));
    }

    if(isa<PegFunType *>(ast))
    {
        // example:
        //bool (PegParser::*x)(Buffer &, QString &, Error &);
        // x = &PegParser::identifier;
        // (this->*x)(_b, s, error);

        PegFunType *funt = to<PegFunType *>(ast);
        QString typeName = context->makeVar("type_");

        QStringList typeArgs;
        for(int i=0; i<funt->paramTypes.count(); i++)
        {
            typeArgs.append(genType(funt->paramTypes[i], context));
        }

        QString type = QString("typedef bool (%1::*%2)(Buffer &, %3 &, Error & %4);")
                .arg(context->className)
                .arg(typeName)
                .arg(genType(funt->returnType, context))
                .arg(typeArgs.empty()?"": QString(", %1").arg(typeArgs.join(", ")));
        context->typeDefs[typeName] = type;
        return typeName;
    }


    throw QString("CPPGenerator::genType");
}

#include <iostream>

QString CPPGenerator::genRule(PegRule  *ast, GenContext *context, QString &retStmts, QString cutVar)
{
    retStmts = "";
    rulesGroupedByReturnType[ast->returnType->toString()].append(ast);

    QStringList trans;
    for(int i=0; i<ast->templateParams.count(); i++)
        trans.append(QString(" class %1 ").arg(ast->templateParams[i]));

    context->vars.clear();
    QString statements;
    QString expression;

    QString memoizationMapName = QString("memoize_")+ ast->name;
    if(ast->templateParams.empty())
    {
        this->memoizationMaps[memoizationMapName] = ast->returnType->toString();
    }
    expression = this->gen(ast->expr, context, statements, cutVar);

    QString funBody = QString("{\n\
                    int _thisPos = _b.getP2();\n\
                    %1\n\
                    if(%2.contains(_thisPos))\n\
                    {\n\
                        ret=%2[_thisPos].value;\n\
                        return %2[_thisPos].getValues(_b);\n\
                    }\n\
                    %3\n\
                    %4\n\
                    stackTrace.push(QString(\"%5\")+\"   \"+_b.remainder().mid(10));\n\
                    %6\n\
                    %7\n\
                   bool _success = %8;\n\
                    %1\n\
                    %2[_thisPos] = ParseResult<%9 >(_success, ret, _b.saveState());\n\
                    %3\n\
                    stackTrace.pop();\n\
                   \treturn _success; \n\
                   }\n\
                   \n")
            .arg(ast->templateParams.empty()? "": "// No memoization due to template params\n/*")
            .arg(memoizationMapName)
            .arg(ast->templateParams.empty()? "": "*/")
            .arg(generateLocalDeclarations(context->vars))
            .arg(ast->name)
            .arg(ast->code)
            .arg(statements)
            .arg(expression)
            .arg(ast->returnType->toString());

        QStringList formalParams;
        for(int i=0; i<ast->paramList.count(); i++)
        {
            // We shall now marry the argument and its type
            // if the type is normal, we shall simply have the form
            //            Type Parameter
            // but if the type is a method pointer it needs to be something like
            //            ret (className::*Parameter)(args)
            // this is why we call it a 'PegFunType', because it is so much fun.

            if(isa<PegFunType*>(ast->paramList[i]->type))
            {
                formalParams.append(marryFunTypeAndArg(to<PegFunType *>(ast->paramList[i]->type), ast->paramList[i]->name, context));
            }
            else
            {
                formalParams.append(QString("%1 %2")
                                    .arg(genType(ast->paramList[i]->type, context))
                                    .arg(ast->paramList[i]->name)
                                    );
            }
        }
        if(ast->templateParams.empty())
        {
            context->prototypes.append(QString("bool %1(Buffer &_b, %2 &ret, Error &error%4);")
                               .arg(ast->name)
                               .arg(ast->returnType->toString())
                               .arg(formalParams.empty()?"": QString(", %1").arg(formalParams.join(", "))));
            QString s = QString("bool %1::%2(Buffer &_b, %3 &ret, Error &error)\n")
                    .arg(context->className)
                    .arg(ast->name)
                    .arg(ast->returnType->toString());
            return s +funBody;
        }
        else
        {
            context->prototypes.append(QString("template <%1> bool %2(Buffer &_b, %3 &ret, Error &error%4)\n\
                                               %5\n")
                           .arg(trans.join(" , "))
                           .arg(ast->name)
                           .arg(ast->returnType->toString())
                           .arg(formalParams.empty()?"": QString(", %1").arg(formalParams.join(", ")))
                           .arg(funBody));
            return "";
        }
}

QString CPPGenerator::marryFunTypeAndArg(PegFunType *type, QString name, GenContext *context)
{
    // todo: If we have function types in the argument or return
    // type then they will be still generated with genType, i.e no templates :(
    // :(    :(    :(
    QStringList typeArgs;
    for(int i=0; i<type->paramTypes.count(); i++)
    {
        typeArgs.append(genType(type->paramTypes[i], context));
    }

    return QString("bool (%1::*%2)(Buffer &, %3 &, Error & %4)")
            .arg(context->className)
            .arg(name)
            .arg(genType(type->returnType, context))
            .arg(typeArgs.empty()?"": QString(", %1").arg(typeArgs.join(", ")));
}

QString CPPGenerator::genNonterminal(PegNonterminal *ast, GenContext *context, QString &statements, QString cutVar)
{
    if(ast->varName == "")
        ast->varName = QString("_dummy_%1").arg(context->dummyCount++);

    if(!context->symbols.contains(ast->id))
        throw QString("unknown rule: " + ast->id);
    context->vars[ast->varName] =
            genType(instantiateType(context->symbols[ast->id]->returnType,
                            context->symbols[ast->id]->templateParams,
                            ast->templateArgs
                            ), context);
    QString resultVar = context->makeVar("result");
    QString codeToGen = "";
    if(ast->code != "")
    {
        codeToGen = QString("if(%1)\n\
                            {\n\
                               %2\n\
                           }\n")
        .arg(resultVar)
        .arg(ast->code);
    }
    statements = QString("bool %1=%2(_b, %3, error%4);\n\
                         %5\n\
                        ")
                    .arg(resultVar)
                    .arg(ast->id)
                    .arg(ast->varName)
                    .arg(generateExtraArgsToCall(ast->args, context))
                    .arg(codeToGen);
    return resultVar;
}

PegType *CPPGenerator::instantiateType(PegType *type, QStringList templateParams, QVector<PegType *> templateArgs)
{
    if(isa<PegPointerType *>(type))
    {
        return new PegPointerType(instantiateType(to<PegPointerType *>(type)->baseType, templateParams, templateArgs));
    }
    if(isa<PegParametrizedType *>(type))
    {
        PegParametrizedType *ppt = to<PegParametrizedType *>(type);
        QVector<PegType *> newArgs;
        for(int i=0; i<ppt->params.count(); i++)
        {
            newArgs.append(instantiateType(ppt->params[i], templateParams, templateArgs));
        }
        return new PegParametrizedType(ppt->baseType, newArgs);
    }
    if(isa<PegTypeId *>(type))
    {
        PegTypeId *id = (PegTypeId *) type;
        if(templateParams.contains(id->id))
        {
            int index = templateParams.indexOf(id->id);
            return templateArgs[index];
        }
        else
        {
            return type;
        }
    }
    throw QString("Cannot instantiate type");
}

QString CPPGenerator::generateArg(PegValue *arg, GenContext *context)
{
    if(isa<PegStringArg *>(arg))
    {
        return to<PegStringArg *>(arg)->str;
    }
    if(isa<PegSharpQuote *>(arg))
    {
        PegSharpQuote *sq = to<PegSharpQuote *>(arg);
        QString s1, s2;
        return genSharpQuote(sq, context, s1, s2);// todo: full generateArg
    }
    throw QString("Unknown pegvalue");
}
QString CPPGenerator::genSeq(PegSeq *ast, GenContext *context, QString &statements, QString cutVar)
{
    if(ast->elements.count()==1 && ast->code =="" && ast->varName=="")
        return gen(ast->elements[0], context, statements, cutVar);
    QStringList ret;
    QString resultVar = context->makeVar("result");
    QString bufferStateVar = context->makeVar("_s");
    QString head = QString("\
        bool %2=true;\n\
        BufferState %1 = _b.saveState();\n\
        do\n\
        {\n").arg(bufferStateVar).arg(resultVar);

        QString _template = QString(
                "%1 %2 = %2 && %3;\n\
        if(!%2)\n\
        {\n\
        \t_b.restoreState(%4);\n\
        \tbreak;\n\
        };\n");

        ret.append(head);
        for(int i=0; i<ast->elements.count(); i++)
        {
            QString stmts;
            QString expr = gen(ast->elements[i], context, stmts, cutVar);
            ret.append(QString(_template)
                       .arg(stmts)
                       .arg(resultVar)
                       .arg(expr)
                       .arg(bufferStateVar));
        }
        ret.append(QString("\n} while(false);\n"));
        statements =  ret.join("");
        return resultVar;
}

QString CPPGenerator::genChoice(PegChoice *ast, GenContext *context, QString &statements, QString cutVar)
{
    if(ast->elements.count()==1 && ast->code =="" && ast->varName=="")
        return gen(ast->elements[0], context, statements, cutVar);

    QString myCutVar = context->makeVar("_cut");
    QString resultVar = context->makeVar("result");
    QString bufferStateVar = context->makeVar("_s");
    QString head = QString("\
                                   bool %1=false;\n\
                                   bool %2=false;\n\
                                   BufferState %3 = _b.saveState();\n")
                              .arg(resultVar)
                              .arg(myCutVar)
                              .arg(bufferStateVar);

    QString _template = QString("if(!%2 && !%5)\n\
                                {\n\
                                    %1 %2 = %2 || %3;\n\
                                    if(!%2)\n\
                                    {\n\
                                       _b.restoreState(%4);\n\
                                    }\n\
                                }\n");
    QStringList ret;
    ret.append(head);
    for(int i=0; i<ast->elements.count(); i++)
    {
        QString stmts;
        QString expr = gen(ast->elements[i], context, stmts, myCutVar);
        ret.append(QString(_template)
                   .arg(stmts)
                   .arg(resultVar)
                   .arg(expr)
                   .arg(bufferStateVar)
                   .arg(myCutVar));
    }
    statements = ret.join("");
    return resultVar;
}

QString CPPGenerator::genLoop(PegLoop *ast, GenContext *context, QString &statements, QString cutVar)
{
    QString resultVar = context->makeVar("result");
    QString myCutVar = context->makeVar("_cut");
    QString stmts2, exp;
    exp = gen(ast->expr, context, stmts2, myCutVar);
    statements = QString("\
    bool %1 = true;\n\
    bool %2 = false;\n\
    while(true)\n\
    {\n\
        %2= false;\n\
        BufferState _s = _b.saveState();\n\
        %3\
        if(!(%4))\n\
        {\n\
            _b.restoreState(_s);\n\
            if(%2)\n\
            {\n\
                %1 = false;\n\
            }\n\
            break;\n\
        };\n\
    }\n")
    .arg(resultVar)
    .arg(myCutVar)
    .arg(stmts2)
    .arg(exp);
    return resultVar;
}

QString CPPGenerator::genNot(PegNot *ast, GenContext *context, QString &statements, QString cutVar)
{
    QString resultVar = context->makeVar("result");
    QString bufferStateVar = context->makeVar("_s");

    QString exp, stmts;
    exp = gen(ast->expr, context, stmts, cutVar);

    statements = QString("\
        BufferState %1 = _b.saveState();\n\
        %2\
        bool %3 = !(%4);\n\
        _b.restoreState(%1);\n")
        .arg(bufferStateVar)
        .arg(stmts)
        .arg(resultVar)
        .arg(exp);
    return resultVar;
}

QString CPPGenerator::genAndPredicate(PegAndPredicate *ast, GenContext *context, QString &statements, QString cutVar)
{
    QString resultVar = context->makeVar("result");
    QString bufferStateVar = context->makeVar("_s");

    QString exp, stmts;
    exp = gen(ast->expr, context, stmts, cutVar);

    statements = QString("\
        BufferState %1 = _b.saveState();\n\
        %2\
        bool %3 = %4;\n\
        _b.restoreState(%1);\n")
        .arg(bufferStateVar)
        .arg(stmts)
        .arg(resultVar)
        .arg(exp);
    return resultVar;

}

QString CPPGenerator::genSnippet(PegSnippet *ast, GenContext *context, QString &statements, QString cutVar)
{
    if(ast->varName == "")
        ast->varName = QString("_dummy_%1").arg(context->dummyCount++);

    context->vars[ast->varName] = "Token";
    QString resultVar = context->makeVar("result");
    QString codeToGen = "";
    if(ast->code != "")
    {
        codeToGen = QString("if(%1)\n\
                            {\n\
                               %2\n\
                            }\n")
        .arg(resultVar)
        .arg(ast->code);
    }
    QString subStatements;
    QString subResult = gen(ast->expr, context, subStatements, cutVar);
    QString bufferStatePre = context->makeVar("_spre");
    QString bufferStatePost = context->makeVar("_spost");
    statements = QString("BufferState %1 = _b.saveState();\n\
                         %2 bool %3=%4;\n\
                         if(%3)\n\
                         {\n\
                            BufferState %5= _b.saveState();\n\
                            %6 = getRange(_b, %1, %5);\n\
                         }\n\
                         %7\
                        ")
                    .arg(bufferStatePre)
                    .arg(subStatements)
                    .arg(resultVar)
                    .arg(subResult)
                    .arg(bufferStatePost)
                    .arg(ast->varName)
                    .arg(codeToGen);
    return resultVar;
}

QString CPPGenerator::genCut(PegCut *ast, GenContext *context, QString &statements, QString cutVar)
{
    statements = QString("%1=true;\n").arg(cutVar);
    return "true";
}

QString CPPGenerator::genSemanticPredicate(PegSemanticPredicate *ast, GenContext *context, QString &statements, QString curVar)
{
    return ast->condition;
}

QString CPPGenerator::genApply(PegApply *ast, GenContext *context, QString &statements, QString cutVar)
{
    //todo: we can either apply sharp quotes or identifiers
    //todo: make apply variadic and pass along all params

    if(ast->varName == "")
        ast->varName = QString("_dummy_%1").arg(context->dummyCount++);

    context->vars[ast->varName] = genType(ast->retType, context);
    PegIdArg *func = (PegIdArg *) ast->func;

   QString allArgs = generateExtraArgsToCall(ast->args, context);

    return QString("(this->*%1)(_b, %2, error%3)")
            .arg(func->id)
            .arg(ast->varName)
            .arg(allArgs);

    /*return QString("apply_%1(%2,_b, ret, error)")
            .arg(normalizeType(ast->retType->toString()))
            .arg(ast->toString());
    */

}
QString CPPGenerator::generateExtraArgsToCall(QVector<PegValue *> args, GenContext *context)
{
    QString allArgs = "";
    QStringList argExpressions;
    if(!args.empty())
    {
        for(int i=0; i<args.count(); i++)
        {
            argExpressions.append(generateArg(args[i], context));
        }
        allArgs = QString(", %1").arg(argExpressions.join(", "));
    }
    return allArgs;
}
QString CPPGenerator::genSharpQuote(PegSharpQuote *ast, GenContext *context, QString &statements, QString curVar)
{
    return QString("&%1::%2")
            .arg(context->className)
            .arg(ast->ruleName);
}

QString CPPGenerator::genError(PegError *ast, GenContext *context, QString &statements, QString cutVar)
{
    statements = QString("throw Error(\"%1\", _b.saveState());").arg(ast->message);
    return "false";
}

QString CPPGenerator::genStr(PegStr *ast, GenContext *context, QString &statements, QString cutVar)
{
    return genFuncall(
            QString("_matchStr(_b, \"%1\", %2, error)")
                .arg(ast->toMatch)
                .arg(ast->varName),
            QString("_matchStr(_b, \"%1\", error)")
                .arg(ast->toMatch),
            ast->code,
            ast->varName,
            context,
            statements
            , cutVar);
}

QString CPPGenerator::genAnyChar(PegAnyChar *ast, GenContext *context, QString &statements, QString cutVar)
{
    return genFuncall(
            QString("_matchAnyChar(_b, %1, error)")
				.arg(ast->varName),
			QString("_matchAnyChar(_b, error)"),
            ast->code,
            ast->varName,
            context,
            statements,
            cutVar
            );
}

QString CPPGenerator::genAlpha(PegAlpha *ast, GenContext *context, QString &statements, QString cutVar)
{
    return genFuncall(
            QString("_matchAlpha(_b, %1, error)")
                .arg(ast->varName),
            QString("_matchAlpha(_b, error)"),
            ast->code,
            ast->varName,
            context,
            statements,
            cutVar
            );
}

QString CPPGenerator::genLetter(PegLetter *ast, GenContext *context, QString &statements, QString cutVar)
{
    return genFuncall(
            QString("_matchLetter(_b, %1, error)")
                .arg(ast->varName),
            QString("_matchLetter(_b, error)"),
            ast->code,
            ast->varName,
            context,
            statements,
            cutVar
            );
}

QString CPPGenerator::genDigit(PegDigit *ast, GenContext *context, QString &statements, QString cutVar)
{
    return genFuncall(
            QString("_matchDigit(_b, %1, error)")
                .arg(ast->varName),
            QString("_matchDigit(_b, error)"),
            ast->code,
            ast->varName,
            context,
            statements,
            cutVar
            );
}

QString CPPGenerator::genEof(PegEof *ast, GenContext *context, QString &statements, QString cutVar)
{
    return "_b.eof()";
}

QString CPPGenerator::fileHeader(GenContext *context)
{
    return QString("#include \"%1.h\"\n\n\n\
                   void %2::clearAllMemoization()\n\
                   {\n\
                       %3\n\
                   }\n\
                   \n\
                   ")
    .arg(context->headerFileName)
    .arg(context->className)
    .arg(generateClearMemoization(this->memoizationMaps));
}

QString CPPGenerator::headerFile(GenContext *context)
{
    QStringList theTypeDefs;
    for(QMap<QString, QString>::const_iterator i = context->typeDefs.begin(); i != context->typeDefs.end(); ++i)
    {
        theTypeDefs.append(i.value());
    }
    return QString("#include \"buffer.h\"\n\
               #ifndef __%1__\n\
               #define __%1__\n\
#include \"match.h\"\n\
                   %2\n\
class %3\n\
    {\n\
                   private:\n\
                   %4\n\
                   public:\n\
                   QStack<QString> stackTrace;\n\
                   QStack<QString> callStackArgs;\n\
                   void clearAllMemoization();\n\
                   %5\n\
                   %6\n\
};\n\
               #endif\n\
")
.arg(context->headerFileName.replace("-","_"))
.arg(theTypeDefs.join("\n"))
.arg(context->className)
.arg(generateMemoizationTables(this->memoizationMaps))
.arg(context->prototypes.join("\n"))
.arg(context->codeInClass);
}

QString normalizeType(QString type)
{
    return type.replace(" ","")
               .replace("<", "_of_")
               .replace(",","_and_")
               .replace(">","_done_")
               .replace("*", "_pointer_");
}

QString CPPGenerator::generateDeclarationOfApplyMethods()
{
    QStringList apps;
    for(QMap<QString, QVector<PegRule *> >::const_iterator i = rulesGroupedByReturnType.begin(); i != rulesGroupedByReturnType.end(); ++i)
    {
        const QString type = i.key();
        QString decl = QString("bool apply_%1(QString _ruleName, Buffer &_b, %2 &ret, Error &error);")
                .arg(normalizeType(type))
                .arg(type);
        apps.append(decl);
    }
    return apps.join("\n");
}


QString CPPGenerator::generateImplementationForAppyMethodForType(const QString type, const QVector<PegRule *> &rules, GenContext *context)
{
    QStringList allCalls;

    for(int i=0; i<rules.count(); i++)
    {
        QString call = QString("if(_ruleName == \"%1\")\n\
                               {\n\
                    return %1(_b, ret, error);\n\
                               }\n")
            .arg(rules[i]->name);
        allCalls.append(call);

    }
    QString decl = QString("{\n\
                            %1\n\
                           \n\
                           error = Error(QString(\"apply_%2 can't find rule: \")+_ruleName, _b.saveState());\n\
                           return false;\n\
                           }\n")
            .arg(allCalls.join("\n"))
            .arg(normalizeType(type));

    return decl;

}

QString CPPGenerator::generateImplementationOfApplyMethods(GenContext *context)
{
    QStringList apps;
    for(QMap<QString, QVector<PegRule *> >::const_iterator i = rulesGroupedByReturnType.begin(); i != rulesGroupedByReturnType.end(); ++i)
    {
        const QString type = i.key();
        const QVector<PegRule *> &rules = i.value();
        QString meth = QString("bool %1::apply_%2(QString _ruleName, Buffer &_b, %3 &ret, Error &error)\n\%4")
                               .arg(context->className)
                                .arg(normalizeType(type))
                                .arg(type)
                                .arg(generateImplementationForAppyMethodForType(type, rules, context));
        apps.append(meth);
    }
    return apps.join("\n");
}

QString CPPGenerator::generateLocalDeclarations(QMap<QString, QString> vars)
{
    QMap<QString, QString>::const_iterator i;
    QStringList ret;
    for(i= vars.begin(); i!=vars.end(); ++i)
    {
        if(i.key() == "ret")
            continue;
        ret.append(QString("%1 %2;").arg(i.value()).arg(i.key()));
    }

    return ret.join("\n");
}

QString CPPGenerator::generateMemoizationTables(QMap<QString, QString> vars)
{
    QMap<QString, QString>::const_iterator i;
    QStringList ret;
    for(i= vars.begin(); i!=vars.end(); ++i)
    {
        ret.append(QString("QMap<int, ParseResult<%1 > > %2;").arg(i.value()).arg(i.key()));
    }
    return ret.join("\n");
}

QString CPPGenerator::generateClearMemoization(QMap<QString, QString> vars)
{
    QMap<QString, QString>::const_iterator i;
    QStringList ret;
    for(i= vars.begin(); i!=vars.end(); ++i)
    {
        ret.append(QString("%1.clear();").arg(i.key()));
    }
    return ret.join("\n");
}

QString CPPGenerator::genFuncall(QString funCallWithRet,
                   QString funCallNoRet,
                   QString code,
                   QString varName,
                   GenContext *context, QString &statements, QString cutVar)
{
    QString codeToGen = "";
    QString successVar = context->makeVar("result");
    if(code !="")
    {
        codeToGen = QString("\tif(%1)\n\
                        {\n\
                            %2\n\
                        };\n")
            .arg(successVar)
            .arg(code);
    }
    if(varName !="")
    {
        context->vars[varName] = "Token";
        statements = QString("bool %1 =%2;\n\
                            %3")
                .arg(successVar)
                .arg(funCallWithRet)
                .arg(codeToGen);
        return successVar;
    }
    else
    {
        statements = QString("bool %1 = %2;\n\
                            %3")
                .arg(successVar)
                .arg(funCallNoRet)
                .arg(codeToGen);
        return successVar;
    }
}
