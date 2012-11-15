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

#include "error.h"

#include <iostream>
#include <stdlib.h>

namespace Error
{
	void reportMessage ( QString msg )
	{
		std::cerr << "Error: " << msg.toStdString() << std::endl;
	}
	void reportMessage ( QString msg, SmartBuffer::Position p )
	{
		std::cerr << QString("%1:%2:%3: ").arg(p.file).arg(p.line).arg(p.column).toStdString();
	}

	void fatal ( QString msg )
	{
		reportMessage(msg);
		exit(1);
	}
	void fatal ( QString msg, SmartBuffer::Position p )
	{
		reportMessage(msg, p);
		exit(1);
	}
}
