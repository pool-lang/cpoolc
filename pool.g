lang="C++"
classname="PoolParser"
inclass
{

}

test:QString -> "this is a test" {ret = "success";};

WhiteSpace:QString -> ("a"/"b"/"c")*;
EOL:QString -> "\n" / "\r\n" / "\r";
