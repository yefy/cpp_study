#include "src/common.h"
#include "src/cpp/skp_cpp.h"
#include "src/lua/skp_lua.h"

int main(int argc, char *argv[])
{
    log_print(" ***** main start ***** ");

    func_run(cpp_test());
    func_run(lua_test());

    log_print(" ***** main end ***** ");

    return 0;
}
