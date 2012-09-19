#-------------------------------------------------
#
# Project created by QtCreator 2010-09-23T16:02:01
#
#-------------------------------------------------

QT       += core

CONFIG += console
TARGET = CParser
TEMPLATE = app


SOURCES += main.cpp\
    token.cpp \
    predicate.cpp \
    peg.cpp \
    parsepeg.cpp \
    charpredicate.cpp \
    buffer.cpp \
    pegast.cpp \
    generator.cpp \
    cppgenerator.cpp \
    javagenerator.cpp \
    match.cpp \
#    peg-new.cpp \
    kalimatgenerator.cpp

HEADERS  += \
    Lexer/token.h \
    Lexer/predicate.h \
    Lexer/charpredicate.h \
    Lexer/BuiltInLexerPredicates.h \
    Lexer/buffer.h \
    token.h \
    predicate.h \
    parsepeg.h \
    charpredicate.h \
    buffer.h \
    pegast.h \
    generator.h \
    cppgenerator.h \
    javagenerator.h \
    match.h \
    kalimatgenerator.h \
    peg.h

FORMS    +=
