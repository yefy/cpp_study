TARGET  = project_cpp
TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

message("project_cpp path = "$$PWD)

INCLUDEPATH +=  ../project_cpp_lib_test/src \
                ../project_lua/src \
                ../project_lua_lib_test/src \
                ../project_gtest/src \
                ../project_gmock/src


#macx {
# mac only
#}
#unix:!macx{
# linux only
#}
#win32 {
# windows only

#INCLUDEPATH += D:\openssl-1.0.1c_static_w32_mingw\include
#LIBS += -LD:\openssl-1.0.1c_static_w32_mingw -lssl -lcrypto -lws2_32 -lgdi32

INCLUDEPATH += C:\msys+7za+wget+svn+git+mercurial+cvs-rev13\msys\local\include
LIBS += -LC:\msys+7za+wget+svn+git+mercurial+cvs-rev13\msys\local\lib -lssl -lcrypto -lws2_32 -lgdi32 -lprotobuf

#INCLUDEPATH += C:\msys+7za+wget+svn+git+mercurial+cvs-rev13\msys\local\ssl_bak\include
#LIBS += -LC:\msys+7za+wget+svn+git+mercurial+cvs-rev13\msys\local\ssl_bak\lib -lssl -lcrypto -lws2_32 -lgdi32
#}


CONFIG(debug, debug|release) {
DESTDIR +=          ../../build_debug/bin
OBJECTS_DIR +=      ../../build_debug/objects
LIBS += -L../../build_debug/bin -lproject_cpp_lib_test -lproject_lua -lproject_gtest -lproject_gmock
} else {
DESTDIR +=          ../../build_release/bin
OBJECTS_DIR +=      ../../build_release/objects
LIBS += -L../../build_release/bin -lproject_cpp_lib_test -lproject_lua -lproject_gtest -lproject_gmock
}

SOURCES += src/main.cpp \
    src/lua/skp_lua_lual_requiref.cpp \
    src/lua/skp_lua_log.cpp \
    src/lua/skp_lua_call.cpp \
    src/skp_common.cpp \
    src/skp_log.cpp \
    src/cpp/skp_allocator_test.cpp \
    src/cpp/skp_cpp_test.cpp \
    src/lua/skp_lua_test.cpp \
    src/openssl/skp_AES.cpp \
    src/openssl/skp_sha256.cpp \
    src/openssl/skp_DES.cpp \
    src/openssl/crypt.cpp \
    src/openssl/crypttool.cpp \
    src/protobuf/skp_protobuf_test.cpp \
    src/protobuf/caffe.pb.cc \
    src/protobuf/test.pb.cc

HEADERS += \
    src/cpp/skp_allocator.h \
    src/lua/skp_lua_lual_requiref.h \
    src/lua/skp_lua_common.h \
    src/lua/skp_lua_log.h \
    src/lua/skp_lua_call.h \
    src/skp_common.h \
    src/skp_log.h \
    src/cpp/skp_allocator_test.h \
    src/cpp/skp_cpp_test.h \
    src/lua/skp_lua_test.h \
    src/openssl/skp_AES.h \
    src/openssl/skp_sha256.h \
    src/openssl/skp_DES.h \
    src/openssl/crypt.h \
    src/protobuf/skp_protobuf_test.h \
    src/protobuf/caffe.pb.h \
    src/protobuf/test.pb.h

DISTFILES += \
    ../lua/src/base/class.lua \
    ../lua/src/base/common.lua \
    ../lua/src/test/class1.lua \
    ../lua/src/test/class2.lua \
    ../lua/src/test/class3.lua \
    ../lua/src/test/func.lua \
    ../lua/src/test/lua_lib.lua \
    ../lua/src/test/lual_requiref.lua




