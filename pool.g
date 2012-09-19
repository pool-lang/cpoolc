lang="C++"
classname="PoolParser"

inclass
{

}

{
#include "module.h"
}

string:int -> "this2356isatest";

S:int -> (WS)*;
RS:int -> WS (WS)*;
WS:int -> " "/"\t"/"\v"/"\f"/EOL;
DIGIT:QChar -> "0"/"1"/"2"/"3"/"4"/"5"/"6"/"7"/"8"/"9";
UPPER:QChar -> "A"/"B"/"C"/"D"/"E"/"F"/"G"/"H"/"I"/"J"/"K"/"L"/"M"/
			   "N"/"O"/"P"/"Q"/"R"/"S"/"T"/"U"/"V"/"W"/"X"/"Y"/"Z";
LOWER:QChar -> "a"/"b"/"c"/"d"/"e"/"f"/"g"/"h"/"i"/"j"/"k"/"l"/"m"/
			   "n"/"o"/"p"/"q"/"r"/"s"/"t"/"u"/"v"/"w"/"x"/"y"/"z";
ALPHA:QChar -> UPPER / LOWER;
ALPHANUM:QChar -> ALPHA / DIGIT;
EOL:int -> "\n" / "\r\n" / "\r";

identifier:QString -> ALPHA (ALPHANUM)*;

tuple:int -> "$";

hashBang:int -> "#!" (!EOL .)* EOL;

module:Module -> (hashBang)? string;

functionBody:Function -> functionSignature? blockContents;
functionSignature:Function -> ( S tuple S identifier? S tuple S S ":" ) /
							  ( S identifier? S tuple? S S ":" );

blockContents:int -> (statement)*;
statement:int -> (!";" .)* ";";
