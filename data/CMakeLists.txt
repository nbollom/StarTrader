cmake_minimum_required(VERSION 3.7)
project(CopyData)

set(DataFiles config.json)

add_custom_target(CopyData ALL SOURCES ${DataFiles})
foreach(file ${DataFiles})
    add_custom_command(TARGET CopyData POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E
            copy "${CMAKE_SOURCE_DIR}/data/${file}" "${RESOURCES_OUTPUT_PATH}/${file}"
            COMMENT "Copying data/${file} to ${RESOURCES_OUTPUT_PATH}/${file}")
endforeach()

set_property(DIRECTORY PROPERTY ADDITIONAL_MAKE_CLEAN_FILES "${RESOURCES_OUTPUT_PATH}")
