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

#include "buffer.h"

#include <math.h>

#include <QChar>
#include <QDebug>

#include "test.h"

const QChar Buffer::END = QChar(-1);

Buffer::Buffer(QString data):
	data(data),
	pos(0)
{
}

Buffer::Buffer(const Buffer &buffer):
	data(buffer.data),
	pos(buffer.pos)
{

}

uint Buffer::toEnd()
{
	return data.length() - pos;
}
#ifdef TEST
TEST(Buffer, toEnd)
{
	Buffer b("A long string!");

	EXPECT_EQ(14, b.toEnd());
	EXPECT_EQ(14, b.toEnd());
	EXPECT_EQ(14, b.toEnd());
	EXPECT_EQ(14, b.toEnd());

	b.pop();

	EXPECT_EQ(13, b.toEnd());
	EXPECT_EQ(13, b.toEnd());
	EXPECT_EQ(13, b.toEnd());

	b.pop();
	b.pop();
	b.pop();

	EXPECT_EQ(10, b.toEnd());

	b.pop();
	b.pop();
	b.pop();
	b.pop();
	b.pop();
	b.pop();
	b.pop();
	b.pop();
	b.pop();
	b.pop();

	EXPECT_EQ(0, b.toEnd());

	b.pop();
	EXPECT_EQ(0, b.toEnd());
	b.pop();
	EXPECT_EQ(0, b.toEnd());
	b.pop();
	EXPECT_EQ(0, b.toEnd());
}
#endif

bool Buffer::canRead(uint count)
{
	return toEnd() >= count;
}
#ifdef TEST
TEST(Buffer, canRead)
{
	Buffer b("A string!");

	EXPECT_TRUE(b.canRead(0));
	EXPECT_TRUE(b.canRead(9));
	EXPECT_FALSE(b.canRead(10));
}
#endif

void Buffer::seek(uint where)
{
	pos = qMin(where, (uint)data.length());
}
#ifdef TEST
TEST(Buffer, seek)
{
	Buffer b("A string!");

	b.seek(0);
	EXPECT_EQ('A', b.peek());
	b.seek(4);
	EXPECT_EQ('r', b.peek());
	b.seek(8);
	EXPECT_EQ('!', b.peek());
	b.seek(9);
	EXPECT_EQ(-1, b.peek());
	b.seek(25);
	EXPECT_EQ(-1, b.peek());
	b.seek(0);
	EXPECT_EQ('A', b.peek());
}
#endif
void Buffer::move(int offset)
{
	seek(qMax((int)(pos)+offset, 0));
}
#ifdef TEST
TEST(Buffer, move)
{
	Buffer b("A string!");

	b.move(1);
	EXPECT_EQ(' ', b.peek());
	b.move(1);
	EXPECT_EQ('s', b.peek());

	b.move(4);
	EXPECT_EQ('n', b.peek());
	b.move(-1);
	EXPECT_EQ('i', b.peek());
	b.move(-3);
	EXPECT_EQ('s', b.peek());

	b.move(-20);
	EXPECT_EQ('A', b.peek());
	b.move(200);
	EXPECT_EQ(-1, b.peek());
}
#endif

uint Buffer::tell()
{
	return pos;
}
#ifdef TEST
TEST(Buffer, tell)
{
	Buffer b("A string!");

	EXPECT_EQ(0, b.tell());
	b.read(5);
	EXPECT_EQ(5, b.tell());
}
#endif

uint Buffer::length()
{
	return data.length();
}
#ifdef TEST
TEST(Buffer, length)
{
	Buffer("A string!");

	EXPECT_EQ(0, Buffer("").length());
	EXPECT_EQ(5, Buffer("01234").length());
	EXPECT_EQ(10, Buffer("0123456789").length());
}
#endif

QChar Buffer::peek()
{
	if (!canRead(1)) return EOF;

	return data[pos];
}
#ifdef TEST
TEST(Buffer, peek)
{
	Buffer b("A Str!");

	for ( uint i = 0; i < 10; i++ )
		EXPECT_EQ("A", b.peek());
}
#endif

QChar Buffer::pop()
{
	if (!canRead(1)) return EOF;

	return data[pos++];
}
#ifdef TEST
TEST(Buffer, pop)
{
	Buffer b("A Str!");

	EXPECT_EQ('A', b.pop());
	EXPECT_EQ(' ', b.pop());
	EXPECT_EQ('S', b.pop());
	EXPECT_EQ('t', b.pop());
	EXPECT_EQ('r', b.pop());
	EXPECT_EQ('!', b.pop());

	for ( uint i = 0; i < 10; i++ )
		EXPECT_EQ(-1, b.pop());
}
#endif

QString Buffer::read()
{
	QString r = look();
	pos = data.length();

	return r;
}
#ifdef TEST
TEST(Buffer, read_all)
{
	Buffer b("A long string!");

	EXPECT_EQ("A long", b.read(6));
	EXPECT_EQ("", b.read(0));
	EXPECT_EQ(" string!", b.read());
	EXPECT_EQ("", b.read());

	Buffer b2("A longer string!");
	EXPECT_EQ("A longer string!", b2.read());
	EXPECT_EQ("", b2.read());
}
#endif

QString Buffer::read(uint count)
{
	QString r = look(count);
	pos += r.length();

	return r;
}
#ifdef TEST
TEST(Buffer, read)
{
	Buffer b("A long string!");

	EXPECT_EQ("A long", b.read(6));
	EXPECT_EQ("", b.read(0));
	EXPECT_EQ(" str", b.read(4));
	EXPECT_EQ("ing", b.read(3));
	EXPECT_EQ(QString("!"), b.read(2));
	EXPECT_EQ("", b.read(2));
}
#endif

QString Buffer::look()
{
	return data.mid(pos);
}
#ifdef TEST
TEST(Buffer, look_all)
{
	Buffer b("A long string!");

	EXPECT_EQ("A long", b.look(6));
	EXPECT_EQ("", b.look(0));
	EXPECT_EQ("A long string!", b.look());
	EXPECT_EQ("A long string!", b.look());

	Buffer b2("A longer string!");
	EXPECT_EQ("A longer string!", b2.look());
	EXPECT_EQ("A longer string!", b2.look());
}
#endif

QString Buffer::look(uint count)
{
	if ( toEnd() < count ) count = toEnd(); // Only read what we have.

	return data.mid(pos, count);
}
#ifdef TEST
TEST(Buffer, look)
{
	Buffer b("A long string!");

	EXPECT_EQ("A long", b.look(6));
	EXPECT_EQ("", b.look(0));
	EXPECT_EQ("A lo", b.look(4));
	EXPECT_EQ("A l", b.look(3));
	EXPECT_EQ("A ", b.look(2));
	EXPECT_EQ("A long string!", b.look(14));
}
#endif

Buffer Buffer::copy()
{
	return Buffer(*this);
}

QString Buffer::get(uint start, uint stop)
{
	return data.mid(start, stop-start);
}
#ifdef TEST
TEST(Buffer, get)
{
	Buffer b("abcdefghijklmnopqrstuvwxyz");

	EXPECT_EQ("abcdefg", b.get(0, 7));
	EXPECT_EQ("cdefghij", b.get(2, 10));
}
#endif
