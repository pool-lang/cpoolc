// Copyright 2012-2013 Kevin Cox

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

#include "symbol.h"

#include <QRegExp>
#include <QHash>

#include "test.h"
#include "variable.h"

Symbol::Symbol():
	type(Unknown)
{
}

Symbol::Type Symbol::getType()
{
	return type;
}

QString Symbol::getID()
{
	return id;
}

QString Symbol::parseIdentifier(SmartBuffer *b)
{
	QString id;

	QChar c = b->peek();
	if (isIdentifierStartCharacter(c))
	{
		id.append(c);
		b->move(1);
	}
	else return "";

	while (true)
	{
		c = b->peek();

		if (isIdentifierCharacter(c))
		{
			id.append(c);
			b->move(1);
		}
		else return id;
	}
}
#ifdef TEST
TEST(SmartBuffer, parseIdentifier)
{
	SmartBuffer b(Buffer("id _id 9not id943 I_d9s I_d9s::another"));
	//                    01234567890123456789012

	EXPECT_EQ("id", Symbol::parseIdentifier(&b));
	EXPECT_EQ(SmartBuffer::Position("", 1, 2), b.position());
	b.consumeWhitespace();
	EXPECT_EQ("_id", Symbol::parseIdentifier(&b));
	EXPECT_EQ(SmartBuffer::Position("", 1, 6), b.position());
	b.consumeWhitespace();
	EXPECT_EQ("", Symbol::parseIdentifier(&b));
	EXPECT_EQ(SmartBuffer::Position("", 1, 7), b.position());

	b.seek(12);
	EXPECT_EQ("id943", Symbol::parseIdentifier(&b));
	b.consumeWhitespace();
	EXPECT_EQ("I_d9s", Symbol::parseIdentifier(&b));
	b.consumeWhitespace();
	EXPECT_EQ("I_d9s", Symbol::parseIdentifier(&b));
	b.move(2);
	EXPECT_EQ("another", Symbol::parseIdentifier(&b));
	b.consumeWhitespace();
	EXPECT_EQ("", Symbol::parseIdentifier(&b));
	b.consumeWhitespace();
	EXPECT_EQ("", Symbol::parseIdentifier(&b));
	b.consumeWhitespace();
}
#endif

QString Symbol::parseQualifiedIdentifier(SmartBuffer *b)
{
	uint p = b->tell();
	QString r = parseIdentifier(b);

	if ( r == "" ) return r;

	while ( b->read(2) == "::" )
	{
		QString c = parseIdentifier(b);
		if ( c == "" )
		{
			b->seek(p); // Return to where we were.
			return c;
		}
		r += "::" + c;
	}

	b->move(-2);

	return r;
}
#ifdef TEST
TEST(SmartBuffer, parseQualifiedIdentifier)
{
	SmartBuffer b(Buffer("mod::id a::b::c::d::e not::::id"));
	//                    01234567890123456789012

	EXPECT_EQ("mod::id", Symbol::parseQualifiedIdentifier(&b));
	b.consumeWhitespace();
	EXPECT_EQ("a::b::c::d::e", Symbol::parseQualifiedIdentifier(&b));
	b.consumeWhitespace();
	EXPECT_EQ("", Symbol::parseQualifiedIdentifier(&b));
}


bool Symbol::isIdentifierCharacter(QChar c)
{
	return isIdentifierStartCharacter(c) ||
		   ( c >= '0' && c <= '9' );
}

bool Symbol::isIdentifierStartCharacter(QChar c)
{
	return ( c >= 'a' && c <= 'z' ) ||
		   ( c >= 'A' && c <= 'Z' ) ||
		   ( c == '_' );
}

#endif
