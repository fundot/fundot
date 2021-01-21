add_library(funstd SHARED
            append.cpp
            close.cpp
            count.cpp
            do.cpp
            insert.cpp
            lambda.cpp
            open.cpp
            pop.cpp
            print.cpp
            quit.cpp
            read.cpp
            remove.cpp
            )

target_link_libraries(funstd fundot)

install(TARGETS funstd DESTINATION fundot/lib)
