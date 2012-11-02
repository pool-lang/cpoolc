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

#ifndef BUFFER_H
#define BUFFER_H

#include <QString>

class Buffer
{
public:
	static const QChar END;
	//typedef uint Position;

private:
	QString data;
	uint pos;

public:
	Buffer(QString data);
	Buffer(const Buffer &buffer);

	uint toEnd ();
	bool canRead(uint count = 1);

	void seek(uint where);
	void move(int off);
	uint tell();

	uint length();

	QChar pop();
	QChar peek();

	QString read();
	QString read(uint count);

	QString look();
	QString look(uint count);

	Buffer copy();

	QString get(uint start, uint stop);
};

#endif // BUFFER_H
