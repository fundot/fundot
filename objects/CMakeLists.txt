add_library(funstd SHARED
            append.cpp
            close.cpp
            count.cpp
            do.cpp
            expand.cpp
            hash.cpp
            insert.cpp
            open.cpp
            pop.cpp
            print.cpp
            quit.cpp
            quote.cpp
            read.cpp
            remove.cpp
            )

target_link_libraries(funstd fundot)

set_target_properties(funstd PROPERTIES SUFFIX ".funso")

install(TARGETS funstd DESTINATION fundot/lib)
