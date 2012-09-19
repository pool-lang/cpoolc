#include "pegast.h"
#include "peg.h"

void PegParser::clearAllMemoization()
{
    memoize_AND.clear();
    memoize_ARROW.clear();
    memoize_ASTERISK.clear();
    memoize_COLON.clear();
    memoize_COMMA.clear();
    memoize_CUT.clear();
    memoize_DOT.clear();
    memoize_EQ.clear();
    memoize_GT.clear();
    memoize_INCLASS.clear();
    memoize_LAMBDA.clear();
    memoize_LBRACE.clear();
    memoize_LBRACKET.clear();
    memoize_LPAREN.clear();
    memoize_LT.clear();
    memoize_NL.clear();
    memoize_NOT.clear();
    memoize_QUESTION.clear();
    memoize_RBRACE.clear();
    memoize_RBRACKET.clear();
    memoize_RPAREN.clear();
    memoize_SEMI.clear();
    memoize_SHARPQUOTE.clear();
    memoize_SLASH.clear();
    memoize_SNIPPET.clear();
    memoize_SPACE.clear();
    memoize_application.clear();
    memoize_arglist.clear();
    memoize_charlit.clear();
    memoize_code.clear();
    memoize_expr.clear();
    memoize_identifier.clear();
    memoize_invokation.clear();
    memoize_kalimatdentifier.clear();
    memoize_nonquote.clear();
    memoize_nonrbrace.clear();
    memoize_normalidentifier.clear();
    memoize_options.clear();
    memoize_param.clear();
    memoize_paramlist.clear();
    memoize_peg.clear();
    memoize_pegArg.clear();
    memoize_prefix.clear();
    memoize_prim.clear();
    memoize_primprefix.clear();
    memoize_quote.clear();
    memoize_rule.clear();
    memoize_seq.clear();
    memoize_spacing.clear();
    memoize_special.clear();
    memoize_specialtoken.clear();
    memoize_strlit.clear();
    memoize_suffix.clear();
    memoize_templateargs.clear();
    memoize_templateparams.clear();
    memoize_type.clear();
    memoize_zilo.clear();
}

bool PegParser::apply_PPegChoice(QString _ruleName, Buffer &_b, PPegChoice &ret, Error &error)
{
    if(_ruleName == "expr")
    {
        return expr(_b, ret, error);
    }


    error = Error(QString("apply_PPegChoice can't find rule: ")+_ruleName, _b.saveState());
    return false;
}

bool PegParser::apply_PPegExpr(QString _ruleName, Buffer &_b, PPegExpr &ret, Error &error)
{
    if(_ruleName == "suffix")
    {
        return suffix(_b, ret, error);
    }

    if(_ruleName == "prefix")
    {
        return prefix(_b, ret, error);
    }

    if(_ruleName == "prim")
    {
        return prim(_b, ret, error);
    }

    if(_ruleName == "primprefix")
    {
        return primprefix(_b, ret, error);
    }

    if(_ruleName == "application")
    {
        return application(_b, ret, error);
    }

    if(_ruleName == "special")
    {
        return special(_b, ret, error);
    }

    if(_ruleName == "specialtoken")
    {
        return specialtoken(_b, ret, error);
    }


    error = Error(QString("apply_PPegExpr can't find rule: ")+_ruleName, _b.saveState());
    return false;
}

bool PegParser::apply_PPegSeq(QString _ruleName, Buffer &_b, PPegSeq &ret, Error &error)
{
    if(_ruleName == "seq")
    {
        return seq(_b, ret, error);
    }


    error = Error(QString("apply_PPegSeq can't find rule: ")+_ruleName, _b.saveState());
    return false;
}

bool PegParser::apply_PRule(QString _ruleName, Buffer &_b, PRule &ret, Error &error)
{
    if(_ruleName == "rule")
    {
        return rule(_b, ret, error);
    }


    error = Error(QString("apply_PRule can't find rule: ")+_ruleName, _b.saveState());
    return false;
}

bool PegParser::apply_PegGrammar_pointer_(QString _ruleName, Buffer &_b, PegGrammar * &ret, Error &error)
{
    if(_ruleName == "peg")
    {
        return peg(_b, ret, error);
    }


    error = Error(QString("apply_PegGrammar_pointer_ can't find rule: ")+_ruleName, _b.saveState());
    return false;
}

bool PegParser::apply_PegNonterminal_pointer_(QString _ruleName, Buffer &_b, PegNonterminal * &ret, Error &error)
{
    if(_ruleName == "invokation")
    {
        return invokation(_b, ret, error);
    }


    error = Error(QString("apply_PegNonterminal_pointer_ can't find rule: ")+_ruleName, _b.saveState());
    return false;
}

bool PegParser::apply_PegParam_pointer_(QString _ruleName, Buffer &_b, PegParam * &ret, Error &error)
{
    if(_ruleName == "param")
    {
        return param(_b, ret, error);
    }


    error = Error(QString("apply_PegParam_pointer_ can't find rule: ")+_ruleName, _b.saveState());
    return false;
}

bool PegParser::apply_PegType_pointer_(QString _ruleName, Buffer &_b, PegType * &ret, Error &error)
{
    if(_ruleName == "type")
    {
        return type(_b, ret, error);
    }


    error = Error(QString("apply_PegType_pointer_ can't find rule: ")+_ruleName, _b.saveState());
    return false;
}

bool PegParser::apply_PegValue_pointer_(QString _ruleName, Buffer &_b, PegValue * &ret, Error &error)
{
    if(_ruleName == "pegArg")
    {
        return pegArg(_b, ret, error);
    }


    error = Error(QString("apply_PegValue_pointer_ can't find rule: ")+_ruleName, _b.saveState());
    return false;
}

bool PegParser::apply_QMap_of_QString_and_QString_done_(QString _ruleName, Buffer &_b, QMap < QString, QString > &ret, Error &error)
{
    if(_ruleName == "options")
    {
        return options(_b, ret, error);
    }


    error = Error(QString("apply_QMap_of_QString_and_QString_done_ can't find rule: ")+_ruleName, _b.saveState());
    return false;
}

bool PegParser::apply_QString(QString _ruleName, Buffer &_b, QString &ret, Error &error)
{
    if(_ruleName == "strlit")
    {
        return strlit(_b, ret, error);
    }

    if(_ruleName == "charlit")
    {
        return charlit(_b, ret, error);
    }

    if(_ruleName == "code")
    {
        return code(_b, ret, error);
    }

    if(_ruleName == "quote")
    {
        return quote(_b, ret, error);
    }

    if(_ruleName == "identifier")
    {
        return identifier(_b, ret, error);
    }

    if(_ruleName == "normalidentifier")
    {
        return normalidentifier(_b, ret, error);
    }

    if(_ruleName == "kalimatdentifier")
    {
        return kalimatdentifier(_b, ret, error);
    }

    if(_ruleName == "spacing")
    {
        return spacing(_b, ret, error);
    }

    if(_ruleName == "COLON")
    {
        return COLON(_b, ret, error);
    }

    if(_ruleName == "ARROW")
    {
        return ARROW(_b, ret, error);
    }

    if(_ruleName == "LAMBDA")
    {
        return LAMBDA(_b, ret, error);
    }

    if(_ruleName == "SLASH")
    {
        return SLASH(_b, ret, error);
    }

    if(_ruleName == "SPACE")
    {
        return SPACE(_b, ret, error);
    }

    if(_ruleName == "NL")
    {
        return NL(_b, ret, error);
    }

    if(_ruleName == "LPAREN")
    {
        return LPAREN(_b, ret, error);
    }

    if(_ruleName == "RPAREN")
    {
        return RPAREN(_b, ret, error);
    }

    if(_ruleName == "LBRACE")
    {
        return LBRACE(_b, ret, error);
    }

    if(_ruleName == "RBRACE")
    {
        return RBRACE(_b, ret, error);
    }

    if(_ruleName == "LBRACKET")
    {
        return LBRACKET(_b, ret, error);
    }

    if(_ruleName == "RBRACKET")
    {
        return RBRACKET(_b, ret, error);
    }

    if(_ruleName == "ASTERISK")
    {
        return ASTERISK(_b, ret, error);
    }

    if(_ruleName == "SEMI")
    {
        return SEMI(_b, ret, error);
    }

    if(_ruleName == "NOT")
    {
        return NOT(_b, ret, error);
    }

    if(_ruleName == "DOT")
    {
        return DOT(_b, ret, error);
    }

    if(_ruleName == "QUESTION")
    {
        return QUESTION(_b, ret, error);
    }

    if(_ruleName == "SNIPPET")
    {
        return SNIPPET(_b, ret, error);
    }

    if(_ruleName == "GT")
    {
        return GT(_b, ret, error);
    }

    if(_ruleName == "LT")
    {
        return LT(_b, ret, error);
    }

    if(_ruleName == "EQ")
    {
        return EQ(_b, ret, error);
    }

    if(_ruleName == "COMMA")
    {
        return COMMA(_b, ret, error);
    }

    if(_ruleName == "CUT")
    {
        return CUT(_b, ret, error);
    }

    if(_ruleName == "AND")
    {
        return AND(_b, ret, error);
    }

    if(_ruleName == "SHARPQUOTE")
    {
        return SHARPQUOTE(_b, ret, error);
    }

    if(_ruleName == "INCLASS")
    {
        return INCLASS(_b, ret, error);
    }

    if(_ruleName == "nonquote")
    {
        return nonquote(_b, ret, error);
    }

    if(_ruleName == "nonrbrace")
    {
        return nonrbrace(_b, ret, error);
    }


    error = Error(QString("apply_QString can't find rule: ")+_ruleName, _b.saveState());
    return false;
}

bool PegParser::apply_QStringList(QString _ruleName, Buffer &_b, QStringList &ret, Error &error)
{
    if(_ruleName == "templateparams")
    {
        return templateparams(_b, ret, error);
    }


    error = Error(QString("apply_QStringList can't find rule: ")+_ruleName, _b.saveState());
    return false;
}

bool PegParser::apply_QVector_of_PegParam_pointer__done_(QString _ruleName, Buffer &_b, QVector < PegParam * > &ret, Error &error)
{
    if(_ruleName == "paramlist")
    {
        return paramlist(_b, ret, error);
    }


    error = Error(QString("apply_QVector_of_PegParam_pointer__done_ can't find rule: ")+_ruleName, _b.saveState());
    return false;
}

bool PegParser::apply_QVector_of_PegType_pointer__done_(QString _ruleName, Buffer &_b, QVector < PegType * > &ret, Error &error)
{
    if(_ruleName == "templateargs")
    {
        return templateargs(_b, ret, error);
    }


    error = Error(QString("apply_QVector_of_PegType_pointer__done_ can't find rule: ")+_ruleName, _b.saveState());
    return false;
}

bool PegParser::apply_QVector_of_PegValue_pointer__done_(QString _ruleName, Buffer &_b, QVector < PegValue * > &ret, Error &error)
{
    if(_ruleName == "arglist")
    {
        return arglist(_b, ret, error);
    }


    error = Error(QString("apply_QVector_of_PegValue_pointer__done_ can't find rule: ")+_ruleName, _b.saveState());
    return false;
}

bool PegParser::apply_QVector_of_QString_done_(QString _ruleName, Buffer &_b, QVector < QString > &ret, Error &error)
{
    if(_ruleName == "zilo")
    {
    }


    error = Error(QString("apply_QVector_of_QString_done_ can't find rule: ")+_ruleName, _b.saveState());
    return false;
}

bool PegParser::peg(Buffer &_b, PegGrammar * &ret, Error &error)
{
    int _thisPos = _b.getP2();

    if(memoize_peg.contains(_thisPos))
    {
        ret=memoize_peg[_thisPos].value;
        return memoize_peg[_thisPos].getValues(_b);
    }

    QString _dummy_0;
    QString _dummy_1;
    QString c1;
    QString c2;
    QString cic;
    QMap < QString, QString > opt;
    PRule r;
    stackTrace.push(QString("peg")+"   "+_b.remainder().mid(10));
    ret = new PegGrammar();
    bool result0=true;
    BufferState _s0 = _b.saveState();
    do
    {

        bool result1=spacing(_b, _dummy_0, error);

        result0 = result0 && result1;
        if(!result0)
        {
            _b.restoreState(_s0);
            break;
        };

        bool result2=options(_b, opt, error);
        if(result2)
        {
            ret->options = opt;
        }

        result0 = result0 && result2;
        if(!result0)
        {
            _b.restoreState(_s0);
            break;
        };
        bool result3=false;
        bool _cut0=false;
        BufferState _s1 = _b.saveState();
        if(!result3 && !_cut0)
        {
            bool result4=true;
            BufferState _s2 = _b.saveState();
            do
            {

                bool result5=INCLASS(_b, _dummy_1, error);

                result4 = result4 && result5;
                if(!result4)
                {
                    _b.restoreState(_s2);
                    break;
                };

                bool result6=code(_b, cic, error);
                if(result6)
                {
                    ret->codeInClass = cic;
                }

                result4 = result4 && result6;
                if(!result4)
                {
                    _b.restoreState(_s2);
                    break;
                };

            } while(false);
            result3 = result3 || result4;
            if(!result3)
            {
                _b.restoreState(_s1);
            }
        }
        if(!result3 && !_cut0)
        {
            bool result7 = _matchStr(_b, "", error);
            result3 = result3 || result7;
            if(!result3)
            {
                _b.restoreState(_s1);
            }
        }
        result0 = result0 && result3;
        if(!result0)
        {
            _b.restoreState(_s0);
            break;
        };
        bool result8=false;
        bool _cut1=false;
        BufferState _s3 = _b.saveState();
        if(!result8 && !_cut1)
        {

            bool result9=code(_b, c1, error);
            if(result9)
            {
                ret->prelude = c1;
            }

            result8 = result8 || result9;
            if(!result8)
            {
                _b.restoreState(_s3);
            }
        }
        if(!result8 && !_cut1)
        {
            bool result10 = _matchStr(_b, "", error);
            result8 = result8 || result10;
            if(!result8)
            {
                _b.restoreState(_s3);
            }
        }
        result0 = result0 && result8;
        if(!result0)
        {
            _b.restoreState(_s0);
            break;
        };
        bool result11 = true;
        bool _cut2 = false;
        while(true)
        {
            _cut2= false;
            BufferState _s = _b.saveState();

            bool result12=rule(_b, r, error);
            if(result12)
            {
                ret->rules.append(r);
            }

            if(!(result12))
            {
                _b.restoreState(_s);
                if(_cut2)
                {
                    result11 = false;
                }
                break;
            };
        }
        result0 = result0 && result11;
        if(!result0)
        {
            _b.restoreState(_s0);
            break;
        };
        bool result13=false;
        bool _cut3=false;
        BufferState _s4 = _b.saveState();
        if(!result13 && !_cut3)
        {

            bool result14=code(_b, c2, error);
            if(result14)
            {
                ret->postlude = c2;
            }

            result13 = result13 || result14;
            if(!result13)
            {
                _b.restoreState(_s4);
            }
        }
        if(!result13 && !_cut3)
        {
            bool result15 = _matchStr(_b, "", error);
            result13 = result13 || result15;
            if(!result13)
            {
                _b.restoreState(_s4);
            }
        }
        result0 = result0 && result13;
        if(!result0)
        {
            _b.restoreState(_s0);
            break;
        };
        result0 = result0 && _b.eof();
        if(!result0)
        {
            _b.restoreState(_s0);
            break;
        };

    } while(false);

    bool _success = result0;

    memoize_peg[_thisPos] = ParseResult<PegGrammar * >(_success, ret, _b.saveState());

    stackTrace.pop();
    return _success;
}


bool PegParser::options(Buffer &_b, QMap < QString, QString > &ret, Error &error)
{
    int _thisPos = _b.getP2();

    if(memoize_options.contains(_thisPos))
    {
        ret=memoize_options[_thisPos].value;
        return memoize_options[_thisPos].getValues(_b);
    }

    QString _dummy_2;
    QString i1;
    QString v;
    stackTrace.push(QString("options")+"   "+_b.remainder().mid(10));

    bool result16 = true;
    bool _cut4 = false;
    while(true)
    {
        _cut4= false;
        BufferState _s = _b.saveState();
        bool result17=true;
        BufferState _s5 = _b.saveState();
        do
        {

            bool result18=identifier(_b, i1, error);

            result17 = result17 && result18;
            if(!result17)
            {
                _b.restoreState(_s5);
                break;
            };

            bool result19=EQ(_b, _dummy_2, error);

            result17 = result17 && result19;
            if(!result17)
            {
                _b.restoreState(_s5);
                break;
            };

            bool result20=strlit(_b, v, error);
            if(result20)
            {
                ret[i1] = v;
                if( i1 == "lang" && v == "Kalimat")
                    isCodeInKalimat = true;

            }

            result17 = result17 && result20;
            if(!result17)
            {
                _b.restoreState(_s5);
                break;
            };

        } while(false);
        if(!(result17))
        {
            _b.restoreState(_s);
            if(_cut4)
            {
                result16 = false;
            }
            break;
        };
    }

    bool _success = result16;

    memoize_options[_thisPos] = ParseResult<QMap < QString, QString > >(_success, ret, _b.saveState());

    stackTrace.pop();
    return _success;
}




bool PegParser::rule(Buffer &_b, PRule &ret, Error &error)
{
    int _thisPos = _b.getP2();

    if(memoize_rule.contains(_thisPos))
    {
        ret=memoize_rule[_thisPos].value;
        return memoize_rule[_thisPos].getValues(_b);
    }

    QString _dummy_3;
    QString _dummy_4;
    QString _dummy_5;
    QString _dummy_6;
    QString _dummy_7;
    QString c1;
    QString c2;
    PPegChoice e1;
    PPegChoice e2;
    QString i1;
    QString i2;
    QVector < PegParam * > param0;
    QVector < PegParam * > param1;
    PegType * t;
    QStringList tp0;
    QStringList tp1;
    stackTrace.push(QString("rule")+"   "+_b.remainder().mid(10));
    QString _code="";
    bool result25=false;
    bool _cut6=false;
    BufferState _s8 = _b.saveState();
    if(!result25 && !_cut6)
    {
        bool result26=true;
        BufferState _s9 = _b.saveState();
        do
        {

            bool result27=identifier(_b, i2, error);

            result26 = result26 && result27;
            if(!result26)
            {
                _b.restoreState(_s9);
                break;
            };

            bool result28=templateparams(_b, tp0, error);

            result26 = result26 && result28;
            if(!result26)
            {
                _b.restoreState(_s9);
                break;
            };

            bool result29=paramlist(_b, param0, error);

            result26 = result26 && result29;
            if(!result26)
            {
                _b.restoreState(_s9);
                break;
            };

            bool result30=COLON(_b, _dummy_3, error);

            result26 = result26 && result30;
            if(!result26)
            {
                _b.restoreState(_s9);
                break;
            };
            _cut6=true;
            result26 = result26 && true;
            if(!result26)
            {
                _b.restoreState(_s9);
                break;
            };

            bool result31=type(_b, t, error);

            result26 = result26 && result31;
            if(!result26)
            {
                _b.restoreState(_s9);
                break;
            };

            bool result32=ARROW(_b, _dummy_4, error);

            result26 = result26 && result32;
            if(!result26)
            {
                _b.restoreState(_s9);
                break;
            };
            bool result33=false;
            bool _cut7=false;
            BufferState _s10 = _b.saveState();
            if(!result33 && !_cut7)
            {

                bool result34=code(_b, c1, error);
                if(result34)
                {
                    _code=c1;
                }

                result33 = result33 || result34;
                if(!result33)
                {
                    _b.restoreState(_s10);
                }
            }
            if(!result33 && !_cut7)
            {
                bool result35 = _matchStr(_b, "", error);
                result33 = result33 || result35;
                if(!result33)
                {
                    _b.restoreState(_s10);
                }
            }
            result26 = result26 && result33;
            if(!result26)
            {
                _b.restoreState(_s9);
                break;
            };

            bool result36=expr(_b, e2, error);
            if(result36)
            {
                ret=new PegRule(i2,e2, t, param0, tp0);ret->code=_code;
            }

            result26 = result26 && result36;
            if(!result26)
            {
                _b.restoreState(_s9);
                break;
            };

            bool result37=SEMI(_b, _dummy_5, error);

            result26 = result26 && result37;
            if(!result26)
            {
                _b.restoreState(_s9);
                break;
            };

        } while(false);
        result25 = result25 || result26;
        if(!result25)
        {
            _b.restoreState(_s8);
        }
    }
    if(!result25 && !_cut6)
    {
        bool result38=true;
        BufferState _s11 = _b.saveState();
        do
        {

            bool result39=identifier(_b, i1, error);

            result38 = result38 && result39;
            if(!result38)
            {
                _b.restoreState(_s11);
                break;
            };

            bool result40=templateparams(_b, tp1, error);

            result38 = result38 && result40;
            if(!result38)
            {
                _b.restoreState(_s11);
                break;
            };

            bool result41=paramlist(_b, param1, error);

            result38 = result38 && result41;
            if(!result38)
            {
                _b.restoreState(_s11);
                break;
            };

            bool result42=ARROW(_b, _dummy_6, error);

            result38 = result38 && result42;
            if(!result38)
            {
                _b.restoreState(_s11);
                break;
            };
            bool result43=false;
            bool _cut8=false;
            BufferState _s12 = _b.saveState();
            if(!result43 && !_cut8)
            {

                bool result44=code(_b, c2, error);
                if(result44)
                {
                    _code=c2;
                }

                result43 = result43 || result44;
                if(!result43)
                {
                    _b.restoreState(_s12);
                }
            }
            if(!result43 && !_cut8)
            {
                bool result45 = _matchStr(_b, "", error);
                result43 = result43 || result45;
                if(!result43)
                {
                    _b.restoreState(_s12);
                }
            }
            result38 = result38 && result43;
            if(!result38)
            {
                _b.restoreState(_s11);
                break;
            };

            bool result46=expr(_b, e1, error);
            if(result46)
            {
                ret=new PegRule(i1,e1, param1, tp1);ret->code=_code;
            }

            result38 = result38 && result46;
            if(!result38)
            {
                _b.restoreState(_s11);
                break;
            };

            bool result47=SEMI(_b, _dummy_7, error);

            result38 = result38 && result47;
            if(!result38)
            {
                _b.restoreState(_s11);
                break;
            };

        } while(false);
        result25 = result25 || result38;
        if(!result25)
        {
            _b.restoreState(_s8);
        }
    }

    bool _success = result25;

    memoize_rule[_thisPos] = ParseResult<PRule >(_success, ret, _b.saveState());

    stackTrace.pop();
    return _success;
}


bool PegParser::paramlist(Buffer &_b, QVector < PegParam * > &ret, Error &error)
{
    int _thisPos = _b.getP2();

    if(memoize_paramlist.contains(_thisPos))
    {
        ret=memoize_paramlist[_thisPos].value;
        return memoize_paramlist[_thisPos].getValues(_b);
    }

    QString _dummy_10;
    QString _dummy_8;
    QString _dummy_9;
    PegParam * p0;
    PegParam * p1;
    stackTrace.push(QString("paramlist")+"   "+_b.remainder().mid(10));
    ret.clear();
    bool result48=false;
    bool _cut9=false;
    BufferState _s13 = _b.saveState();
    if(!result48 && !_cut9)
    {
        bool result49=true;
        BufferState _s14 = _b.saveState();
        do
        {

            bool result50=LPAREN(_b, _dummy_8, error);

            result49 = result49 && result50;
            if(!result49)
            {
                _b.restoreState(_s14);
                break;
            };

            bool result51=param(_b, p0, error);
            if(result51)
            {
                ret.append(p0);
            }

            result49 = result49 && result51;
            if(!result49)
            {
                _b.restoreState(_s14);
                break;
            };
            bool result52 = true;
            bool _cut10 = false;
            while(true)
            {
                _cut10= false;
                BufferState _s = _b.saveState();
                bool result53=true;
                BufferState _s15 = _b.saveState();
                do
                {

                    bool result54=COMMA(_b, _dummy_9, error);

                    result53 = result53 && result54;
                    if(!result53)
                    {
                        _b.restoreState(_s15);
                        break;
                    };

                    bool result55=param(_b, p1, error);
                    if(result55)
                    {
                        ret.append(p1);
                    }

                    result53 = result53 && result55;
                    if(!result53)
                    {
                        _b.restoreState(_s15);
                        break;
                    };

                } while(false);
                if(!(result53))
                {
                    _b.restoreState(_s);
                    if(_cut10)
                    {
                        result52 = false;
                    }
                    break;
                };
            }
            result49 = result49 && result52;
            if(!result49)
            {
                _b.restoreState(_s14);
                break;
            };

            bool result56=RPAREN(_b, _dummy_10, error);

            result49 = result49 && result56;
            if(!result49)
            {
                _b.restoreState(_s14);
                break;
            };

        } while(false);
        result48 = result48 || result49;
        if(!result48)
        {
            _b.restoreState(_s13);
        }
    }
    if(!result48 && !_cut9)
    {
        bool result57 = _matchStr(_b, "", error);
        result48 = result48 || result57;
        if(!result48)
        {
            _b.restoreState(_s13);
        }
    }

    bool _success = result48;

    memoize_paramlist[_thisPos] = ParseResult<QVector < PegParam * > >(_success, ret, _b.saveState());

    stackTrace.pop();
    return _success;
}


bool PegParser::param(Buffer &_b, PegParam * &ret, Error &error)
{
    int _thisPos = _b.getP2();

    if(memoize_param.contains(_thisPos))
    {
        ret=memoize_param[_thisPos].value;
        return memoize_param[_thisPos].getValues(_b);
    }

    QString i;
    PegType * t;
    stackTrace.push(QString("param")+"   "+_b.remainder().mid(10));

    bool result58=true;
    BufferState _s16 = _b.saveState();
    do
    {

        bool result59=identifier(_b, i, error);

        result58 = result58 && result59;
        if(!result58)
        {
            _b.restoreState(_s16);
            break;
        };

        bool result60=type(_b, t, error);
        if(result60)
        {
            ret = new PegParam(i, t);

        }

        result58 = result58 && result60;
        if(!result58)
        {
            _b.restoreState(_s16);
            break;
        };

    } while(false);

    bool _success = result58;

    memoize_param[_thisPos] = ParseResult<PegParam * >(_success, ret, _b.saveState());

    stackTrace.pop();
    return _success;
}


bool PegParser::templateparams(Buffer &_b, QStringList &ret, Error &error)
{
    int _thisPos = _b.getP2();

    if(memoize_templateparams.contains(_thisPos))
    {
        ret=memoize_templateparams[_thisPos].value;
        return memoize_templateparams[_thisPos].getValues(_b);
    }

    QString _dummy_11;
    QString _dummy_12;
    QString _dummy_13;
    QString t;
    QString t2;
    stackTrace.push(QString("templateparams")+"   "+_b.remainder().mid(10));
    ret.clear();
    bool result61=false;
    bool _cut11=false;
    BufferState _s17 = _b.saveState();
    if(!result61 && !_cut11)
    {
        bool result62=true;
        BufferState _s18 = _b.saveState();
        do
        {

            bool result63=LT(_b, _dummy_11, error);

            result62 = result62 && result63;
            if(!result62)
            {
                _b.restoreState(_s18);
                break;
            };

            bool result64=identifier(_b, t, error);
            if(result64)
            {
                ret.append(t);
            }

            result62 = result62 && result64;
            if(!result62)
            {
                _b.restoreState(_s18);
                break;
            };
            bool result65 = true;
            bool _cut12 = false;
            while(true)
            {
                _cut12= false;
                BufferState _s = _b.saveState();
                bool result66=true;
                BufferState _s19 = _b.saveState();
                do
                {

                    bool result67=COMMA(_b, _dummy_12, error);

                    result66 = result66 && result67;
                    if(!result66)
                    {
                        _b.restoreState(_s19);
                        break;
                    };

                    bool result68=identifier(_b, t2, error);
                    if(result68)
                    {
                        ret.append(t2);
                    }

                    result66 = result66 && result68;
                    if(!result66)
                    {
                        _b.restoreState(_s19);
                        break;
                    };

                } while(false);
                if(!(result66))
                {
                    _b.restoreState(_s);
                    if(_cut12)
                    {
                        result65 = false;
                    }
                    break;
                };
            }
            result62 = result62 && result65;
            if(!result62)
            {
                _b.restoreState(_s18);
                break;
            };

            bool result69=GT(_b, _dummy_13, error);

            result62 = result62 && result69;
            if(!result62)
            {
                _b.restoreState(_s18);
                break;
            };

        } while(false);
        result61 = result61 || result62;
        if(!result61)
        {
            _b.restoreState(_s17);
        }
    }
    if(!result61 && !_cut11)
    {
        bool result70 = _matchStr(_b, "", error);
        result61 = result61 || result70;
        if(!result61)
        {
            _b.restoreState(_s17);
        }
    }

    bool _success = result61;

    memoize_templateparams[_thisPos] = ParseResult<QStringList >(_success, ret, _b.saveState());

    stackTrace.pop();
    return _success;
}


bool PegParser::templateargs(Buffer &_b, QVector < PegType * > &ret, Error &error)
{
    int _thisPos = _b.getP2();

    if(memoize_templateargs.contains(_thisPos))
    {
        ret=memoize_templateargs[_thisPos].value;
        return memoize_templateargs[_thisPos].getValues(_b);
    }

    QString _dummy_14;
    QString _dummy_15;
    QString _dummy_16;
    PegType * t;
    PegType * t2;
    stackTrace.push(QString("templateargs")+"   "+_b.remainder().mid(10));
    ret.clear();
    bool result71=false;
    bool _cut13=false;
    BufferState _s20 = _b.saveState();
    if(!result71 && !_cut13)
    {
        bool result72=true;
        BufferState _s21 = _b.saveState();
        do
        {

            bool result73=LT(_b, _dummy_14, error);

            result72 = result72 && result73;
            if(!result72)
            {
                _b.restoreState(_s21);
                break;
            };

            bool result74=type(_b, t, error);
            if(result74)
            {
                ret.append(t);
            }

            result72 = result72 && result74;
            if(!result72)
            {
                _b.restoreState(_s21);
                break;
            };
            bool result75 = true;
            bool _cut14 = false;
            while(true)
            {
                _cut14= false;
                BufferState _s = _b.saveState();
                bool result76=true;
                BufferState _s22 = _b.saveState();
                do
                {

                    bool result77=COMMA(_b, _dummy_15, error);

                    result76 = result76 && result77;
                    if(!result76)
                    {
                        _b.restoreState(_s22);
                        break;
                    };

                    bool result78=type(_b, t2, error);
                    if(result78)
                    {
                        ret.append(t2);
                    }

                    result76 = result76 && result78;
                    if(!result76)
                    {
                        _b.restoreState(_s22);
                        break;
                    };

                } while(false);
                if(!(result76))
                {
                    _b.restoreState(_s);
                    if(_cut14)
                    {
                        result75 = false;
                    }
                    break;
                };
            }
            result72 = result72 && result75;
            if(!result72)
            {
                _b.restoreState(_s21);
                break;
            };

            bool result79=GT(_b, _dummy_16, error);

            result72 = result72 && result79;
            if(!result72)
            {
                _b.restoreState(_s21);
                break;
            };

        } while(false);
        result71 = result71 || result72;
        if(!result71)
        {
            _b.restoreState(_s20);
        }
    }
    if(!result71 && !_cut13)
    {
        bool result80 = _matchStr(_b, "", error);
        result71 = result71 || result80;
        if(!result71)
        {
            _b.restoreState(_s20);
        }
    }

    bool _success = result71;

    memoize_templateargs[_thisPos] = ParseResult<QVector < PegType * > >(_success, ret, _b.saveState());

    stackTrace.pop();
    return _success;
}


bool PegParser::type(Buffer &_b, PegType * &ret, Error &error)
{
    int _thisPos = _b.getP2();

    if(memoize_type.contains(_thisPos))
    {
        ret=memoize_type[_thisPos].value;
        return memoize_type[_thisPos].getValues(_b);
    }



    QString _dummy_17;
    QString _dummy_18;
    QString _dummy_19;
    QString _dummy_20;
    QString _dummy_21;
    QString _dummy_22;
    QString _dummy_23;
    QString _dummy_24;
    QString id0;
    PegType * t0;
    PegType * t1;
    PegType * t2;
    stackTrace.push(QString("type")+"   "+_b.remainder().mid(10));
    QVector<PegType *> funParams;
    QVector<PegType *> args;
    bool result81=false;
    bool _cut15=false;
    BufferState _s23 = _b.saveState();
    if(!result81 && !_cut15)
    {
        bool result82=true;
        BufferState _s24 = _b.saveState();
        do
        {

            bool result83=LPAREN(_b, _dummy_17, error);

            result82 = result82 && result83;
            if(!result82)
            {
                _b.restoreState(_s24);
                break;
            };
            bool result84=false;
            bool _cut16=false;
            BufferState _s25 = _b.saveState();
            if(!result84 && !_cut16)
            {
                bool result85=true;
                BufferState _s26 = _b.saveState();
                do
                {

                    bool result86=type(_b, t0, error);
                    if(result86)
                    {
                        funParams.append(t0);
                    }

                    result85 = result85 && result86;
                    if(!result85)
                    {
                        _b.restoreState(_s26);
                        break;
                    };
                    bool result87 = true;
                    bool _cut17 = false;
                    while(true)
                    {
                        _cut17= false;
                        BufferState _s = _b.saveState();
                        bool result88=true;
                        BufferState _s27 = _b.saveState();
                        do
                        {

                            bool result89=COMMA(_b, _dummy_18, error);

                            result88 = result88 && result89;
                            if(!result88)
                            {
                                _b.restoreState(_s27);
                                break;
                            };

                            bool result90=type(_b, t1, error);
                            if(result90)
                            {
                                funParams.append(t1);
                            }

                            result88 = result88 && result90;
                            if(!result88)
                            {
                                _b.restoreState(_s27);
                                break;
                            };

                        } while(false);
                        if(!(result88))
                        {
                            _b.restoreState(_s);
                            if(_cut17)
                            {
                                result87 = false;
                            }
                            break;
                        };
                    }
                    result85 = result85 && result87;
                    if(!result85)
                    {
                        _b.restoreState(_s26);
                        break;
                    };

                } while(false);
                result84 = result84 || result85;
                if(!result84)
                {
                    _b.restoreState(_s25);
                }
            }
            if(!result84 && !_cut16)
            {
                bool result91 = _matchStr(_b, "", error);
                result84 = result84 || result91;
                if(!result84)
                {
                    _b.restoreState(_s25);
                }
            }
            result82 = result82 && result84;
            if(!result82)
            {
                _b.restoreState(_s24);
                break;
            };

            bool result92=RPAREN(_b, _dummy_19, error);

            result82 = result82 && result92;
            if(!result82)
            {
                _b.restoreState(_s24);
                break;
            };

            bool result93=LAMBDA(_b, _dummy_20, error);

            result82 = result82 && result93;
            if(!result82)
            {
                _b.restoreState(_s24);
                break;
            };

            bool result94=type(_b, t2, error);
            if(result94)
            {
                ret = new PegFunType(funParams, t2);

            }

            result82 = result82 && result94;
            if(!result82)
            {
                _b.restoreState(_s24);
                break;
            };

        } while(false);
        result81 = result81 || result82;
        if(!result81)
        {
            _b.restoreState(_s23);
        }
    }
    if(!result81 && !_cut15)
    {
        bool result95=true;
        BufferState _s28 = _b.saveState();
        do
        {
            bool result96 = _matchStr(_b, "", error);
            if(result96)
            {

            };
            result95 = result95 && result96;
            if(!result95)
            {
                _b.restoreState(_s28);
                break;
            };

            bool result97=identifier(_b, id0, error);
            if(result97)
            {
                ret = new PegTypeId(id0);
            }

            result95 = result95 && result97;
            if(!result95)
            {
                _b.restoreState(_s28);
                break;
            };
            bool result98=false;
            bool _cut18=false;
            BufferState _s29 = _b.saveState();
            if(!result98 && !_cut18)
            {
                bool result99=true;
                BufferState _s30 = _b.saveState();
                do
                {

                    bool result100=LT(_b, _dummy_21, error);

                    result99 = result99 && result100;
                    if(!result99)
                    {
                        _b.restoreState(_s30);
                        break;
                    };

                    bool result101=type(_b, t0, error);
                    if(result101)
                    {
                        args.append(t0);
                    }

                    result99 = result99 && result101;
                    if(!result99)
                    {
                        _b.restoreState(_s30);
                        break;
                    };
                    bool result102 = true;
                    bool _cut19 = false;
                    while(true)
                    {
                        _cut19= false;
                        BufferState _s = _b.saveState();
                        bool result103=true;
                        BufferState _s31 = _b.saveState();
                        do
                        {

                            bool result104=COMMA(_b, _dummy_22, error);

                            result103 = result103 && result104;
                            if(!result103)
                            {
                                _b.restoreState(_s31);
                                break;
                            };

                            bool result105=type(_b, t1, error);
                            if(result105)
                            {
                                args.append(t1);
                            }

                            result103 = result103 && result105;
                            if(!result103)
                            {
                                _b.restoreState(_s31);
                                break;
                            };

                        } while(false);
                        if(!(result103))
                        {
                            _b.restoreState(_s);
                            if(_cut19)
                            {
                                result102 = false;
                            }
                            break;
                        };
                    }
                    result99 = result99 && result102;
                    if(!result99)
                    {
                        _b.restoreState(_s30);
                        break;
                    };

                    bool result106=GT(_b, _dummy_23, error);
                    if(result106)
                    {
                        ret = new PegParametrizedType(ret, args);
                    }

                    result99 = result99 && result106;
                    if(!result99)
                    {
                        _b.restoreState(_s30);
                        break;
                    };

                } while(false);
                result98 = result98 || result99;
                if(!result98)
                {
                    _b.restoreState(_s29);
                }
            }
            if(!result98 && !_cut18)
            {
                bool result107 = _matchStr(_b, "", error);
                result98 = result98 || result107;
                if(!result98)
                {
                    _b.restoreState(_s29);
                }
            }
            result95 = result95 && result98;
            if(!result95)
            {
                _b.restoreState(_s28);
                break;
            };
            bool result108=false;
            bool _cut20=false;
            BufferState _s32 = _b.saveState();
            if(!result108 && !_cut20)
            {

                bool result109=ASTERISK(_b, _dummy_24, error);
                if(result109)
                {
                    ret = new PegPointerType(ret);
                }

                result108 = result108 || result109;
                if(!result108)
                {
                    _b.restoreState(_s32);
                }
            }
            if(!result108 && !_cut20)
            {
                bool result110 = _matchStr(_b, "", error);
                result108 = result108 || result110;
                if(!result108)
                {
                    _b.restoreState(_s32);
                }
            }
            result95 = result95 && result108;
            if(!result95)
            {
                _b.restoreState(_s28);
                break;
            };

        } while(false);
        result81 = result81 || result95;
        if(!result81)
        {
            _b.restoreState(_s23);
        }
    }

    bool _success = result81;

    memoize_type[_thisPos] = ParseResult<PegType * >(_success, ret, _b.saveState());

    stackTrace.pop();
    return _success;
}


bool PegParser::expr(Buffer &_b, PPegChoice &ret, Error &error)
{
    int _thisPos = _b.getP2();

    if(memoize_expr.contains(_thisPos))
    {
        ret=memoize_expr[_thisPos].value;
        return memoize_expr[_thisPos].getValues(_b);
    }

    QString _dummy_25;
    PPegSeq e;
    PPegSeq e2;
    stackTrace.push(QString("expr")+"   "+_b.remainder().mid(10));
    ret = new PegChoice();
    bool result111=true;
    BufferState _s33 = _b.saveState();
    do
    {

        bool result112=seq(_b, e, error);
        if(result112)
        {
            ret->elements.append(e);
        }

        result111 = result111 && result112;
        if(!result111)
        {
            _b.restoreState(_s33);
            break;
        };
        bool result113 = true;
        bool _cut21 = false;
        while(true)
        {
            _cut21= false;
            BufferState _s = _b.saveState();
            bool result114=true;
            BufferState _s34 = _b.saveState();
            do
            {

                bool result115=SLASH(_b, _dummy_25, error);

                result114 = result114 && result115;
                if(!result114)
                {
                    _b.restoreState(_s34);
                    break;
                };

                bool result116=seq(_b, e2, error);
                if(result116)
                {
                    ret->elements.append(e2);
                }

                result114 = result114 && result116;
                if(!result114)
                {
                    _b.restoreState(_s34);
                    break;
                };

            } while(false);
            if(!(result114))
            {
                _b.restoreState(_s);
                if(_cut21)
                {
                    result113 = false;
                }
                break;
            };
        }
        result111 = result111 && result113;
        if(!result111)
        {
            _b.restoreState(_s33);
            break;
        };

    } while(false);

    bool _success = result111;

    memoize_expr[_thisPos] = ParseResult<PPegChoice >(_success, ret, _b.saveState());

    stackTrace.pop();
    return _success;
}


bool PegParser::seq(Buffer &_b, PPegSeq &ret, Error &error)
{
    int _thisPos = _b.getP2();

    if(memoize_seq.contains(_thisPos))
    {
        ret=memoize_seq[_thisPos].value;
        return memoize_seq[_thisPos].getValues(_b);
    }

    PPegExpr p1;
    PPegExpr p2;
    stackTrace.push(QString("seq")+"   "+_b.remainder().mid(10));
    ret = new PegSeq();
    bool result117=true;
    BufferState _s35 = _b.saveState();
    do
    {

        bool result118=suffix(_b, p1, error);
        if(result118)
        {
            ret->elements.append(p1);
        }

        result117 = result117 && result118;
        if(!result117)
        {
            _b.restoreState(_s35);
            break;
        };
        bool result119 = true;
        bool _cut22 = false;
        while(true)
        {
            _cut22= false;
            BufferState _s = _b.saveState();

            bool result120=suffix(_b, p2, error);
            if(result120)
            {
                ret->elements.append(p2);
            }

            if(!(result120))
            {
                _b.restoreState(_s);
                if(_cut22)
                {
                    result119 = false;
                }
                break;
            };
        }
        result117 = result117 && result119;
        if(!result117)
        {
            _b.restoreState(_s35);
            break;
        };

    } while(false);

    bool _success = result117;

    memoize_seq[_thisPos] = ParseResult<PPegSeq >(_success, ret, _b.saveState());

    stackTrace.pop();
    return _success;
}


bool PegParser::suffix(Buffer &_b, PPegExpr &ret, Error &error)
{
    int _thisPos = _b.getP2();

    if(memoize_suffix.contains(_thisPos))
    {
        ret=memoize_suffix[_thisPos].value;
        return memoize_suffix[_thisPos].getValues(_b);
    }

    QString _dummy_26;
    PPegExpr p1;
    PPegExpr p2;
    stackTrace.push(QString("suffix")+"   "+_b.remainder().mid(10));

    bool result121=false;
    bool _cut23=false;
    BufferState _s36 = _b.saveState();
    if(!result121 && !_cut23)
    {
        bool result122=true;
        BufferState _s37 = _b.saveState();
        do
        {

            bool result123=prefix(_b, p1, error);

            result122 = result122 && result123;
            if(!result122)
            {
                _b.restoreState(_s37);
                break;
            };

            bool result124=QUESTION(_b, _dummy_26, error);
            if(result124)
            {
                ret = new PegChoice(p1, new PegStr(""));
            }

            result122 = result122 && result124;
            if(!result122)
            {
                _b.restoreState(_s37);
                break;
            };

        } while(false);
        result121 = result121 || result122;
        if(!result121)
        {
            _b.restoreState(_s36);
        }
    }
    if(!result121 && !_cut23)
    {

        bool result125=prefix(_b, p2, error);
        if(result125)
        {
            ret=p2;
        }

        result121 = result121 || result125;
        if(!result121)
        {
            _b.restoreState(_s36);
        }
    }

    bool _success = result121;

    memoize_suffix[_thisPos] = ParseResult<PPegExpr >(_success, ret, _b.saveState());

    stackTrace.pop();
    return _success;
}


bool PegParser::prefix(Buffer &_b, PPegExpr &ret, Error &error)
{
    int _thisPos = _b.getP2();

    if(memoize_prefix.contains(_thisPos))
    {
        ret=memoize_prefix[_thisPos].value;
        return memoize_prefix[_thisPos].getValues(_b);
    }

    QString _dummy_27;
    QString _dummy_28;
    QString _dummy_29;
    PPegExpr p1;
    PPegExpr p2;
    PPegExpr p3;
    stackTrace.push(QString("prefix")+"   "+_b.remainder().mid(10));

    bool result126=false;
    bool _cut24=false;
    BufferState _s38 = _b.saveState();
    if(!result126 && !_cut24)
    {
        bool result127=true;
        BufferState _s39 = _b.saveState();
        do
        {

            bool result128=NOT(_b, _dummy_27, error);

            result127 = result127 && result128;
            if(!result127)
            {
                _b.restoreState(_s39);
                break;
            };
            _cut24=true;
            result127 = result127 && true;
            if(!result127)
            {
                _b.restoreState(_s39);
                break;
            };

            bool result129=prim(_b, p1, error);
            if(result129)
            {
                ret= new PegNot(p1);
            }

            result127 = result127 && result129;
            if(!result127)
            {
                _b.restoreState(_s39);
                break;
            };

        } while(false);
        result126 = result126 || result127;
        if(!result126)
        {
            _b.restoreState(_s38);
        }
    }
    if(!result126 && !_cut24)
    {
        bool result130=true;
        BufferState _s40 = _b.saveState();
        do
        {

            bool result131=AND(_b, _dummy_28, error);

            result130 = result130 && result131;
            if(!result130)
            {
                _b.restoreState(_s40);
                break;
            };
            BufferState _s41 = _b.saveState();

            bool result133=LBRACE(_b, _dummy_29, error);

            bool result132 = !(result133);
            _b.restoreState(_s41);
            result130 = result130 && result132;
            if(!result130)
            {
                _b.restoreState(_s40);
                break;
            };
            _cut24=true;
            result130 = result130 && true;
            if(!result130)
            {
                _b.restoreState(_s40);
                break;
            };

            bool result134=prim(_b, p2, error);
            if(result134)
            {
                ret = new PegAndPredicate(p2);
            }

            result130 = result130 && result134;
            if(!result130)
            {
                _b.restoreState(_s40);
                break;
            };

        } while(false);
        result126 = result126 || result130;
        if(!result126)
        {
            _b.restoreState(_s38);
        }
    }
    if(!result126 && !_cut24)
    {

        bool result135=prim(_b, p3, error);
        if(result135)
        {
            ret=p3;
        }

        result126 = result126 || result135;
        if(!result126)
        {
            _b.restoreState(_s38);
        }
    }

    bool _success = result126;

    memoize_prefix[_thisPos] = ParseResult<PPegExpr >(_success, ret, _b.saveState());

    stackTrace.pop();
    return _success;
}


bool PegParser::prim(Buffer &_b, PPegExpr &ret, Error &error)
{
    int _thisPos = _b.getP2();

    if(memoize_prim.contains(_thisPos))
    {
        ret=memoize_prim[_thisPos].value;
        return memoize_prim[_thisPos].getValues(_b);
    }

    QString _dummy_30;
    QString _dummy_31;
    QString _dummy_32;
    QString c1;
    QString cond;
    PPegExpr p1;
    QString v1;
    stackTrace.push(QString("prim")+"   "+_b.remainder().mid(10));

    bool result136=false;
    bool _cut25=false;
    BufferState _s42 = _b.saveState();
    if(!result136 && !_cut25)
    {

        bool result137=CUT(_b, _dummy_30, error);
        if(result137)
        {
            ret = new PegCut();
        }

        result136 = result136 || result137;
        if(!result136)
        {
            _b.restoreState(_s42);
        }
    }
    if(!result136 && !_cut25)
    {
        bool result138=true;
        BufferState _s43 = _b.saveState();
        do
        {

            bool result139=AND(_b, _dummy_31, error);

            result138 = result138 && result139;
            if(!result138)
            {
                _b.restoreState(_s43);
                break;
            };

            bool result140=code(_b, cond, error);
            if(result140)
            {
                ret = new PegSemanticPredicate(cond);
            }

            result138 = result138 && result140;
            if(!result138)
            {
                _b.restoreState(_s43);
                break;
            };

        } while(false);
        result136 = result136 || result138;
        if(!result136)
        {
            _b.restoreState(_s42);
        }
    }
    if(!result136 && !_cut25)
    {
        bool result141=true;
        BufferState _s44 = _b.saveState();
        do
        {

            bool result142=primprefix(_b, p1, error);

            result141 = result141 && result142;
            if(!result141)
            {
                _b.restoreState(_s44);
                break;
            };
            bool result143=false;
            bool _cut26=false;
            BufferState _s45 = _b.saveState();
            if(!result143 && !_cut26)
            {
                bool result144=true;
                BufferState _s46 = _b.saveState();
                do
                {

                    bool result145=COLON(_b, _dummy_32, error);

                    result144 = result144 && result145;
                    if(!result144)
                    {
                        _b.restoreState(_s46);
                        break;
                    };

                    bool result146=identifier(_b, v1, error);
                    if(result146)
                    {
                        p1->varName=v1;
                    }

                    result144 = result144 && result146;
                    if(!result144)
                    {
                        _b.restoreState(_s46);
                        break;
                    };

                } while(false);
                result143 = result143 || result144;
                if(!result143)
                {
                    _b.restoreState(_s45);
                }
            }
            if(!result143 && !_cut26)
            {
                bool result147 = _matchStr(_b, "", error);
                result143 = result143 || result147;
                if(!result143)
                {
                    _b.restoreState(_s45);
                }
            }
            result141 = result141 && result143;
            if(!result141)
            {
                _b.restoreState(_s44);
                break;
            };
            bool result148=false;
            bool _cut27=false;
            BufferState _s47 = _b.saveState();
            if(!result148 && !_cut27)
            {

                bool result149=code(_b, c1, error);
                if(result149)
                {
                    p1->code=c1;
                }

                result148 = result148 || result149;
                if(!result148)
                {
                    _b.restoreState(_s47);
                }
            }
            if(!result148 && !_cut27)
            {
                bool result150 = _matchStr(_b, "", error);
                result148 = result148 || result150;
                if(!result148)
                {
                    _b.restoreState(_s47);
                }
            }
            result141 = result141 && result148;
            if(!result141)
            {
                _b.restoreState(_s44);
                break;
            };
            bool result151 = _matchStr(_b, "", error);
            if(result151)
            {
                ret=p1;
            };
            result141 = result141 && result151;
            if(!result141)
            {
                _b.restoreState(_s44);
                break;
            };

        } while(false);
        result136 = result136 || result141;
        if(!result136)
        {
            _b.restoreState(_s42);
        }
    }

    bool _success = result136;

    memoize_prim[_thisPos] = ParseResult<PPegExpr >(_success, ret, _b.saveState());

    stackTrace.pop();
    return _success;
}


bool PegParser::primprefix(Buffer &_b, PPegExpr &ret, Error &error)
{
    int _thisPos = _b.getP2();

    if(memoize_primprefix.contains(_thisPos))
    {
        ret=memoize_primprefix[_thisPos].value;
        return memoize_primprefix[_thisPos].getValues(_b);
    }

    QString _dummy_33;
    QString _dummy_34;
    QString _dummy_35;
    QString _dummy_36;
    QString _dummy_37;
    QString _dummy_38;
    QString _dummy_39;
    QString _dummy_40;
    QString _dummy_41;
    QString _dummy_42;
    QString _dummy_43;
    QString _dummy_44;
    PPegChoice e1;
    PPegChoice e2;
    PPegChoice e3;
    PPegExpr e4;
    PPegExpr e5;
    PegNonterminal * inv0;
    QString s1;
    QString sl0;
    stackTrace.push(QString("primprefix")+"   "+_b.remainder().mid(10));

    bool result152=false;
    bool _cut28=false;
    BufferState _s48 = _b.saveState();
    if(!result152 && !_cut28)
    {
        bool result153=true;
        BufferState _s49 = _b.saveState();
        do
        {

            bool result154=LPAREN(_b, _dummy_33, error);

            result153 = result153 && result154;
            if(!result153)
            {
                _b.restoreState(_s49);
                break;
            };

            bool result155=expr(_b, e1, error);

            result153 = result153 && result155;
            if(!result153)
            {
                _b.restoreState(_s49);
                break;
            };

            bool result156=RPAREN(_b, _dummy_34, error);

            result153 = result153 && result156;
            if(!result153)
            {
                _b.restoreState(_s49);
                break;
            };

            bool result157=ASTERISK(_b, _dummy_35, error);
            if(result157)
            {
                ret=new PegLoop(e1);
            }

            result153 = result153 && result157;
            if(!result153)
            {
                _b.restoreState(_s49);
                break;
            };

        } while(false);
        result152 = result152 || result153;
        if(!result152)
        {
            _b.restoreState(_s48);
        }
    }
    if(!result152 && !_cut28)
    {
        bool result158=true;
        BufferState _s50 = _b.saveState();
        do
        {

            bool result159=LPAREN(_b, _dummy_36, error);

            result158 = result158 && result159;
            if(!result158)
            {
                _b.restoreState(_s50);
                break;
            };

            bool result160=expr(_b, e2, error);

            result158 = result158 && result160;
            if(!result158)
            {
                _b.restoreState(_s50);
                break;
            };

            bool result161=RPAREN(_b, _dummy_37, error);
            if(result161)
            {
                ret=e2;
            }

            result158 = result158 && result161;
            if(!result158)
            {
                _b.restoreState(_s50);
                break;
            };

        } while(false);
        result152 = result152 || result158;
        if(!result152)
        {
            _b.restoreState(_s48);
        }
    }
    if(!result152 && !_cut28)
    {

        bool result162=strlit(_b, s1, error);
        if(result162)
        {
            ret=new PegStr(s1);
        }

        result152 = result152 || result162;
        if(!result152)
        {
            _b.restoreState(_s48);
        }
    }
    if(!result152 && !_cut28)
    {

        bool result163=invokation(_b, inv0, error);
        if(result163)
        {
            ret = inv0;
        }

        result152 = result152 || result163;
        if(!result152)
        {
            _b.restoreState(_s48);
        }
    }
    if(!result152 && !_cut28)
    {

        bool result164=DOT(_b, _dummy_38, error);
        if(result164)
        {
            ret = new PegAnyChar();
        }

        result152 = result152 || result164;
        if(!result152)
        {
            _b.restoreState(_s48);
        }
    }
    if(!result152 && !_cut28)
    {
        bool result165=true;
        BufferState _s51 = _b.saveState();
        do
        {

            bool result166=SNIPPET(_b, _dummy_39, error);

            result165 = result165 && result166;
            if(!result165)
            {
                _b.restoreState(_s51);
                break;
            };

            bool result167=LPAREN(_b, _dummy_40, error);

            result165 = result165 && result167;
            if(!result165)
            {
                _b.restoreState(_s51);
                break;
            };

            bool result168=expr(_b, e3, error);

            result165 = result165 && result168;
            if(!result165)
            {
                _b.restoreState(_s51);
                break;
            };

            bool result169=RPAREN(_b, _dummy_41, error);
            if(result169)
            {
                ret = new PegSnippet(e3);
            }

            result165 = result165 && result169;
            if(!result165)
            {
                _b.restoreState(_s51);
                break;
            };

        } while(false);
        result152 = result152 || result165;
        if(!result152)
        {
            _b.restoreState(_s48);
        }
    }
    if(!result152 && !_cut28)
    {

        bool result170=special(_b, e4, error);
        if(result170)
        {
            ret = e4;
        }

        result152 = result152 || result170;
        if(!result152)
        {
            _b.restoreState(_s48);
        }
    }
    if(!result152 && !_cut28)
    {

        bool result171=application(_b, e5, error);
        if(result171)
        {
            ret = e5;
        }

        result152 = result152 || result171;
        if(!result152)
        {
            _b.restoreState(_s48);
        }
    }
    if(!result152 && !_cut28)
    {
        bool result172=true;
        BufferState _s52 = _b.saveState();
        do
        {
            bool result173 = _matchStr(_b, "_Error", error);
            result172 = result172 && result173;
            if(!result172)
            {
                _b.restoreState(_s52);
                break;
            };

            bool result174=spacing(_b, _dummy_42, error);

            result172 = result172 && result174;
            if(!result172)
            {
                _b.restoreState(_s52);
                break;
            };

            bool result175=LPAREN(_b, _dummy_43, error);

            result172 = result172 && result175;
            if(!result172)
            {
                _b.restoreState(_s52);
                break;
            };

            bool result176=strlit(_b, sl0, error);

            result172 = result172 && result176;
            if(!result172)
            {
                _b.restoreState(_s52);
                break;
            };

            bool result177=RPAREN(_b, _dummy_44, error);
            if(result177)
            {
                ret = new PegError(sl0);
            }

            result172 = result172 && result177;
            if(!result172)
            {
                _b.restoreState(_s52);
                break;
            };

        } while(false);
        result152 = result152 || result172;
        if(!result152)
        {
            _b.restoreState(_s48);
        }
    }

    bool _success = result152;

    memoize_primprefix[_thisPos] = ParseResult<PPegExpr >(_success, ret, _b.saveState());

    stackTrace.pop();
    return _success;
}


bool PegParser::invokation(Buffer &_b, PegNonterminal * &ret, Error &error)
{
    int _thisPos = _b.getP2();

    if(memoize_invokation.contains(_thisPos))
    {
        ret=memoize_invokation[_thisPos].value;
        return memoize_invokation[_thisPos].getValues(_b);
    }

    QVector < PegValue * > arg0;
    QString i1;
    QVector < PegType * > ta0;
    stackTrace.push(QString("invokation")+"   "+_b.remainder().mid(10));

    bool result178=true;
    BufferState _s53 = _b.saveState();
    do
    {

        bool result179=identifier(_b, i1, error);

        result178 = result178 && result179;
        if(!result178)
        {
            _b.restoreState(_s53);
            break;
        };

        bool result180=templateargs(_b, ta0, error);

        result178 = result178 && result180;
        if(!result178)
        {
            _b.restoreState(_s53);
            break;
        };

        bool result181=arglist(_b, arg0, error);
        if(result181)
        {
            ret=new PegNonterminal(i1, arg0, ta0);
        }

        result178 = result178 && result181;
        if(!result178)
        {
            _b.restoreState(_s53);
            break;
        };

    } while(false);

    bool _success = result178;

    memoize_invokation[_thisPos] = ParseResult<PegNonterminal * >(_success, ret, _b.saveState());

    stackTrace.pop();
    return _success;
}


bool PegParser::arglist(Buffer &_b, QVector < PegValue * > &ret, Error &error)
{
    int _thisPos = _b.getP2();

    if(memoize_arglist.contains(_thisPos))
    {
        ret=memoize_arglist[_thisPos].value;
        return memoize_arglist[_thisPos].getValues(_b);
    }

    QString _dummy_45;
    QString _dummy_46;
    QString _dummy_47;
    PegValue * a0;
    PegValue * a1;
    stackTrace.push(QString("arglist")+"   "+_b.remainder().mid(10));
    ret.clear();
    bool result182=false;
    bool _cut29=false;
    BufferState _s54 = _b.saveState();
    if(!result182 && !_cut29)
    {
        bool result183=true;
        BufferState _s55 = _b.saveState();
        do
        {

            bool result184=LBRACKET(_b, _dummy_45, error);

            result183 = result183 && result184;
            if(!result183)
            {
                _b.restoreState(_s55);
                break;
            };

            bool result185=pegArg(_b, a0, error);
            if(result185)
            {
                ret.append(a0);
            }

            result183 = result183 && result185;
            if(!result183)
            {
                _b.restoreState(_s55);
                break;
            };
            bool result186 = true;
            bool _cut30 = false;
            while(true)
            {
                _cut30= false;
                BufferState _s = _b.saveState();
                bool result187=true;
                BufferState _s56 = _b.saveState();
                do
                {

                    bool result188=COMMA(_b, _dummy_46, error);

                    result187 = result187 && result188;
                    if(!result187)
                    {
                        _b.restoreState(_s56);
                        break;
                    };

                    bool result189=pegArg(_b, a1, error);
                    if(result189)
                    {
                        ret.append(a1);
                    }

                    result187 = result187 && result189;
                    if(!result187)
                    {
                        _b.restoreState(_s56);
                        break;
                    };

                } while(false);
                if(!(result187))
                {
                    _b.restoreState(_s);
                    if(_cut30)
                    {
                        result186 = false;
                    }
                    break;
                };
            }
            result183 = result183 && result186;
            if(!result183)
            {
                _b.restoreState(_s55);
                break;
            };

            bool result190=RBRACKET(_b, _dummy_47, error);

            result183 = result183 && result190;
            if(!result183)
            {
                _b.restoreState(_s55);
                break;
            };

        } while(false);
        result182 = result182 || result183;
        if(!result182)
        {
            _b.restoreState(_s54);
        }
    }
    if(!result182 && !_cut29)
    {
        bool result191 = _matchStr(_b, "", error);
        result182 = result182 || result191;
        if(!result182)
        {
            _b.restoreState(_s54);
        }
    }

    bool _success = result182;

    memoize_arglist[_thisPos] = ParseResult<QVector < PegValue * > >(_success, ret, _b.saveState());

    stackTrace.pop();
    return _success;
}


bool PegParser::pegArg(Buffer &_b, PegValue * &ret, Error &error)
{
    int _thisPos = _b.getP2();

    if(memoize_pegArg.contains(_thisPos))
    {
        ret=memoize_pegArg[_thisPos].value;
        return memoize_pegArg[_thisPos].getValues(_b);
    }

    QString _dummy_48;
    QString i0;
    QString id0;
    QString s0;
    stackTrace.push(QString("pegArg")+"   "+_b.remainder().mid(10));

    bool result192=false;
    bool _cut31=false;
    BufferState _s57 = _b.saveState();
    if(!result192 && !_cut31)
    {

        bool result193=identifier(_b, i0, error);
        if(result193)
        {
            ret = new PegIdArg(i0);
        }

        result192 = result192 || result193;
        if(!result192)
        {
            _b.restoreState(_s57);
        }
    }
    if(!result192 && !_cut31)
    {

        bool result194=strlit(_b, s0, error);
        if(result194)
        {
            ret = new PegStringArg("\""+s0+"\"");
        }

        result192 = result192 || result194;
        if(!result192)
        {
            _b.restoreState(_s57);
        }
    }
    if(!result192 && !_cut31)
    {
        bool result195=true;
        BufferState _s58 = _b.saveState();
        do
        {

            bool result196=SHARPQUOTE(_b, _dummy_48, error);

            result195 = result195 && result196;
            if(!result195)
            {
                _b.restoreState(_s58);
                break;
            };

            bool result197=identifier(_b, id0, error);
            if(result197)
            {
                ret = new PegSharpQuote(id0);
            }

            result195 = result195 && result197;
            if(!result195)
            {
                _b.restoreState(_s58);
                break;
            };

        } while(false);
        result192 = result192 || result195;
        if(!result192)
        {
            _b.restoreState(_s57);
        }
    }

    bool _success = result192;

    memoize_pegArg[_thisPos] = ParseResult<PegValue * >(_success, ret, _b.saveState());

    stackTrace.pop();
    return _success;
}


bool PegParser::application(Buffer &_b, PPegExpr &ret, Error &error)
{
    int _thisPos = _b.getP2();

    if(memoize_application.contains(_thisPos))
    {
        ret=memoize_application[_thisPos].value;
        return memoize_application[_thisPos].getValues(_b);
    }

    QString _dummy_49;
    QString _dummy_50;
    QString _dummy_51;
    QString _dummy_52;
    QString _dummy_53;
    PegValue * pa0;
    PegType * t;
    stackTrace.push(QString("application")+"   "+_b.remainder().mid(10));

    bool result198=true;
    BufferState _s59 = _b.saveState();
    do
    {
        bool result199 = _matchStr(_b, "_Apply", error);
        result198 = result198 && result199;
        if(!result198)
        {
            _b.restoreState(_s59);
            break;
        };

        bool result200=spacing(_b, _dummy_49, error);

        result198 = result198 && result200;
        if(!result198)
        {
            _b.restoreState(_s59);
            break;
        };

        bool result201=LT(_b, _dummy_50, error);

        result198 = result198 && result201;
        if(!result198)
        {
            _b.restoreState(_s59);
            break;
        };

        bool result202=type(_b, t, error);

        result198 = result198 && result202;
        if(!result198)
        {
            _b.restoreState(_s59);
            break;
        };

        bool result203=GT(_b, _dummy_51, error);

        result198 = result198 && result203;
        if(!result198)
        {
            _b.restoreState(_s59);
            break;
        };

        bool result204=LPAREN(_b, _dummy_52, error);

        result198 = result198 && result204;
        if(!result198)
        {
            _b.restoreState(_s59);
            break;
        };

        bool result205=pegArg(_b, pa0, error);

        result198 = result198 && result205;
        if(!result198)
        {
            _b.restoreState(_s59);
            break;
        };

        bool result206=RPAREN(_b, _dummy_53, error);
        if(result206)
        {
            ret = new PegApply(t, pa0, QVector<PegValue *>());

        }

        result198 = result198 && result206;
        if(!result198)
        {
            _b.restoreState(_s59);
            break;
        };

    } while(false);

    bool _success = result198;

    memoize_application[_thisPos] = ParseResult<PPegExpr >(_success, ret, _b.saveState());

    stackTrace.pop();
    return _success;
}


bool PegParser::special(Buffer &_b, PPegExpr &ret, Error &error)
{
    int _thisPos = _b.getP2();

    if(memoize_special.contains(_thisPos))
    {
        ret=memoize_special[_thisPos].value;
        return memoize_special[_thisPos].getValues(_b);
    }

    QString _dummy_54;
    PPegExpr t;
    stackTrace.push(QString("special")+"   "+_b.remainder().mid(10));

    bool result207=true;
    BufferState _s60 = _b.saveState();
    do
    {

        bool result208=specialtoken(_b, t, error);
        if(result208)
        {
            ret=t;
        }

        result207 = result207 && result208;
        if(!result207)
        {
            _b.restoreState(_s60);
            break;
        };

        bool result209=spacing(_b, _dummy_54, error);

        result207 = result207 && result209;
        if(!result207)
        {
            _b.restoreState(_s60);
            break;
        };

    } while(false);

    bool _success = result207;

    memoize_special[_thisPos] = ParseResult<PPegExpr >(_success, ret, _b.saveState());

    stackTrace.pop();
    return _success;
}


bool PegParser::specialtoken(Buffer &_b, PPegExpr &ret, Error &error)
{
    int _thisPos = _b.getP2();

    if(memoize_specialtoken.contains(_thisPos))
    {
        ret=memoize_specialtoken[_thisPos].value;
        return memoize_specialtoken[_thisPos].getValues(_b);
    }


    stackTrace.push(QString("specialtoken")+"   "+_b.remainder().mid(10));

    bool result210=false;
    bool _cut32=false;
    BufferState _s61 = _b.saveState();
    if(!result210 && !_cut32)
    {
        bool result211 = _matchStr(_b, "_Eof", error);
        if(result211)
        {
            ret = new PegEof();
        };
        result210 = result210 || result211;
        if(!result210)
        {
            _b.restoreState(_s61);
        }
    }
    if(!result210 && !_cut32)
    {
        bool result212 = _matchStr(_b, "_Alpha", error);
        if(result212)
        {
            ret = new PegAlpha();
        };
        result210 = result210 || result212;
        if(!result210)
        {
            _b.restoreState(_s61);
        }
    }
    if(!result210 && !_cut32)
    {
        bool result213 = _matchStr(_b, "_Letter", error);
        if(result213)
        {
            ret = new PegLetter();
        };
        result210 = result210 || result213;
        if(!result210)
        {
            _b.restoreState(_s61);
        }
    }
    if(!result210 && !_cut32)
    {
        bool result214 = _matchStr(_b, "_Digit", error);
        if(result214)
        {
            ret = new PegDigit();
        };
        result210 = result210 || result214;
        if(!result210)
        {
            _b.restoreState(_s61);
        }
    }

    bool _success = result210;

    memoize_specialtoken[_thisPos] = ParseResult<PPegExpr >(_success, ret, _b.saveState());

    stackTrace.pop();
    return _success;
}


bool PegParser::strlit(Buffer &_b, QString &ret, Error &error)
{
    int _thisPos = _b.getP2();

    if(memoize_strlit.contains(_thisPos))
    {
        ret=memoize_strlit[_thisPos].value;
        return memoize_strlit[_thisPos].getValues(_b);
    }

    QString _dummy_55;
    QString _dummy_56;
    QString _dummy_57;
    QString nq;
    stackTrace.push(QString("strlit")+"   "+_b.remainder().mid(10));
    ret = "";
    bool result215=true;
    BufferState _s62 = _b.saveState();
    do
    {

        bool result216=quote(_b, _dummy_55, error);

        result215 = result215 && result216;
        if(!result215)
        {
            _b.restoreState(_s62);
            break;
        };
        bool result217 = true;
        bool _cut33 = false;
        while(true)
        {
            _cut33= false;
            BufferState _s = _b.saveState();
            bool result218=false;
            bool _cut34=false;
            BufferState _s63 = _b.saveState();
            if(!result218 && !_cut34)
            {
                bool result219 = _matchStr(_b, "\\\"", error);
                if(result219)
                {
                    ret+="\\\"";
                };
                result218 = result218 || result219;
                if(!result218)
                {
                    _b.restoreState(_s63);
                }
            }
            if(!result218 && !_cut34)
            {

                bool result220=nonquote(_b, nq, error);
                if(result220)
                {
                    ret+=nq;
                }

                result218 = result218 || result220;
                if(!result218)
                {
                    _b.restoreState(_s63);
                }
            }
            if(!(result218))
            {
                _b.restoreState(_s);
                if(_cut33)
                {
                    result217 = false;
                }
                break;
            };
        }
        result215 = result215 && result217;
        if(!result215)
        {
            _b.restoreState(_s62);
            break;
        };

        bool result221=quote(_b, _dummy_56, error);

        result215 = result215 && result221;
        if(!result215)
        {
            _b.restoreState(_s62);
            break;
        };

        bool result222=spacing(_b, _dummy_57, error);

        result215 = result215 && result222;
        if(!result215)
        {
            _b.restoreState(_s62);
            break;
        };

    } while(false);

    bool _success = result215;

    memoize_strlit[_thisPos] = ParseResult<QString >(_success, ret, _b.saveState());

    stackTrace.pop();
    return _success;
}


bool PegParser::charlit(Buffer &_b, QString &ret, Error &error)
{
    int _thisPos = _b.getP2();

    if(memoize_charlit.contains(_thisPos))
    {
        ret=memoize_charlit[_thisPos].value;
        return memoize_charlit[_thisPos].getValues(_b);
    }

    QString _dummy_58;
    Token c;
    Token c2;
    stackTrace.push(QString("charlit")+"   "+_b.remainder().mid(10));

    bool result223=true;
    BufferState _s64 = _b.saveState();
    do
    {
        bool result224 = _matchStr(_b, "'", error);
        result223 = result223 && result224;
        if(!result223)
        {
            _b.restoreState(_s64);
            break;
        };
        bool result225=true;
        BufferState _s65 = _b.saveState();
        do
        {
            bool result226 = _matchStr(_b, "\'", error);
            result225 = result225 && result226;
            if(!result225)
            {
                _b.restoreState(_s65);
                break;
            };
            bool result227 =_matchAnyChar(_b, c2, error);
            if(result227)
            {
                ret+=c2.Lexeme;
            };
            result225 = result225 && result227;
            if(!result225)
            {
                _b.restoreState(_s65);
                break;
            };
            BufferState _s66 = _b.saveState();
            bool result229 = _matchStr(_b, "'", error);
            bool result228 = !(result229);
            _b.restoreState(_s66);
            result225 = result225 && result228;
            if(!result225)
            {
                _b.restoreState(_s65);
                break;
            };
            bool result230 =_matchAnyChar(_b, c, error);
            if(result230)
            {
                ret+=c.Lexeme;
            };
            result225 = result225 && result230;
            if(!result225)
            {
                _b.restoreState(_s65);
                break;
            };

        } while(false);
        result223 = result223 && result225;
        if(!result223)
        {
            _b.restoreState(_s64);
            break;
        };
        bool result231 = _matchStr(_b, "'", error);
        result223 = result223 && result231;
        if(!result223)
        {
            _b.restoreState(_s64);
            break;
        };

        bool result232=spacing(_b, _dummy_58, error);

        result223 = result223 && result232;
        if(!result223)
        {
            _b.restoreState(_s64);
            break;
        };

    } while(false);

    bool _success = result223;

    memoize_charlit[_thisPos] = ParseResult<QString >(_success, ret, _b.saveState());

    stackTrace.pop();
    return _success;
}


bool PegParser::code(Buffer &_b, QString &ret, Error &error)
{
    int _thisPos = _b.getP2();

    if(memoize_code.contains(_thisPos))
    {
        ret=memoize_code[_thisPos].value;
        return memoize_code[_thisPos].getValues(_b);
    }

    QString _dummy_59;
    QString _dummy_60;
    QString _dummy_61;
    QString _dummy_62;
    QString _dummy_63;
    Token c;
    Token snp;
    stackTrace.push(QString("code")+"   "+_b.remainder().mid(10));

    bool result233=true;
    BufferState _s67 = _b.saveState();
    do
    {

        bool result234=LBRACE(_b, _dummy_59, error);

        result233 = result233 && result234;
        if(!result233)
        {
            _b.restoreState(_s67);
            break;
        };
        BufferState _spre0 = _b.saveState();
        bool result236=true;
        BufferState _s68 = _b.saveState();
        do
        {
            bool result237 = true;
            bool _cut35 = false;
            while(true)
            {
                _cut35= false;
                BufferState _s = _b.saveState();
                bool result238=false;
                bool _cut36=false;
                BufferState _s69 = _b.saveState();
                if(!result238 && !_cut36)
                {

                    bool result239=strlit(_b, _dummy_60, error);

                    result238 = result238 || result239;
                    if(!result238)
                    {
                        _b.restoreState(_s69);
                    }
                }
                if(!result238 && !_cut36)
                {

                    bool result240=code(_b, _dummy_61, error);

                    result238 = result238 || result240;
                    if(!result238)
                    {
                        _b.restoreState(_s69);
                    }
                }
                if(!result238 && !_cut36)
                {
                    bool result241=true;
                    BufferState _s70 = _b.saveState();
                    do
                    {
                        BufferState _s71 = _b.saveState();
                        bool result243 = _matchStr(_b, "}", error);
                        bool result242 = !(result243);
                        _b.restoreState(_s71);
                        result241 = result241 && result242;
                        if(!result241)
                        {
                            _b.restoreState(_s70);
                            break;
                        };
                        bool result244 =_matchAnyChar(_b, c, error);
                        result241 = result241 && result244;
                        if(!result241)
                        {
                            _b.restoreState(_s70);
                            break;
                        };

                    } while(false);
                    result238 = result238 || result241;
                    if(!result238)
                    {
                        _b.restoreState(_s69);
                    }
                }
                if(!(result238))
                {
                    _b.restoreState(_s);
                    if(_cut35)
                    {
                        result237 = false;
                    }
                    break;
                };
            }
            result236 = result236 && result237;
            if(!result236)
            {
                _b.restoreState(_s68);
                break;
            };

            bool result245=spacing(_b, _dummy_62, error);

            result236 = result236 && result245;
            if(!result236)
            {
                _b.restoreState(_s68);
                break;
            };

        } while(false);
        bool result235=result236;
        if(result235)
        {
            BufferState _spost0= _b.saveState();
            snp = getRange(_b, _spre0, _spost0);
        }
        if(result235)
        {
            ret = snp.Lexeme;
        }
        result233 = result233 && result235;
        if(!result233)
        {
            _b.restoreState(_s67);
            break;
        };

        bool result246=RBRACE(_b, _dummy_63, error);

        result233 = result233 && result246;
        if(!result233)
        {
            _b.restoreState(_s67);
            break;
        };

    } while(false);

    bool _success = result233;

    memoize_code[_thisPos] = ParseResult<QString >(_success, ret, _b.saveState());

    stackTrace.pop();
    return _success;
}


bool PegParser::quote(Buffer &_b, QString &ret, Error &error)
{
    int _thisPos = _b.getP2();

    if(memoize_quote.contains(_thisPos))
    {
        ret=memoize_quote[_thisPos].value;
        return memoize_quote[_thisPos].getValues(_b);
    }


    stackTrace.push(QString("quote")+"   "+_b.remainder().mid(10));

    bool result247 = _matchStr(_b, "\"", error);

    bool _success = result247;

    memoize_quote[_thisPos] = ParseResult<QString >(_success, ret, _b.saveState());

    stackTrace.pop();
    return _success;
}


bool PegParser::identifier(Buffer &_b, QString &ret, Error &error)
{
    int _thisPos = _b.getP2();

    if(memoize_identifier.contains(_thisPos))
    {
        ret=memoize_identifier[_thisPos].value;
        return memoize_identifier[_thisPos].getValues(_b);
    }

    QString kid;
    QString nid;
    stackTrace.push(QString("identifier")+"   "+_b.remainder().mid(10));

    bool result248=false;
    bool _cut37=false;
    BufferState _s72 = _b.saveState();
    if(!result248 && !_cut37)
    {
        bool result249=true;
        BufferState _s73 = _b.saveState();
        do
        {
            result249 = result249 && isCodeInKalimat ;
            if(!result249)
            {
                _b.restoreState(_s73);
                break;
            };
            _cut37=true;
            result249 = result249 && true;
            if(!result249)
            {
                _b.restoreState(_s73);
                break;
            };

            bool result250=kalimatdentifier(_b, kid, error);
            if(result250)
            {
                ret = kid;
            }

            result249 = result249 && result250;
            if(!result249)
            {
                _b.restoreState(_s73);
                break;
            };

        } while(false);
        result248 = result248 || result249;
        if(!result248)
        {
            _b.restoreState(_s72);
        }
    }
    if(!result248 && !_cut37)
    {

        bool result251=normalidentifier(_b, nid, error);
        if(result251)
        {
            ret = nid;
        }

        result248 = result248 || result251;
        if(!result248)
        {
            _b.restoreState(_s72);
        }
    }

    bool _success = result248;

    memoize_identifier[_thisPos] = ParseResult<QString >(_success, ret, _b.saveState());

    stackTrace.pop();
    return _success;
}


bool PegParser::normalidentifier(Buffer &_b, QString &ret, Error &error)
{
    int _thisPos = _b.getP2();

    if(memoize_normalidentifier.contains(_thisPos))
    {
        ret=memoize_normalidentifier[_thisPos].value;
        return memoize_normalidentifier[_thisPos].getValues(_b);
    }

    QString _dummy_64;
    Token a;
    Token b;
    stackTrace.push(QString("normalidentifier")+"   "+_b.remainder().mid(10));

    bool result252=true;
    BufferState _s74 = _b.saveState();
    do
    {
        bool result253 =_matchAlpha(_b, a, error);
        if(result253)
        {
            ret=a.Lexeme;
        };
        result252 = result252 && result253;
        if(!result252)
        {
            _b.restoreState(_s74);
            break;
        };
        bool result254 = true;
        bool _cut38 = false;
        while(true)
        {
            _cut38= false;
            BufferState _s = _b.saveState();
            bool result255 =_matchAlpha(_b, b, error);
            if(result255)
            {
                ret+=b.Lexeme;
            };
            if(!(result255))
            {
                _b.restoreState(_s);
                if(_cut38)
                {
                    result254 = false;
                }
                break;
            };
        }
        result252 = result252 && result254;
        if(!result252)
        {
            _b.restoreState(_s74);
            break;
        };

        bool result256=spacing(_b, _dummy_64, error);

        result252 = result252 && result256;
        if(!result252)
        {
            _b.restoreState(_s74);
            break;
        };

    } while(false);

    bool _success = result252;

    memoize_normalidentifier[_thisPos] = ParseResult<QString >(_success, ret, _b.saveState());

    stackTrace.pop();
    return _success;
}


bool PegParser::kalimatdentifier(Buffer &_b, QString &ret, Error &error)
{
    int _thisPos = _b.getP2();

    if(memoize_kalimatdentifier.contains(_thisPos))
    {
        ret=memoize_kalimatdentifier[_thisPos].value;
        return memoize_kalimatdentifier[_thisPos].getValues(_b);
    }

    QString _dummy_65;
    Token a;
    Token b;
    stackTrace.push(QString("kalimatdentifier")+"   "+_b.remainder().mid(10));

    bool result257=true;
    BufferState _s75 = _b.saveState();
    do
    {
        bool result258 =_matchAlpha(_b, a, error);
        if(result258)
        {
            ret=a.Lexeme;
        };
        result257 = result257 && result258;
        if(!result257)
        {
            _b.restoreState(_s75);
            break;
        };
        bool result259 = true;
        bool _cut39 = false;
        while(true)
        {
            _cut39= false;
            BufferState _s = _b.saveState();
            bool result260=false;
            bool _cut40=false;
            BufferState _s76 = _b.saveState();
            if(!result260 && !_cut40)
            {
                bool result261 =_matchAlpha(_b, b, error);
                if(result261)
                {
                    ret+=b.Lexeme;
                };
                result260 = result260 || result261;
                if(!result260)
                {
                    _b.restoreState(_s76);
                }
            }
            if(!result260 && !_cut40)
            {
                bool result262 = _matchStr(_b, "_", error);
                if(result262)
                {
                    ret+= ".";
                };
                result260 = result260 || result262;
                if(!result260)
                {
                    _b.restoreState(_s76);
                }
            }
            if(!(result260))
            {
                _b.restoreState(_s);
                if(_cut39)
                {
                    result259 = false;
                }
                break;
            };
        }
        result257 = result257 && result259;
        if(!result257)
        {
            _b.restoreState(_s75);
            break;
        };

        bool result263=spacing(_b, _dummy_65, error);

        result257 = result257 && result263;
        if(!result257)
        {
            _b.restoreState(_s75);
            break;
        };

    } while(false);

    bool _success = result257;

    memoize_kalimatdentifier[_thisPos] = ParseResult<QString >(_success, ret, _b.saveState());

    stackTrace.pop();
    return _success;
}


bool PegParser::spacing(Buffer &_b, QString &ret, Error &error)
{
    int _thisPos = _b.getP2();

    if(memoize_spacing.contains(_thisPos))
    {
        ret=memoize_spacing[_thisPos].value;
        return memoize_spacing[_thisPos].getValues(_b);
    }


    stackTrace.push(QString("spacing")+"   "+_b.remainder().mid(10));

    bool result264 = true;
    bool _cut41 = false;
    while(true)
    {
        _cut41= false;
        BufferState _s = _b.saveState();
        bool result265=false;
        bool _cut42=false;
        BufferState _s77 = _b.saveState();
        if(!result265 && !_cut42)
        {
            bool result266 = _matchStr(_b, " ", error);
            result265 = result265 || result266;
            if(!result265)
            {
                _b.restoreState(_s77);
            }
        }
        if(!result265 && !_cut42)
        {
            bool result267 = _matchStr(_b, "\t", error);
            result265 = result265 || result267;
            if(!result265)
            {
                _b.restoreState(_s77);
            }
        }
        if(!result265 && !_cut42)
        {
            bool result268 = _matchStr(_b, "\r", error);
            result265 = result265 || result268;
            if(!result265)
            {
                _b.restoreState(_s77);
            }
        }
        if(!result265 && !_cut42)
        {
            bool result269 = _matchStr(_b, "\n", error);
            result265 = result265 || result269;
            if(!result265)
            {
                _b.restoreState(_s77);
            }
        }
        if(!(result265))
        {
            _b.restoreState(_s);
            if(_cut41)
            {
                result264 = false;
            }
            break;
        };
    }

    bool _success = result264;

    memoize_spacing[_thisPos] = ParseResult<QString >(_success, ret, _b.saveState());

    stackTrace.pop();
    return _success;
}


bool PegParser::COLON(Buffer &_b, QString &ret, Error &error)
{
    int _thisPos = _b.getP2();

    if(memoize_COLON.contains(_thisPos))
    {
        ret=memoize_COLON[_thisPos].value;
        return memoize_COLON[_thisPos].getValues(_b);
    }

    QString _dummy_66;
    stackTrace.push(QString("COLON")+"   "+_b.remainder().mid(10));

    bool result270=true;
    BufferState _s78 = _b.saveState();
    do
    {
        bool result271 = _matchStr(_b, ":", error);
        result270 = result270 && result271;
        if(!result270)
        {
            _b.restoreState(_s78);
            break;
        };

        bool result272=spacing(_b, _dummy_66, error);

        result270 = result270 && result272;
        if(!result270)
        {
            _b.restoreState(_s78);
            break;
        };

    } while(false);

    bool _success = result270;

    memoize_COLON[_thisPos] = ParseResult<QString >(_success, ret, _b.saveState());

    stackTrace.pop();
    return _success;
}


bool PegParser::ARROW(Buffer &_b, QString &ret, Error &error)
{
    int _thisPos = _b.getP2();

    if(memoize_ARROW.contains(_thisPos))
    {
        ret=memoize_ARROW[_thisPos].value;
        return memoize_ARROW[_thisPos].getValues(_b);
    }

    QString _dummy_67;
    stackTrace.push(QString("ARROW")+"   "+_b.remainder().mid(10));

    bool result273=true;
    BufferState _s79 = _b.saveState();
    do
    {
        bool result274 = _matchStr(_b, "->", error);
        result273 = result273 && result274;
        if(!result273)
        {
            _b.restoreState(_s79);
            break;
        };

        bool result275=spacing(_b, _dummy_67, error);

        result273 = result273 && result275;
        if(!result273)
        {
            _b.restoreState(_s79);
            break;
        };

    } while(false);

    bool _success = result273;

    memoize_ARROW[_thisPos] = ParseResult<QString >(_success, ret, _b.saveState());

    stackTrace.pop();
    return _success;
}


bool PegParser::LAMBDA(Buffer &_b, QString &ret, Error &error)
{
    int _thisPos = _b.getP2();

    if(memoize_LAMBDA.contains(_thisPos))
    {
        ret=memoize_LAMBDA[_thisPos].value;
        return memoize_LAMBDA[_thisPos].getValues(_b);
    }

    QString _dummy_68;
    stackTrace.push(QString("LAMBDA")+"   "+_b.remainder().mid(10));

    bool result276=true;
    BufferState _s80 = _b.saveState();
    do
    {
        bool result277 = _matchStr(_b, "=>", error);
        result276 = result276 && result277;
        if(!result276)
        {
            _b.restoreState(_s80);
            break;
        };

        bool result278=spacing(_b, _dummy_68, error);

        result276 = result276 && result278;
        if(!result276)
        {
            _b.restoreState(_s80);
            break;
        };

    } while(false);

    bool _success = result276;

    memoize_LAMBDA[_thisPos] = ParseResult<QString >(_success, ret, _b.saveState());

    stackTrace.pop();
    return _success;
}


bool PegParser::SLASH(Buffer &_b, QString &ret, Error &error)
{
    int _thisPos = _b.getP2();

    if(memoize_SLASH.contains(_thisPos))
    {
        ret=memoize_SLASH[_thisPos].value;
        return memoize_SLASH[_thisPos].getValues(_b);
    }

    QString _dummy_69;
    stackTrace.push(QString("SLASH")+"   "+_b.remainder().mid(10));

    bool result279=true;
    BufferState _s81 = _b.saveState();
    do
    {
        bool result280 = _matchStr(_b, "/", error);
        result279 = result279 && result280;
        if(!result279)
        {
            _b.restoreState(_s81);
            break;
        };

        bool result281=spacing(_b, _dummy_69, error);

        result279 = result279 && result281;
        if(!result279)
        {
            _b.restoreState(_s81);
            break;
        };

    } while(false);

    bool _success = result279;

    memoize_SLASH[_thisPos] = ParseResult<QString >(_success, ret, _b.saveState());

    stackTrace.pop();
    return _success;
}


bool PegParser::SPACE(Buffer &_b, QString &ret, Error &error)
{
    int _thisPos = _b.getP2();

    if(memoize_SPACE.contains(_thisPos))
    {
        ret=memoize_SPACE[_thisPos].value;
        return memoize_SPACE[_thisPos].getValues(_b);
    }

    QString _dummy_70;
    stackTrace.push(QString("SPACE")+"   "+_b.remainder().mid(10));

    bool result282=true;
    BufferState _s82 = _b.saveState();
    do
    {
        bool result283 = _matchStr(_b, " ", error);
        result282 = result282 && result283;
        if(!result282)
        {
            _b.restoreState(_s82);
            break;
        };

        bool result284=spacing(_b, _dummy_70, error);

        result282 = result282 && result284;
        if(!result282)
        {
            _b.restoreState(_s82);
            break;
        };

    } while(false);

    bool _success = result282;

    memoize_SPACE[_thisPos] = ParseResult<QString >(_success, ret, _b.saveState());

    stackTrace.pop();
    return _success;
}


bool PegParser::NL(Buffer &_b, QString &ret, Error &error)
{
    int _thisPos = _b.getP2();

    if(memoize_NL.contains(_thisPos))
    {
        ret=memoize_NL[_thisPos].value;
        return memoize_NL[_thisPos].getValues(_b);
    }

    QString _dummy_71;
    stackTrace.push(QString("NL")+"   "+_b.remainder().mid(10));

    bool result285=true;
    BufferState _s83 = _b.saveState();
    do
    {
        bool result286 = _matchStr(_b, "\n", error);
        result285 = result285 && result286;
        if(!result285)
        {
            _b.restoreState(_s83);
            break;
        };

        bool result287=spacing(_b, _dummy_71, error);

        result285 = result285 && result287;
        if(!result285)
        {
            _b.restoreState(_s83);
            break;
        };

    } while(false);

    bool _success = result285;

    memoize_NL[_thisPos] = ParseResult<QString >(_success, ret, _b.saveState());

    stackTrace.pop();
    return _success;
}


bool PegParser::LPAREN(Buffer &_b, QString &ret, Error &error)
{
    int _thisPos = _b.getP2();

    if(memoize_LPAREN.contains(_thisPos))
    {
        ret=memoize_LPAREN[_thisPos].value;
        return memoize_LPAREN[_thisPos].getValues(_b);
    }

    QString _dummy_72;
    stackTrace.push(QString("LPAREN")+"   "+_b.remainder().mid(10));

    bool result288=true;
    BufferState _s84 = _b.saveState();
    do
    {
        bool result289 = _matchStr(_b, "(", error);
        result288 = result288 && result289;
        if(!result288)
        {
            _b.restoreState(_s84);
            break;
        };

        bool result290=spacing(_b, _dummy_72, error);

        result288 = result288 && result290;
        if(!result288)
        {
            _b.restoreState(_s84);
            break;
        };

    } while(false);

    bool _success = result288;

    memoize_LPAREN[_thisPos] = ParseResult<QString >(_success, ret, _b.saveState());

    stackTrace.pop();
    return _success;
}


bool PegParser::RPAREN(Buffer &_b, QString &ret, Error &error)
{
    int _thisPos = _b.getP2();

    if(memoize_RPAREN.contains(_thisPos))
    {
        ret=memoize_RPAREN[_thisPos].value;
        return memoize_RPAREN[_thisPos].getValues(_b);
    }

    QString _dummy_73;
    stackTrace.push(QString("RPAREN")+"   "+_b.remainder().mid(10));

    bool result291=true;
    BufferState _s85 = _b.saveState();
    do
    {
        bool result292 = _matchStr(_b, ")", error);
        result291 = result291 && result292;
        if(!result291)
        {
            _b.restoreState(_s85);
            break;
        };

        bool result293=spacing(_b, _dummy_73, error);

        result291 = result291 && result293;
        if(!result291)
        {
            _b.restoreState(_s85);
            break;
        };

    } while(false);

    bool _success = result291;

    memoize_RPAREN[_thisPos] = ParseResult<QString >(_success, ret, _b.saveState());

    stackTrace.pop();
    return _success;
}


bool PegParser::LBRACE(Buffer &_b, QString &ret, Error &error)
{
    int _thisPos = _b.getP2();

    if(memoize_LBRACE.contains(_thisPos))
    {
        ret=memoize_LBRACE[_thisPos].value;
        return memoize_LBRACE[_thisPos].getValues(_b);
    }

    QString _dummy_74;
    stackTrace.push(QString("LBRACE")+"   "+_b.remainder().mid(10));

    bool result294=true;
    BufferState _s86 = _b.saveState();
    do
    {
        bool result295 = _matchStr(_b, "{", error);
        result294 = result294 && result295;
        if(!result294)
        {
            _b.restoreState(_s86);
            break;
        };

        bool result296=spacing(_b, _dummy_74, error);

        result294 = result294 && result296;
        if(!result294)
        {
            _b.restoreState(_s86);
            break;
        };

    } while(false);

    bool _success = result294;

    memoize_LBRACE[_thisPos] = ParseResult<QString >(_success, ret, _b.saveState());

    stackTrace.pop();
    return _success;
}


bool PegParser::RBRACE(Buffer &_b, QString &ret, Error &error)
{
    int _thisPos = _b.getP2();

    if(memoize_RBRACE.contains(_thisPos))
    {
        ret=memoize_RBRACE[_thisPos].value;
        return memoize_RBRACE[_thisPos].getValues(_b);
    }

    QString _dummy_75;
    stackTrace.push(QString("RBRACE")+"   "+_b.remainder().mid(10));

    bool result297=true;
    BufferState _s87 = _b.saveState();
    do
    {
        bool result298 = _matchStr(_b, "}", error);
        result297 = result297 && result298;
        if(!result297)
        {
            _b.restoreState(_s87);
            break;
        };

        bool result299=spacing(_b, _dummy_75, error);

        result297 = result297 && result299;
        if(!result297)
        {
            _b.restoreState(_s87);
            break;
        };

    } while(false);

    bool _success = result297;

    memoize_RBRACE[_thisPos] = ParseResult<QString >(_success, ret, _b.saveState());

    stackTrace.pop();
    return _success;
}


bool PegParser::LBRACKET(Buffer &_b, QString &ret, Error &error)
{
    int _thisPos = _b.getP2();

    if(memoize_LBRACKET.contains(_thisPos))
    {
        ret=memoize_LBRACKET[_thisPos].value;
        return memoize_LBRACKET[_thisPos].getValues(_b);
    }

    QString _dummy_76;
    stackTrace.push(QString("LBRACKET")+"   "+_b.remainder().mid(10));

    bool result300=true;
    BufferState _s88 = _b.saveState();
    do
    {
        bool result301 = _matchStr(_b, "[", error);
        result300 = result300 && result301;
        if(!result300)
        {
            _b.restoreState(_s88);
            break;
        };

        bool result302=spacing(_b, _dummy_76, error);

        result300 = result300 && result302;
        if(!result300)
        {
            _b.restoreState(_s88);
            break;
        };

    } while(false);

    bool _success = result300;

    memoize_LBRACKET[_thisPos] = ParseResult<QString >(_success, ret, _b.saveState());

    stackTrace.pop();
    return _success;
}


bool PegParser::RBRACKET(Buffer &_b, QString &ret, Error &error)
{
    int _thisPos = _b.getP2();

    if(memoize_RBRACKET.contains(_thisPos))
    {
        ret=memoize_RBRACKET[_thisPos].value;
        return memoize_RBRACKET[_thisPos].getValues(_b);
    }

    QString _dummy_77;
    stackTrace.push(QString("RBRACKET")+"   "+_b.remainder().mid(10));

    bool result303=true;
    BufferState _s89 = _b.saveState();
    do
    {
        bool result304 = _matchStr(_b, "]", error);
        result303 = result303 && result304;
        if(!result303)
        {
            _b.restoreState(_s89);
            break;
        };

        bool result305=spacing(_b, _dummy_77, error);

        result303 = result303 && result305;
        if(!result303)
        {
            _b.restoreState(_s89);
            break;
        };

    } while(false);

    bool _success = result303;

    memoize_RBRACKET[_thisPos] = ParseResult<QString >(_success, ret, _b.saveState());

    stackTrace.pop();
    return _success;
}


bool PegParser::ASTERISK(Buffer &_b, QString &ret, Error &error)
{
    int _thisPos = _b.getP2();

    if(memoize_ASTERISK.contains(_thisPos))
    {
        ret=memoize_ASTERISK[_thisPos].value;
        return memoize_ASTERISK[_thisPos].getValues(_b);
    }

    QString _dummy_78;
    stackTrace.push(QString("ASTERISK")+"   "+_b.remainder().mid(10));

    bool result306=true;
    BufferState _s90 = _b.saveState();
    do
    {
        bool result307 = _matchStr(_b, "*", error);
        result306 = result306 && result307;
        if(!result306)
        {
            _b.restoreState(_s90);
            break;
        };

        bool result308=spacing(_b, _dummy_78, error);

        result306 = result306 && result308;
        if(!result306)
        {
            _b.restoreState(_s90);
            break;
        };

    } while(false);

    bool _success = result306;

    memoize_ASTERISK[_thisPos] = ParseResult<QString >(_success, ret, _b.saveState());

    stackTrace.pop();
    return _success;
}


bool PegParser::SEMI(Buffer &_b, QString &ret, Error &error)
{
    int _thisPos = _b.getP2();

    if(memoize_SEMI.contains(_thisPos))
    {
        ret=memoize_SEMI[_thisPos].value;
        return memoize_SEMI[_thisPos].getValues(_b);
    }

    QString _dummy_79;
    stackTrace.push(QString("SEMI")+"   "+_b.remainder().mid(10));

    bool result309=true;
    BufferState _s91 = _b.saveState();
    do
    {
        bool result310 = _matchStr(_b, ";", error);
        result309 = result309 && result310;
        if(!result309)
        {
            _b.restoreState(_s91);
            break;
        };

        bool result311=spacing(_b, _dummy_79, error);

        result309 = result309 && result311;
        if(!result309)
        {
            _b.restoreState(_s91);
            break;
        };

    } while(false);

    bool _success = result309;

    memoize_SEMI[_thisPos] = ParseResult<QString >(_success, ret, _b.saveState());

    stackTrace.pop();
    return _success;
}


bool PegParser::NOT(Buffer &_b, QString &ret, Error &error)
{
    int _thisPos = _b.getP2();

    if(memoize_NOT.contains(_thisPos))
    {
        ret=memoize_NOT[_thisPos].value;
        return memoize_NOT[_thisPos].getValues(_b);
    }

    QString _dummy_80;
    stackTrace.push(QString("NOT")+"   "+_b.remainder().mid(10));

    bool result312=true;
    BufferState _s92 = _b.saveState();
    do
    {
        bool result313 = _matchStr(_b, "!", error);
        result312 = result312 && result313;
        if(!result312)
        {
            _b.restoreState(_s92);
            break;
        };

        bool result314=spacing(_b, _dummy_80, error);

        result312 = result312 && result314;
        if(!result312)
        {
            _b.restoreState(_s92);
            break;
        };

    } while(false);

    bool _success = result312;

    memoize_NOT[_thisPos] = ParseResult<QString >(_success, ret, _b.saveState());

    stackTrace.pop();
    return _success;
}


bool PegParser::DOT(Buffer &_b, QString &ret, Error &error)
{
    int _thisPos = _b.getP2();

    if(memoize_DOT.contains(_thisPos))
    {
        ret=memoize_DOT[_thisPos].value;
        return memoize_DOT[_thisPos].getValues(_b);
    }

    QString _dummy_81;
    stackTrace.push(QString("DOT")+"   "+_b.remainder().mid(10));

    bool result315=true;
    BufferState _s93 = _b.saveState();
    do
    {
        bool result316 = _matchStr(_b, ".", error);
        result315 = result315 && result316;
        if(!result315)
        {
            _b.restoreState(_s93);
            break;
        };

        bool result317=spacing(_b, _dummy_81, error);

        result315 = result315 && result317;
        if(!result315)
        {
            _b.restoreState(_s93);
            break;
        };

    } while(false);

    bool _success = result315;

    memoize_DOT[_thisPos] = ParseResult<QString >(_success, ret, _b.saveState());

    stackTrace.pop();
    return _success;
}


bool PegParser::QUESTION(Buffer &_b, QString &ret, Error &error)
{
    int _thisPos = _b.getP2();

    if(memoize_QUESTION.contains(_thisPos))
    {
        ret=memoize_QUESTION[_thisPos].value;
        return memoize_QUESTION[_thisPos].getValues(_b);
    }

    QString _dummy_82;
    stackTrace.push(QString("QUESTION")+"   "+_b.remainder().mid(10));

    bool result318=true;
    BufferState _s94 = _b.saveState();
    do
    {
        bool result319 = _matchStr(_b, "?", error);
        result318 = result318 && result319;
        if(!result318)
        {
            _b.restoreState(_s94);
            break;
        };

        bool result320=spacing(_b, _dummy_82, error);

        result318 = result318 && result320;
        if(!result318)
        {
            _b.restoreState(_s94);
            break;
        };

    } while(false);

    bool _success = result318;

    memoize_QUESTION[_thisPos] = ParseResult<QString >(_success, ret, _b.saveState());

    stackTrace.pop();
    return _success;
}


bool PegParser::SNIPPET(Buffer &_b, QString &ret, Error &error)
{
    int _thisPos = _b.getP2();

    if(memoize_SNIPPET.contains(_thisPos))
    {
        ret=memoize_SNIPPET[_thisPos].value;
        return memoize_SNIPPET[_thisPos].getValues(_b);
    }

    QString _dummy_83;
    stackTrace.push(QString("SNIPPET")+"   "+_b.remainder().mid(10));

    bool result321=true;
    BufferState _s95 = _b.saveState();
    do
    {
        bool result322 = _matchStr(_b, "_Snippet", error);
        result321 = result321 && result322;
        if(!result321)
        {
            _b.restoreState(_s95);
            break;
        };

        bool result323=spacing(_b, _dummy_83, error);

        result321 = result321 && result323;
        if(!result321)
        {
            _b.restoreState(_s95);
            break;
        };

    } while(false);

    bool _success = result321;

    memoize_SNIPPET[_thisPos] = ParseResult<QString >(_success, ret, _b.saveState());

    stackTrace.pop();
    return _success;
}


bool PegParser::GT(Buffer &_b, QString &ret, Error &error)
{
    int _thisPos = _b.getP2();

    if(memoize_GT.contains(_thisPos))
    {
        ret=memoize_GT[_thisPos].value;
        return memoize_GT[_thisPos].getValues(_b);
    }

    QString _dummy_84;
    stackTrace.push(QString("GT")+"   "+_b.remainder().mid(10));

    bool result324=true;
    BufferState _s96 = _b.saveState();
    do
    {
        bool result325 = _matchStr(_b, ">", error);
        result324 = result324 && result325;
        if(!result324)
        {
            _b.restoreState(_s96);
            break;
        };

        bool result326=spacing(_b, _dummy_84, error);

        result324 = result324 && result326;
        if(!result324)
        {
            _b.restoreState(_s96);
            break;
        };

    } while(false);

    bool _success = result324;

    memoize_GT[_thisPos] = ParseResult<QString >(_success, ret, _b.saveState());

    stackTrace.pop();
    return _success;
}


bool PegParser::LT(Buffer &_b, QString &ret, Error &error)
{
    int _thisPos = _b.getP2();

    if(memoize_LT.contains(_thisPos))
    {
        ret=memoize_LT[_thisPos].value;
        return memoize_LT[_thisPos].getValues(_b);
    }

    QString _dummy_85;
    stackTrace.push(QString("LT")+"   "+_b.remainder().mid(10));

    bool result327=true;
    BufferState _s97 = _b.saveState();
    do
    {
        bool result328 = _matchStr(_b, "<", error);
        result327 = result327 && result328;
        if(!result327)
        {
            _b.restoreState(_s97);
            break;
        };

        bool result329=spacing(_b, _dummy_85, error);

        result327 = result327 && result329;
        if(!result327)
        {
            _b.restoreState(_s97);
            break;
        };

    } while(false);

    bool _success = result327;

    memoize_LT[_thisPos] = ParseResult<QString >(_success, ret, _b.saveState());

    stackTrace.pop();
    return _success;
}


bool PegParser::EQ(Buffer &_b, QString &ret, Error &error)
{
    int _thisPos = _b.getP2();

    if(memoize_EQ.contains(_thisPos))
    {
        ret=memoize_EQ[_thisPos].value;
        return memoize_EQ[_thisPos].getValues(_b);
    }

    QString _dummy_86;
    stackTrace.push(QString("EQ")+"   "+_b.remainder().mid(10));

    bool result330=true;
    BufferState _s98 = _b.saveState();
    do
    {
        bool result331 = _matchStr(_b, "=", error);
        result330 = result330 && result331;
        if(!result330)
        {
            _b.restoreState(_s98);
            break;
        };

        bool result332=spacing(_b, _dummy_86, error);

        result330 = result330 && result332;
        if(!result330)
        {
            _b.restoreState(_s98);
            break;
        };

    } while(false);

    bool _success = result330;

    memoize_EQ[_thisPos] = ParseResult<QString >(_success, ret, _b.saveState());

    stackTrace.pop();
    return _success;
}


bool PegParser::COMMA(Buffer &_b, QString &ret, Error &error)
{
    int _thisPos = _b.getP2();

    if(memoize_COMMA.contains(_thisPos))
    {
        ret=memoize_COMMA[_thisPos].value;
        return memoize_COMMA[_thisPos].getValues(_b);
    }

    QString _dummy_87;
    stackTrace.push(QString("COMMA")+"   "+_b.remainder().mid(10));

    bool result333=true;
    BufferState _s99 = _b.saveState();
    do
    {
        bool result334 = _matchStr(_b, ",", error);
        result333 = result333 && result334;
        if(!result333)
        {
            _b.restoreState(_s99);
            break;
        };

        bool result335=spacing(_b, _dummy_87, error);

        result333 = result333 && result335;
        if(!result333)
        {
            _b.restoreState(_s99);
            break;
        };

    } while(false);

    bool _success = result333;

    memoize_COMMA[_thisPos] = ParseResult<QString >(_success, ret, _b.saveState());

    stackTrace.pop();
    return _success;
}


bool PegParser::CUT(Buffer &_b, QString &ret, Error &error)
{
    int _thisPos = _b.getP2();

    if(memoize_CUT.contains(_thisPos))
    {
        ret=memoize_CUT[_thisPos].value;
        return memoize_CUT[_thisPos].getValues(_b);
    }

    QString _dummy_88;
    stackTrace.push(QString("CUT")+"   "+_b.remainder().mid(10));

    bool result336=true;
    BufferState _s100 = _b.saveState();
    do
    {
        bool result337 = _matchStr(_b, "^", error);
        result336 = result336 && result337;
        if(!result336)
        {
            _b.restoreState(_s100);
            break;
        };

        bool result338=spacing(_b, _dummy_88, error);

        result336 = result336 && result338;
        if(!result336)
        {
            _b.restoreState(_s100);
            break;
        };

    } while(false);

    bool _success = result336;

    memoize_CUT[_thisPos] = ParseResult<QString >(_success, ret, _b.saveState());

    stackTrace.pop();
    return _success;
}


bool PegParser::AND(Buffer &_b, QString &ret, Error &error)
{
    int _thisPos = _b.getP2();

    if(memoize_AND.contains(_thisPos))
    {
        ret=memoize_AND[_thisPos].value;
        return memoize_AND[_thisPos].getValues(_b);
    }

    QString _dummy_89;
    stackTrace.push(QString("AND")+"   "+_b.remainder().mid(10));

    bool result339=true;
    BufferState _s101 = _b.saveState();
    do
    {
        bool result340 = _matchStr(_b, "&", error);
        result339 = result339 && result340;
        if(!result339)
        {
            _b.restoreState(_s101);
            break;
        };

        bool result341=spacing(_b, _dummy_89, error);

        result339 = result339 && result341;
        if(!result339)
        {
            _b.restoreState(_s101);
            break;
        };

    } while(false);

    bool _success = result339;

    memoize_AND[_thisPos] = ParseResult<QString >(_success, ret, _b.saveState());

    stackTrace.pop();
    return _success;
}


bool PegParser::SHARPQUOTE(Buffer &_b, QString &ret, Error &error)
{
    int _thisPos = _b.getP2();

    if(memoize_SHARPQUOTE.contains(_thisPos))
    {
        ret=memoize_SHARPQUOTE[_thisPos].value;
        return memoize_SHARPQUOTE[_thisPos].getValues(_b);
    }

    QString _dummy_90;
    stackTrace.push(QString("SHARPQUOTE")+"   "+_b.remainder().mid(10));

    bool result342=true;
    BufferState _s102 = _b.saveState();
    do
    {
        bool result343 = _matchStr(_b, "#'", error);
        result342 = result342 && result343;
        if(!result342)
        {
            _b.restoreState(_s102);
            break;
        };

        bool result344=spacing(_b, _dummy_90, error);

        result342 = result342 && result344;
        if(!result342)
        {
            _b.restoreState(_s102);
            break;
        };

    } while(false);

    bool _success = result342;

    memoize_SHARPQUOTE[_thisPos] = ParseResult<QString >(_success, ret, _b.saveState());

    stackTrace.pop();
    return _success;
}


bool PegParser::INCLASS(Buffer &_b, QString &ret, Error &error)
{
    int _thisPos = _b.getP2();

    if(memoize_INCLASS.contains(_thisPos))
    {
        ret=memoize_INCLASS[_thisPos].value;
        return memoize_INCLASS[_thisPos].getValues(_b);
    }

    QString _dummy_91;
    stackTrace.push(QString("INCLASS")+"   "+_b.remainder().mid(10));

    bool result345=true;
    BufferState _s103 = _b.saveState();
    do
    {
        bool result346 = _matchStr(_b, "inclass", error);
        result345 = result345 && result346;
        if(!result345)
        {
            _b.restoreState(_s103);
            break;
        };

        bool result347=spacing(_b, _dummy_91, error);

        result345 = result345 && result347;
        if(!result345)
        {
            _b.restoreState(_s103);
            break;
        };

    } while(false);

    bool _success = result345;

    memoize_INCLASS[_thisPos] = ParseResult<QString >(_success, ret, _b.saveState());

    stackTrace.pop();
    return _success;
}


bool PegParser::nonquote(Buffer &_b, QString &ret, Error &error)
{
    int _thisPos = _b.getP2();

    if(memoize_nonquote.contains(_thisPos))
    {
        ret=memoize_nonquote[_thisPos].value;
        return memoize_nonquote[_thisPos].getValues(_b);
    }

    Token c;
    stackTrace.push(QString("nonquote")+"   "+_b.remainder().mid(10));

    bool result348=true;
    BufferState _s104 = _b.saveState();
    do
    {
        BufferState _s105 = _b.saveState();
        bool result350 = _matchStr(_b, "\"", error);
        bool result349 = !(result350);
        _b.restoreState(_s105);
        result348 = result348 && result349;
        if(!result348)
        {
            _b.restoreState(_s104);
            break;
        };
        bool result351 =_matchAnyChar(_b, c, error);
        if(result351)
        {
            ret=c.Lexeme;
        };
        result348 = result348 && result351;
        if(!result348)
        {
            _b.restoreState(_s104);
            break;
        };

    } while(false);

    bool _success = result348;

    memoize_nonquote[_thisPos] = ParseResult<QString >(_success, ret, _b.saveState());

    stackTrace.pop();
    return _success;
}


bool PegParser::nonrbrace(Buffer &_b, QString &ret, Error &error)
{
    int _thisPos = _b.getP2();

    if(memoize_nonrbrace.contains(_thisPos))
    {
        ret=memoize_nonrbrace[_thisPos].value;
        return memoize_nonrbrace[_thisPos].getValues(_b);
    }

    Token c2;
    stackTrace.push(QString("nonrbrace")+"   "+_b.remainder().mid(10));

    bool result352=true;
    BufferState _s106 = _b.saveState();
    do
    {
        BufferState _s107 = _b.saveState();
        bool result354 = _matchStr(_b, "}", error);
        bool result353 = !(result354);
        _b.restoreState(_s107);
        result352 = result352 && result353;
        if(!result352)
        {
            _b.restoreState(_s106);
            break;
        };
        bool result355 =_matchAnyChar(_b, c2, error);
        if(result355)
        {
            ret=c2.Lexeme;
        };
        result352 = result352 && result355;
        if(!result352)
        {
            _b.restoreState(_s106);
            break;
        };

    } while(false);

    bool _success = result352;

    memoize_nonrbrace[_thisPos] = ParseResult<QString >(_success, ret, _b.saveState());

    stackTrace.pop();
    return _success;
}



