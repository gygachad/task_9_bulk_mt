cmake_minimum_required(VERSION 3.2)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(bulk_mt VERSION ${PROJECT_VESRION})

configure_file(version.h.in version.h)

file(COPY ${CMAKE_BINARY_DIR}/version.h
        DESTINATION ${CMAKE_CURRENT_SOURCE_DIR})
		
add_library(async STATIC async.cpp async.h)
add_executable(async_cli main.cpp version.cpp)

set_target_properties(async_cli async PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(async_cli
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(async_cli async)

if (MSVC)
    target_compile_options(async_cli PRIVATE
        /W4
    )
else ()
    target_compile_options(async_cli PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS async_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

if (WIN32)
    set(CPACK_GENERATOR ZIP)
endif()

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)