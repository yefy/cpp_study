#-------------------------------------------------
#
# Project created by QtCreator 2018-06-15T15:24:25
#
#-------------------------------------------------

TARGET = project_gmock
TEMPLATE = lib

message("project_gmock path = "$$PWD)


CONFIG(debug, debug|release) {
DESTDIR +=          ../../build_debug/bin
OBJECTS_DIR +=      ../../build_debug/objects
LIBS += -L../../build_debug/bin -lproject_gtest
} else {
DESTDIR +=          ../../build_release/bin
OBJECTS_DIR +=      ../../build_release/objects
LIBS += -L../../build_release/bin -lproject_gtest
}

INCLUDEPATH += ./src \
                ../project_gtest/src


#DEFINES += PROJECT_LUA_LIBRARY
#DLUA_BUILD_AS_DLL

SOURCES += \
    src/gmock.cc \
    src/gmock_main.cc \
    src/gmock-all.cc \
    src/gmock-cardinalities.cc \
    src/gmock-internal-utils.cc \
    src/gmock-matchers.cc \
    src/gmock-spec-builders.cc

DISTFILES += \
    src/gmock/gmock-generated-nice-strict.h.pump

HEADERS += \
    src/gmock/gmock.h \
    src/gmock/gmock-actions.h \
    src/gmock/gmock-cardinalities.h \
    src/gmock/gmock-generated-actions.h \
    src/gmock/gmock-generated-actions.h.pump \
    src/gmock/gmock-generated-function-mockers.h \
    src/gmock/gmock-generated-function-mockers.h.pump \
    src/gmock/gmock-generated-matchers.h \
    src/gmock/gmock-generated-matchers.h.pump \
    src/gmock/gmock-generated-nice-strict.h \
    src/gmock/gmock-matchers.h \
    src/gmock/gmock-more-actions.h \
    src/gmock/gmock-more-matchers.h \
    src/gmock/gmock-spec-builders.h \
    src/gmock/internal/gmock-generated-internal-utils.h \
    src/gmock/internal/gmock-generated-internal-utils.h.pump \
    src/gmock/internal/gmock-internal-utils.h \
    src/gmock/internal/gmock-port.h

