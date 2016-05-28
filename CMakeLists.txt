cmake_minimum_required (VERSION 2.8.11)
project (AA-Project)


set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -ggdb -O3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -ggdb --std=c++0x -O3")

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

add_library (graph_lib Graph.cpp)

target_include_directories (graph_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable (graph_parser 
	graph_parser.cpp)

add_executable (we_serial 
	work_efficient_sequential.cpp)

add_executable (we_parallel 
	work_efficient_parallel.cpp)

add_executable (ep 
	edge_parallel.cpp)

add_executable (work_efficient_hybrid
	hybrid_approach.cpp)

target_link_libraries(graph_parser
	graph_lib)

target_link_libraries(we_serial
	graph_lib)

target_link_libraries(we_parallel
	graph_lib)

target_link_libraries(ep
	graph_lib)

target_link_libraries(work_efficient_hybrid
	graph_lib)
