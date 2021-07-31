cmake_minimum_required(VERSION 2.8.11)
project(qt_sample)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

set(SRC_LIST main.cpp
			 sampleItem.h
			 sampleItem.cpp
			 sampleModel.h
			 sampleModel.cpp
			 testClasses.h
			 resources/main.qml
			 resources/picker.qml
			 resources/palette.qml)

find_package(Qt5 COMPONENTS Core Quick)
qt5_add_resources(RESOURCES resources/images.qrc)
qt5_add_resources(RESOURCES resources/qml.qrc)

add_executable(qtSample ${SRC_LIST} ${RESOURCES})
qt5_use_modules(qtSample Core Quick)

set_target_properties(qtSample PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY  $ENV{Qt5_DIR}/bin/)