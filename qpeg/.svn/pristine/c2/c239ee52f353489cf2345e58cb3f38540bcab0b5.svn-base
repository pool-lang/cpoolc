/**************************************************************************
**   QPeg, the PEG parser generator
**   Copyright 2010 Mohamed Samy Ali - samy2004@gmail.com
**   This project is released under the Apache License version 2.0
**   as described in the included license.txt file
**************************************************************************/

#include "javagenerator.h"


QString JavaGenerator::genRule(PegRule  *ast, GenContext *context, QString &retStmts, QString cutVar)
{
    retStmts = "";
    context->vars.clear();
    QString statements;
    QString expression;
    this->memoizationMaps[QString("memoize_")+ ast->name] = ast->returnType->toString();

    expression = this->gen(ast->expr, context, statements, cutVar);
    return QString("public Result<%2> %1(Buffer _b)\n\
                   {\n\
                    %2 ret=null;\n\
                    int _thisPos = _b.getP2();\n\
                    if(memoize_%1.containsKey(_thisPos))\n\
                    {\n\
                        return memoize_%1.get(_thisPos).getValues(_b);\n\
                    }\n\
                    %3\n\
                    %4\n\
                    %5\n\
                   boolean _success = %6;\n\
                    memoize_%1.put(_thisPos, new ParseResult< %2 >(_success, ret, _b.saveState()));\n\
                   \treturn new Result<%2>(_success, ret); \n\
                   }\n\
                   \n")

            .arg(ast->name)
            .arg(ast->returnType->toString())
            .arg(generateLocalDeclarations(context->vars))
            .arg(ast->code)
            .arg(statements)
            .arg(expression);

}

QString JavaGenerator::genNonterminal(PegNonterminal *ast, GenContext *context, QString &statements, QString cutVar)
{
    if(ast->varName == "")
        ast->varName = QString("_dummy_%1").arg(context->dummyCount++);

    if(!context->symbols.contains(ast->id))
        throw QString("unknown rule: " + ast->id);
    QString retType = context->symbols[ast->id]->returnType->toString();
    context->vars[ast->varName] = retType;
    QString resultVar = context->makeVar("result");
    QString tempVar = context->makeVar("temp");
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
    statements = QString("Result<%5> %6=%2(_b);\n\
                          boolean %1=%6.success;\n\
                          %3=%6.ret;\n\
                          %4\n\
                        ")
                    .arg(resultVar)
                    .arg(ast->id)
                    .arg(ast->varName)
                    .arg(codeToGen)
                    .arg(retType)
                    .arg(tempVar);
    return resultVar;
}


QString JavaGenerator::genSeq(PegSeq *ast, GenContext *context, QString &statements, QString cutVar)
{
    if(ast->elements.count()==1 && ast->code =="" && ast->varName=="")
        return gen(ast->elements[0], context, statements, cutVar);
    QStringList ret;
    QString resultVar = context->makeVar("result");
    QString bufferStateVar = context->makeVar("_s");
    QString head = QString("\
        boolean %2=true;\n\
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

QString JavaGenerator::genChoice(PegChoice *ast, GenContext *context, QString &statements, QString cutVar)
{
    if(ast->elements.count()==1 && ast->code =="" && ast->varName=="")
        return gen(ast->elements[0], context, statements, cutVar);
    QString myCutVar = context->makeVar("_cut");
    QString resultVar = context->makeVar("result");
    QString bufferStateVar = context->makeVar("_s");
    QString head = QString("\
                                   boolean %1=false;\n\
                                   boolean %2=false;\n\
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

QString JavaGenerator::genLoop(PegLoop *ast, GenContext *context, QString &statements, QString cutVar)
{
    QString resultVar = context->makeVar("result");
    QString myCutVar = context->makeVar("_cut");
    QString stmts2, exp;
    exp = gen(ast->expr, context, stmts2, myCutVar);
    statements = QString("\
    boolean %1 = true;\n\
    boolean %2 = false;\n\
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

QString JavaGenerator::genNot(PegNot *ast, GenContext *context, QString &statements, QString cutVar)
{
    QString resultVar = context->makeVar("result");
    QString bufferStateVar = context->makeVar("_s");

    QString exp, stmts;
    exp = gen(ast->expr, context, stmts, cutVar);

    statements = QString("\
        BufferState %1 = _b.saveState();\n\
        %2\
        boolean %3 = !(%4);\n\
        _b.restoreState(%1);\n")
        .arg(bufferStateVar)
        .arg(stmts)
        .arg(resultVar)
        .arg(exp);
    return resultVar;

}

QString JavaGenerator::genAndPredicate(PegAndPredicate *ast, GenContext *context, QString &statements, QString cutVar)
{
    QString resultVar = context->makeVar("result");
    QString bufferStateVar = context->makeVar("_s");

    QString exp, stmts;
    exp = gen(ast->expr, context, stmts, cutVar);

    statements = QString("\
        BufferState %1 = _b.saveState();\n\
        %2\
        boolean %3 = (%4);\n\
        _b.restoreState(%1);\n")
        .arg(bufferStateVar)
        .arg(stmts)
        .arg(resultVar)
        .arg(exp);
    return resultVar;

}

QString JavaGenerator::genSnippet(PegSnippet *ast, GenContext *context, QString &statements, QString cutVar)
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
                         %2 boolean %3=%4;\n\
                         if(%3)\n\
                         {\n\
                            BufferState %5= _b.saveState();\n\
                            %6 = b.getRange(_b, %1, %5);\n\
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

QString JavaGenerator::genCut(PegCut *ast, GenContext *context, QString &statements, QString cutVar)
{
    statements = QString("%1=true;\n").arg(cutVar);
    return "true";
}

QString JavaGenerator::genSemanticPredicate(PegSemanticPredicate *ast, GenContext *context, QString &statements, QString curVar)
{
    return ast->condition;
}

QString JavaGenerator::genApply(PegApply *ast, GenContext *context, QString &statements, QString curVar)
{
    return "apply_eih_ya_beh";
}

QString JavaGenerator::genSharpQuote(PegSharpQuote *ast, GenContext *context, QString &statements, QString curVar)
{
    return "what do you think this is???!!! Lisp??";
}

QString JavaGenerator::genError(PegError *ast, GenContext *context, QString &statements, QString curVar)
{
    //todo:
    return "_Error not implemented";
}

QString JavaGenerator::genStr(PegStr *ast, GenContext *context, QString &statements, QString cutVar)
{
    return genFuncall(
            QString("Buffer._matchStr(_b, \"%1\")")
                .arg(ast->toMatch),
            ast->code,
            ast->varName,
            context,
            statements,
            cutVar
            );
}

QString JavaGenerator::genAnyChar(PegAnyChar *ast, GenContext *context, QString &statements, QString cutVar)
{
    return genFuncall(
            QString("Buffer._matchAnyChar(_b)"),
            ast->code,
            ast->varName,
            context,
            statements,
            cutVar
            );
}

QString JavaGenerator::genAlpha(PegAlpha *ast, GenContext *context, QString &statements, QString cutVar)
{
    return genFuncall(
            QString("Buffer._matchAlpha(_b)"),
            ast->code,
            ast->varName,
            context,
            statements,
            cutVar
            );
}

QString JavaGenerator::genLetter(PegLetter *ast, GenContext *context, QString &statements, QString cutVar)
{
    return genFuncall(
            QString("Buffer._matchLetter(_b)"),
            ast->code,
            ast->varName,
            context,
            statements,
            cutVar
            );
}

QString JavaGenerator::genDigit(PegDigit *ast, GenContext *context, QString &statements, QString cutVar)
{
    return genFuncall(
            QString("Buffer._matchDigit(_b)"),
            ast->code,
            ast->varName,
            context,
            statements,
            cutVar
            );
}

QString JavaGenerator::genEof(PegEof *ast, GenContext *context, QString &statements, QString cutVar)
{
    return "_b.eof()";
}

QString JavaGenerator::fileHeader(GenContext *context)
{
   return QString("import java.util.HashMap;\nimport QPeg.*;\nimport QPeg.PegAst.*;\nclass MyParser\n\
           {\n\
            %1\n")
            .arg(generateMemoizationTables(this->memoizationMaps));

}

QString JavaGenerator::fileFooter()
{
    return QString("\n void clearAllMemoizations()\n{\n%1\n}\n}\n")
            .arg(generateClearMemoization(this->memoizationMaps));
}

QString JavaGenerator::generateClearMemoization(QMap<QString, QString> vars)
{
    QMap<QString, QString>::const_iterator i;
    QStringList ret;
    for(i= vars.begin(); i!=vars.end(); ++i)
    {
        ret.append(QString("%1.clear();").arg(i.key()));
    }
    return ret.join("\n");
}

QString JavaGenerator::generateLocalDeclarations(QMap<QString, QString> vars)
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

QString JavaGenerator::generateMemoizationTables(QMap<QString, QString> vars)
{
    QMap<QString, QString>::const_iterator i;
    QStringList ret;
    for(i= vars.begin(); i!=vars.end(); ++i)
    {
        ret.append(QString("HashMap<Integer, ParseResult< %1 >> %2 = new HashMap<Integer,ParseResult< %1 >>();").arg(i.value()).arg(i.key()));
    }
    return ret.join("\n");
}

QString JavaGenerator::genFuncall(QString funCallWithRet,
                   QString code,
                   QString varName,
                   GenContext *context, QString &statements, QString cutVar)
{
    QString codeToGen = "";
    QString resultVar = context->makeVar("result");
    QString successVar = context->makeVar("_success");
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
        statements = QString("Result<Token> %4 =%2;\n\
                             boolean %1 = %4.success;\n\
                             %5 = %4.ret;\n\
                            %3")
                .arg(successVar)
                .arg(funCallWithRet)
                .arg(codeToGen)
                .arg(resultVar)
                .arg(varName);
        return successVar;
    }
    else
    {
        statements = QString("Result<Token> %4 = %2;\n\
                              boolean %1 = %4.success;\n\
                            %3")
                .arg(successVar)
                .arg(funCallWithRet)
                .arg(codeToGen)
                .arg(resultVar);
        return successVar;
    }
}

