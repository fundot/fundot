add_library(fundot_core
            object.cpp
            null.cpp
            boolean.cpp
            number.cpp
            string.cpp
            symbol.cpp
            quote.cpp
            pair.cpp
            vector.cpp
            set.cpp
            function.cpp
            parser.cpp
            )

add_executable(fundot_bin main.cpp)

target_link_libraries(fundot_bin fundot_core)

set_target_properties(fundot_bin PROPERTIES OUTPUT_NAME fundot)
