add_library(fundot_repl
            reader.cpp
            repl.cpp
            )

add_executable(fundot_bin fundot.cpp)

target_include_directories(fundot_repl PUBLIC ${PROJECT_SOURCE_DIR})

target_link_libraries(fundot_repl readline fundot_std)

target_link_libraries(fundot_bin fundot_repl)

set_target_properties(fundot_bin PROPERTIES OUTPUT_NAME fundot)
