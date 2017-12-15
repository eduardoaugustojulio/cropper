cmake_minimum_required(VERSION 2.8)
project(croper)

add_compile_options(-std=c++11)

set(PROJECT_PATH	${CMAKE_CURRENT_SOURCE_DIR})
set(SRCS_PATH		"${PROJECT_PATH}/src")
set(LIB_INCLUDE_DIR	"${PROJECT_PATH}/include" CACHE	INTERNAL "directories")
include_directories(${LIB_INCLUDE_DIR})

find_package(OpenCV REQUIRED HINTS "/home/eduardo/opencv/build-arm/")

include_directories( ${OpenCV_INCLUDE_DIRS} )

file(GLOB SRCS "${SRCS_PATH}/*.cpp" "${SRCS_PATH}/*.h")

add_executable(${PROJECT_NAME} "${PROJECT_PATH}/test/main.cpp" ${SRCS})

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})



