#include "buffer.h"
#ifndef __peg_new__
#define __peg_new__
#include "match.h"
class PegParser
{
private:
    QMap<int, ParseResult<QString > > memoize_AND;
    QMap<int, ParseResult<QString > > memoize_ARROW;
    QMap<int, ParseResult<QString > > memoize_ASTERISK;
    QMap<int, ParseResult<QString > > memoize_COLON;
    QMap<int, ParseResult<QString > > memoize_COMMA;
    QMap<int, ParseResult<QString > > memoize_CUT;
    QMap<int, ParseResult<QString > > memoize_DOT;
    QMap<int, ParseResult<QString > > memoize_EQ;
    QMap<int, ParseResult<QString > > memoize_GT;
    QMap<int, ParseResult<QString > > memoize_INCLASS;
    QMap<int, ParseResult<QString > > memoize_LAMBDA;
    QMap<int, ParseResult<QString > > memoize_LBRACE;
    QMap<int, ParseResult<QString > > memoize_LBRACKET;
    QMap<int, ParseResult<QString > > memoize_LPAREN;
    QMap<int, ParseResult<QString > > memoize_LT;
    QMap<int, ParseResult<QString > > memoize_NL;
    QMap<int, ParseResult<QString > > memoize_NOT;
    QMap<int, ParseResult<QString > > memoize_QUESTION;
    QMap<int, ParseResult<QString > > memoize_RBRACE;
    QMap<int, ParseResult<QString > > memoize_RBRACKET;
    QMap<int, ParseResult<QString > > memoize_RPAREN;
    QMap<int, ParseResult<QString > > memoize_SEMI;
    QMap<int, ParseResult<QString > > memoize_SHARPQUOTE;
    QMap<int, ParseResult<QString > > memoize_SLASH;
    QMap<int, ParseResult<QString > > memoize_SNIPPET;
    QMap<int, ParseResult<QString > > memoize_SPACE;
    QMap<int, ParseResult<PPegExpr > > memoize_application;
    QMap<int, ParseResult<QVector < PegValue * > > > memoize_arglist;
    QMap<int, ParseResult<QString > > memoize_charlit;
    QMap<int, ParseResult<QString > > memoize_code;
    QMap<int, ParseResult<PPegChoice > > memoize_expr;
    QMap<int, ParseResult<QString > > memoize_identifier;
    QMap<int, ParseResult<PegNonterminal * > > memoize_invokation;
    QMap<int, ParseResult<QString > > memoize_kalimatdentifier;
    QMap<int, ParseResult<QString > > memoize_nonquote;
    QMap<int, ParseResult<QString > > memoize_nonrbrace;
    QMap<int, ParseResult<QString > > memoize_normalidentifier;
    QMap<int, ParseResult<QMap < QString, QString > > > memoize_options;
    QMap<int, ParseResult<PegParam * > > memoize_param;
    QMap<int, ParseResult<QVector < PegParam * > > > memoize_paramlist;
    QMap<int, ParseResult<PegGrammar * > > memoize_peg;
    QMap<int, ParseResult<PegValue * > > memoize_pegArg;
    QMap<int, ParseResult<PPegExpr > > memoize_prefix;
    QMap<int, ParseResult<PPegExpr > > memoize_prim;
    QMap<int, ParseResult<PPegExpr > > memoize_primprefix;
    QMap<int, ParseResult<QString > > memoize_quote;
    QMap<int, ParseResult<PRule > > memoize_rule;
    QMap<int, ParseResult<PPegSeq > > memoize_seq;
    QMap<int, ParseResult<QString > > memoize_spacing;
    QMap<int, ParseResult<PPegExpr > > memoize_special;
    QMap<int, ParseResult<PPegExpr > > memoize_specialtoken;
    QMap<int, ParseResult<QString > > memoize_strlit;
    QMap<int, ParseResult<PPegExpr > > memoize_suffix;
    QMap<int, ParseResult<QVector < PegType * > > > memoize_templateargs;
    QMap<int, ParseResult<QStringList > > memoize_templateparams;
    QMap<int, ParseResult<PegType * > > memoize_type;
    QMap<int, ParseResult<QVector < QString > > > memoize_zilo;
public:
    QStack<QString> stackTrace;
    QStack<QString> callStackArgs;
    void clearAllMemoization();
    bool peg(Buffer &_b, PegGrammar * &ret, Error &error);
    bool options(Buffer &_b, QMap < QString, QString > &ret, Error &error);



bool rule(Buffer &_b, PRule &ret, Error &error);
bool paramlist(Buffer &_b, QVector < PegParam * > &ret, Error &error);
bool param(Buffer &_b, PegParam * &ret, Error &error);
bool templateparams(Buffer &_b, QStringList &ret, Error &error);
bool templateargs(Buffer &_b, QVector < PegType * > &ret, Error &error);
bool type(Buffer &_b, PegType * &ret, Error &error);
bool expr(Buffer &_b, PPegChoice &ret, Error &error);
bool seq(Buffer &_b, PPegSeq &ret, Error &error);
bool suffix(Buffer &_b, PPegExpr &ret, Error &error);
bool prefix(Buffer &_b, PPegExpr &ret, Error &error);
bool prim(Buffer &_b, PPegExpr &ret, Error &error);
bool primprefix(Buffer &_b, PPegExpr &ret, Error &error);
bool invokation(Buffer &_b, PegNonterminal * &ret, Error &error);
bool arglist(Buffer &_b, QVector < PegValue * > &ret, Error &error);
bool pegArg(Buffer &_b, PegValue * &ret, Error &error);
bool application(Buffer &_b, PPegExpr &ret, Error &error);
bool special(Buffer &_b, PPegExpr &ret, Error &error);
bool specialtoken(Buffer &_b, PPegExpr &ret, Error &error);
bool strlit(Buffer &_b, QString &ret, Error &error);
bool charlit(Buffer &_b, QString &ret, Error &error);
bool code(Buffer &_b, QString &ret, Error &error);
bool quote(Buffer &_b, QString &ret, Error &error);
bool identifier(Buffer &_b, QString &ret, Error &error);
bool normalidentifier(Buffer &_b, QString &ret, Error &error);
bool kalimatdentifier(Buffer &_b, QString &ret, Error &error);
bool spacing(Buffer &_b, QString &ret, Error &error);
bool COLON(Buffer &_b, QString &ret, Error &error);
bool ARROW(Buffer &_b, QString &ret, Error &error);
bool LAMBDA(Buffer &_b, QString &ret, Error &error);
bool SLASH(Buffer &_b, QString &ret, Error &error);
bool SPACE(Buffer &_b, QString &ret, Error &error);
bool NL(Buffer &_b, QString &ret, Error &error);
bool LPAREN(Buffer &_b, QString &ret, Error &error);
bool RPAREN(Buffer &_b, QString &ret, Error &error);
bool LBRACE(Buffer &_b, QString &ret, Error &error);
bool RBRACE(Buffer &_b, QString &ret, Error &error);
bool LBRACKET(Buffer &_b, QString &ret, Error &error);
bool RBRACKET(Buffer &_b, QString &ret, Error &error);
bool ASTERISK(Buffer &_b, QString &ret, Error &error);
bool SEMI(Buffer &_b, QString &ret, Error &error);
bool NOT(Buffer &_b, QString &ret, Error &error);
bool DOT(Buffer &_b, QString &ret, Error &error);
bool QUESTION(Buffer &_b, QString &ret, Error &error);
bool SNIPPET(Buffer &_b, QString &ret, Error &error);
bool GT(Buffer &_b, QString &ret, Error &error);
bool LT(Buffer &_b, QString &ret, Error &error);
bool EQ(Buffer &_b, QString &ret, Error &error);
bool COMMA(Buffer &_b, QString &ret, Error &error);
bool CUT(Buffer &_b, QString &ret, Error &error);
bool AND(Buffer &_b, QString &ret, Error &error);
bool SHARPQUOTE(Buffer &_b, QString &ret, Error &error);
bool INCLASS(Buffer &_b, QString &ret, Error &error);
bool nonquote(Buffer &_b, QString &ret, Error &error);
bool nonrbrace(Buffer &_b, QString &ret, Error &error);
bool isCodeInKalimat;
PegParser() { isCodeInKalimat = false; }

bool apply_PPegChoice(QString _ruleName, Buffer &_b, PPegChoice &ret, Error &error);
bool apply_PPegExpr(QString _ruleName, Buffer &_b, PPegExpr &ret, Error &error);
bool apply_PPegSeq(QString _ruleName, Buffer &_b, PPegSeq &ret, Error &error);
bool apply_PRule(QString _ruleName, Buffer &_b, PRule &ret, Error &error);
bool apply_PegGrammar_pointer_(QString _ruleName, Buffer &_b, PegGrammar * &ret, Error &error);
bool apply_PegNonterminal_pointer_(QString _ruleName, Buffer &_b, PegNonterminal * &ret, Error &error);
bool apply_PegParam_pointer_(QString _ruleName, Buffer &_b, PegParam * &ret, Error &error);
bool apply_PegType_pointer_(QString _ruleName, Buffer &_b, PegType * &ret, Error &error);
bool apply_PegValue_pointer_(QString _ruleName, Buffer &_b, PegValue * &ret, Error &error);
bool apply_QMap_of_QString_and_QString_done_(QString _ruleName, Buffer &_b, QMap < QString, QString > &ret, Error &error);
bool apply_QString(QString _ruleName, Buffer &_b, QString &ret, Error &error);
bool apply_QStringList(QString _ruleName, Buffer &_b, QStringList &ret, Error &error);
bool apply_QVector_of_PegParam_pointer__done_(QString _ruleName, Buffer &_b, QVector < PegParam * > &ret, Error &error);
bool apply_QVector_of_PegType_pointer__done_(QString _ruleName, Buffer &_b, QVector < PegType * > &ret, Error &error);
bool apply_QVector_of_PegValue_pointer__done_(QString _ruleName, Buffer &_b, QVector < PegValue * > &ret, Error &error);
bool apply_QVector_of_QString_done_(QString _ruleName, Buffer &_b, QVector < QString > &ret, Error &error);
};
#endif
