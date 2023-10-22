cmake_minimum_required(VERSION 3.20)

project("AED2")

set(CMAKE_C_STANDARD 11)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/public/filainfo.txt
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
file(GLOB_RECURSE HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

add_executable(program 
    ${SOURCE_FILES}
    ${HEADER_FILES}
)

target_include_directories(program PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(program PRIVATE m)
