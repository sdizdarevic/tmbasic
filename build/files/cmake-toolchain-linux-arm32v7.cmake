set(CMAKE_SYSTEM_NAME Linux)
set(TRIPLE "armhf-alpine-linux-musl")
set(CMAKE_SYSROOT /target-sysroot)
set(CMAKE_C_COMPILER clang)
set(CMAKE_C_COMPILER_TARGET ${TRIPLE})
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_COMPILER_TARGET ${TRIPLE})
set(CMAKE_LINKER /usr/local/${TRIPLE}/ld)
set(CMAKE_FIND_ROOT_PATH /usr/local/${TRIPLE})
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
