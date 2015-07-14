INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_DK_TEST dk_test)

FIND_PATH(
    DK_TEST_INCLUDE_DIRS
    NAMES dk_test/api.h
    HINTS $ENV{DK_TEST_DIR}/include
        ${PC_DK_TEST_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    DK_TEST_LIBRARIES
    NAMES gnuradio-dk_test
    HINTS $ENV{DK_TEST_DIR}/lib
        ${PC_DK_TEST_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(DK_TEST DEFAULT_MSG DK_TEST_LIBRARIES DK_TEST_INCLUDE_DIRS)
MARK_AS_ADVANCED(DK_TEST_LIBRARIES DK_TEST_INCLUDE_DIRS)

