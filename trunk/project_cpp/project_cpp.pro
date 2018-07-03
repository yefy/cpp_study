TARGET  = project_cpp
TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

message("project_cpp path = "$$PWD)

INCLUDEPATH +=  ../project_cpp_lib_test/src \
                ../project_lua/src \
                ../project_lua_lib_test/src \
                ../project_gtest


CONFIG(debug, debug|release) {
DESTDIR +=          ../../build_debug/bin
OBJECTS_DIR +=      ../../build_debug/objects
LIBS += -L../../build_debug/bin -lproject_cpp_lib_test -lproject_lua -lproject_gtest
} else {
DESTDIR +=          ../../build_release/bin
OBJECTS_DIR +=      ../../build_release/objects
LIBS += -L../../build_release/bin -lproject_cpp_lib_test -lproject_lua -lproject_gtest
}

SOURCES += src/main.cpp \
    src/lua/skp_lua.cpp \
    src/cpp/skp_cpp.cpp \
    src/common.cpp \
    src/lua/skp_lua_lual_requiref.cpp \
    src/lua/skp_lua_log.cpp \
    src/lua/skp_lua_call.cpp

HEADERS += \
    src/cpp/skp_allocator.h \
    src/lua/skp_lua.h \
    src/cpp/skp_cpp.h \
    src/common.h \
    src/lua/skp_lua_lual_requiref.h \
    src/lua/skp_lua_common.h \
    src/lua/skp_lua_log.h \
    src/lua/skp_lua_call.h

DISTFILES += \
    ../lua/src/base/class.lua \
    ../lua/src/base/common.lua \
    ../lua/src/test/class1.lua \
    ../lua/src/test/class2.lua \
    ../lua/src/test/class3.lua \
    ../lua/src/test/func.lua \
    ../lua/src/test/lua_lib.lua \
    ../lua/src/test/lual_requiref.lua




