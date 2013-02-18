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

#ifndef INTERFACE_H
#define INTERFACE_H

#include <QString>
#include <QHash>

#include "overloadset.h"

class Variable;

class Interface
{
	QString name;
	QString binaryname;
	QHash<QString, Interface*> implements;

	QHash<QString, OverloadSet> functions;
	QHash<QString, Variable*>   variables;

	void init();
public:
	Interface();
	Interface(QString name);

	QString getName();
	Interface *setName(QString name);
};

#endif // INTERFACE_H
