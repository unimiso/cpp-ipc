project(test-ipc)

include(FetchContent)

set( gtest_force_shared_crt ON CACHE BOOL "Always use msvcrt.dll" FORCE )
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.x
)
FetchContent_MakeAvailable( googletest )

FetchContent_Declare(
  gtestx
  GIT_REPOSITORY https://github.com/mikewei/gtestx.git
  GIT_TAG        master
)
FetchContent_MakeAvailable( gtestx )

if(NOT MSVC)
  add_compile_options(
    -Wno-attributes 
    -Wno-missing-field-initializers 
    -Wno-unused-variable 
    -Wno-unused-function)
endif()

include_directories(
    ${LIBIPC_PROJECT_DIR}/include 
    ${LIBIPC_PROJECT_DIR}/src
    ${LIBIPC_PROJECT_DIR}/test
    ${LIBIPC_PROJECT_DIR}/3rdparty
    ${LIBIPC_PROJECT_DIR}/3rdparty/gtest/include
)
file(GLOB SRC_FILES
    ${LIBIPC_PROJECT_DIR}/test/*.cpp
    #${LIBIPC_PROJECT_DIR}/test/*.cc
)
file( GLOB HEAD_FILES ${LIBIPC_PROJECT_DIR}/test/*.h )

add_executable( ${PROJECT_NAME} ${SRC_FILES} ${HEAD_FILES} )

target_link_libraries( ${PROJECT_NAME} gtest gtest_main ipc )

include( GoogleTest )
gtest_discover_tests( ${PROJECT_NAME})
