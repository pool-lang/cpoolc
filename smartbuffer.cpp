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

#include "smartbuffer.h"

#include "test.h"

SmartBuffer::SmartBuffer(Buffer b):
	Buffer(b),
	posindex(b.length())
{
	init();
}


SmartBuffer::Position::Position(uint line, uint col):
	line(line),
	column(col)
{
}

int SmartBuffer::Position::operator ==(const SmartBuffer::Position &p) const
{
	return ( this->line == p.line ) && ( this->column == p.column );
}

void SmartBuffer::init()
{
	uint prev = tell();
	seek(0);

	Position p(0,0);
	for ( uint i = 0; i < length(); i++ )
	{
		QChar c = pop();
		if ( c == '\n' )
		{
			p.line++;
			p.column = 0;
		}
		else p.column++;

		posindex[i] = p;
	}
}

SmartBuffer::Position SmartBuffer::position()
{
	return posindex[tell()];
}
#ifdef TEST
TEST(SmartBuffer, position)
{
	SmartBuffer b(Buffer("a string\ntwo lines"));
	//                    12345678 0123456789 // Column
	//                    0123456789012345678 // Index

	EXPECT_EQ('a', b.tell());
	EXPECT_EQ(SmartBuffer::Position(0,0), b.position());
	b.seek(1);
	EXPECT_EQ(' ', b.tell());
	EXPECT_EQ(SmartBuffer::Position(0,1), b.position());
	b.seek(7);
	EXPECT_EQ('g', b.tell());
	EXPECT_EQ(SmartBuffer::Position(0,7), b.position());
	b.seek(8);
	EXPECT_EQ('\n', b.tell());
	EXPECT_EQ(SmartBuffer::Position(1,0), b.position());
	b.seek(9);
	EXPECT_EQ('t', b.tell());
	EXPECT_EQ(SmartBuffer::Position(1,1), b.position());
}
#endif

QDebug operator<<(QDebug dbg, const SmartBuffer::Position &p)
{
	dbg.nospace() << "{l:" << p.line << ", c:" << p.column << "}";

	return dbg.space();
}
