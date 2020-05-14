cmake_minimum_required(VERSION 3.12)

project(elemento)

set(CMAKE_CXX_STANDARD 17)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast -Wno-deprecated-register -fno-asynchronous-unwind-tables -fomit-frame-pointer -march=native -m64")

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
set(BOOST_ROOT ~/boost)

find_package(Boost 1.67.0 COMPONENTS timer serialization REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")
endif()

include_directories(include include/interfaces)
link_directories(include include/interfaces)

add_library(elemento_warpdrive

        include/interfaces/ELWD_Starting_Stage_I.h
        include/interfaces/ELWD_Ending_Stage_I.h
        include/interfaces/ELWD_Middle_Stage_I.h
        include/interfaces/ELWD_Thread_I.h
        include/interfaces/ELWD_Queue_I.h
        include/interfaces/ELWD_Sizeable_I.h

        include/ELWD_Pipeline.h
        include/ELWD_Stage.h
        include/ELWD_Thread_State.h
        include/ELWD_Thread.h
        include/ELWD_Controller.h
        include/ELWD_Safe_Queue.h
        include/ELWD_Dummy_Queue.h
        include/ELWD_Clock_Generator.h
        include/ELWD_Thread_Pool.h
        include/ELWD_Load_Balanced_Thread_Pool.h

        test/test_Pipeline_Allocation.cpp
        test/test_Pipeline_Computing.cpp
        test/test_Pipeline_Multi_Cons.cpp
        test/test_Pipeline_Multi_Cons2.cpp
        test/test_Clock_Generator.cpp
        test/test_Controller.cpp
        test/test_Load_Balancing_Pipeline.cpp
        )
target_include_directories(elemento_warpdrive PUBLIC include src test)

add_executable(
        test_Pipeline_Allocation
        test/test_Pipeline_Allocation.cpp
)
target_link_libraries(test_Pipeline_Allocation elemento_warpdrive)
target_include_directories(test_Pipeline_Allocation PUBLIC include src test)

add_executable(
        test_Pipeline_Declaration
        test/test_Pipeline_Declaration.cpp
)
target_link_libraries(test_Pipeline_Declaration elemento_warpdrive)
target_include_directories(test_Pipeline_Declaration PUBLIC include src test)

add_executable(
        test_Pipeline_Computing
        test/test_Pipeline_Computing.cpp
)
target_link_libraries(test_Pipeline_Computing elemento_warpdrive)
target_include_directories(test_Pipeline_Computing PUBLIC include src test)

add_executable(
        test_Pipeline_Multi_Cons
        test/test_Pipeline_Multi_Cons.cpp
)
target_link_libraries(test_Pipeline_Multi_Cons elemento_warpdrive)
target_include_directories(test_Pipeline_Multi_Cons PUBLIC include src test)

add_executable(
        test_Pipeline_Multi_Cons2
        test/test_Pipeline_Multi_Cons2.cpp
)
target_link_libraries(test_Pipeline_Multi_Cons2 elemento_warpdrive)
target_include_directories(test_Pipeline_Multi_Cons2 PUBLIC include src test)

add_executable(
        test_Clock_Generator
        test/test_Clock_Generator.cpp
)
target_link_libraries(test_Clock_Generator elemento_warpdrive)
target_include_directories(test_Clock_Generator PUBLIC include src test)

add_executable(
        test_Controller
        test/test_Controller.cpp
)
target_link_libraries(test_Controller elemento_warpdrive)
target_include_directories(test_Controller PUBLIC include src test)

add_executable(
        test_Load_Balancing_Pipeline
        test/test_Load_Balancing_Pipeline.cpp
)
target_link_libraries(test_Load_Balancing_Pipeline elemento_warpdrive)
target_include_directories(test_Load_Balancing_Pipeline PUBLIC include src test)
