/**************************************************************************
**   QPeg, the PEG parser generator
**   Copyright 2010 Mohamed Samy Ali - samy2004@gmail.com
**   This project is released under the Apache License version 2.0
**   as described in the included license.txt file
**************************************************************************/

#ifndef PARSEPEG_H
#define PARSEPEG_H
#include <QStringList>
#include "pegast.h"

/*
  This is an ad-hoc parser that was used to bootstrap qpeg by parsing the peg grammar itself.
  It is now way out of date.
*/
struct PP
{
    QStringList tokens;
    int curToken;
    PP(QStringList tokens) { this->tokens = tokens; this->curToken = 0;}
    void match(QString toMatch)
    {
        if(eof())
            throw QString("eof");
        if(tokens[curToken] != toMatch)
            throw QString("expected:") + toMatch + (curToken>0?" after" + tokens[curToken-1]:"");
        curToken++;
    }
    bool LA(QString toLa)
    {
        if(eof())
            return false;
        return tokens[curToken] == toLa;
    }
    QString lookAhead() { return tokens[curToken];}
    bool eof() { return curToken >= tokens.count();}
    QVector<PegRule *> grammar()
    {
        QVector<PegRule *> ret;
        while(!eof())
        {
            PegRule *r = rule();
            match(";");
            match("\n");
            ret.append(r);
        }
        return ret;
    }
    PegRule *rule()
    {
        QString name = identifier();
        QString type = "int";
        if(LA(":"))
        {
            match(":");
            type = identifier();
        }
        match("->");
        PegExpr *expr = expression();
        return new PegRule(name, expr, new PegTypeId(type), QVector<PegParam *>(), QStringList());
    }
    PegExpr *expression()
    {
        return or_expr();
    }
    PegExpr *or_expr()
    {
        PegExpr *ret = seq_expr();
        while(lookAhead() == "/")
        {
            match("/");
            ret = new PegChoice(ret, seq_expr());
        }
        return ret;
    }
    PegExpr *seq_expr()
    {
        PegExpr *ret = primary_expr();
        while(lookAhead() == " ")
        {
            match(" ");
            ret = new PegSeq(ret, primary_expr());
        }
        return ret;
    }
    PegExpr *primary_expr()
    {
        PegExpr *ret = NULL;
        if(la_identifier())
        {
            ret = new PegNonterminal(identifier());
        }
        else if(LA("("))
        {
            match("(");
            ret = expression();
            match(")");
            if(LA("*"))
            {
                match("*");
                ret = new PegLoop(ret);
            }
        }
        else if(eof())
        {
            throw QString("unexpected end of file");
        }
        else if(lookAhead().startsWith("\"") && lookAhead().endsWith("\""))
        {
            ret = new PegStr(lookAhead().mid(1, lookAhead().length()-2));
            match(lookAhead());
        }
        if(LA(":"))
        {
            match(":");
            ret->varName = identifier();
        }
        if(!eof() && lookAhead().startsWith("{"))
        {
            ret->code = lookAhead().mid(1, lookAhead().length() -2);
            match(lookAhead());
        }
        return ret;
    }
    QString identifier()
    {
        if(!la_identifier())
            throw QString("expected identifier");
        QString id = lookAhead();
        match(lookAhead());
        return id;
    }
    bool la_identifier()
    {
        if(eof())
            return false;
        QString la = lookAhead();
        if(!la[0].isLetter())
            return false;
        for(int i=1; i<la.length(); i++)
            if(!la[i].isLetterOrNumber())
                return false;
        return true;
    }
};

#endif // PARSEPEG_H
