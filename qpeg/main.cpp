/**************************************************************************
**   QPeg, the PEG parser generator
**   Copyright 2010 Mohamed Samy Ali - samy2004@gmail.com
**   This project is released under the Apache License version 2.0
**   as described in the included license.txt file
**************************************************************************/

#include <QFile>
#include <QTextStream>
#include <iostream>

#include "parsepeg.h"
#include "cppgenerator.h"
#include "javagenerator.h"
#include "kalimatgenerator.h"
#include "match.h"
#include "peg.h"

using namespace std;

QStringList lexize(Buffer &b, QString &error);
QString readInput(char *fname);
void testLexParse(Buffer &b);
void generatePegParser(int argc, char **argv);
int main(int argc, char *argv[])
{
    generatePegParser(argc, argv);
    return 0;
}

void printStackTrace(QStack<QString> stack)
{
    for(int i=0; i<stack.count(); i++)
    {
        for(int j=0; j<i;j++)
            cout<<" ";
        cout << stack[i].toStdString() << endl;
    }
}

void generatePegParser(int argc, char **argv)
{
    if(argc!=3)
    {
        cout << "Usage: QPeg grammarfile outputfile" << endl;
        cout.flush();
        return;
    }
    GenContext context;
    QString grammar = readInput(argv[1]);
    Error error;
    Buffer b;
    if(!grammar.endsWith("\n"))
        grammar.append("\n");
    b.init(grammar);
    PegGrammar *g;
    PegParser parser;
    bool result = false;
    try
    {
        result = parser.peg(b, g, error);
    }
    catch(Error err)
    {
        cout << "Peg Error: " << err.message.toStdString() << endl;
    }

    int n = g->rules.count();
    if(!result)
    {
        cout << "couldn't parse at rule " << n << " :(" <<endl;
        if(g->rules.count() !=0)
        {
            cout << "last rule successfully parsed was: " << g->rules[g->rules.count()-1]->name.toStdString() << endl;
        }
        b.restoreState(error.bufferState);
        cout << "Parse error at " << b.GetLine() << ":" << b.GetColumn() <<
        " near ..." ;
        if(b.eof())
           cout << "eof";
        else
            cout <<b.remainder().left(5).toStdString();
        cout << "... "<< endl;

        cout << error.message.toStdString() << endl;

        printStackTrace(parser.stackTrace);
            ::exit(1);
    }
    //*/
    for(int i=0; i<g->rules.count(); i++)
    {
        context.symbols[g->rules[i]->name] = g->rules[i];
    }

    QStringList generated;

    QFile output(QString::fromAscii(argv[2]));
    output.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);
    QTextStream out(&output);
    out.setCodec("UTF-8");
    out.setAutoDetectUnicode(true);
    //out.setGenerateByteOrderMark(true);
    QString statements;

    Generator *cppgen = NULL;
    bool langset = false;
    QString headerFullPath;
    if(g->options.contains("lang"))
    {
        QString lang = g->options["lang"];
        if(lang == "C++")
        {
            langset = true;
            cppgen = new CPPGenerator();
            QFileInfo fi(argv[2]);

            headerFullPath  = fi.absolutePath()+ "/" +fi.baseName() +".h";

            context.headerFileName = fi.completeBaseName();
            context.className = g->options["classname"];
            context.codeInClass = g->codeInClass;
        }
        else if(lang == "Java")
        {
            langset = true;
            cppgen = new JavaGenerator();
        }
        else if(lang == "Kalimat")
        {
            langset = true;
            cppgen = new KalimatGenerator();
            context.className = g->options["classname"];
        }
    }
    if(!langset)
        cppgen = new CPPGenerator();

    try
    {
        for(int i=0; i<g->rules.count(); i++)
        {
            cout << g->rules[i]->toString().toStdString() << endl;
            cout.flush();
            generated.append(cppgen->gen(g->rules[i], &context, statements, ""));
        }
    }
    catch(QString ex)
    {
        cout << ex.toStdString() <<endl;

        ::exit(1);
    }

    generated.prepend(cppgen->fileHeader(&context));
    generated.append(cppgen->fileFooter());

    if(g->prelude!="")
        generated.prepend(g->prelude);
    if(g->postlude!="")
        generated.append(g->postlude);

    for(int i=0; i<generated.length(); i++)
        out << generated[i] << endl;

    output.close();
    if(context.headerFileName != "")
    {
        output.setFileName(headerFullPath);
        output.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);
        QTextStream out(&output);
        out.setCodec("UTF-8");
        out.setAutoDetectUnicode(true);
        //out.setGenerateByteOrderMark(true);

        out << cppgen->headerFile(&context);
        output.close();;
    }

    cout << "done" <<endl;
    cout.flush();
}

void testLexParse(Buffer &b)
{
    QString error;
    QStringList tokens = lexize(b, error);
    if(error !="")
    {
        cout<<error.toStdString()<<endl;
        cout.flush();
        return;
    }
    else
    {
        PP pp(tokens);
        try
        {
            QVector<PegRule *> rules = pp.grammar();
            for(int i=0; i<rules.count(); i++)
                cout << rules[i]->toString().toStdString() << endl;
        }
        catch(QString err)
        {
            cout << err.toStdString();
        }
        return ;
    }
}

QString readInput(char *fname)
{
    QString inputFile = QString::fromAscii(fname);
    if(!QFile::exists(inputFile))
    {
        cout << "File not found: " << inputFile.toStdString() << endl;
        cout.flush();
        exit(0);
    }
    QFile input(inputFile);
    input.open(QFile::ReadOnly | QFile::Text);
    QTextStream in(&input);
    QString grammar = in.readAll();
    input.close();
    return grammar;
}
