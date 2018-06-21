TARGET  = project_cpp
TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

message("project_cpp path = "$$PWD)

INCLUDEPATH +=  ../project_cpp_lib_test/src \
                ../project_lua/src \
                ../project_lua_lib_test/src


CONFIG(debug, debug|release) {
DESTDIR +=          ../../build_debug/bin
OBJECTS_DIR +=      ../../build_debug/objects
LIBS += -L../../build_debug/bin -lproject_cpp_lib_test -lproject_lua
} else {
DESTDIR +=          ../../build_release/bin
OBJECTS_DIR +=      ../../build_release/objects
LIBS += -L../../build_release/bin -lproject_cpp_lib_test -lproject_lua
}

SOURCES += src/main.cpp \
    src/lua/skp_lua.cpp \
    src/cpp/skp_cpp.cpp \
    src/common.cpp \
    src/lua/skp_lua_lual_requiref.cpp

HEADERS += \
    src/cpp/skp_allocator.h \
    src/lua/skp_lua.h \
    src/cpp/skp_cpp.h \
    src/common.h \
    src/lua/skp_lua_lual_requiref.h \
    src/lua/skp_lua_common.h

DISTFILES += \
    ../lua/add.lua \
    ../lua/class.lua \
    ../lua/lua_lib.lua \
    ../lua/lual_requiref.lua \
    ../lua/class2.lua \
    ../lua/class3.lua

