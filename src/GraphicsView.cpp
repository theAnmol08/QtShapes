#include "GraphicsView.h"
#include <QDebug>

GraphicsView::GraphicsView(QWidget *parent) : QGraphicsView(parent) {
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    setResizeAnchor(NoAnchor);
    setDragMode(NoDrag);
    isDragging = false;
    currentTool = ShapeFactory::Move;
}

void GraphicsView::setTool(int mTool) {
    currentTool = ShapeFactory::ToolType(mTool);
}

void GraphicsView::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_H) {
        setDragMode(ScrollHandDrag);
    }

    if((event->keyCombination().keyboardModifiers() & Qt::ControlModifier) && (event->keyCombination().key() == Qt::Key_C)) {
        qDebug() << __FUNCTION__ << "COPY";
    }

    QGraphicsView::keyPressEvent(event);
}

void GraphicsView::keyReleaseEvent(QKeyEvent *event) {
    setDragMode(RubberBandDrag);
    QGraphicsView::keyReleaseEvent(event);
}

void GraphicsView::mouseDoubleClickEvent(QMouseEvent *event) {
    QGraphicsView::mouseDoubleClickEvent(event);
}

void GraphicsView::mouseMoveEvent(QMouseEvent *event) {
    if(isDragging && currentTool != ShapeFactory::ToolType::Move) {
        QPointF pt = mapToScene(event->pos());
        currentItem->mouseMove(pt.x(), pt.y(), event->modifiers());
        return;
    }
    QGraphicsView::mouseMoveEvent(event);
}

void GraphicsView::mousePressEvent(QMouseEvent *event) {
    isDragging = true;

    if (currentTool == ShapeFactory::ToolType::Move) {
        if(dragMode() != ScrollHandDrag)
            setDragMode(QGraphicsView::RubberBandDrag);
    }
    else {
        QPointF scenePos = mapToScene(event->pos());
        currentItem = ShapeFactory::createShape(currentTool, scenePos);

        if (currentItem.get()) {
            shapeList.push_back(currentItem);
            scene()->addItem(currentItem->getParent());
        }
    }

    QGraphicsView::mousePressEvent(event);
}

void GraphicsView::mouseReleaseEvent(QMouseEvent *) {
    isDragging = false;
    setDragMode(NoDrag);
    currentItem.reset();
}

void GraphicsView::wheelEvent(QWheelEvent *event) {
    // if (event->modifiers() & Qt::AltModifier) {
    //     double scaleFactor = (event->angleDelta().x() < 0) ? 1 / 1.15 : 1.15;
    //     scale(scaleFactor, scaleFactor);
    //     event->accept();
    //     return;
    // }

    QGraphicsView::wheelEvent(event);
}
