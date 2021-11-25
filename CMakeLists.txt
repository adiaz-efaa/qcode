cmake_minimum_required(VERSION 3.4...3.18)

project(qcode)

add_subdirectory(pybind11)
add_subdirectory(time)
pybind11_add_module(qc_time
        src/qc_time.cpp
        time/src/date.cpp)

target_include_directories(qc_time PUBLIC time/include)

# EXAMPLE_VERSION_INFO is defined by setup.py and passed into the C++ code as a
# define (VERSION_INFO) here.
target_compile_definitions(qc_time
                           PRIVATE VERSION_INFO=${EXAMPLE_VERSION_INFO})
