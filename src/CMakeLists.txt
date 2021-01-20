add_library(fundot
            arithmetic.cpp
            bitwise.cpp
            cfun.cpp
            comparison.cpp
            eval.cpp
            hash.cpp
            input.cpp
            logical.cpp
            output.cpp
            )

target_link_libraries(fundot
                      ${Boost_FILESYSTEM_LIBRARY}
                      ${Boost_SYSTEM_LIBRARY}
                      )


add_executable(fundot_bin main.cpp)

target_link_libraries(fundot_bin fundot)

set_target_properties(fundot_bin PROPERTIES OUTPUT_NAME fundot)

install(TARGETS fundot_bin)
