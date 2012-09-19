#include <QChar>
#include "buffer.h"
#include "charpredicate.h"

CharEquals::CharEquals(QChar c)
{
        _c = c;
}

bool CharEquals::operator ()(QChar c)
{
        return _c == c;
}

CharNotEqual::CharNotEqual(QChar c)
{
        _c = c;
}

bool CharNotEqual::operator ()(QChar c)
{
        return _c != c;
}

bool CharIsLetter::operator ()(QChar c)
{
    return c.isLetter();
}

CharRange::CharRange(QChar c1, QChar c2)
{
        _c1 = c1, _c2 = c2;;
}

bool CharRange::operator ()(QChar c)
{
        return (_c1<= c) && (_c2 >= c);
}

CharOr::CharOr(CharPredicate *a,CharPredicate *b)
{
        _predicates.append(a);
        _predicates.append(b);
}

CharOr::CharOr(CharPredicate *a,CharPredicate *b, CharPredicate *c)
{
        _predicates.append(a);
        _predicates.append(b);
        _predicates.append(c);
}

CharOr::CharOr(CharPredicate *a,CharPredicate *b, CharPredicate *c, CharPredicate *d)
{
        _predicates.append(a);
        _predicates.append(b);
        _predicates.append(c);
        _predicates.append(d);

}

CharOr::CharOr(QString s)
{
    for(int i=0; i<s.length(); i++)
    {
        CharPredicate *p = new CharEquals(s[i]);
        _predicates.append(p);
    }
}

bool CharOr::operator ()(QChar c)
{
    for(int i=0; i<_predicates.count(); i++)
    {
        CharPredicate *p = _predicates[i];
        if((*p)(c))
        {
            return true;
        }
    }
    return false;
}

AnyChar::AnyChar() : CharPredicate()
{
}

bool AnyChar::operator ()(QChar)
{
    return true;
}
