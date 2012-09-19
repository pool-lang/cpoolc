/**************************************************************************
**   QPeg, the PEG parser generator
**   Copyright 2010 Mohamed Samy Ali - samy2004@gmail.com
**   This project is released under the Apache License version 2.0
**   as described in the included license.txt file
**************************************************************************/

#include "generator.h"
#include <typeinfo>

QString Generator::gen(PegAst *ast, GenContext *context, QString &statements, QString cutVar)
{
    if(isa<PegRule*>(ast))
    {
        return genRule(to<PegRule *>(ast), context, statements, cutVar);
    }

    if(isa<PegNonterminal*>(ast))
    {
        return genNonterminal(to<PegNonterminal *>(ast), context, statements, cutVar);
    }

    if(isa<PegSeq *>(ast))
    {
        return genSeq(to<PegSeq *>(ast), context, statements, cutVar);
    }

    if(isa<PegChoice *>(ast))
    {
        return genChoice(to<PegChoice *>(ast), context, statements, cutVar);
    }

    if(isa<PegLoop*>(ast))
    {
        return genLoop(to<PegLoop *>(ast), context, statements, cutVar);
    }

    if(isa<PegNot*>(ast))
    {
        return genNot(to<PegNot *>(ast), context, statements, cutVar);
    }

    if(isa<PegAndPredicate*>(ast))
    {
        return genAndPredicate(to<PegAndPredicate *>(ast), context, statements, cutVar);
    }

    if(isa<PegSnippet*>(ast))
    {
        return genSnippet(to<PegSnippet*>(ast), context, statements, cutVar);
    }

    if(isa<PegCut *>(ast))
    {
        return genCut(to<PegCut *>(ast), context, statements, cutVar);
    }

    if(isa<PegSemanticPredicate *>(ast))
    {
        return genSemanticPredicate(to<PegSemanticPredicate *>(ast), context, statements, cutVar);
    }

    if(isa<PegApply *>(ast))
    {
        return genApply(to<PegApply *>(ast), context, statements, cutVar);
    }

    if(isa<PegError *>(ast))
    {
        return genError(to<PegError *>(ast), context, statements, cutVar);
    }

    if(isa<PegStr*>(ast))
    {
        return genStr(to<PegStr *>(ast), context, statements, cutVar);
    }

    if(isa<PegAnyChar*>(ast))
    {
        return genAnyChar(to<PegAnyChar*>(ast), context, statements, cutVar);
    }

    if(isa<PegAlpha*>(ast))
    {
        return genAlpha(to<PegAlpha*>(ast), context, statements, cutVar);
    }

    if(isa<PegLetter*>(ast))
    {
        return genLetter(to<PegLetter*>(ast), context, statements, cutVar);
    }

    if(isa<PegDigit*>(ast))
    {
        return genDigit(to<PegDigit*>(ast), context, statements, cutVar);
    }

    if(isa<PegEof*>(ast))
    {
        return genEof(to<PegEof*>(ast), context, statements, cutVar);
    }
    throw QString("Cannot generate from type: %1").arg(typeid(ast).name());

}
