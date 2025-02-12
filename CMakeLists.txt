CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

if (POLICY CMP0072)
    cmake_policy (SET CMP0072 NEW)
endif(POLICY CMP0072)

# GoogleTest requires at least C++14
SET(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

OPTION(BUILD_TESTS "Enable gtest build" OFF)
OPTION(BUILD_DOCS  "Enable documentation build" OFF)

PROJECT(ray-challenges)

FIND_PACKAGE(OpenGL REQUIRED)

ADD_SUBDIRECTORY(raylib)

IF(BUILD_TESTS)
    ADD_SUBDIRECTORY(test)
ENDIF()

IF(BUILD_DOCS)
    FIND_PACKAGE(Doxygen)

    if (DOXYGEN_FOUND)
        SET(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/doxygen/Doxyfile.in)
        SET(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.out)

        CONFIGURE_FILE(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
        MESSAGE("Building Doxygen documentation")

        ADD_CUSTOM_TARGET( docs
                COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                COMMENT "Generating API documentation with Doxygen"
                VERBATIM )
    else (DOXYGEN_FOUND)
        MESSAGE("Doxygen not found")
    endif (DOXYGEN_FOUND)
ENDIF()

INCLUDE_DIRECTORIES(include)

SET_TARGET_PROPERTIES(raylib PROPERTIES BUILD_SHARED_LIBS ON)

# Add src files
FILE(GLOB sources src/*.cpp)
LIST(APPEND source_files ${sources})

# Add apps executables - based on Raylib examples build
FILE(GLOB sources apps/*.cpp)
LIST(APPEND apps_sources ${sources})
FOREACH (app_src ${apps_sources})
    GET_FILENAME_COMPONENT(app_name ${app_src} NAME)
    STRING(REPLACE ".cpp" "" app_name ${app_name})
    MESSAGE("APP: " ${app_name})

    ADD_EXECUTABLE(${app_name} ${app_src} ${source_files})
    TARGET_LINK_LIBRARIES(${app_name} raylib)
    TARGET_LINK_LIBRARIES(${app_name} OpenGL::GL)
endforeach ()