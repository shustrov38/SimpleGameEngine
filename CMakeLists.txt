cmake_minimum_required(VERSION 3.17)
project(SimpleGameEngine)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
        main.cpp
        Window.h
        Window.cpp
        Engine.cpp
        Engine.h)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# SFML -------------------------------------------------------------------------------------------------------

set(SFML_DIR "${PROJECT_SOURCE_DIR}/SFML/lib/cmake/SFML")
set(SFML_ROOT ${SFML_DIR})
set(SFML_STATIC_LIBRARIES TRUE)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} sfml-audio sfml-network sfml-graphics sfml-window sfml-system)
endif ()