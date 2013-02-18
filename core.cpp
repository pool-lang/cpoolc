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

#include "core.h"

#include <QString>

#include "integer.h"
#include "pool-include.h"

namespace Core
{
	Scope *createGlobalScope()
	{
		Scope *g = new Scope();

		QString prefix = "core::";

		/*g->newSymbol(new Integer(    "int",   0, true));
		g->newSymbol(new Integer(   "uint",   0, false));

		g->newSymbol(new Integer(   "int8",   8, true));
		g->newSymbol(new Integer(  "uint8",   8, false));
		g->newSymbol(new Integer(  "int16",  16, true));
		g->newSymbol(new Integer( "uint16",  16, false));
		g->newSymbol(new Integer(  "int32",  32, true));
		g->newSymbol(new Integer( "uint32",  32, false));
		g->newSymbol(new Integer(  "int64",  64, true));
		g->newSymbol(new Integer( "uint64",  64, false));
		g->newSymbol(new Integer( "int128", 128, true));
		g->newSymbol(new Integer("uint128", 128, false));*/

		return g;
	}
}
