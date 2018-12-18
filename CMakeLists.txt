cmake_minimum_required(VERSION 3.0.0)

include("cmake/HunterGate.cmake")

option(HUNTER_NO_TOOLCHAIN_ID_RECALCULATION "Speeds up configure time." ON)

HunterGate(
    URL "https://github.com/ruslo/hunter/archive/v0.23.48.tar.gz"
    SHA1 "515a12255189d9f85e88174c56ea5d1ed3031d40"
)

project(gzCrypt VERSION 0.1.0)

include(CTest)
enable_testing()

add_subdirectory(src)
add_subdirectory(test)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
