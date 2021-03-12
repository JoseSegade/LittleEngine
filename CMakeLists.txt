project(LittleEngine)
cmake_minimum_required(VERSION 3.12)

find_package(OpenGL REQUIRED)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SRCS ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HDRS ${CMAKE_SOURCE_DIR}/src/*.h)

add_subdirectory("ext/glfw")
add_subdirectory("ext/glad")
add_subdirectory("ext/glm/glm")


#           DOWNLOAD ALL THE SUBMODULES
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

#           CHECK ALL THE SUBMODULES
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/ext/glfw/CMakeLists.txt")
    message(FATAL_ERROR "The glfw submodules was not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/ext/glad/CMakeLists.txt")
    message(FATAL_ERROR "The glad submodules was not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/ext/glm/glm/CMakeLists.txt")
    message(FATAL_ERROR "The glm submodules was not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

# CHECK PYTHON FOR COMPILING GLAD
find_package(Python3 COMPONENTS Interpreter Development)
if(NOT PYTHON3_FOUND)
    message(FATAL_ERROR "Python 3 interpreter not installed. Please download and install python to continue. See: https://www.python.org/downloads/")
    endif()

add_library(lodepng 
    STATIC 
    "ext/lodepng/lodepng.cpp"
    "ext/lodepng/lodepng.h"
)

add_executable("${PROJECT_NAME}"
    "${SRCS}"
    "${HDRS}"
) 

target_include_directories("${PROJECT_NAME}"
    PUBLIC

    "ext/glfw/include"
    "ext/glad/include/glad"
    "ext/glm"
    "ext/lodepng"
    "src"
)

target_link_libraries("${PROJECT_NAME}" 
    PUBLIC 
    glfw
    glad
    glm
    lodepng
)



