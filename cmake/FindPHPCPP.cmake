find_path(PHPCPP_INCLUDE_DIRS
        NAMES
            phpcpp.h
        HINTS
            ${PHPCPP_ROOT}/include
            $ENV{PHPCPP_ROOT}/include
        PATHS
            /usr/local/include
            /usr/include
        )
mark_as_advanced( PHPCPP_INCLUDE_DIRS )

find_library(PHPCPP_LIBRARIES
        NAMES
            phpcpp
        HINTS
            ${PHPCPP_ROOT}/libs
            ${PHPCPP_ROOT}
            $ENV{PHPCPP_ROOT}/libs
            $ENV{PHPCPP_ROOT}
        PATHS
            /usr/local/lib
            /usr/lib
            /usr/lib64
        )
mark_as_advanced( PHPCPP_LIBRARIES )

include( FindPackageHandleStandardArgs )
FIND_PACKAGE_HANDLE_STANDARD_ARGS( CPPPHP DEFAULT_MSG PHPCPP_LIBRARIES PHPCPP_INCLUDE_DIRS )

if( NOT CPPPHP_FOUND )
    message( STATUS "Could not find PHP-CPP" )
endif()
