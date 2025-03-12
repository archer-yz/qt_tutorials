cmake_minimum_required(VERSION 3.16)

# Project details
project(
    notepad VERSION 0.0.1
    LANGUAGES CXX
    DESCRIPTION "A simple notepad application"
)

# set installation folder
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/dist
        CACHE PATH "force path to set CMAKE_INSTALL_PREFIX" FORCE
       )
endif(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

# Add postfix for debug built file
set(CMAKE_DEBUG_POSTFIX d)

# Note: if using MSYS2 Cmake and Qt packages, the MSYS2 cmake path is already defined, no need to do the following.
# Set prefix path to Qt cmake library so that find_package will search that folder.
# set(CMAKE_PREFIX_PATH "C:/Yunchi/Soft/qt_6.8.2_MSVC2022/lib/cmake")

# Set the CXX standard. Qt 6 uses c++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# find_package should find everything of Qt: Core, Widgets, Charts, etc. Looking into lib folder
# to find available components.

# find_package(OpenSSL)
# if (${OPENSSL_FOUND})
#     message("Found OpenSSL${OPENSSL_VERSION} at ${OPENSSL_INCLUDE_DIR}")
# endif()

find_package(Qt6
    REQUIRED COMPONENTS Core Gui Widgets
    OPTIONAL_COMPONENTS PrintSupport
    )
if (${Qt6_FOUND})
    message("Found Qt${Qt6_VERSION}")
    set(QT_INCLUDE_DIRS ${Qt6Widgets_INCLUDE_DIRS})
    # message("Include: ${QT_INCLUDE_DIRS}")
else()
    message("Couldn't find Qt6")
endif()

qt_standard_project_setup()


# Add include and src folders and auto find all header and source files
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")
set(IMAGE_DIR "${CMAKE_SOURCE_DIR}/images")
# include_directories(INCLUDE_DIR)
# include_directories(SOURCE_DIR)

file(GLOB_RECURSE SOURCES
    "${INCLUDE_DIR}/*.hpp"
    "${INCLUDE_DIR}/*.h"
    "${SOURCE_DIR}/*.cpp"
    "${SOURCE_DIR}/*.cxx"
)

# # Include Test
# include(CTest)
# enable_testing()

# build Win32 applications
# app icon for windows
set(app_icon_resource_windows "${CMAKE_CURRENT_SOURCE_DIR}/images/appicon.rc")
qt_add_executable(${CMAKE_PROJECT_NAME} ${SOURCES} ${app_icon_resource_windows})
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
    DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}
    RELEASE_OUTPUT_NAME ${CMAKE_PROJECT_NAME}
)

# # Package
# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)

# set compiler options
if(MSVC)
    target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE /W4 /WX)
else()
    target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

# include path to Qt includes and project includes

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR})
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    ${INCLUDE_DIR}
    ${SOURCE_DIR}
    ${QT_INCLUDE_DIRS}
)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${SOURCE_DIR})

# set built file names for debug and release
# set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX} RELEASE_OUTPUT_NAME ${CMAKE_PROJECT_NAME})

# Add any extra libs to link also.
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
    Qt6::Widgets
    Qt6::Core
    Qt6::Gui
)
if (TARGET Qt6::PrintSupport)
    target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE Qt6::PrintSupport)
endif()

# copy platform plugin folder to binary folder to avoid QT runtime error
if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    file(COPY $ENV{VCPKG_ROOT}/installed/x64-windows/debug/Qt6/plugins/platforms/
        DESTINATION ${PROJECT_BINARY_DIR}/platforms/)
else()
    file(COPY $ENV{VCPKG_ROOT}/installed/x64-windows/Qt6/plugins/platforms/
        DESTINATION ${PROJECT_BINARY_DIR}/platforms/)
endif()

# Find and add Resources
file(GLOB_RECURSE icon_files
    "${IMAGE_DIR}/*.png"
    "${IMAGE_DIR}/*.ico"
)
set (notepad_resource_files "")
foreach(icon_file ${icon_files})
    get_filename_component(file_name ${icon_file} NAME)
    list(APPEND notepad_resource_files "images/${file_name}")
endforeach(icon_file ${icon_files})

# in Qt6CoreMacros.cmake, the resource file is added to the target
qt_add_resources(${CMAKE_PROJECT_NAME} "${CMAKE_PROJECT_NAME}_icons"
    PREFIX
        "/"
    FILES
        ${notepad_resource_files}
)

install(TARGETS ${CMAKE_PROJECT_NAME}
    DESTINATION ${CMAKE_INSTALL_BINDIR}
    BUNDLE  DESTINATION ${CMAKE_INSTALL_BINDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# in Qt6CoreMacros.cmake
qt_generate_deploy_app_script(
    TARGET ${CMAKE_PROJECT_NAME}
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
