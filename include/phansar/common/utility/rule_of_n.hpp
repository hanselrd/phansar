#ifndef PHANSAR_COMMON_UTILITY_RULE_OF_N_HPP
#define PHANSAR_COMMON_UTILITY_RULE_OF_N_HPP

#include <phansar/common/macro/pack.hpp>
#include <phansar/common/utility/default_operation.hpp>

#define PH_RULE_OF_6(_classname)                                                                   \
    PH_CONSTRUCTOR(_classname);                                                                    \
    PH_COPY_CONSTRUCTOR(_classname);                                                               \
    PH_COPY_ASSIGNMENT(_classname);                                                                \
    PH_MOVE_CONSTRUCTOR(_classname);                                                               \
    PH_MOVE_ASSIGNMENT(_classname);                                                                \
    PH_DESTRUCTOR(_classname)

#define PH_RULE_OF_6_DEFAULT(_classname)                                                           \
    PH_CONSTRUCTOR_DEFAULT(_classname);                                                            \
    PH_COPY_CONSTRUCTOR_DEFAULT(_classname);                                                       \
    PH_COPY_ASSIGNMENT_DEFAULT(_classname);                                                        \
    PH_MOVE_CONSTRUCTOR_DEFAULT(_classname);                                                       \
    PH_MOVE_ASSIGNMENT_DEFAULT(_classname);                                                        \
    PH_DESTRUCTOR_DEFAULT(_classname)

#define PH_RULE_OF_6_TEMPLATE_DEFAULT(_classname, _template, ...)                                  \
    _template PH_CONSTRUCTOR_DEFAULT(_classname, __VA_ARGS__);                                     \
    _template PH_COPY_CONSTRUCTOR_DEFAULT(_classname, __VA_ARGS__);                                \
    _template PH_COPY_ASSIGNMENT_DEFAULT(_classname, __VA_ARGS__);                                 \
    _template PH_MOVE_CONSTRUCTOR_DEFAULT(_classname, __VA_ARGS__);                                \
    _template PH_MOVE_ASSIGNMENT_DEFAULT(_classname, __VA_ARGS__);                                 \
    _template PH_DESTRUCTOR_DEFAULT(_classname, __VA_ARGS__)

#define PH_RULE_OF_5(_classname)                                                                   \
    PH_COPY_CONSTRUCTOR(_classname);                                                               \
    PH_COPY_ASSIGNMENT(_classname);                                                                \
    PH_MOVE_CONSTRUCTOR(_classname);                                                               \
    PH_MOVE_ASSIGNMENT(_classname);                                                                \
    PH_DESTRUCTOR(_classname)

#define PH_RULE_OF_5_DEFAULT(_classname)                                                           \
    PH_COPY_CONSTRUCTOR_DEFAULT(_classname);                                                       \
    PH_COPY_ASSIGNMENT_DEFAULT(_classname);                                                        \
    PH_MOVE_CONSTRUCTOR_DEFAULT(_classname);                                                       \
    PH_MOVE_ASSIGNMENT_DEFAULT(_classname);                                                        \
    PH_DESTRUCTOR_DEFAULT(_classname)

#define PH_RULE_OF_5_TEMPLATE_DEFAULT(_classname, _template, ...)                                  \
    _template PH_COPY_CONSTRUCTOR_DEFAULT(_classname, __VA_ARGS__);                                \
    _template PH_COPY_ASSIGNMENT_DEFAULT(_classname, __VA_ARGS__);                                 \
    _template PH_MOVE_CONSTRUCTOR_DEFAULT(_classname, __VA_ARGS__);                                \
    _template PH_MOVE_ASSIGNMENT_DEFAULT(_classname, __VA_ARGS__);                                 \
    _template PH_DESTRUCTOR_DEFAULT(_classname, __VA_ARGS__)

#define PH_RULE_OF_3(_classname)                                                                   \
    PH_COPY_CONSTRUCTOR(_classname);                                                               \
    PH_COPY_ASSIGNMENT(_classname);                                                                \
    PH_DESTRUCTOR(_classname)

#define PH_RULE_OF_3_DEFAULT(_classname)                                                           \
    PH_COPY_CONSTRUCTOR_DEFAULT(_classname);                                                       \
    PH_COPY_ASSIGNMENT_DEFAULT(_classname);                                                        \
    PH_DESTRUCTOR_DEFAULT(_classname)

#define PH_RULE_OF_3_TEMPLATE_DEFAULT(_classname, _template, ...)                                  \
    _template PH_COPY_CONSTRUCTOR_DEFAULT(_classname, __VA_ARGS__);                                \
    _template PH_COPY_ASSIGNMENT_DEFAULT(_classname, __VA_ARGS__);                                 \
    _template PH_DESTRUCTOR_DEFAULT(_classname, __VA_ARGS__)

#endif
