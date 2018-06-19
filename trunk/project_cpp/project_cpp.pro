TARGET  = project_cpp
TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH +=  ../project_cpp_lib_test \
                ../project_lua \
                ../project_lua/src \
                ../project_lua_lib_test

LIBS += -L./debug -lproject_cpp_lib_test -lproject_lua

SOURCES += main.cpp \
    src/lua/skp_lua.cpp \
    src/cpp/skp_cpp.cpp \
    src/common.cpp \
    src/lua/skp_lua_lual_requiref.cpp

HEADERS += \
    src/cpp/skp_allocator.h \
    src/lua/skp_lua.h \
    src/cpp/skp_cpp.h \
    src/common.h \
    src/lua/skp_lua_lual_requiref.h

