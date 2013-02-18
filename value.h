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

#ifndef VALUE_H
#define VALUE_H

#include <stdint.h>
#include <QtCore>

class Interface;

class Value
{
public:
	enum ValueType {
		object,
		interger,
		real
	};

private:
	Interface *type;
	ValueType currentType;
	union {
		qint64 intValue; //@todo Use a bigger value. (gmp?)
		double floatValue;
	};

public:
	Value(Interface *type = NULL);

	Value *setType(ValueType t);
};

#endif // VALUE_H
