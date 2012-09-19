/**************************************************************************
**   QPeg, the PEG parser generator
**   Copyright 2010 Mohamed Samy Ali - samy2004@gmail.com
**   This project is released under the Apache License version 2.0
**   as described in the included license.txt file
**************************************************************************/

#include "parsepeg.h"

/*
    peg  ->  (rule "\n")* Eof
    rule ->  identifier "->" expr / identifier ":" identifier "->" expr
    expr ->  or ":" identifier code/ or ":" identifier / or
    or   ->  seq "/" or
           / seq

    seq -> prim " " seq
           / prim

    prim  -> "(" expr ")*" / quote (non-quote)* quote / identifier
    identifier -> alpha (alpha)*
*/

QStringList lexize(Buffer &b, QString &error);

QStringList lexize(Buffer &b, QString &error)
{
    const int READY = 0;
    const int ID = 1;
    const int STRLIT = 2;
    const int ARROW = 3;
    const int CODE = 4;
    const int ESCAPE = 5;
    int state = READY;
    QStringList tokens;
    error = "";
    while(!b.eof())
    {
        QChar c = b.read();
        switch(state)
        {
        case READY:
            if(c == '"')
            {
                state = STRLIT;
            }
            else if(c == '(' || c == ':' || c ==')' || c==';' || c == '/' || c == '*' || c =='\n')
            {
                tokens.append(b.accept());
            }
            else if(c =='{')
            {
                state = CODE;
            }
            else if(c==' ')
            {
                tokens.append(b.accept());
                //b.accept();
            }
            else if(c =='}')
            {
                b.accept();
            }
            else if(c == '-')
            {
                state = ARROW;
            }
            else if(c.isLetter())
            {
                state = ID;
            }
            else
            {
                error = QString("didn't expect %1 in state READY").arg(c);
                return tokens;
            }
            break;
        case ID:
            if(c.isLetterOrNumber())
            {
            }
            else
            {
                b.retract(1);
                tokens.append(b.accept());
                state = READY;
            }
            break;
        case STRLIT:
            if(c == '"')
            {
                tokens.append(b.accept());
                state = READY;
            }
            else if( c == '\\' )
            {
                state = ESCAPE;
            }
            break;
        case ESCAPE:
            state = STRLIT;
            break;
        case ARROW:
            if(c == '>')
            {
                tokens.append(b.accept());
                state = READY;
            }
            else
            {
                error = "expected >";
                return tokens;
            }
            break;
       case CODE:
            if(c == '$')
            {
                tokens.append(b.accept().replace("$","}"));
                state = READY;
            }
            break;
        default:
            error = QString("didn't expect %1 in state CODE").arg(c);
            return tokens;
        }
    }
    return tokens;
}
