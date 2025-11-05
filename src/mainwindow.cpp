#include "mainwindow.h"

#include "ToolQuickWidget.h"
#include <QQmlContext>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    init();
}

void MainWindow::init() {
    mScene = std::make_unique<GraphicsScene>();
    mView = std::make_unique<GraphicsView>();
    mView->setScene(mScene.get());
    toolBarQuick = std::make_unique<ToolQuickWidget>(mView.get());
    toolBarQuick->setSource(QUrl("qrc:/QML/ToolBar.qml"));
    toolBarQuick->setResizeMode(QQuickWidget::SizeViewToRootObject);
    toolBarQuick->rootContext()->setContextProperty("myView", mView.get());

    setCentralWidget(mView.get());
}
