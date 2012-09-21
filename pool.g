lang="C++"
classname="PoolParser"
inclass
{
	QStack<Scope*> scopes;
}
{
#include "pool-include.h"
}

string:int -> "this2356isatest";

S:int -> (WS)*;
RS:int -> WS (WS)*;
WS:int -> " "/"\t"/"\v"/"\f"/EOL;
DIGIT:QChar -> _Digit:c { ret = c.Lexeme[0]; };
UPPER:QChar -> "A" { ret = 'A'; }
             / "B" { ret = 'B'; }
             / "C" { ret = 'C'; }
             / "D" { ret = 'D'; }
             / "E" { ret = 'E'; }
             / "F" { ret = 'F'; }
             / "G" { ret = 'G'; }
             / "H" { ret = 'H'; }
             / "I" { ret = 'I'; }
             / "J" { ret = 'J'; }
             / "K" { ret = 'K'; }
             / "L" { ret = 'L'; }
             / "M" { ret = 'M'; }
             / "N" { ret = 'N'; }
             / "O" { ret = 'O'; }
             / "P" { ret = 'P'; }
             / "Q" { ret = 'Q'; }
             / "R" { ret = 'R'; }
             / "S" { ret = 'S'; }
             / "T" { ret = 'T'; }
             / "U" { ret = 'U'; }
             / "V" { ret = 'V'; }
             / "W" { ret = 'W'; }
             / "X" { ret = 'X'; }
             / "Y" { ret = 'Y'; }
             / "Z" { ret = 'Z'; }
             ;
LOWER:QChar -> "a" { ret = 'a'; }
             / "b" { ret = 'b'; }
             / "c" { ret = 'c'; }
             / "d" { ret = 'd'; }
             / "e" { ret = 'e'; }
             / "f" { ret = 'f'; }
             / "g" { ret = 'g'; }
             / "h" { ret = 'h'; }
             / "i" { ret = 'i'; }
             / "j" { ret = 'j'; }
             / "k" { ret = 'k'; }
             / "l" { ret = 'l'; }
             / "m" { ret = 'm'; }
             / "n" { ret = 'n'; }
             / "o" { ret = 'o'; }
             / "p" { ret = 'p'; }
             / "q" { ret = 'q'; }
             / "r" { ret = 'r'; }
             / "s" { ret = 's'; }
             / "t" { ret = 't'; }
             / "u" { ret = 'u'; }
             / "v" { ret = 'v'; }
             / "w" { ret = 'w'; }
             / "x" { ret = 'x'; }
             / "y" { ret = 'y'; }
             / "z" { ret = 'z'; }
             ;
ALPHA:QChar -> UPPER:c / LOWER:c { ret = c; };
ALPHANUM:QChar -> ALPHA:c { ret = c; }
				/ DIGIT:c { ret = c; }
				;
IDSTART:QChar -> ALPHA:c { ret = c; }
			   / "_"     { ret = '_'; }
			   ;
IDCHAR:QChar  -> IDSTART:c { ret = c;   }
			   / DIGIT:c   { ret = c; }
			  ;
EOL:int -> "\n" / "\r\n" / "\r";

identifier:QString -> IDSTART:b { ret = QString(b); }
					 (IDCHAR:n { ret += n; })*
					 !IDCHAR S;

openScope:int -> "{" S { scopes.push(new Scope(scopes.top())); };
openFunction:int -> "[[" S { scopes.push(new Scope(scopes.top())); };
closeScope:Scope* -> "}" S { ret = scopes.pop(); };
closeFunction:Scope* -> "]]" S { ret = scopes.pop(); };

tuple:int -> "$" S;

hashBang:int -> "#!" (!EOL .)* EOL;

module:Module -> (hashBang)? identifier:s { std::cout << s.toStdString() << std::endl; };

function:Function* -> openFunction
					  functionSignature:f { ret = f; }
					  blockContents
					  closeFunction:s { ret->setScope(s); }
					  ;

functionSignature:Function* -> { ret = new Function(); }
							  ((!":")* ":");


blockContents:int -> (statement)*;
statement:int -> (!";" .)* ";";
