/**************************************************************************
**   QPeg, the PEG parser generator
**   Copyright 2010 Mohamed Samy Ali - samy2004@gmail.com
**   This project is released under the Apache License version 2.0
**   as described in the included license.txt file
**************************************************************************/

#ifndef PEGAST_H
#define PEGAST_H
#include "buffer.h"
#include "token.h"
#include "predicate.h"
#include <QStringList>
#include <QMap>
struct PegExpr;
struct PegRule;
struct GenContext
{
    QStringList prototypes;
    QMap<QString, PegRule *> symbols;
    QMap<QString, QString> vars;
    QMap<QString, int> varCount;
    QString className;
    QString headerFileName;
    QString codeInClass;

    QMap<QString, QString> typeDefs; // maps from type name to typedef statement that defines it

    int dummyCount;
    QString makeVar(QString prefix)
    {
        if(!varCount.contains(prefix))
            varCount[prefix] = 0;
        return QString("%1%2").arg(prefix).arg(varCount[prefix]++);
    }
    GenContext() { dummyCount = 0;}
};

struct PegAst
{
    virtual QString toString() = 0;
};

struct PegType
{
    virtual QString toString() = 0;
};

struct PegTypeId : public PegType
{
    QString id;
    PegTypeId(QString id) { this->id = id; }
    QString toString() { return id;}
};

struct PegParametrizedType : public PegType
{
    PegType *baseType;
    QVector<PegType *> params;
    PegParametrizedType(PegType *baseType, QVector<PegType *> params)
    {
        this->baseType = baseType;
        this->params = params;
    }

    QString toString()
    {
        QStringList pars;
        for(QVector<PegType *>::iterator i= params.begin(); i!= params.end(); ++i)
        {
            pars.append((*i)->toString());
        }
        return QString("%1 < %2 >").arg(baseType->toString()).arg(pars.join(", "));
    }
};

struct PegPointerType : public PegType
{
    PegType *baseType;
    PegPointerType(PegType *baseType)
    {
        this->baseType= baseType;
    }

    QString toString()
    {
        return QString("%1 *").arg(baseType->toString());
    }
};

struct PegFunType : public PegType
{
    QVector<PegType *> paramTypes;
    PegType *returnType;
    PegFunType(QVector<PegType *> paramTypes, PegType *returnType) { this->paramTypes = paramTypes; this->returnType = returnType;}
    QString toString()
    {
        return "a PegFunType";
    }
};

struct PegExpr : public PegAst
{
    virtual QString type() = 0;
    virtual QString toExprString() = 0;
    QString toString()
    {
        return QString("%1%2%3")
                .arg(toExprString())
                .arg(varName==""?"":QString(":")+varName)
                .arg(code==""?"":QString(" {%1} ").arg(code));
    }

    QString code;
    QString varName;
};

struct PegParam
{
    QString name;
    PegType *type;
    PegParam(QString name,PegType *type)
    {
        this->name = name;
        this->type = type;
    }
};

struct PegRule : public PegAst
{
    QString name;
    QString code;
    PegType *returnType;
    PegExpr *expr;
    QVector<PegParam*> paramList;
    QStringList templateParams;
    PegRule(QString name, PegExpr *expr, QVector<PegParam *> paramList, QStringList templateParams) { this->name = name; this->expr = expr; this->returnType = NULL; this->paramList = paramList ; this->templateParams = templateParams;}
    PegRule(QString name, PegExpr *expr, PegType *returnType, QVector<PegParam*> paramList, QStringList templateParams) { this->name = name; this->expr = expr; this->returnType = returnType; this->paramList = paramList; this->templateParams = templateParams;}
    QString toString() { return QString("%1%3 -> %2")
                         .arg(name)
                         .arg(expr->toString())
                         .arg((returnType==NULL)?"":QString(":")+returnType->toString()); }

};

struct PegGrammar : public PegAst
{
    QMap<QString,QString> options;
    QString codeInClass;
    QString prelude, postlude;
    QVector<PegRule *> rules;
    QString toString()
    {
        QStringList lst;
        if(prelude != "")
        {
            lst.append("{\n");
            lst.append(prelude);
            lst.append("}\n");
        }
        for(int i=0; i<rules.count(); i++)
            lst.append(rules[i]->toString()+"\n");
        if(postlude!= "")
        {
            lst.append("{\n");
            lst.append(postlude);
            lst.append("}\n");
        }
        return lst.join("\n");
    }
};

struct PegError : public PegExpr
{
    QString message;
    PegError(QString message) { this->message = message; }
    QString toExprString() { return QString("_Error(\"%1\")").arg(message);}
    QString type() { return "QString";}
};

struct PegValue;
struct PegNonterminal : public PegExpr
{
    QString id;
    QVector<PegValue *> args;
    QVector<PegType *> templateArgs;
    PegNonterminal(QString id) { this->id = id; }
    PegNonterminal(QString id, QVector<PegValue *> args, QVector<PegType *> templateArgs) { this->id = id; this->args = args; this->templateArgs = templateArgs;}
    QString toExprString() { return id; }
    QString type() { return "int"; }
};


struct PegSeq : public PegExpr
{
    QVector<PegExpr *> elements;
    PegSeq(PegExpr *left, PegExpr *right) { elements.append(left); elements.append(right); }
    PegSeq() { }
    QString type() { return "int"; }
    QString toExprString()
    {
        QStringList ret;
        for(int i=0; i<elements.count();i++)
            ret.append(elements[i]->toString());
        return ret.join(" ");
    }
};

struct PegChoice : public PegExpr
{
    QVector<PegExpr *> elements;
    PegChoice(PegExpr *left, PegExpr *right) { elements.append(left); elements.append(right); }
    PegChoice(){}
    QString type() { return "int"; }
    QString toExprString()
    {
        QStringList ret;
        for(int i=0; i<elements.count();i++)
            ret.append(elements[i]->toString());
        return ret.join("\n / ");
    }
};

struct PegLoop : public PegExpr
{
    PegExpr *expr;
    PegLoop(PegExpr *expr) { this->expr = expr;}
    QString type() { return "int"; }
    QString toExprString() { return QString("( %1 )*").arg(expr->toString()); }
};

struct PegNot : public PegExpr
{
    PegExpr *expr;
    PegNot(PegExpr *expr) { this->expr = expr;}
    QString type() { return "int"; }
    QString toExprString() { return QString("!( %1 )").arg(expr->toString()); }
};

struct PegAndPredicate : public PegExpr
{
    PegExpr *expr;
    PegAndPredicate(PegExpr *expr) { this->expr = expr;}
    QString type() { return "int"; }
    QString toExprString() { return QString("&( %1 )").arg(expr->toString()); }
};

struct PegSnippet : public PegExpr
{
    PegExpr *expr;
    PegSnippet(PegExpr *expr) { this->expr = expr; }
    QString type() { return "Token"; }
    QString toExprString() { return QString("_Snippet(%1)").arg(expr->toString()); }
};

struct PegCut : public PegExpr
{
    QString type() { return "bool"; }
    QString toExprString() { return "^"; }
};

struct PegSemanticPredicate : public PegExpr
{
    PegSemanticPredicate(QString cond) { this->condition = cond; }
    QString condition;
    QString type() { return "bool"; }
    QString toExprString() { return QString("&{%1}").arg(condition); }
};

struct PegApply : public PegExpr
{
    PegType *retType;
    PegValue *func;
    QVector<PegValue *> args;

    PegApply(PegType *retType, PegValue *func, QVector<PegValue *> args)
    {
        this->retType = retType;
        this->func = func;
        this->args = args;
    }
    QString toExprString();
    QString type() { return retType->toString(); }

};

struct PegStr : public PegExpr
{
    QString toMatch;
    PegStr(QString toMatch) { this->toMatch = toMatch; }
    QString type() { return "Token"; }
    QString toExprString() { return QString("\"%1\"").arg(toMatch);}
};

struct PegAnyChar : public PegExpr
{
    QString type() { return "bool"; }
    QString toExprString() { return "."; }
};

struct PegAlpha: public PegExpr
{
    QString type() { return "bool"; }
    QString toExprString() { return "_Alpha"; }
};

struct PegLetter: public PegExpr
{
    QString type() { return "bool"; }
    QString toExprString() { return "_Letter"; }
};

struct PegDigit: public PegExpr
{
    QString type() { return "bool"; }
    QString toExprString() { return "_Digit"; }
};

struct PegEof : public PegExpr
{
    QString type() { return "bool"; }
    QString toExprString() { return "Eof"; }
};


struct PegValue
{
    virtual QString toString()=0;
};

struct PegStringArg : public PegValue
{
    QString str;
    PegStringArg(QString str) { this->str = str;}
    QString toString() { return str; }
};

struct PegIdArg : public PegValue
{
    QString id;
    PegIdArg(QString id) { this->id = id;}
    QString toString() { return id;}
};

struct PegSharpQuote : public PegValue
{
    QString ruleName;
    PegSharpQuote(QString ruleName) { this->ruleName = ruleName; }
    QString toString() { return QString("#'%1").arg(ruleName);}
};

struct Step
{
    QString info;
    QString err;
    Step *parent;
    Step(QString info, Step *parent = NULL) { this->info = info; this->parent = parent;}
    QString toString() { return QString ("[%1]%2").arg(info, parent?parent->toString():"");}
};


typedef PegRule * PRule;
typedef QVector<PegRule *> RuleVector ;
typedef QVector<PegExpr *> ExprVector ;
typedef PegExpr * PPegExpr;
typedef PegChoice* PPegChoice;
typedef PegSeq* PPegSeq;
typedef PegGrammar* PPegGrammar;


#endif // PEGAST_H
