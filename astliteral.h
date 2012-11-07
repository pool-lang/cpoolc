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

#ifndef ASTLITERAL_H
#define ASTLITERAL_H

#include "astelement.h"

class ASTLiteral: public ASTElement
{
public:
	enum Type {
		Interger,
		Float,
		String,
		Char,
	};

private:
	Type type;
	SmartBuffer::Position pos;

protected:
	void setLiteralType(Type t);
	void setPos(SmartBuffer::Position pos);

public:
	ASTLiteral();

	virtual ASTElement::Type getType();
	virtual SmartBuffer::Position definedAt();
	virtual Type getLiteralType() = 0;
};

#endif // ASTLITERAL_H
