cmake_minimum_required(VERSION 2.8)
project(cropper)

add_compile_options(-std=c++11)
set(CMAKE_C_FLAGS "-O3")
set(CMAKE_CXX_FLAGS "-O3")

set(PROJECT_PATH        ${CMAKE_CURRENT_SOURCE_DIR})
set(SRCS_PATH		"${PROJECT_PATH}/src")
set(TEST_PATH           "${PROJECT_PATH}/test")
set(INCD_DIR	        "${PROJECT_PATH}/include" CACHE	INTERNAL "include dir")

set(OPENCV_DEFAULT_LIB_PATH "")
if( ${CMAKE_SYSTEM_PROCESSOR} STREQUAL "arm")
        message(STATUS "SET UP OPENCV TO ARM")
        set(OPENCV_DEFAULT_LIB_PATH "/home/eduardo/opencv/build-arm/")
endif()

file(GLOB SRCS
        "${SRCS_PATH}/*.cpp"
        "${SRCS_PATH}/*.h"
)

find_package(OpenCV REQUIRED HINTS ${OPENCV_DEFAULT_LIB_PATH})
include_directories( ${OpenCV_INCLUDE_DIRS} ${INCD_DIR} )
link_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable("${PROJECT_NAME}-test-old" "${TEST_PATH}/old-main.cpp")
target_link_libraries("${PROJECT_NAME}-test-old" ${OpenCV_LIBS})

add_executable(cropper "${TEST_PATH}/main.cpp" ${SRCS})
target_link_libraries(cropper ${OpenCV_LIBS})

