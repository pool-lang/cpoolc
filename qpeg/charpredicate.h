#ifndef CHARPREDICATE_H
#define CHARPREDICATE_H

#include <QChar>
#include <QVector>

class CharPredicate
{
public:
        virtual bool operator()(QChar c)=0;
};

class CharEquals : public CharPredicate
{
        QChar _c;
public:
        CharEquals(QChar c);
        bool operator()(QChar c);
};
class CharNotEqual : public CharPredicate
{
        QChar _c;
public:
        CharNotEqual(QChar c);
        bool operator()(QChar c);
};

class CharIsLetter : public CharPredicate
{
public:
    bool operator()(QChar c);
};

class CharRange: public CharPredicate
{
        QChar _c1, _c2;
public:
        CharRange(QChar c1, QChar c2);
        bool operator()(QChar c);
};
class CharOr: public CharPredicate
{
        QVector<CharPredicate *> _predicates;
public:
        CharOr(CharPredicate *a, CharPredicate *b);
        CharOr(CharPredicate *a, CharPredicate *b, CharPredicate *c);
        CharOr(CharPredicate *a, CharPredicate *b, CharPredicate *c, CharPredicate *d);
        CharOr(QString s);
        bool operator()(QChar c);
};
class AnyChar : public CharPredicate
{
public:
    AnyChar();
    bool operator()(QChar c);
};


#endif // CHARPREDICATE_H
