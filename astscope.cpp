// Copyright 2011-2013 Kevin Cox

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

#include "astscope.h"

ASTScope::ASTScope(AST::List list, Type type, SmartBuffer::Position defined):
	def(defined),
	type(type),
	contents(list)
{
}

SmartBuffer::Position ASTScope::definedAt()
{
	return def;
}


ASTElement::Type ASTScope::getType()
{
	return Scope;
}

QString ASTScope::prettyType() const
{
	return QString("<ASTE Identifier>");
}

ASTScope *ASTScope::fromTokens(Token::List *tl, Token::List::iterator *tli)
{
	if ( (**tli).type != Token::Operator ) return NULL;

	Type t = None;
	Token::List::iterator i = *tli;
	SmartBuffer::Position pos = i->defined;

	if ( i->data == "{" )
	{
		t = Block;
		i++;
	}
	else if ( i->data == "[" )
	{
		tli++;
		if ( i->type == Token::Operator && i->data == "[" )
		{
			t = Function;
			i++;
		}
		else return NULL;
	}

	AST::List ast = AST::parse(*tl, &i);

	switch (t)
	{
		Block:
		if ( i->type == Token::Operator && i->data == "}" )
		{
			*tli = i;
			return new ASTScope(ast, Block, pos);
		}
		Function:
		if ( i->type == Token::Operator && i->data == "[" )
		{
			i++;
			if ( i->type == Token::Operator && i->data == "[" )
			{
				*tli = i;
				return new ASTScope(ast, Block, pos);
			}
		}
	}

	return NULL;
}
