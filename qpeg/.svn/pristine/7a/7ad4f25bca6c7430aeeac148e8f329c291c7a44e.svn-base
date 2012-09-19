#include <QString>
#include "token.h"

Token::Token(QString lexeme, TokenType type)
{
    Lexeme = lexeme;
    Type = type;
}
Token::Token()
{
    Lexeme = "";
    Type = TokenInvalid;
}
Token::Token(const Token &other)
{
    Lexeme = other.Lexeme;
    Type = other.Type;
    Line = other.Line;
    Column = other.Column;
    Pos = other.Pos;
}
Token &Token::operator = (const Token &other)
{
    Lexeme = other.Lexeme;
    Type = other.Type;
    Line = other.Line;
    Column = other.Column;
    Pos = other.Pos;

    return *this;
}
bool Token::operator ==(Token &t2)
{
    return Type==t2.Type && Lexeme == t2.Lexeme && Line == t2.Line && Column == t2.Column && Pos == t2.Pos;
}
bool Token::operator !=(Token &t2)
{
    return Type!=t2.Type || Lexeme != t2.Lexeme  || Line != t2.Line || Column != t2.Column || Pos != t2.Pos;;
}
bool Token::Is(QString lexeme)
{
    return Lexeme == lexeme;
}
bool Token::Is(TokenType type)
{
    return Type == type;
}


