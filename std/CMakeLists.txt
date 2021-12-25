add_library(fundot_std
            builtins.cpp
            cond.cpp
            )

target_include_directories(fundot_std PUBLIC ${PROJECT_SOURCE_DIR})

target_link_libraries(fundot_std fundot_core)
