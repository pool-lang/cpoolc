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

#include "astliteralstring.h"

ASTLiteralString::ASTLiteralString()
{
	setLiteralType(String);
}

ASTLiteralString::ASTLiteralString(QString d, SmartBuffer::Position pos):
	data(d)
{
	setPos(pos);
	setLiteralType(String);
}

QString ASTLiteralString::prettyType() const
{
	return QString("<ASTE LString %0>").arg(data);
}

QString ASTLiteralString::getData()
{
	return data;
}

ASTLiteralString *ASTLiteralString::fromTokens(Token::List *tl,
                                               Token::List::iterator *tli)
{
	if ( (**tli).type == Token::String )
	{
		ASTLiteralString *r = new ASTLiteralString((**tli).data, (**tli).defined);
		(*tli)++;
		return r;
	}

	return NULL;
}
