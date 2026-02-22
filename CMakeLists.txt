cmake_minimum_required(VERSION 3.20)
project(LabsProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SHARED_SOURCES
    ${CMAKE_SOURCE_DIR}/shared/src/*.cpp
)

add_library(shared STATIC ${SHARED_SOURCES})

target_include_directories(shared
    PUBLIC
        ${CMAKE_SOURCE_DIR}/shared/include
)

file(GLOB LAB_DIRS RELATIVE ${CMAKE_SOURCE_DIR} lab*)

foreach(LAB ${LAB_DIRS})
    if(IS_DIRECTORY ${CMAKE_SOURCE_DIR}/${LAB})

        file(GLOB_RECURSE LAB_SOURCES
            ${CMAKE_SOURCE_DIR}/${LAB}/src/*.cpp
        )

        if(LAB_SOURCES)

            add_executable(${LAB} ${LAB_SOURCES})

            target_include_directories(${LAB}
                PRIVATE
                    ${CMAKE_SOURCE_DIR}/${LAB}/include
            )

            target_link_libraries(${LAB}
                PRIVATE shared
            )

        endif()
    endif()
endforeach()
