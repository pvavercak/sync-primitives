include_directories(${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES})

add_executable(test_custom_type src/test_custom_type.cc)
target_link_libraries(test_custom_type PRIVATE pva::sync)
add_test(NAME test_custom_type COMMAND test_custom_type)

add_executable(test_stl_containers src/test_stl_containers.cc)
target_link_libraries(test_stl_containers PRIVATE pva::sync)
set_target_properties(test_stl_containers PROPERTIES
    CXX_CLANG_TIDY clang-tidy)
add_test(NAME test_stl_containers COMMAND test_stl_containers)
