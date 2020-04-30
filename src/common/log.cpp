#include <phansar/common/log.hpp>

#include <phansar/vendor/plibsys.hpp>
#include <phansar/vendor/rangev3.hpp>
#include <phansar/vendor/spdlog_private.hpp>

#include <cstdlib>

#define LOG_MAX_FILE_SIZE (1024 * 1024 * 5)

namespace phansar::common::log::detail {
auto parse_file_name(std::string_view file_name) -> std::string {
    return file_name | ranges::views::split('/') | ranges::views::drop_while([](const auto & s) {
               return ! ranges::equal(s, ranges::view::c_str("include")) &&
                      ! ranges::equal(s, ranges::view::c_str("src")) &&
                      ! ranges::equal(s, ranges::view::c_str("test")) &&
                      ! ranges::equal(s, ranges::view::c_str("vendor"));
           }) |
           ranges::views::drop(1) | ranges::views::join('/') | ranges::to<std::string>();
}
} // namespace phansar::common::log::detail

namespace phansar::common::log {
void init(std::string_view          log_file,
          spdlog::level::level_enum log_level,
          std::string_view          log_name) {
    if (log_file.empty()) {
        return;
    }

    auto pattern = std::string{"[%Y-%m-%d %H:%M:%S.%e %z] [%n] [%t] [%^%l%$] [%g@%#] %v"};

    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_pattern(pattern);
    console_sink->set_level(log_level);

    auto rotating_sink =
        std::make_shared<spdlog::sinks::rotating_file_sink_mt>(std::string{log_file},
                                                               LOG_MAX_FILE_SIZE,
                                                               3);
    rotating_sink->set_pattern(pattern);
    rotating_sink->set_level(log_level);

    auto logger = std::make_shared<spdlog::logger>(
        spdlog::logger{std::string{log_name}, {console_sink, rotating_sink}});
    logger->set_level(spdlog::level::trace);
    spdlog::set_default_logger(logger);

    LOGI("");
    LOGD("Logger initialized");
    LOGD("  log file: {}", log_file);

#ifndef NDEBUG
    LOGT("     trace");
    LOGD("     debug");
    LOGI("      info");
    LOGW("   warning");
    LOGE("     error");
    LOGC("  critical");
#endif

    auto cpu_str = std::string{};
#ifdef P_CPU_ALPHA
    cpu_str += " ALPHA";
#endif
#ifdef P_CPU_ARM
    cpu_str += " ARM";
#endif
#ifdef P_CPU_ARM_32
    cpu_str += " ARM_32";
#endif
#ifdef P_CPU_ARM_64
    cpu_str += " ARM_64";
#endif
#ifdef P_CPU_ARM_V2
    cpu_str += " ARM_V2";
#endif
#ifdef P_CPU_ARM_V3
    cpu_str += " ARM_V3";
#endif
#ifdef P_CPU_ARM_V4
    cpu_str += " ARM_V4";
#endif
#ifdef P_CPU_ARM_V5
    cpu_str += " ARM_V5";
#endif
#ifdef P_CPU_ARM_V6
    cpu_str += " ARM_V6";
#endif
#ifdef P_CPU_ARM_V7
    cpu_str += " ARM_V7";
#endif
#ifdef P_CPU_ARM_V8
    cpu_str += " ARM_V8";
#endif
#ifdef P_CPU_X86
    cpu_str += " X86";
#endif
#ifdef P_CPU_X86_32
    cpu_str += " X86_32";
#endif
#ifdef P_CPU_X86_64
    cpu_str += " X86_64";
#endif
#ifdef P_CPU_IA64
    cpu_str += " IA64";
#endif
#ifdef P_CPU_MIPS
    cpu_str += " MIPS";
#endif
#ifdef P_CPU_MIPS_I
    cpu_str += " MIPS_I";
#endif
#ifdef P_CPU_MIPS_II
    cpu_str += " MIPS_II";
#endif
#ifdef P_CPU_MIPS_III
    cpu_str += " MIPS_III";
#endif
#ifdef P_CPU_MIPS_IV
    cpu_str += " MIPS_IV";
#endif
#ifdef P_CPU_MIPS_32
    cpu_str += " MIPS_32";
#endif
#ifdef P_CPU_MIPS_64
    cpu_str += " MIPS_64";
#endif
#ifdef P_CPU_POWER
    cpu_str += " POWER";
#endif
#ifdef P_CPU_POWER_32
    cpu_str += " POWER_32";
#endif
#ifdef P_CPU_POWER_64
    cpu_str += " POWER_64";
#endif
#ifdef P_CPU_SPARC
    cpu_str += " SPARC";
#endif
#ifdef P_CPU_SPARC_V8
    cpu_str += " SPARC_V8";
#endif
#ifdef P_CPU_SPARC_V9
    cpu_str += " SPARC_V9";
#endif
#ifdef P_CPU_HPPA
    cpu_str += " HPPA";
#endif
#ifdef P_CPU_HPPA_32
    cpu_str += " HPPA_32";
#endif
#ifdef P_CPU_HPPA_64
    cpu_str += " HPPA_64";
#endif
    LOGI("CPU:{}", cpu_str);
    /* LOGI("CPU count: {}", 0); */
    /* LOGI("CPU cache line size: {}", 0); */
    LOGI_IF(P_BYTE_ORDER,
            "CPU endianness: {}",
            (P_BYTE_ORDER == P_LITTLE_ENDIAN) ? "little" : "big");

    auto os_str = std::string{};
#ifdef P_OS_DARWIN
    os_str += " DARWIN";
#endif
#ifdef P_OS_DARWIN32
    os_str += " DARWIN32";
#endif
#ifdef P_OS_DARWIN64
    os_str += " DARWIN64";
#endif
#ifdef P_OS_BSD4
    os_str += " BSD4";
#endif
#ifdef P_OS_FREEBSD
    os_str += " FREEBSD";
#endif
#ifdef P_OS_DRAGONFLY
    os_str += " DRAGONFLY";
#endif
#ifdef P_OS_NETBSD
    os_str += " NETBSD";
#endif
#ifdef P_OS_OPENBSD
    os_str += " OPENBSD";
#endif
#ifdef P_OS_AIX
    os_str += " AIX";
#endif
#ifdef P_OS_HPUX
    os_str += " HPUX";
#endif
#ifdef P_OS_TRU64
    os_str += " TRU64";
#endif
#ifdef P_OS_SOLARIS
    os_str += " SOLARIS";
#endif
#ifdef P_OS_QNX
    os_str += " QNX";
#endif
#ifdef P_OS_QNX6
    os_str += " QNX6";
#endif
#ifdef P_OS_BB10
    os_str += " BB10";
#endif
#ifdef P_OS_SCO
    os_str += " SCO";
#endif
#ifdef P_OS_UNIXWARE
    os_str += " UNIXWARE";
#endif
#ifdef P_OS_IRIX
    os_str += " IRIX";
#endif
#ifdef P_OS_HAIKU
    os_str += " HAIKU";
#endif
#ifdef P_OS_SYLLABLE
    os_str += " SYLLABLE";
#endif
#ifdef P_OS_BEOS
    os_str += " BEOS";
#endif
#ifdef P_OS_OS2
    os_str += " OS2";
#endif
#ifdef P_OS_VMS
    os_str += " VMS";
#endif
#ifdef P_OS_AMIGA
    os_str += " AMIGA";
#endif
#ifdef P_OS_UNIX
    os_str += " UNIX";
#endif
#ifdef P_OS_LINUX
    os_str += " LINUX";
#endif
#ifdef P_OS_MAC9
    os_str += " MAC9";
#endif
#ifdef P_OS_MAC
    os_str += " MAC";
#endif
#ifdef P_OS_MAC32
    os_str += " MAC32";
#endif
#ifdef P_OS_MAC64
    os_str += " MAC64";
#endif
#ifdef P_OS_CYGWIN
    os_str += " CYGWIN";
#endif
#ifdef P_OS_MSYS
    os_str += " MSYS";
#endif
#ifdef P_OS_WIN
    os_str += " WIN";
#endif
#ifdef P_OS_WIN64
    os_str += " WIN64";
#endif
#ifdef P_OS_ANDROID
    os_str += " ANDROID";
#endif
    LOGI("OS:{}", os_str);

    auto cc_str = std::string{};
#ifdef P_CC_MSVC
    cc_str += " MSVC";
#endif
#ifdef P_CC_GNU
    cc_str += " GNU";
#endif
#ifdef P_CC_MINGW
    cc_str += " MINGW";
#endif
#ifdef P_CC_INTEL
    cc_str += " INTEL";
#endif
#ifdef P_CC_CLANG
    cc_str += " CLANG";
#endif
#ifdef P_CC_SUN
    cc_str += " SUN";
#endif
#ifdef P_CC_XLC
    cc_str += " XLC";
#endif
#ifdef P_CC_HP
    cc_str += " HP";
#endif
#ifdef P_CC_DEC
    cc_str += " DEC";
#endif
#ifdef P_CC_MIPS
    cc_str += " MIPS";
#endif
#ifdef P_CC_USLC
    cc_str += " USLC";
#endif
#ifdef P_CC_WATCOM
    cc_str += " WATCOM";
#endif
#ifdef P_CC_BORLAND
    cc_str += " BORLAND";
#endif
#ifdef P_CC_PGI
    cc_str += " PGI";
#endif
#ifdef P_CC_CRAY
    cc_str += " CRAY";
#endif
    LOGI("Compiler:{}", cc_str);

    /* LOGI("System RAM: {}", "unknown"); */

    auto build_type_str =
#ifdef NDEBUG
        "release"
#else
        "debug"
#endif
        ;
    LOGI("Build type: {}", build_type_str);

    std::atexit([] {
        LOGD("Logger shutdown");
        LOGI("");
    });
}
} // namespace phansar::common::log