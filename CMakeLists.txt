cmake_minimum_required (VERSION 3.6)

project (test)
set(CMAKE_CXX_STANDARD 17)

find_package(Boost 1.71 REQUIRED COMPONENTS date_time filesystem log system thread log_setup 
chrono atomic  )
add_executable(${PROJECT_NAME}  main.cpp)

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})


