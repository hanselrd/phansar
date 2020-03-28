#include <ph_common.hpp>

int main(int argc, char *argv[]) {
    PH_UNUSED(argc);
    PH_UNUSED(argv);

    ph::common::log::init("ph_client.log");

    return 0;
}
