cmake_minimum_required(VERSION 3.15)
project(VACCEL_TEST CXX)

set(COMMON_COMPILE_OPTIONS -Wall -Wextra -g -ggdb --coverage)
add_library(tests-main STATIC main.cpp)

# Function to simplify adding tests
function(add_test_target_core TARGET_NAME SOURCE_FILE)
    add_executable(${TARGET_NAME} ${PROJECT_SOURCE_DIR}/unit/${SOURCE_FILE})
    target_include_directories(${TARGET_NAME}
        PRIVATE
            ../third-party/slog/src
            ../src
            ../src/include
            ./fff
            ./catch2
    )
    target_compile_options(${TARGET_NAME} PRIVATE ${COMMON_COMPILE_OPTIONS})
    target_link_libraries(${TARGET_NAME} PRIVATE vaccel tests-main gcov --coverage)
    add_test(NAME ${TARGET_NAME} COMMAND ${TARGET_NAME})
endfunction()

function(add_test_target_api TARGET_NAME SOURCE_FILE)
    add_executable(${TARGET_NAME} ${PROJECT_SOURCE_DIR}/op/${SOURCE_FILE})
    target_include_directories(${TARGET_NAME}
        PRIVATE
            ../third-party/slog/src
            ../src
            ../src/include
            ../src/include/ops
            ./fff
            ./catch2
            ../src/resources
    )
    target_compile_options(${TARGET_NAME} PRIVATE ${COMMON_COMPILE_OPTIONS})
    target_link_libraries(${TARGET_NAME} PRIVATE vaccel tests-main gcov --coverage)
    add_test(NAME ${TARGET_NAME} COMMAND ${TARGET_NAME})
endfunction()

set(TESTS_CORE
    test_plugin
    test_session
    test_misc
    test_misc_mock
    test_resource
    test_id_pool
    test_vaccel
    test_log
    test_bootstrap_shutdown
    test_headers
)

set(TESTS_API
    test_fpga
    test_image
    test_image_generic
    test_tf_interference
    test_tf_model
    test_tf_saved_model
    test_exec
    test_minmax
    test_noop
    test_blas
)

foreach(TEST_NAME ${TESTS_CORE})
    add_test_target_core(${TEST_NAME} ${TEST_NAME}.cpp)
endforeach()

foreach(TEST_NAME ${TESTS_API})
    add_test_target_api(${TEST_NAME} ${TEST_NAME}.cpp)
endforeach()

# Add fast compile to catch

foreach(TEST_NAME ${TESTS_CORE})
    target_compile_definitions(${TEST_NAME} PRIVATE CATCH_CONFIG_FAST_COMPILE CATCH_CONFIG_DISABLE_MATCHERS)
endforeach()

foreach(TEST_NAME ${TESTS_API})
    target_compile_definitions(${TEST_NAME} PRIVATE CATCH_CONFIG_FAST_COMPILE CATCH_CONFIG_DISABLE_MATCHERS)
endforeach()

# Set properties for specific tests

set_tests_properties(
    test_image test_image_generic test_tf_interference test_tf_model test_tf_saved_model test_exec test_minmax test_noop test_blas test_fpga test_vaccel
    PROPERTIES
    ENVIRONMENT "VACCEL_BACKENDS=${CMAKE_BINARY_DIR}/plugins/noop/libvaccel-noop.so"
    ARGS=--order rand --warn NoAssertions
)

set_tests_properties(
    test_log test_id_pool test_misc_mock test_resource test_session test_plugin test_vaccel test_bootstrap_shutdown
    PROPERTIES
    ENVIRONMENT "VACCEL_DEBUG_LEVEL=4"
    ARGS=--order rand --warn NoAssertions
)


set_tests_properties(
    test_misc test_headers
    PROPERTIES
    ENVIRONMENT "VACCEL_BACKENDS=${CMAKE_BINARY_DIR}/plugins/noop/libvaccel-noop.so;VACCEL_DEBUG_LEVEL=4"
    ARGS=--order rand --warn NoAssertions
)

