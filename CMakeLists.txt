project(DynamicArray)

add_compile_options(-Wall -Wextra)

include_directories(include)

add_executable(main
    src/main.cpp
    src/DynamicArray.cpp
)