#ifndef LINE_H
#define LINE_H

#include "ShapeBase.h"
#include <QGraphicsLineItem>

namespace Shapes {

class Line : public Shapes::ShapeBase, public QGraphicsLineItem {
    Q_OBJECT
    Q_PROPERTY(QString qml READ qml WRITE setQml NOTIFY qmlChanged FINAL)
    Q_PROPERTY(double width READ width WRITE setWidth NOTIFY widthChanged FINAL)
    Q_PROPERTY(double height READ height WRITE setHeight NOTIFY heightChanged FINAL)

public:
    Line(const QPointF& pos, QGraphicsItem* parent = nullptr);

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
    QPointF initPos;
    QString m_qml;
    double m_width;
    double m_height;

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
#endif // LINE_H
