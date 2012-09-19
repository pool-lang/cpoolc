lang="C++"
classname="PoolParser"

inclass
{

}

{
#include "module.h"
}

S:int -> (WS)*;
RS:int -> WS (WS)*;
WS:int -> " "/"\t"/"\v"/"\f"/EOL;
EOL:int -> "\n" / "\r\n" / "\r";

hashBang:int -> "#!" !(EOL) EOL;

module:Module -> (hashBang)? ;

