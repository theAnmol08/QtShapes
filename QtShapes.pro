QT       += quickwidgets

CONFIG += c++17

TARGET = QtShapes
DESTDIR = $$PWD/bin
OBJECTS_DIR = $$PWD/build/
MOC_DIR     = $$PWD/build/
RCC_DIR     = $$PWD/build/
UI_DIR      = $$PWD/build/
RCC_DIR     = $$PWD/build/

INCLUDEPATH += include
INCLUDEPATH += include/Shapes

HEADERS += \
    include/GraphicsScene.h \
    include/GraphicsView.h \
    include/Shapes/Ellipse.h \
    include/Shapes/Line.h \
    include/Shapes/Polygon.h \
    include/Shapes/Rectangle.h \
    include/Shapes/ShapeBase.h \
    include/Shapes/ShapesFactory \
    include/ToolQuickWidget.h \
    include/mainwindow.h

SOURCES += \
    src/GraphicsScene.cpp \
    src/GraphicsView.cpp \
    src/Tools/Ellipse.cpp \
    src/Tools/Line.cpp \
    src/Tools/Polygon.cpp \
    src/Tools/Rectangle.cpp \
    src/main.cpp \
    src/mainwindow.cpp

RESOURCES += \
    res/resources.qrc
