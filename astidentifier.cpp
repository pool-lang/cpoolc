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

#include "astidentifier.h"

#include <stdlib.h>

#include "error.h"
#include "test.h"

ASTIdentifier::ASTIdentifier()
{
}

ASTIdentifier::ASTIdentifier(SmartBuffer::Position pos):
	pos(pos)
{
}

ASTElement::Type ASTIdentifier::getType()
{
	return Identifier;
}

SmartBuffer::Position ASTIdentifier::definedAt()
{
	return pos;
}

QString ASTIdentifier::prettyType() const
{
	return QString("<ASTE Identifier %0>").arg(data);
}

QString ASTIdentifier::getIdentifier()
{
	return data;
}

ASTIdentifier *ASTIdentifier::fromTokens(Token::List *tl,
                                         Token::List::iterator *tli)
{
	Token::List::iterator i = *tli;
	ASTIdentifier r((*i).defined);

	if ( i == tl->end() ) return NULL;

	if ( (*i).type == Token::Operator && (*i).data == ":" )
	{
		i++;
		if ( i == tl->end() ) return NULL;

		if ( (*i).type == Token::Operator && (*i).data == ":" )
		{
			r.data = "::";
			i++;
		}
		else return NULL;
	}

	if ( i == tl->end() ) return NULL;
	if ( (*i).type != Token::Identifier ) return NULL;

	r.data += (*i).data;
	i++;

	if ( i != tl->end() )
	{
		while ( (*i).type == Token::Operator && (*i).data == ":" )
		{
			i++;
			if ( i == tl->end() ) return NULL;

			if ( (*i).type == Token::Operator && (*i).data == ":" )
			{
				r.data += "::";
				i++;
				if ( i == tl->end() ) return NULL;
			}
			else
			{
				i--;
				break;
			}

			if ( (*i).type != Token::Identifier ) Error::fatal("Trailing ::.");
			r.data += (*i).data;

			i++;
			if ( i == tl->end() ) break;
		}
	}

	*tli = i;
	return new ASTIdentifier(r);
}
#ifdef TEST
static Token::List strToList_(QString s, int l)
{
	SmartBuffer b(Buffer(s), QString("input%1").arg(l));
	return Token::tokenize(&b);
}

#define strToList(s) strToList_(s, __LINE__)
TEST(ASTIdentifier, fromAST)
{
	Token::List l;
	Token::List::iterator li;
	ASTIdentifier *id;

	l = strToList("identifier");
	li = l.begin();
	id = ASTIdentifier::fromTokens(&l, &li);
	ASSERT_TRUE(id);
	EXPECT_EQ("identifier", id->getIdentifier());
	EXPECT_EQ(l.end(), li);
	free(id);

	l = strToList("::modid");
	li = l.begin();
	id = ASTIdentifier::fromTokens(&l, &li);
	ASSERT_TRUE(id);
	EXPECT_EQ("::modid", id->getIdentifier());
	EXPECT_EQ(l.end(), li);
	free(id);

	l = strToList("core::compiler");
	li = l.begin();
	id = ASTIdentifier::fromTokens(&l, &li);
	ASSERT_TRUE(id);
	EXPECT_EQ("core::compiler", id->getIdentifier());
	EXPECT_EQ(l.end(), li);
	free(id);

	l = strToList("this::is::an::error::");
	li = l.begin();
	id = ASTIdentifier::fromTokens(&l, &li);
	ASSERT_FALSE(id);
	EXPECT_EQ(l.begin(), li);
	free(id);

	l = strToList("an::id next::id");
	li = l.begin();
	id = ASTIdentifier::fromTokens(&l, &li);
	ASSERT_TRUE(id);
	EXPECT_EQ("an::id", id->getIdentifier());
	EXPECT_EQ(l.begin()+4, li);
	free(id);
}

#endif
