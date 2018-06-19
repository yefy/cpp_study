#-------------------------------------------------
#
# Project created by QtCreator 2018-06-15T15:24:25
#
#-------------------------------------------------

TARGET = project_lua
TEMPLATE = lib


CONFIG(debug, debug|release) {
DESTDIR +=          ../../build_debug/bin
OBJECTS_DIR +=      ../../build_debug/objects
} else {
DESTDIR +=          ../../build_release/bin
OBJECTS_DIR +=      ../../build_release/objects
}


#DEFINES += PROJECT_LUA_LIBRARY
#DLUA_BUILD_AS_DLL

SOURCES += \
    src/lapi.c \
    src/lauxlib.c \
    src/lbaselib.c \
    src/lbitlib.c \
    src/lcode.c \
    src/lcorolib.c \
    src/lctype.c \
    src/ldblib.c \
    src/ldebug.c \
    src/ldo.c \
    src/ldump.c \
    src/lfunc.c \
    src/lgc.c \
    src/linit.c \
    src/liolib.c \
    src/llex.c \
    src/lmathlib.c \
    src/lmem.c \
    src/loadlib.c \
    src/lobject.c \
    src/lopcodes.c \
    src/loslib.c \
    src/lparser.c \
    src/lstate.c \
    src/lstring.c \
    src/lstrlib.c \
    src/ltable.c \
    src/ltablib.c \
    src/ltm.c \
    src/lua.c \
    src/luac.c \
    src/lundump.c \
    src/lvm.c \
    src/lzio.c

HEADERS +=\
    src/lapi.h \
    src/lauxlib.h \
    src/lcode.h \
    src/lctype.h \
    src/ldebug.h \
    src/ldo.h \
    src/lfunc.h \
    src/lgc.h \
    src/llex.h \
    src/llimits.h \
    src/lmem.h \
    src/lobject.h \
    src/lopcodes.h \
    src/lparser.h \
    src/lstate.h \
    src/lstring.h \
    src/ltable.h \
    src/ltm.h \
    src/lua.h \
    src/lua.hpp \
    src/luaconf.h \
    src/lualib.h \
    src/lundump.h \
    src/lvm.h \
    src/lzio.h
