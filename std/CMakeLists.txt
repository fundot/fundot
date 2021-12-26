add_library(fundot_std
            builtins.cpp
            unary_plus.cpp
            unary_minus.cpp
            addition.cpp
            subtraction.cpp
            multiplication.cpp
            division.cpp
            modulo.cpp
            equal_to.cpp
            not_equal_to.cpp
            less_than.cpp
            greater_than.cpp
            less_than_or_equal_to.cpp
            greater_than_or_equal_to.cpp
            logical_not.cpp
            logical_and.cpp
            logical_or.cpp
            cond.cpp
            while.cpp
            print.cpp
            )

target_include_directories(fundot_std PUBLIC ${PROJECT_SOURCE_DIR})

target_link_libraries(fundot_std fundot_core)
