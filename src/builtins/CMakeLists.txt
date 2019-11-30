add_library(builtins
    builtins.c
    cd.c
    export.c
    history.c
    shopt.c
    break_continue.c)

target_link_libraries(builtins options)

######################

# SHOPT TEST

add_executable(test_builtin_shopt tests/test_shopt.c)

target_link_libraries(test_builtin_shopt builtins)

set_target_properties(test_builtin_shopt
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "."
    EXCLUDE_FROM_ALL "true"
)

######################

add_custom_target(builtins_check
    DEPENDS test_builtin_shopt
)
