/**************************************************************************
**   QPeg, the PEG parser generator
**   Copyright 2010 Mohamed Samy Ali - samy2004@gmail.com
**   This project is released under the Apache License version 2.0
**   as described in the included license.txt file
**************************************************************************/

#ifndef CPPGENERATOR_H
#define CPPGENERATOR_H

#include "generator.h"

QString normalizeType(QString type);
class CPPGenerator : public Generator
{
    QMap<QString, QString> memoizationMaps;
    // todo: Using a string to index types is buggy
    // since the same type can be represented by multiple strings
    // this is a high-priority issue
    QMap<QString, QVector<PegRule *> > rulesGroupedByReturnType;
public:
    QString genType(PegType *ast, GenContext *context);
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
    QString headerFile(GenContext *context);
    QString generateDeclarationOfApplyMethods();
    QString generateImplementationOfApplyMethods(GenContext *context);
    QString generateImplementationForAppyMethodForType(const QString type, const QVector<PegRule *> &rules, GenContext *context);
private:

    PegType *instantiateType(PegType *type, QStringList templateParams, QVector<PegType *> templateArgs);
    QString marryFunTypeAndArg(PegFunType *type, QString name, GenContext *context);
    QString generateExtraArgsToCall(QVector<PegValue *> args, GenContext *context);
    QString generateArg(PegValue *arg, GenContext *context);
    QString generateLocalDeclarations(QMap<QString, QString> vars);
    QString genFuncall(QString funCallWithRet,
                       QString funCallNoRet,
                       QString code,
                       QString varName,
                       GenContext *context, QString &statements, QString cutVar);


    QString generateMemoizationTables(QMap<QString, QString> vars);
    QString generateClearMemoization(QMap<QString, QString> vars);
};

#endif // CPPGENERATOR_H
