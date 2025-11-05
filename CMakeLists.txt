cmake_minimum_required(VERSION 3.16)

project(QtShapes LANGUAGES CXX)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS
    Widgets
    QuickWidgets
)

set(SOURCES
    src/GraphicsScene.cpp
    src/GraphicsView.cpp
    src/Tools/Ellipse.cpp
    src/Tools/Line.cpp
    src/Tools/Polygon.cpp
    src/Tools/Rectangle.cpp
    src/main.cpp
    src/mainwindow.cpp
)

set(HEADERS
    include/GraphicsScene.h
    include/GraphicsView.h
    include/Shapes/Ellipse.h
    include/Shapes/Line.h
    include/Shapes/Polygon.h
    include/Shapes/Rectangle.h
    include/Shapes/ShapeBase.h
    include/Shapes/ShapesFactory
    include/ToolQuickWidget.h
    include/mainwindow.h
)

set(RESOURCES
    res/resources.qrc
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

qt_add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
    ${RESOURCES}
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Shapes
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Qt6::QuickWidgets
        Qt6::Widgets
)

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)
