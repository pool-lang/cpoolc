#ifndef KALIMATGENERATOR_H
#define KALIMATGENERATOR_H
#include "generator.h"

class KalimatGenerator : public Generator
{
    QMap<QString, QString> memoizationMaps;
public:
    QString genRule(PegRule *ast, GenContext *context, QString &statements, QString cutVar);
    QString genNonterminal(PegNonterminal *ast, GenContext *context, QString &statements, QString cutVar);
    QString genSeq(PegSeq *ast, GenContext *context, QString &statements, QString cutVar);
    QString genChoice(PegChoice *ast, GenContext *context, QString &statements, QString cutVar);
    QString genLoop(PegLoop *ast, GenContext *context, QString &statements, QString cutVar);
    QString genNot(PegNot *ast, GenContext *context, QString &statements, QString cutVar);
    QString genAndPredicate(PegAndPredicate *ast, GenContext *context, QString &statements, QString cutVar);
    QString genSnippet(PegSnippet *ast, GenContext *context, QString &statements, QString cutVar);
    QString genCut(PegCut *ast, GenContext *context, QString &statements, QString cutVar);
    QString genSemanticPredicate(PegSemanticPredicate *ast, GenContext *context, QString &statements, QString curVar);
    QString genApply(PegApply *ast, GenContext *context, QString &statements, QString curVar);
    QString genSharpQuote(PegSharpQuote *ast, GenContext *context, QString &statements, QString curVar);
    QString genError(PegError *ast, GenContext *context, QString &statements, QString curVar);
    QString genStr(PegStr *ast, GenContext *context, QString &statements, QString cutVar);
    QString genAnyChar(PegAnyChar *ast, GenContext *context, QString &statements, QString cutVar);
    QString genAlpha(PegAlpha *ast, GenContext *context, QString &statements, QString cutVar);
    QString genLetter(PegLetter *ast, GenContext *context, QString &statements, QString cutVar);
    QString genDigit(PegDigit *ast, GenContext *context, QString &statements, QString cutVar);
    QString genEof(PegEof *ast, GenContext *context, QString &statements, QString cutVar);

    QString fileHeader(GenContext *context);
    QString fileFooter();
private:
    QString generateLocalDeclarations(QMap<QString, QString> vars);

    QString generateMemoizationFields(QMap<QString, QString> vars);

    QString generateParserFuncPrototypes(GenContext *context);
    QString generateClearMemoization(QMap<QString, QString> vars);
    QString generateConstructor(GenContext *context, QMap<QString, QString> vars);


    QString genFuncall(QString funCallWithRet,
                       QString code,
                       QString varName,
                       GenContext *context, QString &statements, QString cutVar);
};
#endif // KALIMATGENERATOR_H
