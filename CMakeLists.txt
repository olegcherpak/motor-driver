cmake_minimum_required(VERSION 3.1)
set (CMAKE_CXX_STANDARD 11)
project(motor-driver)

FIND_PACKAGE( Boost 1.40 COMPONENTS system REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hpp)

add_executable(${PROJECT_NAME} ${sources} ${headers})

TARGET_LINK_LIBRARIES( ${PROJECT_NAME} ${Boost_LIBRARIES} pthread)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)

