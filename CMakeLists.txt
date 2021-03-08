project(LittleEngine)
cmake_minimum_required(VERSION 3.12)


add_subdirectory("ext/glfw")
add_subdirectory("ext/glad")

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

find_package(Python3 COMPONENTS Interpreter Development)
if(NOT PYTHON3_FOUND)
    message(FATAL_ERROR "Python 3 interpreter not installed. Please download and install python to continue. See: https://www.python.org/downloads/")
    endif()

add_executable("${PROJECT_NAME}"
  #Header files

  #Source code files
  src/main.cpp
) 

target_include_directories("${PROJECT_NAME}"
    PUBLIC "ext/glfw/include"
    PUBLIC "ext/glad/include/glad"
)

target_link_directories("${PROJECT_NAME}"
    PRIVATE "ext/glfw/src"
    PRIVATE "ext/glew/src"
)

target_link_libraries("${PROJECT_NAME}" glfw glad)

