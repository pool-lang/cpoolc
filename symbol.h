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

#ifndef SYMBOL_H
#define SYMBOL_H

#include <stdint.h>
#include <QString>

class Symbol;

#include "smartbuffer.h"
#include "scope.h"
#include "token.h"

class Symbol
{
public:
	enum Type {
		Unknown,
		Function,
		Interface,
		Value
	};

private:
	QString id;
	bool defined;

protected:
	Type type;

public:
	Symbol();

	Type getType();
	QString getID();

	static bool isIdentifierCharacter(QChar c);
	static bool isIdentifierStartCharacter(QChar c);
	static QString parseIdentifier(SmartBuffer *b);
	static QString parseQualifiedIdentifier(SmartBuffer *b);
};

#endif // SYMBOL_H
