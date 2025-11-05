#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QWheelEvent>
#include "Shapes/ShapesFactory"

class GraphicsView : public QGraphicsView {
    Q_OBJECT

    bool isDragging;
    ShapeFactory::ToolType currentTool;
    std::shared_ptr<Shapes::ShapeBase> currentItem;
    std::vector<std::shared_ptr<Shapes::ShapeBase>> shapeList;
    std::vector<std::shared_ptr<Shapes::ShapeBase>> copyStack;

public:
    explicit GraphicsView(QWidget *parent = nullptr);
    ~GraphicsView() {

        for(int ii = 0; ii < (int)shapeList.size(); ++ii) {
            qDebug() << (shapeList[ii].use_count());
        }

        shapeList.clear();
        currentItem.reset();
    }

    Q_INVOKABLE void setTool(int mTool);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
};


#endif // GRAPHICSVIEW_H
