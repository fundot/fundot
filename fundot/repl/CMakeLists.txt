add_library(fundot_repl
            reader.cpp
            repl.cpp
            )

target_include_directories(fundot_repl PUBLIC ${PROJECT_SOURCE_DIR})

target_link_libraries(fundot_repl readline fundot_std)
