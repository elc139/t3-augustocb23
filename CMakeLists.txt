cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)

project(OpenMP)
find_package (OpenMP REQUIRED)
add_executable(OpenMPDemoABC.cpp)
target_link_libraries(OpenMPDemoABC OpenMP::OpenMP_CXX)

project(PThreads)
find_package (Threads REQUIRED)
add_executable(ThreadDemoABC ThreadDemoABC.cpp)
target_link_libraries (ThreadDemoABC ${CMAKE_THREAD_LIBS_INIT})
