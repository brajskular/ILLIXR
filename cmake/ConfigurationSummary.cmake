# Report configuration

# helper functions

# based on https://github.com/jimbraun/XCDF/blob/master/cmake/CMakePadString.cmake
function(pad_string RESULT REQUESTED_LENGTH VALUE)
    string(LENGTH "${VALUE}" VALUE_LENGTH)
    math(EXPR REQUIRED_PAD "${REQUESTED_LENGTH} - ${VALUE_LENGTH}")
    set(PAD ${VALUE})
    if(REQUIRED_PAD GREATER 0)
        math(EXPR REQUIRED_MINUS_ONE "${REQUIRED_PAD} - 1")
        foreach(BLAH RANGE ${REQUIRED_PAD})
            set(PAD "${PAD} ")
        endforeach()
    endif()
    set(${RESULT} "${PAD}" PARENT_SCOPE)
endfunction()

set(ILLIXR_SUMMARY_PADDING 35 CACHE STRING "Padding of each report summary line")
mark_as_advanced(ILLIXR_SUMMARY_PADDING)

function(report_value value msg)
    pad_string(padded_value ${ILLIXR_SUMMARY_PADDING} "  ${value}")
    message(STATUS "${padded_value}: ${msg}")
endfunction()

function(print_enabled_disabled value msg)
    pad_string(padded_value ${ILLIXR_SUMMARY_PADDING} "  ${msg}")
    if(value)
        message(STATUS "${padded_value}: Enabled")
    else()
        message(STATUS "${padded_value}: Disabled")
    endif()
endfunction()

function(report_padded varname)
    pad_string(padded_value ${ILLIXR_SUMMARY_PADDING} " ${varname}")
    message(STATUS "${padded_value}: ${${varname}}")
endfunction()

string(TOUPPER "${CMAKE_BUILD_TYPE}" CMAKE_BUILD_TYPE_UPPER)
message(STATUS "-------------------------------------------------------------")
message(STATUS "------------------- Configuration Options -------------------")
if(YAML_FILE)
    report_value("Arguments read from" "Command line and ${YAML_FILE}")
else()
    report_value("Arguments read from" "Command line")
endif()
report_value("Linux vendor" "${OS_FLAVOR}")
report_value("CMAKE_CXX_COMPILER_ID type" "${CMAKE_CXX_COMPILER_ID}")
report_value("CMAKE_CXX_COMPILER_VERSION" "${CMAKE_CXX_COMPILER_VERSION}")
report_value("CMake version"    "${CMAKE_VERSION}")
report_value("CMake generator"  "${CMAKE_GENERATOR}")
report_value("CMake build tool" "${CMAKE_BUILD_TOOL}")
report_value("Build type" "${CMAKE_BUILD_TYPE}")
report_value("Library suffix" "${ILLIXR_BUILD_SUFFIX}${CMAKE_SHARED_LIBRARY_SUFFIX}")
report_value("C compilation flags" "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_${CMAKE_BUILD_TYPE_UPPER}}")
report_value("C++ compilation flags" "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE_UPPER}}")
report_value("Install location" "$CMAKE_INSTALL_PREFIX}")

# ------------------------- External Libraries ---------------------------------
message(STATUS "External Libraries")
foreach(ITEM IN LISTS EXTERNAL_LIBRARIES)
    if(${ITEM}_EXTERNAL)
        report_value("${ITEM}" "Download and Install")
    else()
        report_value("${ITEM}" "Found version ${${ITEM}_VERSION}")
    endif()
endforeach()
if(BUILDING_OPENCV)
    report_value("OpenCV" "Download and Install")
endif()

# ------------------------- Plugins --------------------------------------------
message(STATUS "Build Plugins")
#set(GROUP_LINE "")
#if(BUILD_GROUP)
#    report_value("Build components type" "${BUILD_GROUP}")
#    set(GROUP_LINE "group: ${BUILD_GROUP}\n")
#endif()
set(PLUGIN_LINE "plugins: ")
set(FIRST True)
set(HAVE_PLUGIN False)
foreach(ITEM IN LISTS PLUGIN_LIST EXT_PLUGIN_LIST)
    string(TOUPPER "USE_${ITEM}" ITEM_UPPER)
    if(${${ITEM_UPPER}})
        if(NOT FIRST)
            set(PLUGIN_LINE "${PLUGIN_LINE},")
        else()
            set(FIRST False)
            set(HAVE_PLUGIN True)
        endif()
        set(PLUGIN_LINE "${PLUGIN_LINE}${ITEM}")
    endif()
    print_enabled_disabled("${${ITEM_UPPER}}" "${ITEM}")
endforeach()
report_value("Data file" "${DATA_FILE}")
report_value("Generating yaml file" "illixr.yaml")
message(STATUS "-------------------------------------------------------------")

set(OUTFILE "illixr.yaml")
file(WRITE ${OUTFILE} ${GROUP_LINE})
if(HAVE_PLUGIN)
    if(ILLIXR_RUN_NAMES)
        file(APPEND ${OUTFILE} "plugins: ${ILLIXR_RUN_NAMES}\n")
    else()
        file(APPEND ${OUTFILE} "${PLUGIN_LINE}\n")
    endif()
endif()
if(DATA_FILE)
    file(APPEND ${OUTFILE} "data: ${CMAKE_SOURCE_DIR}/data/mav0\n")
endif()
if(DEMO_DATA)
    file(APPEND ${OUTFILE} "demo_data: ${DEMO_DATA}\n")
else()
    file(APPEND ${OUTFILE} "demo_data: ${CMAKE_BINARY_DIR}/demo_data\n")
endif()
file(APPEND ${OUTFILE} "enable_offload: ${ENABLE_OFFLOAD}\n")
file(APPEND ${OUTFILE} "enable_alignment: ${ENABLE_ALIGNMENT}\n")
file(APPEND ${OUTFILE} "enable_verbose_errors: ${ENABLE_VERBOSE_ERRORS}\n")
file(APPEND ${OUTFILE} "enable_pre_sleep: ${ENABLE_PRE_SLEEP}\n")
