#ifndef PHANSAR_COMMON_UTILITY_DEFAULT_OPERATIONS_HPP
#define PHANSAR_COMMON_UTILITY_DEFAULT_OPERATIONS_HPP

#define PH_CONSTRUCTOR(_classname) _classname()
#define PH_CONSTRUCTOR_IMPLEMENTATION(_classname, ...)                                             \
    _classname __VA_OPT__(<__VA_ARGS__>)::_classname()
#define PH_CONSTRUCTOR_DEFAULT(_classname, ...)                                                    \
    PH_CONSTRUCTOR_IMPLEMENTATION(_classname, __VA_ARGS__) = default
#define PH_CONSTRUCTOR_DELETE(_classname, ...)                                                     \
    PH_CONSTRUCTOR_IMPLEMENTATION(_classname, __VA_ARGS__) = delete

#define PH_COPY_CONSTRUCTOR(_classname) _classname(const _classname &)
#define PH_COPY_CONSTRUCTOR_IMPLEMENTATION(_classname, ...)                                        \
    _classname __VA_OPT__(<__VA_ARGS__>)::_classname(const _classname & _other)
#define PH_COPY_CONSTRUCTOR_DEFAULT(_classname, ...)                                               \
    PH_COPY_CONSTRUCTOR_IMPLEMENTATION(_classname, __VA_ARGS__) = default
#define PH_COPY_CONSTRUCTOR_DELETE(_classname, ...)                                                \
    PH_COPY_CONSTRUCTOR_IMPLEMENTATION(_classname, __VA_ARGS__) = delete

#define PH_COPY_ASSIGNMENT(_classname) auto operator=(const _classname &)->_classname &
#define PH_COPY_ASSIGNMENT_IMPLEMENTATION(_classname, ...)                                         \
    auto _classname __VA_OPT__(<__VA_ARGS__>)::operator=(const _classname & _other)->_classname &
#define PH_COPY_ASSIGNMENT_DEFAULT(_classname, ...)                                                \
    PH_COPY_ASSIGNMENT_IMPLEMENTATION(_classname, __VA_ARGS__) = default
#define PH_COPY_ASSIGNMENT_DELETE(_classname, ...)                                                 \
    PH_COPY_ASSIGNMENT_IMPLEMENTATION(_classname, __VA_ARGS__) = delete

#define PH_MOVE_CONSTRUCTOR(_classname) _classname(_classname &&) noexcept
#define PH_MOVE_CONSTRUCTOR_IMPLEMENTATION(_classname, ...)                                        \
    _classname __VA_OPT__(<__VA_ARGS__>)::_classname(_classname && _other) noexcept
#define PH_MOVE_CONSTRUCTOR_DEFAULT(_classname, ...)                                               \
    PH_MOVE_CONSTRUCTOR_IMPLEMENTATION(_classname, __VA_ARGS__) = default
#define PH_MOVE_CONSTRUCTOR_DELETE(_classname, ...)                                                \
    PH_MOVE_CONSTRUCTOR_IMPLEMENTATION(_classname, __VA_ARGS__) = delete

#define PH_MOVE_ASSIGNMENT(_classname) auto operator=(_classname &&) noexcept->_classname &
#define PH_MOVE_ASSIGNMENT_IMPLEMENTATION(_classname, ...)                                         \
    auto _classname __VA_OPT__(<__VA_ARGS__>)::operator=(                                          \
        _classname && _other) noexcept->_classname &
#define PH_MOVE_ASSIGNMENT_DEFAULT(_classname, ...)                                                \
    PH_MOVE_ASSIGNMENT_IMPLEMENTATION(_classname, __VA_ARGS__) = default
#define PH_MOVE_ASSIGNMENT_DELETE(_classname, ...)                                                 \
    PH_MOVE_ASSIGNMENT_IMPLEMENTATION(_classname, __VA_ARGS__) = delete

#define PH_DESTRUCTOR(_classname) ~_classname()
#define PH_DESTRUCTOR_IMPLEMENTATION(_classname, ...)                                              \
    _classname __VA_OPT__(<__VA_ARGS__>)::~_classname()
#define PH_DESTRUCTOR_DEFAULT(_classname, ...)                                                     \
    PH_DESTRUCTOR_IMPLEMENTATION(_classname, __VA_ARGS__) = default
#define PH_DESTRUCTOR_DELETE(_classname, ...)                                                      \
    PH_DESTRUCTOR_IMPLEMENTATION(_classname, __VA_ARGS__) = delete

#endif
