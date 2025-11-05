#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QQuickWidget>
#include <memory.h>

#include "GraphicsScene.h"
#include "GraphicsView.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private:
    std::unique_ptr<GraphicsScene> mScene;
    std::unique_ptr<GraphicsView> mView;
    std::unique_ptr<QQuickWidget> toolBarQuick;

    void init();
};
#endif // MAINWINDOW_H
