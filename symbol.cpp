// Copyright 2012 Kevin Cox

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

#include "test.h"
#include "variable.h"

Symbol::Symbol()
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

Symbol *Symbol::parseDecleartion(SmartBuffer *b, Scope *s)
{
	if ( b->read(3) == "var" )
	{
		Variable *v = Variable::parseVariableDeclearation(b);
		return NULL;
	}
	else return NULL;
}

QString Symbol::parseIdentifier(SmartBuffer *b)
{
	QString id;

	QChar c = b->peek();
	if (( c >= 'a' && c <= 'z' ) ||
		( c >= 'A' && c <= 'Z' ) ||
		( c == '_' )
	   )
	{
		id.append(c);
		b->move(1);
	}
	else return "";

	while (true)
	{
		c = b->peek();

		if (( c >= 'a' && c <= 'z' ) ||
			( c >= 'A' && c <= 'Z' ) ||
			( c >= '0' && c <= '9' ) ||
			( c == '_' )
		   )
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
	SmartBuffer b(Buffer("id _id 9not id943 I_d9s"));
	//                    01234567890123456789012

	EXPECT_EQ("id", Symbol::parseIdentifier(&b));
	b.consumeWhitespace();
	EXPECT_EQ("_id", Symbol::parseIdentifier(&b));
	b.consumeWhitespace();
	EXPECT_EQ("", Symbol::parseIdentifier(&b));

	b.seek(12);
	EXPECT_EQ("id943", Symbol::parseIdentifier(&b));
	b.consumeWhitespace();
	EXPECT_EQ("I_d9s", Symbol::parseIdentifier(&b));
	b.consumeWhitespace();
	EXPECT_EQ("", Symbol::parseIdentifier(&b));
	b.consumeWhitespace();
	EXPECT_EQ("", Symbol::parseIdentifier(&b));
	b.consumeWhitespace();
}
#endif
