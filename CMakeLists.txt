cmake_minimum_required(VERSION 3.16)

project(BGUI VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(BGUI_TARGET test_library)

set(BGUI_LOG_LEVEL "3" CACHE STRING "Maximum log level: 0=none, 1=error, 2=info, 3=debug")
set_property(CACHE BGUI_LOG_LEVEL PROPERTY STRINGS 0 1 2 3)
if(NOT BGUI_LOG_LEVEL MATCHES "^[0-3]$")
    message(FATAL_ERROR "BGUI_LOG_LEVEL must be 0 (none), 1 (error), 2 (info), or 3 (debug)")
endif()

file(MAKE_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

set(BGUI_SOURCES
        sources/_manager_Obtain.c
        sources/_manager_Release.c
        sources/_manager_Open.c
        sources/_manager_Close.c
        sources/_manager_Expunge.c
        sources/_manager_Init.c
        sources/_main_Obtain.c
        sources/_main_Release.c
        sources/_main_Expunge.c
        sources/_main_Clone.c
        sources/_main_FuncAdd.c
        sources/Resources.c
        sources/Resources_Init.c
        sources/Resources_Free.c
        sources/Debug.c
        sources/Library.c
)

add_library(${BGUI_TARGET} SHARED ${BGUI_SOURCES})

add_custom_command(TARGET ${BGUI_TARGET} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_SOURCE_DIR}/bin"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE:${BGUI_TARGET}>"
        "${CMAKE_SOURCE_DIR}/bin/$<TARGET_FILE_NAME:${BGUI_TARGET}>"
    COMMENT "Copying ${BGUI_TARGET} to ${CMAKE_SOURCE_DIR}/bin"
)

set_target_properties(${BGUI_TARGET} PROPERTIES
    PREFIX ""
    OUTPUT_NAME "test_library"
    SUFFIX ".library"
    POSITION_INDEPENDENT_CODE ON
)

target_include_directories(${BGUI_TARGET}
        PRIVATE
#        "src/includes"
#        "src/includes/public"
        "${CMAKE_CURRENT_SOURCE_DIR}/sources"
        "${CMAKE_CURRENT_SOURCE_DIR}/sources/includes"
        "${CMAKE_CURRENT_SOURCE_DIR}/sources/includes/public"
)

target_compile_definitions(${BGUI_TARGET}
        PRIVATE
#        __USE_INLINE__
        BGUI_LOG_LEVEL=${BGUI_LOG_LEVEL}
)

target_compile_options(${BGUI_TARGET}
        PRIVATE
        -O2
        -Wall
        -W
        -gstabs
)

target_link_options(${BGUI_TARGET}
        PRIVATE
        -nostartfiles
        "-Wl,--cref,-M,-Map=${CMAKE_CURRENT_BINARY_DIR}/test_library.library.map"
)

option(BGUI_BUILD_TESTS "Build the example test program" OFF)

if(BGUI_BUILD_TESTS)
    add_executable(test_lib_test test/test_lib.c)
    target_include_directories(test_lib_test
        PRIVATE
            "sources/includes"
            "sources/includes/public"
    )
    target_link_libraries(test_lib_test PRIVATE ${BGUI_TARGET})

    add_custom_command(TARGET test_lib_test POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_SOURCE_DIR}/bin"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE:test_lib_test>"
            "${CMAKE_SOURCE_DIR}/bin/$<TARGET_FILE_NAME:test_lib_test>"
        COMMENT "Copying test_lib_test to ${CMAKE_SOURCE_DIR}/bin"
    )
endif()

install(TARGETS ${BGUI_TARGET}
    LIBRARY DESTINATION sys:libs
    RUNTIME DESTINATION sys:libs
)
