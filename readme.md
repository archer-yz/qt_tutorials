# Qt Development in VS Code with CMake and vcpkg

This repository has template and tutorials for Qt GUI development in VS code using vcpkg and CMake.
Tutorial for general c++ development in VS Code with CMake and vcpkg can be found in [Manifest
Mode](https://learn.microsoft.com/en-us/vcpkg/get_started/get-started-vscode?pivots=shell-cmd) and
[Classic
Mode](https://learn.microsoft.com/en-us/vcpkg/consume/classic-mode?tabs=msbuild%2Cbuild-MSBuild).
All projects in this repository are developed in classic mode.

## Qt Package Installation

System wide installation is suggested for Qt package, as it takes long time to install using vcpkg.
The following command can be executed to check the availability.

`vcpkg search qt`

*qtbase* and *qtgraphs* are usually sufficent for most of the needs. Use the following command to
install them.

`vcpkg install qtbase qtgraphs --clean-after-build`

> [!NOTE]
> Ensure there is enough storage in your drive for Qt package.
> Also it takes long time to install Qt packages using vcpkg.

## Folders

### Template

This folder can be duplicated for a new Qt project development.

### AnalogClock and Notepad

These are reproduced projects based on the tutorials provided by Qt. Small modifications are made.

## Build Projects

- *build_all.bat* can be run to build all projects except *Template*.
- *build_project.bat* can be run with a project name to build a specific project. For instance, `build_project.bat AnalogClock`

## Tips

### Platform Plugin Error

The following script can be included in *CMakeLists.txt* to copy platform plugin folder from
*vcpkg_installed* to the build folder to avoid runtime error.

```
# copy platform plugin folder to binary folder to avoid QT runtime error
if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    file(COPY ${PROJECT_BINARY_DIR}/vcpkg_installed/x64-windows/debug/Qt6/plugins/platforms/
        DESTINATION ${PROJECT_BINARY_DIR}/platforms/)
else()
    file(COPY ${PROJECT_BINARY_DIR}/vcpkg_installed/x64-windows/Qt6/plugins/platforms/
        DESTINATION ${PROJECT_BINARY_DIR}/platforms/)
endif()
```

