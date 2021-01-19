add_library(fundot_core
            hash.cpp
            comparison.cpp
            arithmetic.cpp
            logical.cpp
            bitwise.cpp
            input.cpp
            output.cpp
            built_in.cpp
            eval.cpp
            )

add_executable(fundot main.cpp)

target_link_libraries(fundot fundot_core)
