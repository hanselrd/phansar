#include <common.hpp>

int main(int argc, char *argv[]) {
    common::system::init(argc, argv);
    common::system::shutdown();

    return 0;
}
