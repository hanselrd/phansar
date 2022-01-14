#ifndef PHANSAR_COMMON_UTILITY_RULE_OF_N_HPP
#define PHANSAR_COMMON_UTILITY_RULE_OF_N_HPP

#include <phansar/common/utility/default_operations.hpp>

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

#define PH_RULE_OF_3(_classname)                                                                   \
    PH_COPY_CONSTRUCTOR(_classname);                                                               \
    PH_COPY_ASSIGNMENT(_classname);                                                                \
    PH_DESTRUCTOR(_classname)

#define PH_RULE_OF_3_DEFAULT(_classname)                                                           \
    PH_COPY_CONSTRUCTOR_DEFAULT(_classname);                                                       \
    PH_COPY_ASSIGNMENT_DEFAULT(_classname);                                                        \
    PH_DESTRUCTOR_DEFAULT(_classname)

#endif
