#include <common.hpp>
#include <docopt.h>
#include <fmt/format.h>
#include <iterator>
#include <string>

static const auto USAGE =
    /* R"(Phansar Server */

    /* Usage: */
    /*     ph_server ship new <name>... */
    /*     ph_server ship <name> move <x> <y> [--speed=<kn>] */
    /*     ph_server ship shoot <x> <y> */
    /*     ph_server mine (set|remove) <x> <y> [--moored | --drifting] */
    /*     ph_server (-h | --help) */
    /*     ph_server --version */

    /* Options: */
    /*     -h --help       Show this screen */
    /*     -v --version    Show version */
    /*     --speed=<kn>    Speed in knots [default: 10] */
    /*     --moored        Moored (anchored) mine */
    /*     --drifting      Drifting mine */
    /* )"; */
    R"(Phansar Server

    Usage:
        ph_server [options]

    Options:
        -h, --help                          Show this screen
        -v, --version                       Show version
        -l <file>, --log-file=<file>        Log file [default: {logfile}]
        -L <level>, --log-level=<level>     Log level [default: debug]
        -i <ip>, --ip=<ip>                  IP Address [default: 0.0.0.0]
        -p <port>, --port=<port>            Port [default: 7000]
        -t <threads>, --threads=<threads>   Number of threads [default: 2]

    Arguments:
        <level>: trace,debug,info,warn,error,critical,off
)";

auto main(int argc, char * argv[]) -> int {
    auto bin  = std::string{argv[0]};
    auto args = docopt::docopt(
        fmt::format(USAGE, fmt::arg("logfile", bin.substr(bin.find_last_of('/') + 1) + ".log")),
        {std::next(argv), std::next(argv, argc)},
        true,
        "Phansar Server 1.0");

    common::system::init(argc, argv);

    for (const auto & arg : args) {
        LOGI("{}: {}", arg.first, arg.second);
    }

    common::system::shutdown();

    return 0;
}
