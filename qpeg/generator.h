/**************************************************************************
**   QPeg, the PEG parser generator
**   Copyright 2010 Mohamed Samy Ali - samy2004@gmail.com
**   This project is released under the Apache License version 2.0
**   as described in the included license.txt file
**************************************************************************/

#ifndef GENERATOR_H
#define GENERATOR_H
#include "pegast.h"

template <class T, class T1>
bool isa(T1 a)
{
    T b = dynamic_cast<T>(a);
    return b!=NULL;
}

template <class T, class T1>
T to(T1 a)
{
    T b = dynamic_cast<T>(a);
    return b;
}

class Generator
{
public:
    QString gen(PegAst *ast, GenContext *context, QString &statements, QString cutVar);
    virtual QString genRule(PegRule *ast, GenContext *context, QString &statements, QString cutVar)=0;
    virtual QString genNonterminal(PegNonterminal *ast, GenContext *context, QString &statements, QString cutVar)=0;
    virtual QString genSeq(PegSeq *ast, GenContext *context, QString &statements, QString cutVar)=0;
    virtual QString genChoice(PegChoice *ast, GenContext *context, QString &statements, QString cutVar)=0;
    virtual QString genLoop(PegLoop *ast, GenContext *context, QString &statements, QString cutVar)=0;
    virtual QString genNot(PegNot *ast, GenContext *context, QString &statements, QString cutVar)=0;
    virtual QString genAndPredicate(PegAndPredicate *ast, GenContext *context, QString &statements, QString cutVar)=0;
    virtual QString genSnippet(PegSnippet *ast, GenContext *context, QString &statements, QString cutVar)=0;
    virtual QString genCut(PegCut *ast, GenContext *context, QString &statements, QString cutVar)=0;
    virtual QString genSemanticPredicate(PegSemanticPredicate *ast, GenContext *context, QString &statements, QString curVar)=0;
    virtual QString genApply(PegApply *ast, GenContext *context, QString &statements, QString curVar)=0;
    virtual QString genSharpQuote(PegSharpQuote *ast, GenContext *context, QString &statements, QString curVar)=0;
    virtual QString genError(PegError *ast, GenContext *context, QString &statements, QString curVar)=0;
    virtual QString genStr(PegStr *ast, GenContext *context, QString &statements, QString cutVar)=0;
    virtual QString genAnyChar(PegAnyChar *ast, GenContext *context, QString &statements, QString cutVar)=0;
    virtual QString genAlpha(PegAlpha *ast, GenContext *context, QString &statements, QString cutVar)=0;
    virtual QString genLetter(PegLetter *ast, GenContext *context, QString &statements, QString cutVar)=0;
    virtual QString genDigit(PegDigit *ast, GenContext *context, QString &statements, QString cutVar)=0;
    virtual QString genEof(PegEof *ast, GenContext *context, QString &statements, QString cutVar)=0;

    virtual QString fileHeader(GenContext *context)=0;
    virtual QString headerFile(GenContext *context) { return "";}
    virtual QString fileFooter() { return "";}
};

#endif // GENERATOR_H
