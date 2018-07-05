#-------------------------------------------------
#
# Project created by QtCreator 2018-06-15T15:24:25
#
#-------------------------------------------------

TARGET = project_gtest
TEMPLATE = lib

message("project_gtest path = "$$PWD)


CONFIG(debug, debug|release) {
DESTDIR +=          ../../build_debug/bin
OBJECTS_DIR +=      ../../build_debug/objects
} else {
DESTDIR +=          ../../build_release/bin
OBJECTS_DIR +=      ../../build_release/objects
}

INCLUDEPATH += ./src


#DEFINES += PROJECT_LUA_LIBRARY
#DLUA_BUILD_AS_DLL

HEADERS += \
    src/gtest-internal-inl.h \
    src/gtest/gtest.h \
    src/gtest/gtest_pred_impl.h \
    src/gtest/gtest_prod.h \
    src/gtest/gtest-death-test.h \
    src/gtest/gtest-message.h \
    src/gtest/gtest-param-test.h \
    src/gtest/gtest-param-test.h.pump \
    src/gtest/gtest-printers.h \
    src/gtest/gtest-spi.h \
    src/gtest/gtest-test-part.h \
    src/gtest/gtest-typed-test.h \
    src/gtest/internal/gtest-death-test-internal.h \
    src/gtest/internal/gtest-filepath.h \
    src/gtest/internal/gtest-internal.h \
    src/gtest/internal/gtest-linked_ptr.h \
    src/gtest/internal/gtest-param-util.h \
    src/gtest/internal/gtest-param-util-generated.h \
    src/gtest/internal/gtest-port.h \
    src/gtest/internal/gtest-string.h \
    src/gtest/internal/gtest-tuple.h \
    src/gtest/internal/gtest-tuple.h.pump \
    src/gtest/internal/gtest-type-util.h

SOURCES += \
    src/gtest.cc \
    src/gtest_main.cc \
    src/gtest-all.cc \
    src/gtest-death-test.cc \
    src/gtest-filepath.cc \
    src/gtest-port.cc \
    src/gtest-printers.cc \
    src/gtest-test-part.cc \
    src/gtest-typed-test.cc

DISTFILES += \
    src/gtest/internal/gtest-param-util-generated.h.pump \
    src/gtest/internal/gtest-type-util.h.pump
