#ifndef POLYGON_H
#define POLYGON_H

#include "ShapeBase.h"
#include <QGraphicsPolygonItem>

namespace Shapes {

class Polygon : public Shapes::ShapeBase, public QGraphicsPolygonItem {
    Q_OBJECT
    Q_PROPERTY(QString qml READ qml WRITE setQml NOTIFY qmlChanged FINAL)
    Q_PROPERTY(double width READ width WRITE setWidth NOTIFY widthChanged FINAL)
    Q_PROPERTY(double height READ height WRITE setHeight NOTIFY heightChanged FINAL)

public:
    Polygon(const QPointF& pos, QGraphicsItem* parent = nullptr);

    QString qml() const;
    void setQml(const QString &newQml);

    double width() const;
    void setWidth(double newWidth);

    double height() const;
    void setHeight(double newHeight);

signals:
    void qmlChanged();
    void widthChanged();
    void heightChanged();

private:
    int sides;
    QString m_qml;
    double m_width;
    double m_height;
    std::array<std::unique_ptr<Shapes::Marker>, 4> markers;

    QPolygonF getRegularPolygon(int sides, double radius, QPointF center, double startAngleDeg);

    void mouseMove(double x, double y, Qt::KeyboardModifiers key) override;
    void mousePress(double x, double y, Qt::KeyboardModifiers key) override;
    QGraphicsItem* getParent() override;
    void select(bool flag) override;
    bool isItemSelected() override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
};
}
#endif // POLYGON_H
