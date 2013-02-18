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

#include <iostream>
#include <stdint.h>
#include <string.h>
#include <sysexits.h>

#include <QFile>
#include <QDebug>
#include <QxtCore/QxtCommandOptions>

#include "symbol.h"
#include "function.h"
#include "core.h"
#include "smartbuffer.h"
#include "ast.h"

using namespace std;

#include "pool-include.h" // Parser

void usage ( QxtCommandOptions *opt )
{
	opt->showUsage();
	exit(EX_USAGE);
}

int main ( int argc, char **argv )
{
	 QLocale::setDefault(QLocale::C); // This isn't a UI, we want things to be
	                                  // consistant across compiles, environment
	                                  // independant.

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
	SmartBuffer b(&src);

	if ( b.look(2) == "#!" )      // Skip the hashbang.
		while ( b.pop() != '\n' ) //
			;

	Token::List tl = Token::tokenize(&b);
	qDebug() << tl;
	AST::List ast = AST::parse(tl);
	qDebug() << ast;

	//Module *mod = Module::parse(&b);

	cerr << "SUCCESS!" << endl;

	return 0;
}
