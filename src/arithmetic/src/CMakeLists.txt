include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ast)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/eval)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lexer)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/parser)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/utils)


add_subdirectory(ast/)
add_subdirectory(eval/)
add_subdirectory(parser/)
add_subdirectory(lexer/)
add_subdirectory(utils/)
