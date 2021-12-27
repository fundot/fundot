add_subdirectory(core)

add_subdirectory(std)

add_subdirectory(repl)

add_executable(fundot_bin fundot.cpp)

target_include_directories(fundot_bin PUBLIC ${PROJECT_SOURCE_DIR})

target_link_libraries(fundot_bin fundot_repl)

set_target_properties(fundot_bin PROPERTIES OUTPUT_NAME fundot)
