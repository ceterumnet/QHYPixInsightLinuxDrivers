set(CMAKE_INCLUDE_CURRENT_DIR ON)
file(GLOB all_SOURCES "*.cpp" "*.c")
file(GLOB all_HEADERS "*.hpp" "*.h")

add_library(qhy5_ii_raw-pxm SHARED ${all_SOURCES} ${all_HEADERS})
add_definitions(-D__PCL_LINUX -D_ITERATOR_DEBUG_LEVEL=0)
add_custom_command(TARGET qhy5_ii_raw-pxm POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:qhy5_ii_raw-pxm> ${PIXINSIGHT64}
)

target_link_libraries(qhy5_ii_raw-pxm ${PCL_SDK_HOME}/lib/linux/x64/libPCL-pxi.a qhyccd usb-1.0)
