cmake_minimum_required(VERSION 3.7)
project(spasm-ng
    HOMEPAGE_URL https://github.com/alberthdev/spasm-ng
)

set(
    CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
    CACHE STRING "vcpkg toolchain file"
)

add_compile_options(-Wall)
if(WIN32)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif()

add_executable(
    spasm
    main.cpp opcodes.cpp pass_one.cpp pass_two.cpp utils.cpp
    export.cpp preop.cpp directive.cpp console.cpp expand_buf.cpp
    hash.cpp list.cpp parser.cpp storage.cpp errors.cpp bitmap.cpp
    modp_ascii.cpp opcodes_ez80.cpp md5.c
)

set_property(TARGET spasm PROPERTY CXX_STANDARD 17)

set(ENABLE_APP_SIGNING ON CACHE BOOL "Enable support for signing applications")
if (ENABLE_APP_SIGNING)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(gmp REQUIRED IMPORTED_TARGET gmp)
    target_link_libraries(spasm PkgConfig::gmp)
else()
    add_compile_definitions(NO_APPSIGN)
endif()

set(ENABLE_DEBUG_PRINT OFF CACHE BOOL "Enable additional debug messages")
if (ENABLE_DEBUG_PRINT)
    add_compile_definitions(DEBUG_PRINT)
endif()

add_compile_definitions(
    USE_REUSABLES
    USE_BUILTIN_FCREATE
)
if (WIN32)
    add_compile_definitions(UNICODE _UNICODE)
endif()

# Version generation
find_package(Git)
if (Git_FOUND)
    execute_process(
        COMMAND "${GIT_EXECUTABLE}" describe --always --dirty
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
        RESULT_VARIABLE res
        OUTPUT_VARIABLE GIT_TREE_DESC
        ERROR_QUIET
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
else()
    set(GIT_TREE_DESC "unknown")
endif()
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/version.h.in" "${CMAKE_CURRENT_BINARY_DIR}/version.h")
target_include_directories(spasm
    PRIVATE "${CMAKE_CURRENT_BINARY_DIR}"
)
# Trick from https://cmake.org/pipermail/cmake/2018-October/068389.html
# to force a reconfigure on git change so the version string is always up to date
set_property(GLOBAL APPEND
    PROPERTY CMAKE_CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/.git/index"
)

# Tests
include(CTest)
add_subdirectory(${PROJECT_SOURCE_DIR}/tests)

# Install target
include(GNUInstallDirs)
install(TARGETS spasm)
install(FILES README.md LICENSE
    DESTINATION ${CMAKE_INSTALL_DOCDIR}/spasm
)
file(GLOB include_files "inc/*.inc")
install(FILES ${include_files}
    DESTINATION ${CMAKE_INSTALL_DATADIR}/spasm/inc
)

# Distribution packaging
set(CPACK_PACKAGE_VERSION "${GIT_TREE_DESC}")
set(CPACK_PACKAGE_DESCRIPTION "SPASM-ng is a z80 assembler with extra features to support development for TI calculators.")
set(CPACK_PACKAGE_CONTACT "alberthdev@users.noreply.github.com")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "zlib1g, libssl1.0.0, libgmp10")
include(CPack)
