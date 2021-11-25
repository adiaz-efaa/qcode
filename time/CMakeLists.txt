set(CMAKE_CXX_STANDARD 17)

add_library(time SHARED src/date.cpp)

target_include_directories(time PUBLIC include)