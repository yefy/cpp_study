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


#DEFINES += PROJECT_LUA_LIBRARY
#DLUA_BUILD_AS_DLL

HEADERS += \
    gtest/gtest.h \
    gtest/gtest_pred_impl.h \
    gtest/gtest_prod.h \
    gtest/gtest-death-test.h \
    gtest/gtest-message.h \
    gtest/gtest-param-test.h \
    gtest/gtest-param-test.h.pump \
    gtest/gtest-printers.h \
    gtest/gtest-spi.h \
    gtest/gtest-test-part.h \
    gtest/gtest-typed-test.h \
    gtest/internal/gtest-death-test-internal.h \
    gtest/internal/gtest-filepath.h \
    gtest/internal/gtest-internal.h \
    gtest/internal/gtest-linked_ptr.h \
    gtest/internal/gtest-param-util.h \
    gtest/internal/gtest-param-util-generated.h \
    gtest/internal/gtest-port.h \
    gtest/internal/gtest-string.h \
    gtest/internal/gtest-tuple.h \
    gtest/internal/gtest-tuple.h.pump \
    gtest/internal/gtest-type-util.h \
    src/gtest-internal-inl.h

DISTFILES += \
    gtest/internal/gtest-param-util-generated.h.pump \
    gtest/internal/gtest-type-util.h.pump

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


