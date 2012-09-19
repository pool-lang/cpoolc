/**************************************************************************
**   QPeg, the PEG parser generator
**   Copyright 2010 Mohamed Samy Ali - samy2004@gmail.com
**   This project is released under the Apache License version 2.0
**   as described in the included license.txt file
**************************************************************************/

#ifndef MATCH_H
#define MATCH_H

#include "buffer.h"
#include "token.h"


struct Error
{
    BufferState bufferState;
    QString message;
    Error() { }
    Error(QString message, BufferState state)
    {
        this->message = message;
        this->bufferState = state;
    }
};

template<class Ret> struct ParseResult
{
    bool success;
    Ret value;
    BufferState state;
    ParseResult(bool a, const Ret &b, BufferState c){success=a; value=b;state=c;}
    ParseResult(){}
    bool getValues(Buffer &_b)
    {
        _b.restoreState(state);
        return success;
    }
};

bool _matchStr(Buffer &buffer, QString str, Error &error);
bool _matchAnyChar(Buffer &buffer, Error &error);
bool _matchDigit(Buffer &buffer, Error &error);
bool _matchAlpha(Buffer &buffer, Error &error);
bool _matchLetter(Buffer &buffer, QString &error);

bool _matchStr(Buffer &buffer, QString str, Token &ret, Error &error);
bool _matchAnyChar(Buffer &buffer, Token &ret, Error &error);
bool _matchDigit(Buffer &buffer, Token &ret, Error &error);
bool _matchLetter(Buffer &buffer, Token &ret, Error &error);
bool _matchAlpha(Buffer &buffer, Token &ret, Error &error);

Token getRange(const Buffer &_b, const BufferState &s1, const BufferState &s2);


#endif // MATCH_H
