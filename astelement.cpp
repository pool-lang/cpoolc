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

#include "astelement.h"

#include "astliteral.h"
#include "astidentifier.h"

QString ASTElement::prettyType() const
{
	return "<ASTE unknown>";
}

ASTElement *ASTElement::fromTokens(Token::List *tl, Token::List::iterator *tli)
{
	ASTElement *r = NULL;

	r = ASTIdentifier::fromTokens(tl, tli);
	if ( r != NULL ) return r;

	r = ASTLiteral::fromTokens(tl, tli);
	if ( r != NULL ) return r;

	return NULL;
}

QDebug operator<<(QDebug dbg, const ASTElement *t)
{
	dbg.nospace() << t->prettyType();
	return dbg.space();
}

