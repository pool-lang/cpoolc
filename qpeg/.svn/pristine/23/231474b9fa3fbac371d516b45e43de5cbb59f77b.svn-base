/**************************************************************************
**   QPeg, the PEG parser generator
**   Copyright 2010 Mohamed Samy Ali - samy2004@gmail.com
**   This project is released under the Apache License version 2.0
**   as described in the included license.txt file
**************************************************************************/

#ifndef PREDICATE_H
#define PREDICATE_H

#include <QString>
#include "buffer.h"
#include "token.h"
#include "charpredicate.h"

class Buffer;
class CharPredicate;

template<class T> class Predicate
{
public:
    QString name;
public:
    virtual bool operator()(Buffer &b, T &ret)=0;
};

class LA : public Predicate<Token>
{
    CharPredicate *predicate;
    TokenType type;
public:
    LA(CharPredicate *pred, TokenType type= -1) : Predicate<Token>()
    {
        this->predicate = pred;
        this->type = type;
    }

    virtual bool operator()(Buffer &buffer, Token &ret)
    {
        BufferState s = buffer.saveState();
        if(buffer.eof())
            return false;
        QChar c = buffer.read();
        if((*predicate)(c))
        {
            QString str;
            int line, col, pos;
            str = buffer.accept(line, col, pos);
            ret  = Token(str,type);
            ret.Line = line;
            ret.Column = col;
            ret.Pos = pos;
            return true;
        }
        buffer.restoreState(s);
        return false;
    }
};

class LAStr : public Predicate<Token>
{
    QString str;
    TokenType type;
public:
    LAStr(QString s, TokenType type=-1) :Predicate<Token>()
    {
        this->str = s;
        this->type = type;
    }
    virtual bool operator()(Buffer &buffer, Token &ret)
    {
        bool value;
        BufferState s = buffer.saveState();
        if(buffer.eof())
        {
            value = false;
        }
        else if(buffer.readAhead(str))
        {
            buffer.read(str);
            QString lexeme;
            int line, col, pos;
            lexeme = buffer.accept(line, col, pos);
            ret  = Token(lexeme, type);
            ret.Line = line;
            ret.Column = col;
            ret.Pos = pos;
            value = true;
        }
        else
        {
            buffer.restoreState(s);
            value = false;
        }
        return value;
    }
};

template<class T> class Else : public Predicate<T>
{
public:
    Else() : Predicate<T>()
    {
    }

    virtual bool operator()(Buffer &b, T &ret)
    {
        return true;
    }
};

template<class T> class LineStart : public Predicate<T>
{
public:
    virtual bool operator()(Buffer &b, T &ret)
    {
        return b.isStartOfLine();
    }

};

class Eof : public Predicate<bool>
{
public:
    virtual bool operator()(Buffer &b, bool &ret)
    {
        return b.eof();
    }
};

template<class T, class T1, class T2> class Seq : public Predicate<T>
{
public:
    Predicate<T1> *left;
    Predicate<T2> *right;
public:
    Seq(Predicate<T1> *p1= NULL, Predicate<T2> *p2= NULL) : Predicate<T>()
    {
        left = p1;
        right = p2;
    }
    virtual bool operator()(Buffer &b, T &ret)
    {
        T1 r1;
        T2 r2;
        BufferState s = b.saveState();
        bool result = (*left)(b, r1);
        if(!result)
        {
            b.restoreState(s);
            return false;
        }
        result = (*right)(b, r2);
        if(!result)
        {
            b.restoreState(s);
            return false;
        }
        combine(ret, r1, r2);
        return true;
    }
    virtual void combine(T &result, T1 &t1, T2 &t2)
    {

    }
};
template<class T, class T1, class T2> class Choice : public Predicate<T>
{
public:
    Predicate<T1> *left;
    Predicate<T2> *right;
public:
    Choice(Predicate<T1> *p1 = NULL, Predicate<T2> *p2= NULL) : Predicate<T>()
    {
        left = p1;
        right = p2;
    }

    virtual bool operator()(Buffer &b, T &ret)
    {
        T1 r1;
        T2 r2;
        BufferState s = b.saveState();
        if((*left)(b, r1))
        {
            processLeft(ret, r1);
            return true;
        }
        b.restoreState(s);
        s = b.saveState();
        if((*right)(b, r2))
        {
            processRight(ret, r2);
            return true;
        }
        b.restoreState(s);
        return false;
    }
    virtual void processLeft(T &result, T1 &r1)
    {

    }
    virtual void processRight(T &result, T2 &r2)
    {

    }
};

template<class T, class T1> class Loop : public Predicate<T>
{
public:
    Predicate<T1> *predicate;
public:
    Loop(Predicate<T1> *p= NULL) : Predicate<T>() { this->predicate = p; }
    virtual bool operator()(Buffer &b, T &ret)
    {
        T1 r1;
        init(ret);
        while(true)
        {
            BufferState s = b.saveState();
            bool result = (*predicate)(b, r1);
            if(!result)
            {
                b.restoreState(s);
                break;
            }
            process(ret, r1);
        }
        return true;
    }
    virtual void process(T &ret, T1 &r1)
    {

    }
    virtual void init(T &ret)
    {

    }
};

#endif // PREDICATE_H
