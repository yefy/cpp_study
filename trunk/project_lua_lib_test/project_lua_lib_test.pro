#-------------------------------------------------
#
# Project created by QtCreator 2018-06-15T16:40:15
#
#-------------------------------------------------

TARGET = project_lua_lib_test
TEMPLATE = lib

DESTDIR += ../project_cpp/debug

#DEFINES += PROJECT_LUA_LIB_TEST_LIBRARY

INCLUDEPATH +=  ../project_lua \
                ../project_lua/src

LIBS += -L../project_cpp/debug -lproject_lua \


SOURCES += project_lua_lib_test.cpp

HEADERS += project_lua_lib_test.h
