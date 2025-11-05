#ifndef SHAPEBASE_H
#define SHAPEBASE_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QPen>

namespace Shapes {
class ShapeBase: public QObject {
protected:
    enum MarkerType {
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight
    };

    bool itemSelected;
    QPen currentPen;
    QBrush currentBrush;
    QPointF moveHelper;
    QGraphicsRectItem* selectionRect; // Managed by QGraphicsItem: as we are setting parent for it in subclass

    ShapeBase() {
        itemSelected = true;
        currentPen.setWidth(1);
        currentBrush.setStyle(Qt::NoBrush);

        QPen pen(Qt::DotLine);
        pen.setColor(Qt::black);
        pen.setWidth(1);
        selectionRect = new QGraphicsRectItem;
        selectionRect->setPen(pen);
    }

public:
    virtual void select(bool flag) = 0;
    virtual void mouseMove(double x, double y, Qt::KeyboardModifiers key) = 0;
    virtual void mousePress(double x, double y, Qt::KeyboardModifiers key) = 0;
    virtual QGraphicsItem* getParent() = 0;
    virtual bool isItemSelected() = 0;
};

class Marker: public QGraphicsEllipseItem {
    ShapeBase* parent;
public:

    Marker(const QPointF& pos, ShapeBase* parent = nullptr) : QGraphicsEllipseItem(parent->getParent()) {
        setPos(pos);
        setPen(QPen(Qt::transparent));
        setBrush(QColor(Qt::black));
        setRect(-5,-5,10,10);
        setFlag(QGraphicsItem::ItemIgnoresTransformations);
        this->parent = parent;
    }

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override {
        parent->mousePress(event->scenePos().x(), scenePos().y(), event->modifiers());
    }

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override {
        parent->mouseMove(event->scenePos().x(), event->scenePos().y(), event->modifiers());
    }

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *) override {
        // parent->mouseRe(event->scenePos().x(), scenePos().y(), event->modifiers());
    }
};

}
#endif // SHAPEBASE_H
