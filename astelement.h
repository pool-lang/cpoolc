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

#ifndef ASTELEMENT_H
#define ASTELEMENT_H

#include "smartbuffer.h"
#include "token.h"

class ASTElement
{
public:
	enum Type {
		None,
		Keyword,
		Literal,
		Identifier,
		Comment,
		Operator,
	};

	virtual SmartBuffer::Position definedAt() = 0;
	virtual Type getType() = 0;

	virtual QString prettyType() const;

	static ASTElement *fromTokens(Token::List *tl, Token::List::iterator *tli);
};

QDebug operator<<(QDebug dbg, const ASTElement *t);

#endif // ASTELEMENT_H
