#-------------------------------------------------
#
# Project created by QtCreator 2018-06-15T16:40:15
#
#-------------------------------------------------

TARGET = project_lua_lib_test
TEMPLATE = lib

CONFIG(debug, debug|release) {
DESTDIR +=          ../../build_debug/bin
OBJECTS_DIR +=      ../../build_debug/objects
LIBS += -L../../build_debug/bin -lproject_lua
} else {
DESTDIR +=          ../../build_release/bin
OBJECTS_DIR +=      ../../build_release/objects
LIBS += -L../../build_release/bin -lproject_lua
}

#DEFINES += PROJECT_LUA_LIB_TEST_LIBRARY

INCLUDEPATH +=  ../project_lua \
                ../project_lua/src

SOURCES += project_lua_lib_test.cpp

HEADERS += project_lua_lib_test.h
