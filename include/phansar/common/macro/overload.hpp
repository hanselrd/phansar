#ifndef PHANSAR_COMMON_MACRO_OVERLOAD_HPP
#define PHANSAR_COMMON_MACRO_OVERLOAD_HPP

#define PH_OVERLOAD(_name, ...)                                                                    \
    PH_OVERLOAD_OVR(_name, PH_OVERLOAD_NUM_ARGS(__VA_ARGS__))(__VA_ARGS__)

#define PH_OVERLOAD_OVR(_name, _num)  PH_OVERLOAD__OVR(_name, _num)
#define PH_OVERLOAD__OVR(_name, _num) _name##_##_num

#define PH_OVERLOAD_ARG_N(_0,                                                                      \
                          _1,                                                                      \
                          _2,                                                                      \
                          _3,                                                                      \
                          _4,                                                                      \
                          _5,                                                                      \
                          _6,                                                                      \
                          _7,                                                                      \
                          _8,                                                                      \
                          _9,                                                                      \
                          _10,                                                                     \
                          _11,                                                                     \
                          _12,                                                                     \
                          _13,                                                                     \
                          _14,                                                                     \
                          _15,                                                                     \
                          _16,                                                                     \
                          _17,                                                                     \
                          _18,                                                                     \
                          _19,                                                                     \
                          _20,                                                                     \
                          _21,                                                                     \
                          _22,                                                                     \
                          _23,                                                                     \
                          _24,                                                                     \
                          _25,                                                                     \
                          _26,                                                                     \
                          _27,                                                                     \
                          _28,                                                                     \
                          _29,                                                                     \
                          _30,                                                                     \
                          _31,                                                                     \
                          _32,                                                                     \
                          _33,                                                                     \
                          _34,                                                                     \
                          _35,                                                                     \
                          _36,                                                                     \
                          _37,                                                                     \
                          _38,                                                                     \
                          _39,                                                                     \
                          _40,                                                                     \
                          _41,                                                                     \
                          _42,                                                                     \
                          _43,                                                                     \
                          _44,                                                                     \
                          _45,                                                                     \
                          _46,                                                                     \
                          _47,                                                                     \
                          _48,                                                                     \
                          _49,                                                                     \
                          _50,                                                                     \
                          _51,                                                                     \
                          _52,                                                                     \
                          _53,                                                                     \
                          _54,                                                                     \
                          _55,                                                                     \
                          _56,                                                                     \
                          _57,                                                                     \
                          _58,                                                                     \
                          _59,                                                                     \
                          _60,                                                                     \
                          _61,                                                                     \
                          _62,                                                                     \
                          _63,                                                                     \
                          N,                                                                       \
                          ...)                                                                     \
    N

#define PH_OVERLOAD_RSEQ_N                                                                         \
    64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42,    \
        41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20,    \
        19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0

#define PH_OVERLOAD_DETECT_0_ARGS(...) PH_OVERLOAD__DETECT_0##__VA_ARGS__##_
#define PH_OVERLOAD__DETECT_0_                                                                     \
    , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , ,  \
        , , , , , , , , , , , , , , , , , 0

#define PH_OVERLOAD__NUM_ARGS(_args) PH_OVERLOAD_ARG_N _args
#define PH_OVERLOAD_NUM_ARGS(...)                                                                  \
    PH_OVERLOAD__NUM_ARGS((PH_OVERLOAD_DETECT_0_ARGS(__VA_ARGS__), PH_OVERLOAD_RSEQ_N))

#endif
