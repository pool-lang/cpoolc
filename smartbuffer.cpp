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

SmartBuffer::SmartBuffer(Buffer b, QString file):
	Buffer(b),
	posindex(b.length()),
	fname(file)
{
	init();
}

SmartBuffer::SmartBuffer(QFile *file):
	Buffer(file->readAll()),
	fname(file->fileName())
{
}


SmartBuffer::Position::Position(QString file, uint line, uint col):
	file(file),
	line(line),
	column(col),
	eof(false)
{
}

int SmartBuffer::Position::operator ==(const SmartBuffer::Position &that) const
{
	if ( this->file != that.file ) return false;

	if ( this->eof  && that.eof  ) return true;

	return ( this->line == that.line ) && ( this->column == that.column );
}

void SmartBuffer::init()
{
	uint prev = tell();
	seek(0);

	Position p(fname, 0,0);
	for ( uint i = 0; i < length(); i++ )
	{
		posindex[i] = p;

		QChar c = pop();
		if ( c == '\n' )
		{
			p.line++;
			p.column = 0;
		}
		else p.column++;
	}

	p.eof = true;
	posindex.append(p);

	seek(0);
}

SmartBuffer::Position SmartBuffer::position()
{
	return posindex[tell()];
}
#ifdef TEST
TEST(SmartBuffer, position)
{
	SmartBuffer b(Buffer("a string\ntwo lines"), "test");
	//                    12345678 0123456789 // Column
	//                    0123456789012345678 // Index

	EXPECT_EQ('a', b.peek());
	EXPECT_EQ(SmartBuffer::Position("test", 0,0), b.position());
	b.seek(1);
	EXPECT_EQ(' ', b.peek());
	EXPECT_EQ(SmartBuffer::Position("test",0,1), b.position());
	b.seek(7);
	EXPECT_EQ('g', b.peek());
	EXPECT_EQ(SmartBuffer::Position("test",0,7), b.position());
	b.seek(8);
	EXPECT_EQ('\n', b.peek());
	EXPECT_EQ(SmartBuffer::Position("test",0,8), b.position());
	b.seek(9);
	EXPECT_EQ('t', b.peek());
	EXPECT_EQ(SmartBuffer::Position("test",1,0), b.position());
	b.seek(10);
	EXPECT_EQ('w', b.peek());
	EXPECT_EQ(SmartBuffer::Position("test",1,1), b.position());
}
#endif

void SmartBuffer::consumeWhitespace()
{
	while (peek().isSpace())
		pop();
}
#ifdef TEST
TEST(SmartBuffer, consumeWhitespace)
{
	SmartBuffer b(Buffer("a \t\t string\ntwo lines"));

	b.consumeWhitespace();
	EXPECT_EQ('a', b.peek());

	b.seek(1);
	b.consumeWhitespace();
	EXPECT_EQ('s', b.peek());

	b.seek(11);
	b.consumeWhitespace();
	EXPECT_EQ('t', b.peek());

	b.seek(b.length());
	b.consumeWhitespace();
	EXPECT_EQ(-1, b.peek());
}
#endif

QDebug operator<<(QDebug dbg, const SmartBuffer::Position &p)
{
	if (p.eof) dbg.nospace() << "{EOF}";
	else     dbg.nospace() << "{l:" << p.line << ", c:" << p.column << "}";

	return dbg.space();
}
::std::ostream& operator<<(::std::ostream& os, const SmartBuffer::Position &p)
{
	if (p.eof) os << "{EOF}";
	else       os << "{l:" << p.line << ", c:" << p.column << "}";

	return os;
}

