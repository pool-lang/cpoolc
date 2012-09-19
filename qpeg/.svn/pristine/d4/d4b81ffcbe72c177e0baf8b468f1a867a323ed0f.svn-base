#include "kalimatgenerator.h"

#define ws(x) QString::fromStdWString(x)

QString KalimatGenerator::genRule(PegRule  *ast, GenContext *context, QString &retStmts, QString cutVar)
{
    retStmts = "";
    context->vars.clear();
    QString statements;
    QString expression;
    this->memoizationMaps[ws(L"تذكر.")+ ast->name] = ast->returnType->toString();
    context->prototypes.append(ws(L"%1(المدخل)").arg(ast->name));

    expression = this->gen(ast->expr, context, statements, cutVar);
    return ws(L" رد %1 أنا على %2(المدخل):\n\
                    المرجع=لاشيء\n\
                    مكاني = المدخل: م2()\n\
                    إذا (تذكر.%2 أنا): يحتوي(مكاني):\n\
                        ارجع ب: (تذكر.%2 أنا ):قيمة(مكاني):القيم.في(المدخل)\n\
                    تم\n\
                    %3\n\
                    %4\n\
                    %5\n\
                   أنجح = %6\n\
                        (تذكر.%2 أنا): ضع(مكاني, نتيجة.للتذكر(نتيجة(أنجح, المرجع), المدخل:حالته()))\n\
                   \tارجع ب: نتيجة(أنجح, المرجع) \n\
                   نهاية\n\
                   \n")
            .arg(context->className)
            .arg(ast->name)
            .arg(generateLocalDeclarations(context->vars))
            .arg(ast->code)
            .arg(statements)
            .arg(expression);

}

QString KalimatGenerator::genNonterminal(PegNonterminal *ast, GenContext *context, QString &statements, QString cutVar)
{
    if(ast->varName == "")
        ast->varName = ws(L"صوري%1").arg(context->dummyCount++);

    if(!context->symbols.contains(ast->id))
        throw QString("unknown rule: " + ast->id);
    QString retType = context->symbols[ast->id]->returnType->toString();
    context->vars[ast->varName] = retType;
    QString resultVar = context->makeVar(ws(L"النتيجة"));
    QString tempVar = context->makeVar(ws(L"مؤقت"));
    QString codeToGen = "";
    if(ast->code != "")
    {
        codeToGen = ws(L"إذا %1 :\n\
                               %2\n\
                           تم\n")
        .arg(resultVar)
        .arg(ast->code);
    }
    statements = ws(L"%5= أنا : %2(المدخل)\n\
                          %1= نجاح %5\n\
                          %3=مرجع %5\n\
                          %4\n\
                        ")
                    .arg(resultVar)
                    .arg(ast->id)
                    .arg(ast->varName)
                    .arg(codeToGen)
                    .arg(tempVar);
    return resultVar;
}

QString KalimatGenerator::genSeq(PegSeq *ast, GenContext *context, QString &statements, QString cutVar)
{
    if(ast->elements.count()==1 && ast->code =="" && ast->varName=="")
        return gen(ast->elements[0], context, statements, cutVar);

    QStringList ret;
    QString resultVar = context->makeVar(ws(L"النتيجة"));
    QString bufferStateVar = context->makeVar(ws(L"حالة"));
    QString exitLabel = context->makeVar(ws(L"خروج"));

    QString head = ws(L"\
        %2=صحيح\n\
        %1 = المدخل: حالته()\n\
        \n").arg(bufferStateVar).arg(resultVar);

        QString _template = ws(
                L"%1\n%2 = %2 وأيضا %3\n\
        إذا ليس %2:\n\
        \tالمدخل: استرجع.الحالة(%4)\n\
        \tاذهب إلى %5\n\
        تم\n");

        ret.append(head);
        for(int i=0; i<ast->elements.count(); i++)
        {
            QString stmts;
            QString expr = gen(ast->elements[i], context, stmts, cutVar);
            ret.append(QString(_template)
                       .arg(stmts)
                       .arg(resultVar)
                       .arg(expr)
                       .arg(bufferStateVar)
                       .arg(exitLabel));
        }
    ret.append(ws(L"علامة %1\n").arg(exitLabel));
        statements =  ret.join("");
        return resultVar;
}

QString KalimatGenerator::genChoice(PegChoice *ast, GenContext *context, QString &statements, QString cutVar)
{
    if(ast->elements.count()==1 && ast->code =="" && ast->varName=="")
        return gen(ast->elements[0], context, statements, cutVar);
    QString myCutVar = context->makeVar(ws(L"قطع"));
    QString resultVar = context->makeVar(ws(L"النتيجة"));
    QString bufferStateVar = context->makeVar(ws(L".حالة"));
    QString head = ws(L"\
                                   %1=خطأ\n\
                                   %2=خطأ\n\
                                   %3 = المدخل: حالته()\n")
                              .arg(resultVar)
                              .arg(myCutVar)
                              .arg(bufferStateVar);

    QString _template = ws(L"إذا ليس %2 ولا %5:\n\
                                    %1\n\
                                    %2 = %2 أو %3\n\
                                    إذا ليس %2:\n\
                                       المدخل: استرجع.الحالة(%4)\n\
                                    تم\n\
                                تم\n");
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

QString KalimatGenerator::genLoop(PegLoop *ast, GenContext *context, QString &statements, QString cutVar)
{
    QString resultVar = context->makeVar(ws(L"النتيجة"));
    QString myCutVar = context->makeVar(ws(L"قطع"));
    QString exitLabel = context->makeVar(ws(L"خروج"));
    QString stmts2, exp;
    exp = gen(ast->expr, context, stmts2, myCutVar);
    statements = ws(L"\
    %1 = صحيح\n\
    %2 = خطأ\n\
    طالما صحيح:\n\
     %2= خطأ\n\
     الحالة = المدخل: حالته()\n\
     %3\
     إذا ليس %4:\n\
             المدخل: استرجع.الحالة(الحالة)\n\
         إذا %2:\n\
             %1 = خطأ\n\
         تم\n\
         اذهب إلى %5\n\
     تم\n\
    تابع\n\
         علامة %5")
    .arg(resultVar)
    .arg(myCutVar)
    .arg(stmts2)
    .arg(exp)
    .arg(exitLabel);
    return resultVar;

}

QString KalimatGenerator::genNot(PegNot *ast, GenContext *context, QString &statements, QString cutVar)
{
    QString resultVar = context->makeVar(ws(L"النتيجة"));
    QString bufferStateVar = context->makeVar(ws(L"الحالة"));

    QString exp, stmts;
    exp = gen(ast->expr, context, stmts, cutVar);

    statements = ws(L"\
        %1 = المدخل: حالته()\n\
        %2\
        %3 = ليس %4\n\
        المدخل: استرجع.الحالة(%1)\n")
        .arg(bufferStateVar)
        .arg(stmts)
        .arg(resultVar)
        .arg(exp);
    return resultVar;

}

QString KalimatGenerator::genAndPredicate(PegAndPredicate *ast, GenContext *context, QString &statements, QString cutVar)
{
    QString resultVar = context->makeVar(ws(L"النتيجة"));
    QString bufferStateVar = context->makeVar(ws(L"الحالة"));

    QString exp, stmts;
    exp = gen(ast->expr, context, stmts, cutVar);

    statements = ws(L"\
        %1 = المدخل: حالته\n\
        %2\
        %3 = (%4)\n\
        المدخل: استرجع.الحالة(%1)\n")
        .arg(bufferStateVar)
        .arg(stmts)
        .arg(resultVar)
        .arg(exp);
    return resultVar;

}

QString KalimatGenerator::genSnippet(PegSnippet *ast, GenContext *context, QString &statements, QString cutVar)
{
    if(ast->varName == "")
        ast->varName = ws(L"صوري%1").arg(context->dummyCount++);

    context->vars[ast->varName] = "Token";
    QString resultVar = context->makeVar(ws(L"النتيجة"));
    QString codeToGen = "";
    if(ast->code != "")
    {
        codeToGen = QString("إذا %1:\n\
                               %2\n\
                            تم\n")
        .arg(resultVar)
        .arg(ast->code);
    }
    QString subStatements;
    QString subResult = gen(ast->expr, context, subStatements, cutVar);
    QString bufferStatePre = context->makeVar(ws(L"حالة.قبلية"));
    QString bufferStatePost = context->makeVar(ws(L"حالة.بعدية"));
    statements = ws(L"%1 = المدخل: حالته()\n\
                         %2 \n\
                         %3=%4\n\
                         إذا %3 :\n\
                            %5= المدخل: حالته()\n\
                            %6 = اقتطاع(المدخل, %1, %5)\n\
                         تم\n\
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

QString KalimatGenerator::genCut(PegCut *ast, GenContext *context, QString &statements, QString cutVar)
{
    statements = ws(L"%1=صحيح\n").arg(cutVar);
    return ws(L"صحيح");
}

QString KalimatGenerator::genSemanticPredicate(PegSemanticPredicate *ast, GenContext *context, QString &statements, QString curVar)
{
    return ast->condition;
}

QString KalimatGenerator::genApply(PegApply *ast, GenContext *context, QString &statements, QString curVar)
{
    return ws(L"ابلاي.إيه.يا.بيه");
}

QString KalimatGenerator::genSharpQuote(PegSharpQuote *ast, GenContext *context, QString &statements, QString curVar)
{
    return ws(L"الدالة %1؛%2").arg(ast->ruleName).arg(context->className);
}

QString KalimatGenerator::genError(PegError *ast, GenContext *context, QString &statements, QString curVar)
{
    //todo:
    return "_Error not implemented";
}

QString KalimatGenerator::genStr(PegStr *ast, GenContext *context, QString &statements, QString cutVar)
{
    return genFuncall(
            ws(L"طابق.نص(المدخل, \"%1\")")
                .arg(ast->toMatch),
            ast->code,
            ast->varName,
            context,
            statements,
            cutVar
            );
}

QString KalimatGenerator::genAnyChar(PegAnyChar *ast, GenContext *context, QString &statements, QString cutVar)
{
    return genFuncall(
            ws(L"طابق.أي.رمز(المدخل)"),
            ast->code,
            ast->varName,
            context,
            statements,
            cutVar
            );
}

QString KalimatGenerator::genAlpha(PegAlpha *ast, GenContext *context, QString &statements, QString cutVar)
{
    return genFuncall(
            ws(L"طابق.حرف.او.رقم(المدخل)"),
            ast->code,
            ast->varName,
            context,
            statements,
            cutVar
            );
}

QString KalimatGenerator::genLetter(PegLetter *ast, GenContext *context, QString &statements, QString cutVar)
{
    return genFuncall(
            ws(L"طابق.حرف(المدخل)"),
            ast->code,
            ast->varName,
            context,
            statements,
            cutVar
            );
}

QString KalimatGenerator::genDigit(PegDigit *ast, GenContext *context, QString &statements, QString cutVar)
{
    return genFuncall(
            ws(L"طابق.رقم(المدخل)"),
            ast->code,
            ast->varName,
            context,
            statements,
            cutVar
            );
}

QString KalimatGenerator::genEof(PegEof *ast, GenContext *context, QString &statements, QString cutVar)
{
    return ws(L"المدخل: منته()");
}

QString KalimatGenerator::fileHeader(GenContext *context)
{
   return ws(L"باستخدام \"الجداول\"\n\
             باستخدام \"الإعراب\"\n\
                       فصيلة %1:\n\
له %2\n\
يرد على %3\n\
                             يستجيب ل: فرغ.جداول.التذكر()\n\
                             نهاية\n\
                                   استجابة %1 أنا ل: فرغ.جداول.التذكر():\n\
                                    %4\n\
       نهاية\n\
             دالة %1.جديد():\n\
                         %5\n\
             نهاية\n\
            \n")
               .arg(context->className)
               .arg(generateMemoizationFields(this->memoizationMaps))
             .arg(generateParserFuncPrototypes(context))
                   .arg(generateClearMemoization(this->memoizationMaps))
                   .arg(generateConstructor(context, this->memoizationMaps));

}

QString KalimatGenerator::fileFooter()
{
    return "\n";
}

QString KalimatGenerator::generateLocalDeclarations(QMap<QString, QString> vars)
{
    return "\n";
}

QString KalimatGenerator::generateMemoizationFields(QMap<QString, QString> vars)
{
    QMap<QString, QString>::const_iterator i;
    QStringList ret;
    for(i= vars.begin(); i!=vars.end(); ++i)
    {
        QString varName = i.key();
        QString varType = i.value();
        ret.append(ws(L"%1").arg(varName));
    }
    return ret.join(", ");
}

QString KalimatGenerator::generateParserFuncPrototypes(GenContext *context)
{
    return context->prototypes.join(", ");
}

QString KalimatGenerator::generateClearMemoization(QMap<QString, QString> vars)
{
    QMap<QString, QString>::const_iterator i;
    QStringList ret;
    for(i= vars.begin(); i!=vars.end(); ++i)
    {
        ret.append(ws(L"%1 أنا = جدول()").arg(i.key()));
    }
    return ret.join("\n");
}

QString KalimatGenerator::generateConstructor(GenContext *context, QMap<QString, QString> vars)
{
    QMap<QString, QString>::const_iterator i;
    QStringList ret;
    for(i= vars.begin(); i!=vars.end(); ++i)
    {
        QString varName = i.key();
        QString varType = i.value();
        ret.append(ws(L"%1 د = جدول()").arg(varName));
    }
    return ws(L"د = %1 جديد\n").arg(context->className) + ret.join("\n") + ws(L"\nارجع ب: د\n") ;
}

QString KalimatGenerator::genFuncall(QString funCallWithRet,
                   QString code,
                   QString varName,
                   GenContext *context, QString &statements, QString cutVar)
{
    QString codeToGen = "";
    QString resultVar = context->makeVar(ws(L"النتيجة"));
    QString successVar = context->makeVar(ws(L"النجاح"));
    if(code !="")
    {
        codeToGen = ws(L"\tإذا %1:\n\
                            %2\n\
                        تم\n")
            .arg(successVar)
            .arg(code);
    }
    if(varName !="")
    {
        context->vars[varName] = "Token";
        statements = ws(L"%4 =%2\n\
                             %1 =نجاح %4\n\
                             %5 = مرجع %4\n\
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
        statements = ws(L"%4 = %2\n\
                              %1 = نجاح %4\n\
                            %3")
                .arg(successVar)
                .arg(funCallWithRet)
                .arg(codeToGen)
                .arg(resultVar);
        return successVar;
    }
}

