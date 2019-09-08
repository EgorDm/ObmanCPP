project(object_manager C CXX)

find_package(PHPCPP REQUIRED)

select_source_files()

include_directories(${PHPCPP_INCLUDE_DIRS})

set(USED_LIBRARIES
        ${PHPCPP_LIBRARIES}
        )

init_library(${PROJECT_NAME} "${USED_LIBRARIES}" SHARED)