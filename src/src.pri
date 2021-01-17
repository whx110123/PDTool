SOURCES	+= \
		$$PWD/main.cpp
HEADERS	+= \
		$$PWD/head.h

include ($$PWD/api/api.pri)
include ($$PWD/interface/interface.pri)
include ($$PWD/protocol/protocol.pri)

INCLUDEPATH	+= $$PWD/api 
INCLUDEPATH	+= $$PWD/interface 
INCLUDEPATH	+= $$PWD/protocol 



