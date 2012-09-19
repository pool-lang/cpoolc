#ifndef TOKEN_H
#define TOKEN_H
#include <QtCore>
typedef int TokenType;

// Tokens of type 'TokenNone' are skipped during lexical analysis.
const TokenType TokenNone = -1;
// Invalid tokens are returned by functions that return tokens
// when they shouldn't, for example Parser.getPos() at the end of file
const TokenType TokenInvalid = -2;
class Token
{
public:
    QString Lexeme;
    TokenType Type;
    int Line, Column, Pos;
public:
        Token(QString lexeme, TokenType type);
        Token(Token const &other);
        Token();
        bool operator ==(Token &t2);
        bool operator !=(Token &t2);
        Token &operator = (const Token &other);
        bool Is(QString lexeme);
        bool Is(TokenType type);
};
Q_DECLARE_METATYPE(Token);
Q_DECLARE_METATYPE(QVector<Token>);
#endif // TOKEN_H
