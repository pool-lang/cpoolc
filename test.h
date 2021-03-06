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

#ifndef TEST_H
#define TEST_H

#ifdef TEST
	#include <gtest/gtest.h>

	#define IFACE_TEST(iface) \
		template <class T> \
		void test##iface (void)

	#define RUN_IFACE_TEST(iface, impl) TEST(impl, iface##Compatability) \
	                                { test##iface<impl>(); }
\
	// Define Streaming Operators for some Qt types.
	#include <QString>
	static ::std::ostream& operator<<(::std::ostream& os, const QString &p)
	{
		os << "here";
		os << p.toStdString();
	}
	static ::std::ostream& operator<<(::std::ostream& os, const QChar &p)
	{
		os << '"' << p.toAscii() << '"';
	}

#else ///// NOT TESTING
	#define RUN_IFACE_TEST(iface, impl) // Gone
#endif

#endif // TEST_H
