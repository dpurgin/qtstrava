# QtStrava - A Qt wrapper for Strava API
# Copyright (C) 2020 Dmitriy Purgin <dpurgin@gmail.com>
#
# Licensed under the MIT license. See LICENSE for details.

cmake_minimum_required(VERSION 3.14)

project(qtstrava LANGUAGES CXX)

option(QTSTRAVA_BUILD_EXAMPLES "Build examples" OFF)

include(FetchContent)

FetchContent_Declare(qtpromise
    GIT_REPOSITORY https://github.com/simonbrunel/qtpromise.git
    GIT_TAG v0.6.0
    GIT_SHALLOW TRUE
)
FetchContent_Declare(range-v3
    GIT_REPOSITORY https://github.com/ericniebler/range-v3.git
    GIT_TAG 0.11.0
    GIT_SHALLOW TRUE
)
FetchContent_Declare(expected-lite
    GIT_REPOSITORY https://github.com/martinmoene/expected-lite.git
    GIT_TAG v0.4.0
    GIT_SHALLOW TRUE
)
FetchContent_Declare(json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.9.1
    GIT_SHALLOW TRUE
)
set(JSON_BuildTests OFF CACHE BOOL "")
set(JSON_Install OFF CACHE BOOL "")

FetchContent_Declare(json-schema-validator
    GIT_REPOSITORY https://github.com/pboettch/json-schema-validator.git
    GIT_TAG 2.1.0
    GIT_SHALLOW TRUE
)
set(BUILD_TESTS OFF CACHE BOOL "")
set(BUILD_EXAMPLES OFF CACHE BOOL "")

FetchContent_MakeAvailable(
    qtpromise
    range-v3
    expected-lite
    json
    json-schema-validator
)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Network NetworkAuth Gui REQUIRED)

add_library(qtstrava SHARED
    include/QtStrava/Model/detailedathlete.h
    include/QtStrava/Model/error.h
    include/QtStrava/Model/fault.h
    include/QtStrava/Model/summaryactivity.h
    include/QtStrava/client.h
    include/QtStrava/deserializererror.h
    include/QtStrava/networkerror.h
    include/QtStrava/global.h

    src/jsondeserializer_p.h

    src/Model/detailedathlete.cpp
    src/Model/error.cpp
    src/Model/fault.cpp
    src/Model/summaryactivity.cpp
    src/client.cpp
    src/deserializererror.cpp
    src/networkerror.cpp
    src/global.cpp
    src/jsondeserializer.cpp

    qtstrava.qrc
)

target_link_libraries(qtstrava
    PUBLIC
        Qt5::Core
        qtpromise
    PRIVATE
        Qt5::Network
        range-v3
        nlohmann_json_schema_validator
        expected-lite
)
target_compile_definitions(qtstrava PRIVATE QTSTRAVA_LIBRARY)
target_include_directories(qtstrava PUBLIC include)

if (QTSTRAVA_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
