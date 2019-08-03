cmake_minimum_required(VERSION 2.8.11)
project(qt_sample)

if(CMAKE_PREFIX_PATH)
    # Find includes in corresponding build directories
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
    # Instruct CMake to run moc automatically when needed.
    set(CMAKE_AUTOMOC ON)

    # For now, just copy what we need for this project
    file(COPY ${CMAKE_PREFIX_PATH}/bin/opengl32sw.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
    file(COPY ${CMAKE_PREFIX_PATH}/bin/opengl32sw.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)  
    file(COPY ${CMAKE_PREFIX_PATH}/bin/Qt5Cored.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
    file(COPY ${CMAKE_PREFIX_PATH}/bin/Qt5Core.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
    file(COPY ${CMAKE_PREFIX_PATH}/bin/Qt5Widgetsd.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
    file(COPY ${CMAKE_PREFIX_PATH}/bin/Qt5Widgets.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
    file(COPY ${CMAKE_PREFIX_PATH}/bin/Qt5Guid.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
    file(COPY ${CMAKE_PREFIX_PATH}/bin/Qt5Gui.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
    file(COPY ${CMAKE_PREFIX_PATH}/bin/Qt5Qmld.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
    file(COPY ${CMAKE_PREFIX_PATH}/bin/Qt5Qml.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
    file(COPY ${CMAKE_PREFIX_PATH}/bin/Qt5Networkd.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
    file(COPY ${CMAKE_PREFIX_PATH}/bin/Qt5Network.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
    file(COPY ${CMAKE_PREFIX_PATH}/bin/Qt5Quickd.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
    file(COPY ${CMAKE_PREFIX_PATH}/bin/Qt5Quick.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)

    # QtQuick Controls 2.0
    file(COPY ${CMAKE_PREFIX_PATH}/bin/Qt5QuickControls2d.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
    file(COPY ${CMAKE_PREFIX_PATH}/bin/Qt5QuickControls2.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
    file(COPY ${CMAKE_PREFIX_PATH}/bin/Qt5QuickTemplates2d.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
    file(COPY ${CMAKE_PREFIX_PATH}/bin/Qt5QuickTemplates2.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
    file(COPY ${CMAKE_PREFIX_PATH}/qml/QtQuick.2/qtquick2plugind.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
    file(COPY ${CMAKE_PREFIX_PATH}/qml/QtQuick.2/qtquick2plugin.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
    file(COPY ${CMAKE_PREFIX_PATH}/qml/QtQuick/Controls.2/qtquickcontrols2plugind.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
    file(COPY ${CMAKE_PREFIX_PATH}/qml/QtQuick/Controls.2/qtquickcontrols2plugin.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)

    set(SRC_LIST main.cpp
                 sampleItem.h
                 sampleItem.cpp
                 sampleModel.h
                 sampleModel.cpp
                 testClasses.h
                 resources/main.qml
                 resources/palette.qml)

    find_package(Qt5 COMPONENTS Core Widgets Quick)
    qt5_add_resources(RESOURCES resources/images.qrc)
    qt5_add_resources(RESOURCES resources/qml.qrc)

    add_executable(qtSample ${SRC_LIST} ${RESOURCES})
    qt5_use_modules(qtSample Core Widgets Quick)
else()
    error("Please set the CMAKE_PREFIX_PATH to where Qt is installed")
endif()
