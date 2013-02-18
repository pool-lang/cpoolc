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

#include "astliteral.h"

#include "astliteralchar.h"
#include "astliteralstring.h"
#include "astliteralint.h"
#include "astliteralfloat.h"

ASTLiteral::ASTLiteral()
{
}

void ASTLiteral::setLiteralType(ASTLiteral::Type t)
{
	this->type = t;
}

void ASTLiteral::setPos(SmartBuffer::Position pos)
{
	this->pos = pos;
}

ASTElement::Type ASTLiteral::getType()
{
	return ASTElement::Literal;
}

SmartBuffer::Position ASTLiteral::definedAt()
{
	return pos;
}

ASTLiteral::Type ASTLiteral::getLiteralType()
{
	return type;
}

QString ASTLiteral::prettyType() const
{
	return "<ASTE Literal>";
}

ASTLiteral *ASTLiteral::fromTokens(Token::List *tl, Token::List::iterator *tli)
{
	ASTLiteral *r = NULL;

	r = ASTLiteralChar::fromTokens(tl, tli);
	if ( r != NULL ) return r;

	r = ASTLiteralString::fromTokens(tl, tli);
	if ( r != NULL ) return r;

	r = ASTLiteralInt::fromTokens(tl, tli);
	if ( r != NULL ) return r;

	r = ASTLiteralFloat::fromTokens(tl, tli);
	if ( r != NULL ) return r;

	return NULL;
}
