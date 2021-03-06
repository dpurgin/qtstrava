# QtStrava - A Qt wrapper for Strava API
# Copyright (C) 2020 Dmitriy Purgin <dpurgin@gmail.com>
#
# Licensed under the MIT license. See LICENSE for details.

cmake_minimum_required(VERSION 3.14)

project(qtstrava LANGUAGES CXX)

# https://stackoverflow.com/questions/25199677/how-to-detect-if-current-scope-has-a-parent-in-cmake
get_directory_property(hasParent PARENT_DIRECTORY)

if (hasParent)
    option(QTSTRAVA_BUILD_EXAMPLES "Build QtStrava examples" OFF)
    option(QTSTRAVA_BUILD_TESTS "Build QtStrava tests" OFF)
else()
    option(QTSTRAVA_BUILD_EXAMPLES "Build QtStrava examples" ON)
    option(QTSTRAVA_BUILD_TESTS "Build QtStrava tests" ON)
endif()

option(QTSTRAVA_BUILD_SHARED_LIBS "Build QtStrava as shared library" OFF)

message("QtStrava Configuration:")
message("    Examples: ${QTSTRAVA_BUILD_EXAMPLES}")
message("    Tests: ${QTSTRAVA_BUILD_TESTS}")
message("    Shared libs: ${QTSTRAVA_BUILD_SHARED_LIBS}")

include(FetchContent)

FetchContent_Declare(qtpromise
    GIT_REPOSITORY https://github.com/simonbrunel/qtpromise.git
    GIT_TAG v0.6.0
    GIT_SHALLOW TRUE
)
FetchContent_Declare(expected-lite
    GIT_REPOSITORY https://github.com/martinmoene/expected-lite.git
    GIT_TAG v0.4.0
    GIT_SHALLOW TRUE
)
FetchContent_Declare(nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.9.1
    GIT_SHALLOW TRUE
)
set(JSON_BuildTests OFF CACHE BOOL "")
set(JSON_Install OFF CACHE BOOL "")

FetchContent_Declare(nlohmann_json_qt
    GIT_REPOSITORY https://github.com/dpurgin/nlohmann_json_qt.git
    GIT_TAG main
    GIT_SHALLOW TRUE
)
set(JSON_QT_BUILD_TESTS OFF CACHE BOOL "")

FetchContent_Declare(nlohmann_json_schema
    GIT_REPOSITORY https://github.com/pboettch/json-schema-validator.git
    GIT_TAG 2.1.0
    GIT_SHALLOW TRUE
)
set(BUILD_TESTS OFF CACHE BOOL "")
set(BUILD_EXAMPLES OFF CACHE BOOL "")

FetchContent_MakeAvailable(
    qtpromise
    expected-lite
    nlohmann_json
    nlohmann_json_qt
    nlohmann_json_schema
)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Network NetworkAuth Gui REQUIRED)

set(QTSTRAVA_HEADERS
    include/QtStrava/Model/detailedactivity.h
    include/QtStrava/Model/detailedathlete.h
    include/QtStrava/Model/error.h
    include/QtStrava/Model/fault.h
    include/QtStrava/Model/metaathlete.h
    include/QtStrava/Model/summaryactivity.h
    include/QtStrava/Model/summaryclub.h
    include/QtStrava/Model/summarygear.h
    include/QtStrava/Model/updatableactivity.h
    include/QtStrava/Model/upload.h
    include/QtStrava/client.h
    include/QtStrava/deserializererror.h
    include/QtStrava/networkerror.h
    include/QtStrava/global.h

    src/jsondeserializer_p.h
)

set(QTSTRAVA_SOURCES
    src/Model/detailedactivity.cpp
    src/Model/detailedathlete.cpp
    src/Model/error.cpp
    src/Model/fault.cpp
    src/Model/metaathlete.cpp
    src/Model/summaryactivity.cpp
    src/Model/summaryclub.cpp
    src/Model/summarygear.cpp
    src/Model/updatableactivity.cpp
    src/Model/upload.cpp
    src/client.cpp
    src/deserializererror.cpp
    src/global.cpp
    src/jsondeserializer.cpp
    src/networkerror.cpp
)

set(QTSTRAVA_RESOURCES qtstrava.qrc)

if (QTSTRAVA_BUILD_SHARED_LIBS)
    add_library(qtstrava SHARED ${QTSTRAVA_HEADERS} ${QTSTRAVA_SOURCES} ${QTSTRAVA_RESOURCES})
    target_compile_definitions(qtstrava PUBLIC QTSTRAVA_LIBRARY_SHARED)
    set_target_properties(nlohmann_json_schema_validator
        PROPERTIES
            POSITION_INDEPENDENT_CODE ON
    )
else()
    add_library(qtstrava STATIC ${QTSTRAVA_HEADERS} ${QTSTRAVA_SOURCES} ${QTSTRAVA_RESOURCES})
endif()

target_link_libraries(qtstrava
    PUBLIC
        Qt5::Core
        qtpromise
    PRIVATE
        Qt5::Network
        nlohmann_json_qt
        nlohmann_json_schema_validator
        expected-lite
)
target_compile_definitions(qtstrava PRIVATE QTSTRAVA_LIBRARY)
target_include_directories(qtstrava PUBLIC include)

if (QTSTRAVA_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if (QTSTRAVA_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
