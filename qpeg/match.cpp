/**************************************************************************
**   QPeg, the PEG parser generator
**   Copyright 2010 Mohamed Samy Ali - samy2004@gmail.com
**   This project is released under the Apache License version 2.0
**   as described in the included license.txt file
**************************************************************************/

#include "match.h"

bool _matchStr(Buffer &buffer, QString str, Error &error)
{
    Token ret;
    return _matchStr(buffer, str, ret, error);
}
bool _matchAlpha(Buffer &buffer, Error &error)
{
    Token ret;
    return _matchAlpha(buffer, ret, error);
}
bool _matchStr(Buffer &buffer, QString str, Token &ret, Error &error)
{
        bool value;
        BufferState s = buffer.saveState();
        if(buffer.eof() && str.length()>0)
        {
            error = Error(QString("EOF encountered while looking for '%1'").arg(str), s);
            value = false;
        }
        else if(buffer.readAhead(str))
        {
                buffer.read(str);
                QString lexeme;
                int line, col, pos;
                lexeme = buffer.accept(line, col, pos);
                ret  = Token(lexeme, -1);
                ret.Line = line;
                ret.Column = col;
                ret.Pos = pos;
                value = true;
        }
        else
        {
                buffer.restoreState(s);
                error = Error(QString("Expected '%1', found '%2'").arg(str).arg(buffer.readAhead(5)), s);
                value = false;
        }
        return value;
}

bool _matchAnyChar(Buffer &buffer, Error &error)
{
    Token tok;
    return _matchAnyChar(buffer, tok, error);
}

bool _matchAnyChar(Buffer &buffer, Token &ret, Error &error)
{
        bool value;
        BufferState s = buffer.saveState();
        if(buffer.eof())
        {
            value = false;
            error = Error(QString("EOF encountered while expecting a character"), s);
        }
        else
        {
            buffer.read();
            QString lexeme;
            int line, col, pos;
            lexeme = buffer.accept(line, col, pos);
            ret  = Token(lexeme, -1);
            ret.Line = line;
            ret.Column = col;
            ret.Pos = pos;
            value = true;
        }
        return value;
}

bool _matchAlpha(Buffer &buffer, Token &ret, Error &error)
{
        bool value;
        BufferState s = buffer.saveState();
        if(buffer.eof())
        {
            value = false;
            error = Error(QString("EOF encountered while looking for an alphanumeric character"), s);
        }
        else
        {
            QChar c = buffer.read();
            if(!c.isLetterOrNumber())
            {
                buffer.restoreState(s);
                error = Error(QString("Expected a letter or number, found '%1'").arg(buffer.readAhead(5)), s);
                return false;
            }
            QString lexeme;
            int line, col, pos;
            lexeme = buffer.accept(line, col, pos);
            ret  = Token(lexeme, -1);
            ret.Line = line;
            ret.Column = col;
            ret.Pos = pos;
            value = true;
        }
        return value;
}

bool _matchLetter(Buffer &buffer, Token &ret, Error &error)
{
        bool value;
        BufferState s = buffer.saveState();
        if(buffer.eof())
        {
            value = false;
            error = Error(QString("EOF encountered while looking for an alphanumeric character"), s);
        }
        else
        {
            QChar c = buffer.read();
            if(!c.isLetter())
            {
                buffer.restoreState(s);
				error = Error(QString("Expected a letter, found '%1'").arg(buffer.readAhead(5)), s);
                return false;
            }
            QString lexeme;
            int line, col, pos;
            lexeme = buffer.accept(line, col, pos);
            ret  = Token(lexeme, -1);
            ret.Line = line;
            ret.Column = col;
            ret.Pos = pos;
            value = true;
        }
        return value;
}

bool _matchDigit(Buffer &buffer, Error &error)
{
    Token tok;
    return _matchDigit(buffer, tok, error);
}

bool _matchDigit(Buffer &buffer, Token &ret, Error &error)
{
        bool value;
        BufferState s = buffer.saveState();
        if(buffer.eof())
        {
            value = false;
            error = Error(QString("EOF encountered while looking for a digit"), s);
        }
        else
        {
            QChar c = buffer.read();
            if(!c.isDigit() )
            {
                buffer.restoreState(s);
                error = Error(QString("Expected a digit, found '%1'").arg(buffer.readAhead(5)), s);
                return false;
            }
            QString lexeme;
            int line, col, pos;
            lexeme = buffer.accept(line, col, pos);
            ret  = Token(lexeme, -1);
            ret.Line = line;
            ret.Column = col;
            ret.Pos = pos;
            value = true;
        }
        return value;
}

Token getRange(const Buffer &_b, const BufferState &s1, const BufferState &s2)
{
    Token ret;
    ret.Lexeme = _b.getRange(s1, s2, ret.Line, ret.Column, ret.Pos);
    return ret;
}

void recordFailure(QString rule, Buffer &b);
QStack<QString> failure;
void recordFailure(QString rule, Buffer &b)
{
    QString f;
    f = QString("Failed at rule '%1', buffer %2")
        .arg(rule)
        .arg(b.eof()? " at eof" : b.accept());

    failure.push(f);
}

