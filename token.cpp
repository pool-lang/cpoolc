// Copyright 2011-2012 Kevin Cox

/*******************************************************************************
*                                                                              *
*  This software is provided 'as-is', without any express or implied           *
*  warranty. In no event will the authors be held liable for any damages       *
*  arising from the use of this software.                                      *
*                                                                              *
*  Permission is granted to anyone to use this software for any purpose,       *
*  including commercial applications, and to alter it and redistribute it      *
*  freely, subject to the following restrictions:                              *
*                                                                              *
*  1. The origin of this software must not be misrepresented; you must not     *
*     claim that you wrote the original software. If you use this software in  *
*     a product, an acknowledgment in the product documentation would be       *
*     appreciated but is not required.                                         *
*                                                                              *
*  2. Altered source versions must be plainly marked as such, and must not be  *
*     misrepresented as being the original software.                           *
*                                                                              *
*  3. This notice may not be removed or altered from any source distribution.  *                                                           *
*                                                                              *
*******************************************************************************/

#include "token.h"

#include "error.h"
#include "symbol.h"
#include "test.h"

Token::Token()
{
	type = Undefined;
}

static QChar parseEscape (SmartBuffer *b)
{
	if (b->peek().isDigit())
	{
		if ( b->peek() == '0' )
		{
			b->pop();

			bool ok;
			b->look(1).toInt(&ok, 16); // Check if next character is hex.
			if (!ok) // Is a null character.
				return '\0';

			b->move(-1); // Not a NULL.
		}

		bool ok;
		QChar r = QChar(b->read(4).toInt(&ok, 16));
		if (!ok) Error::fatal("Could not parse character.", b->position());
		return r;
	}
	else
	{
		switch (b->pop().toAscii())
		{
		case '\'':
			return '\'';
		case '"':
			return '"';
		case 'n':
			return '\n';
		case 'r':
			return '\r';
		case 't':
			return '\t';
		default:
			Error::fatal("Invalid escape sequence.", b->position());
		}
	}
}

static QString parseNumber(SmartBuffer *b, uint forceBase = 0)
{
	uint base = 10;

	if (!forceBase)
	{
		if ( b->peek() == '0' )
		{
			b->pop();
			switch (b->pop().toAscii())
			{
			case 'b':
				base = 2;
				break;
			case 'o':
				base = 8;
				break;
			case 'x':
				base = 16;
				break;
			default:
				b->move(-2);
			}
		}
	}
	else base = forceBase;

	uint p = b->tell();

	switch (base)
	{
	case 2:
		while ( b->peek() == '0' || b->peek() == '1' )
			b->pop();
		break;
	case 8:
		while ( b->peek() >= '0' && b->peek() <= '7' )
			b->pop();
		break;
	case 10:
		while ( b->peek() >= '0' && b->peek() <= '9' )
			b->pop();
		break;
	case 16:
		while (( b->peek() >= '0' && b->peek() <= '9' ) ||
			   ( b->peek() >= 'A' && b->peek() <= 'F' ) ||
			   ( b->peek() >= 'a' && b->peek() <= 'f' ))
			b->pop();
		break;
	default:
		Error::fatal(QString("Bug in code! Bad base.  Look at %0:%1")
					 .arg(__FILE__).arg(__LINE__), b->position());
	}

	uint d = b->tell() - p;
	b->seek(p);
	QString r = b->read(d);
	if ( base != 10 ) // Make it base 10.
		r = QString("%0").arg(r.toInt(NULL, base));

	if ( b->pop() == '.' && b->peek().isDigit() )
	{
		if ( base != 10 )
			Error::fatal("Floating points can only be specified in base 10.", b->position());

		r += "." + parseNumber(b, base);
	}
	else b->move(-1); // For the pop in the if.

	if (Symbol::isIdentifierStartCharacter(b->peek()))
		Error::fatal("Unexpected identifier character.", b->position());

	return r;
}

Token::List Token::tokenize(SmartBuffer *b)
{
	List l;

	b->consumeWhitespace();

	while (b->canRead())
	{
		Token t;
		t.defined = b->position();

		switch (b->peek().toAscii())
		{
		case '\'':
			b->pop();
			t.type = Character;

			if (b->peek() == '\\' )
			{
				b->pop();
				t.data = QString(parseEscape(b));
			}
			else t.data = QString(b->pop());
			break;
		case '"':
			t.type = String;
			if ( b->look(3) == "\"\"\"" )
			{
				b->move(3);
				int i = b->look().indexOf("\"\"\"");
				if ( i < 0 ) Error::fatal("Expected end of raw string.", b->position());
				t.data = b->read(i);
				b->move(3);
			}
			else
			{
				b->pop();
				t.data = "";
				while ( b->peek() != '"' )
				{
					if (!b->canRead())
						Error::fatal("Expected end of string.", b->position());

					QChar c = b->pop();
					if ( c == '\\' ) t.data += parseEscape(b);
					else             t.data += c;
				}
				b->pop(); // Pop the ".
			}
			break;
		case '/':
			b->pop();
			if ( b->peek() == '/' )
			{
				b->pop();
				t.type = Comment;

				while ( b->peek() != '\n' )
					t.data += b->pop();

				break;
			}
			else if ( b->peek() == '*' )
			{
				b->pop();
				t.type = Comment;

				while ( b->look(2) != "*/" )
					t.data += b->pop();

				b->move(2);
				break;
			}
			else if ( b->peek() == '+' )
			{
				b->pop();
				t.type = Comment;

				uint d = 1;
				while (d)
				{
					if (!b->canRead())
						Error::fatal("Unmatched nesting comments.", b->position());

					if ( b->look(2) == "+/" )
					{
						d--;
						t.data += b->read(2);
					}
					else if ( b->look(2) == "/+" )
					{
						d++;
						t.data += b->read(2);
					}
					else t.data += b->pop();
				}

				t.data = t.data.left(t.data.length()-2);
				break;
			}
		case '~':
		case '!':
			if ( b->peek() == '=' )
			{
				t.type = Operator;
				t.data = QString(b->read(2));
				break;
			}
		case '@':
		case '#':
		case '$':
		case '%':
		case '^':
		case '&':
			if ( b->peek() == '&' )
			{
				t.type = Operator;
				t.data = QString(b->read(2));
				break;
			}
		case '*':
		case '(':
		case ')':
		case '-':
		case '=':
			if ( b->look(2) == "==" )
			{
				t.type = Operator;
				t.data = QString(b->read(3));
				break;
			}
			else if ( b->peek() == '=' )
			{
				t.type = Operator;
				t.data = QString(b->read(2));
				break;
			}
		case '+':
			if ( b->peek() == '=' )
			{
				t.type = Operator;
				t.data = QString(b->read(2));
				break;
			}
		case '[':
			if ( b->peek() == '[' )
			{
				t.type = Operator;
				t.data = QString(b->read(2));
				break;
			}
		case '{':
		case ']':
			if ( b->peek() == ']' )
			{
				t.type = Operator;
				t.data = QString(b->read(2));
				break;
			}
		case '}':
		case ';':
		case ':':
		case '|':
		case ',':
		case '<':
		case '.':
		case '>':
		case '?':
			t.type = Operator;
			t.data = QString(b->pop());
			break;
		case 'A': case 'a':
		case 'B': case 'b':
		case 'C': case 'c':
		case 'D': case 'd':
		case 'E': case 'e':
		case 'F': case 'f':
		case 'G': case 'g':
		case 'H': case 'h':
		case 'I': case 'i':
		case 'J': case 'j':
		case 'K': case 'k':
		case 'L': case 'l':
		case 'M': case 'm':
		case 'N': case 'n':
		case 'O': case 'o':
		case 'P': case 'p':
		case 'Q': case 'q':
		case 'R': case 'r':
		case 'S': case 's':
		case 'T': case 't':
		case 'U': case 'u':
		case 'V': case 'v':
		case 'W': case 'w':
		case 'X': case 'x':
		case 'Y': case 'y':
		case 'Z': case 'z':
			t.type = Identifier;
			t.data = Symbol::parseIdentifier(b);
			break;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			t.type = Number;
			t.data = parseNumber(b);
			break;
		default:
			Error::fatal("Invalid character.", b->position());
		}

		l.append(t);
		b->consumeWhitespace();
	}

	return l;
}
#ifdef TEST
static Token::List strToList_(QString s, int l)
{
	SmartBuffer b(Buffer(s), QString("input%1").arg(l));
	return Token::tokenize(&b);
}
#define strToList(s) strToList_(s, __LINE__)
TEST(Token, tokenize)
{
	Token::List l;

	l = strToList("\"string\"");
	ASSERT_EQ(1, l.length());
	EXPECT_EQ(Token::String, l[0].type);
	EXPECT_EQ("string", l[0].data);

	l = strToList("\"str \\\" ing\"");
	ASSERT_EQ(1, l.length());
	EXPECT_EQ(Token::String, l[0].type);
	EXPECT_EQ("str \" ing", l[0].data);

	l = strToList("identifier");
	ASSERT_EQ(1, l.length());
	EXPECT_EQ(Token::Identifier, l[0].type);
	EXPECT_EQ("identifier", l[0].data);

	l = strToList("'i");
	ASSERT_EQ(1, l.length());
	EXPECT_EQ(Token::Character, l[0].type);
	EXPECT_EQ("i", l[0].data);

	l = strToList("'\\0020    '\\0");
	ASSERT_EQ(2, l.length());
	EXPECT_EQ(Token::Character, l[0].type);
	EXPECT_EQ(" ", l[0].data);
	EXPECT_EQ(Token::Character, l[1].type);
	EXPECT_EQ(QString(QChar('\0')), l[1].data);

	l = strToList("$ id @ \"hey\".hi");
	ASSERT_EQ(6, l.length());
	EXPECT_EQ(Token::Operator, l[0].type);
	EXPECT_EQ("$", l[0].data);
	EXPECT_EQ(Token::Identifier, l[1].type);
	EXPECT_EQ("id", l[1].data);
	EXPECT_EQ(Token::Operator, l[2].type);
	EXPECT_EQ("@", l[2].data);
	EXPECT_EQ(Token::String, l[3].type);
	EXPECT_EQ("hey", l[3].data);
	EXPECT_EQ(Token::Operator, l[4].type);
	EXPECT_EQ(".", l[4].data);
	EXPECT_EQ(Token::Identifier, l[5].type);
	EXPECT_EQ("hi", l[5].data);
}
#endif


QDebug operator<<(QDebug dbg, const Token &t)
{
	switch (t.type)
	{
	case Token::Character:
		//dbg.nospace() << "<C " << t.data << ">";
		dbg.nospace() << "<C " << QString("%0").arg(t.data.at(0).unicode(),1,16) << ">";
		break;
	case Token::String:
		dbg.nospace() << "<S " << t.data << ">";
		break;
	case Token::Number:
		dbg.nospace() << "<N " << t.data << ">";
		break;
	case Token::Identifier:
		dbg.nospace() << "<I " << t.data << ">";
		break;
	case Token::Operator:
		dbg.nospace() << "<O " << t.data << ">";
		break;
	case Token::Comment:
		dbg.nospace() << "</ " << t.data << ">";
		break;
	default:
		dbg.nospace() << "<? " << t.data << ">";
	}

	return dbg.space();
}
