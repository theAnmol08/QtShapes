#include "Polygon.h"

#include <QKeyEvent>

using namespace Shapes;

Polygon::Polygon(const QPointF &pos, QGraphicsItem *parent) : QGraphicsPolygonItem(parent) {
    setPos(pos);
    selectionRect->setParentItem(this);
    setPen(currentPen);
    setBrush(currentBrush);

    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsMovable);
    sides = 8;
}

QPolygonF Polygon::getRegularPolygon(int sides, double radius, QPointF center) {
    QPolygonF polygon;
    if (sides < 3)
        return polygon;

    double startAngleRad = qDegreesToRadians(0);

    for (int i = 0; i < sides; ++i) {
        double angle = startAngleRad + (2 * M_PI * i) / sides;
        double x = center.x() + radius * qCos(angle);
        double y = center.y() + radius * qSin(angle);
        polygon << QPointF(x, y);
    }

    return polygon;
}

void Polygon::mouseMove(double x, double y, Qt::KeyboardModifiers key) {
    QLineF line(mapFromScene(scenePos()), mapFromScene(QPointF(x, y)));
    double hypotenuse = line.length();
    double theta = line.angle();

    qDebug() << __FUNCTION__ << theta << key;

    if((theta < 135 && theta > 45) || (theta < 315 && theta > 225)) {
        theta = abs(sin(qDegreesToRadians(theta)));
    }
    else {
        theta = abs(cos(qDegreesToRadians(theta)));
    }

    double radius = hypotenuse * theta;
    setPolygon(getRegularPolygon(sides, radius, mapFromScene(scenePos())));

    selectionRect->setRect(boundingRect());
    // markers[MarkerType::TopLeft]->setPos(boundingRect().topLeft());
    // markers[MarkerType::TopRight]->setPos(boundingRect().topRight());
    // markers[MarkerType::BottomLeft]->setPos(boundingRect().bottomLeft());
    // markers[MarkerType::BottomRight]->setPos(boundingRect().bottomRight());
}

void Polygon::mousePress(double, double, Qt::KeyboardModifiers ) {
}

QGraphicsItem *Polygon::getParent() {
    return this;
}

void Polygon::select(bool flag) {
    markers[MarkerType::TopLeft]->setVisible(flag);
    markers[MarkerType::TopRight]->setVisible(flag);
    markers[MarkerType::BottomLeft]->setVisible(flag);
    markers[MarkerType::BottomRight]->setVisible(flag);

    markers[MarkerType::TopLeft]->setPos(boundingRect().topLeft());
    markers[MarkerType::TopRight]->setPos(boundingRect().topRight());
    markers[MarkerType::BottomLeft]->setPos(boundingRect().bottomLeft());
    markers[MarkerType::BottomRight]->setPos(boundingRect().bottomRight());

    selectionRect->setVisible(flag);
    selectionRect->setRect(boundingRect());
}

bool Polygon::isItemSelected() {
    return itemSelected;
}

void Polygon::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    moveHelper = pos() - event->scenePos();
}

void Polygon::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if(isItemSelected())
        setPos(event->scenePos() + moveHelper);
}

void Polygon::mouseReleaseEvent(QGraphicsSceneMouseEvent *) {
}

void Polygon::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *) {
    itemSelected = !itemSelected;
    select(itemSelected);
}

void Polygon::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_Up)
        ++sides;
    else if(event->key() == Qt::Key_Down && sides > 3)
        --sides;
}

void Polygon::keyReleaseEvent(QKeyEvent *) {

}

//--------------------------------------------------------------------------//
// PROPERTY

QString Polygon::qml() const
{
    return m_qml;
}

void Polygon::setQml(const QString &newQml)
{
    if (m_qml == newQml)
        return;
    m_qml = newQml;
    emit qmlChanged();
}

double Polygon::width() const
{
    return m_width;
}

void Polygon::setWidth(double newWidth)
{
    if (qFuzzyCompare(m_width, newWidth))
        return;
    m_width = newWidth;
    emit widthChanged();
}

double Polygon::height() const
{
    return m_height;
}

void Polygon::setHeight(double newHeight)
{
    if (qFuzzyCompare(m_height, newHeight))
        return;
    m_height = newHeight;
    emit heightChanged();
}

// PROPERTY
//--------------------------------------------------------------------------//
