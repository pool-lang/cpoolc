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

#include <iostream>
#include <stdint.h>
#include <string.h>
#include <sysexits.h>

#include <QFile>
#include <QDebug>
#include <QxtCore/QxtCommandOptions>

#include "symbol.h"
#include "function.h"

using namespace std;

/*bool vaild = false;
unsigned int line = 1;
const char *source = NULL;

#define YY_INPUT(buf, result, max_size) \
{                                       \
	size_t left = max_size;             \
	char *i = buf;                      \
	result = 0;                         \
	while ( left-- > 0 )                \
	{                                   \
		if ( *source == '\0' ) break;   \
		*i++ = *(source++);             \
		result++;                       \
	}                                   \
}*/

#include "pool.h" // Parser

void usage ( QxtCommandOptions *opt )
{
	opt->showUsage();
	exit(EX_USAGE);
}

int main ( int argc, char **argv )
{
	QxtCommandOptions opt;
	opt.add("output", "Where to write the output file to.", QxtCommandOptions::Required);
	opt.alias("output", "o");
	opt.add("help", "Display this text.");
	opt.alias("help", "h");
	opt.parse(argc, argv);
	if ( opt.count("help") || opt.showUnrecognizedWarning() ) usage(&opt);

	QStringList pos = opt.positional();
	if ( pos.length() < 1 )
	{
		cerr << "Error: No source files." << endl;
		usage(&opt); // No files.
	}
	if ( pos.length() > 1 )
	{
		if (opt.count("output")) // Multiple files and only one output.
		{
			cerr << "Error: Multiple source files but output file given." << endl;
			usage(&opt); // No files.
		}

		for ( QStringList::Iterator i = pos.begin(); i != pos.end(); i++ )
		{
			system((QString(argv[0])+" '"+*i+"'").toStdString().c_str());
		}
		exit(0); // Our work here is done.
	}

	QFile src(pos[0]);
	if (!src.open(QIODevice::ReadOnly))
	{
		cerr << "Error: could not open source file." << endl;
		exit(EX_IOERR);
	}
	QString qstr = QString(src.readAll());
	std::string sstr(qstr.toStdString());
	Buffer b;
	b.init(qstr);
	//source = sstr.c_str();

	/*while (yyparse())
		;*/

	PoolParser parser;
	QString test;
	Error e;

	qDebug() << parser.test(b, test, e);
	qDebug() << test;

	return 0;
}
