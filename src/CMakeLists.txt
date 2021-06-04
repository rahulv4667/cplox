file(GLOB HEADER_LIST CMAKE_CONFIGURE_DEPENDS "${cplox_SOURCE_DIR}/include/**/*.hpp")
file(GLOB SRC_LIST CMAKE_CONFIGURE_DEPENDS "${cplox_SOURCE_DIR}/src/**/*.cpp")

message(HEADERS_LIST ${HEADER_LIST})
message(SRC_LIST ${SRC_LIST})

add_library(cplox_lib STATIC ${SRC_LIST} ${HEADER_LIST})

target_include_directories(cplox_lib PUBLIC ../include)

target_compile_features(cplox_lib PUBLIC cxx_std_17)

source_group(
    TREE "${PROJECT_SOURCE_DIR}/include"
    PREFIX "Header files"
    FILES ${HEADER_LIST}
)