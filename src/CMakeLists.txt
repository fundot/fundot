add_library(fundot
            arithmetic.cpp
            bitwise.cpp
            built_in.cpp
            comparison.cpp
            eval.cpp
            fundot.cpp
            hash.cpp
            input.cpp
            logical.cpp
            output.cpp
            )

add_executable(fundot_bin main.cpp)

target_link_libraries(fundot_bin fundot)

set_target_properties(fundot_bin PROPERTIES OUTPUT_NAME fundot)

install(TARGETS fundot_bin)
