lang="C++"
classname="PegParser"

inclass
{
	bool isCodeInKalimat;
	PegParser() { isCodeInKalimat = false; }
}

{
#include "pegast.h"
}

	
peg:PegGrammar *->
	{ ret = new PegGrammar(); }
	spacing
	options:opt {ret->options = opt;}
	(
		INCLASS code:cic { ret->codeInClass = cic;}
	)?

	(code:c1 	{ret->prelude = c1;})?
	(
		rule:r	{ret->rules.append(r);}
	)*
	(code:c2 	{ret->postlude = c2;})?
	_Eof
	;

options:QMap<QString,QString>->
	(identifier:i1 EQ strlit:v 
		{ 
			ret[i1] = v;
			if( i1 == "lang" && v == "Kalimat")
				isCodeInKalimat = true;
		}
		
	)*
	;

sepBy<T>(rule ()=>T, separator ()=>QString):QVector<T>->
	_Apply<T>(rule):t0 { ret.append(t0); }
	(
		_Apply<QString>(separator)
		_Apply<T>(rule):t1 { ret.append(t1);}
	)*
	;

zilo:QVector<QString>->
	sepBy<QString>[#'identifier, #'SPACE]:t { ret = t;}
	;

	
rule:PRule-> 
	{QString _code="";}
		identifier:i2
		templateparams:tp0
		paramlist:param0
		COLON ^
		type:t
		ARROW 
		(code:c1 {_code=c1;})?
		expr:e2
		{ret=new PegRule(i2,e2, t, param0, tp0);ret->code=_code;}
		SEMI
	/   
		identifier:i1
		templateparams:tp1
		paramlist:param1 
		ARROW 
		(code:c2 {_code=c2;})?
		expr:e1
		{ret=new PegRule(i1,e1, param1, tp1);ret->code=_code;}
		SEMI
	;

paramlist:QVector<PegParam *>->
{ ret.clear();}
		LPAREN
		param:p0 { ret.append(p0); }
		(
			COMMA
			param:p1 { ret.append(p1); }
		)*
		RPAREN
	/
		""
	;
	
param:PegParam *->
	identifier:i
	type:t
	{
		ret = new PegParam(i, t);
	}
	;
	
templateparams:QStringList->
{ ret.clear();}
		LT
		
		identifier:t { ret.append(t); }
		(
			COMMA
			identifier:t2 { ret.append(t2); }
		)*
		GT
	/
		""
	;

templateargs:QVector<PegType *>->
		{ ret.clear();}
		LT
		type:t { ret.append(t); }
		(
			COMMA
			type:t2 { ret.append(t2); }
		)*
		GT
	/
		""
	;

type:PegType *->
{
	QVector<PegType *> funParams;
	QVector<PegType *> args;
}
		LPAREN 
		(
			type:t0	    { funParams.append(t0); }
			(
				COMMA
				type:t1 { funParams.append(t1); }
			)*
		)?
		RPAREN
		LAMBDA
		type:t2
		{
			ret = new PegFunType(funParams, t2);
		}
		
		/
		identifier:id0 { ret = new PegTypeId(id0); }
		(LT
			type:t0 { args.append(t0); }
			(COMMA type:t1 { args.append(t1); } )*
		GT
			{ret = new PegParametrizedType(ret, args); } 
		)?
		(ASTERISK { ret = new PegPointerType(ret); } )?

	;
		
expr:PPegChoice-> { ret = new PegChoice();}
	seq:e{ret->elements.append(e);} (SLASH seq:e2{ret->elements.append(e2);})*;

seq:PPegSeq-> { ret = new PegSeq();}
	suffix:p1{ret->elements.append(p1);} (suffix:p2{ret->elements.append(p2);})*;

suffix:PPegExpr->
	  prefix:p1 QUESTION {ret = new PegChoice(p1, new PegStr(""));}
	/ prefix:p2 {ret=p2;}
	;
	
prefix:PPegExpr-> 
	  NOT ^ prim:p1 { ret= new PegNot(p1);} 
	/ AND !LBRACE ^ prim:p2 { ret = new PegAndPredicate(p2); }
	/ prim:p3 { ret=p3;};

prim:PPegExpr->
	CUT { ret = new PegCut(); }
	/
	AND code:cond { ret = new PegSemanticPredicate(cond);}
	/
	primprefix:p1
	(COLON identifier:v1 {p1->varName=v1;})?
	(code:c1 {p1->code=c1;})? 
	"" {ret=p1;}
	;

primprefix:PPegExpr->
	  LPAREN expr:e1 RPAREN ASTERISK{ret=new PegLoop(e1);}
	/ LPAREN expr:e2 RPAREN {ret=e2;}
	/ strlit:s1{ret=new PegStr(s1);}
	/ invokation:inv0 { ret = inv0; }
	/ DOT { ret = new PegAnyChar();}
	/ SNIPPET LPAREN expr:e3 RPAREN { ret = new PegSnippet(e3); }
	/ special:e4 { ret = e4;}
	/ application:e5 { ret = e5; }
	/ "_Error" spacing LPAREN strlit:sl0 RPAREN { ret = new PegError(sl0); }
	;

invokation:PegNonterminal *->
	identifier:i1 templateargs:ta0 arglist:arg0  {ret=new PegNonterminal(i1, arg0, ta0);}
	;
	
arglist:QVector<PegValue *>->
	{ ret.clear(); }
	LBRACKET
	pegArg:a0 { ret.append(a0); }
	(
	COMMA
	(pegArg:a1 { ret.append(a1); } )
	)*
	RBRACKET
	
	/
	""
	;

pegArg:PegValue *->
	identifier:i0 { ret = new PegIdArg(i0); }
	/
	strlit:s0 { ret = new PegStringArg("\""+s0+"\""); }
	/
	SHARPQUOTE identifier:id0 { ret = new PegSharpQuote(id0); }
	;	
application:PPegExpr->
	{
		QVector<PegValue *> args;
	}
	"_Apply" spacing
	LT type:t GT
	LPAREN
		pegArg:pa0 
		(
			COMMA
			pegArg:pa1 { args.append(pa1); }
		)*
	RPAREN
	{
		ret = new PegApply(t, pa0, args);
	}
;

special:PPegExpr-> specialtoken:t {ret=t;} spacing;
specialtoken:PPegExpr->
	  "_Eof" { ret = new PegEof();}
	/ "_Alpha" { ret = new PegAlpha();}
	/ "_Letter" { ret = new PegLetter();}
	/ "_Digit" {  ret = new PegDigit();}

	;
	
strlit:QString->
	{ ret = "";}
	quote
	(
		  "\\\""{ ret+="\\\"";} 
		/ nonquote:nq{ret+=nq;}
	)*
	quote
	spacing
	;

charlit:QString->"'"
				 (
					  "\'" .:c2{ ret+=c2.Lexeme;}
					! "'" .:c{ret+=c.Lexeme;}
				 )
				 "'"
				 spacing;

code:QString->
	LBRACE 
	_Snippet
	(
		
		(
			strlit
			/ code
			/ (! "}") .:c
		)*
	
		spacing
	):snp { ret = snp.Lexeme; }
	RBRACE
	;

quote:QString->"\"";

identifier:QString->
	  & { isCodeInKalimat } ^ kalimatdentifier:kid { ret = kid; }
	/ normalidentifier:nid { ret = nid; }
	;

normalidentifier:QString->_Alpha:a{ret=a.Lexeme;} (_Alpha:b{ret+=b.Lexeme;})* spacing;

kalimatdentifier:QString->
	_Alpha:a{ret=a.Lexeme;}
	(
		   _Alpha:b   {ret+=b.Lexeme;}
		/  "_"        { ret+= "."; }
	)*
	spacing
	;

spacing:QString->(" "/"\t"/"\r"/"\n")*;
COLON:QString->":" spacing;
ARROW:QString->"->" spacing;
LAMBDA:QString->"=>" spacing;
SLASH:QString->"/" spacing;
SPACE:QString->" " spacing;
NL:QString->"\n" spacing;
LPAREN:QString->"(" spacing;
RPAREN:QString->")" spacing;
LBRACE:QString->"{" spacing;
RBRACE:QString->"}" spacing;

LBRACKET:QString->"[" spacing;
RBRACKET:QString->"]" spacing;

ASTERISK:QString->"*" spacing;
SEMI:QString->";" spacing;
NOT:QString->"!" spacing;
DOT:QString-> "." spacing;
QUESTION:QString-> "?" spacing;
SNIPPET:QString-> "_Snippet" spacing;
GT:QString -> ">" spacing;
LT:QString -> "<" spacing;
EQ:QString -> "=" spacing;
COMMA:QString -> "," spacing;
CUT:QString-> "^" spacing;
AND:QString-> "&" spacing;
SHARPQUOTE:QString-> "#'" spacing;
INCLASS:QString-> "inclass" spacing;
nonquote:QString->!"\"" .:c{ret=c.Lexeme;};
nonrbrace:QString->!"}" .:c2{ret=c2.Lexeme;};

