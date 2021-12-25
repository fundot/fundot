add_executable(fundot_repl
               fundot.cpp
               reader.cpp
	       )

target_include_directories(fundot_repl PUBLIC ${PROJECT_SOURCE_DIR})

target_link_libraries(fundot_repl readline fundot_std fundot_core)

set_target_properties(fundot_repl PROPERTIES OUTPUT_NAME fundot)
