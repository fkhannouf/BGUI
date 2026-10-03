cmake_minimum_required(VERSION 3.16)

project(BGUI VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(BGUI_TARGET test_library)

file(MAKE_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

set(BGUI_SOURCES
    src/_man_Obtain.c
    src/_man_Release.c
    src/_man_Open.c
    src/_man_Close.c
    src/_man_Expunge.c
    src/_man_Init.c
    src/_main_Obtain.c
    src/_main_Release.c
    src/_main_Expunge.c
    src/_main_Clone.c
    src/_main_FuncAdd.c
    src/Resources.c
    src/Resources_Init.c
    src/Resources_Free.c
    src/Debug.c
    src/Library.c
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
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/inc_private
        ${CMAKE_CURRENT_SOURCE_DIR}/inc_public
)

target_compile_definitions(${BGUI_TARGET}
    PRIVATE
        __USE_INLINE__
        DO_ERROR
        DO_INFO
        DO_DEBUG
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
    target_include_directories(test_lib_test PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/inc_private
        ${CMAKE_CURRENT_SOURCE_DIR}/inc_public
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
