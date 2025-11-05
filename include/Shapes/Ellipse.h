#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "ShapeBase.h"
#include <QGraphicsEllipseItem>

namespace Shapes {

class Ellipse : public Shapes::ShapeBase, public QGraphicsEllipseItem {
    Q_OBJECT
    Q_PROPERTY(QString qml READ qml WRITE setQml NOTIFY qmlChanged FINAL)
    Q_PROPERTY(double width READ width WRITE setWidth NOTIFY widthChanged FINAL)
    Q_PROPERTY(double height READ height WRITE setHeight NOTIFY heightChanged FINAL)

public:
    Ellipse(const QPointF& pos, QGraphicsItem* parent = nullptr);

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
    QString m_qml;
    double m_width;
    double m_height;
    std::array<std::function<QRectF(QPointF, QPointF)>, 2> typeStore;
    std::array<std::unique_ptr<Shapes::Marker>, 4> markers;

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
#endif // ELLIPSE_H
