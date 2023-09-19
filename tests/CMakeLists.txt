include(CTest)

# A fixture that compiles the assembler so the test runner can run it
add_test(test_build_assembler
    "${CMAKE_COMMAND}"
    --build "${CMAKE_BINARY_DIR}"
    --config "$<CONFIG>"
    --target spasm
)
set_tests_properties(test_build_assembler PROPERTIES FIXTURES_SETUP f_build_assembler)

# Find every .asm file and run it under the test runner
file(GLOB_RECURSE asm_files "*.asm")
foreach(asm_file ${asm_files})
    cmake_path(
        RELATIVE_PATH asm_file
        BASE_DIRECTORY "${CMAKE_SOURCE_DIR}"
        OUTPUT_VARIABLE asm_file_relpath
    )
    add_test(
        NAME autotest_${asm_file_relpath}
        COMMAND ${CMAKE_SOURCE_DIR}/tests/test-runner.py $<TARGET_FILE:spasm> ${asm_file}
    )
    SET_TESTS_PROPERTIES(autotest_${asm_file_relpath}
        PROPERTIES
        FIXTURES_REQUIRED f_build_assembler)
endforeach()
