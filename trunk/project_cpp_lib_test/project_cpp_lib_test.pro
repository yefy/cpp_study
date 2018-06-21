#-------------------------------------------------
#
# Project created by QtCreator 2018-06-15T16:06:10
#
#-------------------------------------------------

TARGET = project_cpp_lib_test
TEMPLATE = lib

message("project_cpp_lib_test path = "$$PWD)

CONFIG(debug, debug|release) {
DESTDIR +=          ../../build_debug/bin
OBJECTS_DIR +=      ../../build_debug/objects
} else {
DESTDIR +=          ../../build_release/bin
OBJECTS_DIR +=      ../../build_release/objects
}

#DEFINES += PROJECT_CPP_LIB_TEST_LIBRARY

SOURCES += src/project_cpp_lib_test.cpp

HEADERS += src/project_cpp_lib_test.h
