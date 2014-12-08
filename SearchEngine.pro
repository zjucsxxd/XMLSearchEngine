TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

SOURCES += main.cpp \
    docparser.cpp \
    referencestringcleaner.cpp \
    indexedword.cpp \
    avlinterface.cpp \
    porter2_stemmer.cpp \
    stemmedword.cpp \
    interface.cpp \
    hashtableinterface.cpp \
    indexhandler.cpp \
    queryengine.cpp

HEADERS += \
    docparser.h \
    referencestringcleaner.h \
    avltree.h \
    rapidxml_iterators.h \
    rapidxml_print.h \
    rapidxml_utils.h \
    rapidxml.h \
    indexinterface.h \
    indexedword.h \
    avlinterface.h \
    porter2_stemmer.h \
    stemmedword.h \
    interface.h \
    hashtableinterface.h \
    indexhandler.h \
    queryengine.h

