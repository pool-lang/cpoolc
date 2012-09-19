-- Copyright 2012 Kevin Cox

--[[---------------------------------------------------------------------------]
[                                                                              ]
[  This software is provided 'as-is', without any express or implied           ]
[  warranty. In no event will the authors be held liable for any damages       ]
[  arising from the use of this software.                                      ]
[                                                                              ]
[  Permission is granted to anyone to use this software for any purpose,       ]
[  including commercial applications, and to alter it and redistribute it      ]
[  freely, subject to the following restrictions:                              ]
[                                                                              ]
[  1. The origin of this software must not be misrepresented; you must not     ]
[     claim that you wrote the original software. If you use this software in  ]
[     a product, an acknowledgment in the product documentation would be       ]
[     appreciated but is not required.                                         ]
[                                                                              ]
[  2. Altered source versions must be plainly marked as such, and must not be  ]
[     misrepresented as being the original software.                           ]
[                                                                              ]
[  3. This notice may not be removed or altered from any source distribution.  ]                                                           *
[                                                                              ]
[-----------------------------------------------------------------------------]]

L.import "qt"

L.qpeg = {}

do

local headers = T.List(T.dir.getfiles(".", "*.h"))
local sources = T.List(T.dir.getfiles(".", "*.cpp"))

L.qpeg.headers = T.List{"buffer.h", "match.h", "token.h"}:map(C.path)
L.qpeg.sources = T.List{"buffer.cpp", "match.cpp", "token.cpp"}:map(C.path)
L.qpeg.sources:extend(L.qpeg.headers:map(L.qt.moc))

L.qt.addLib "QtCore"

local parsergen = L.qt.compile(T.List(headers):extend(sources), "@CParser")

function L.qpeg.generateParser ( input, header, source )
	input = C.path(input)
	header = C.path(header)
	source = C.path(source)

	C.addGenerator({input}, {parsergen, input, header}, {header}, {
		description = "Generating "..header
	})
	C.addGenerator({input}, {parsergen, input, source}, {source}, {
		description = "Generating "..source
	})
end

end
