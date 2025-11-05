#include "Ellipse.h"
using namespace Shapes;

Ellipse::Ellipse(const QPointF &pos, QGraphicsItem *parent) : QGraphicsEllipseItem(parent) {
    setPos(pos);
    selectionRect->setParentItem(this);
    setPen(currentPen);
    setBrush(currentBrush);
    setStartAngle(270);

    auto circle = [&](QPointF center, QPointF mousePos) -> QRectF {
        QLineF line(center, mousePos);
        double hypotenuse = line.length();
        double theta = line.angle();

        if((theta < 135 && theta > 45) || (theta < 315 && theta > 225)) {
            theta = abs(sin(qDegreesToRadians(theta)));
        }
        else {
            theta = abs(cos(qDegreesToRadians(theta)));
        }

        double rad = hypotenuse * theta;
        return QRectF(-rad, -rad, 2 * rad, 2 * rad);
    };

    auto ellipse = [&](QPointF center, QPointF mousePos) -> QRectF {
        double width = abs(center.x() - mousePos.x());
        double height = abs(center.y() - mousePos.y());
        return QRectF(-width, -height, 2 * width, 2 * height);
    };

    typeStore[0] = ellipse;
    typeStore[1] = circle;
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsMovable);

    for(int ii = 0; ii < 4; ++ii) {
        markers[ii] = std::make_unique<Shapes::Marker>(QPointF(), this);
    }
}

void Ellipse::mouseMove(double x, double y, Qt::KeyboardModifiers key) {
    bool shiftPressed = key & Qt::ShiftModifier;
    QRectF rec = typeStore[shiftPressed](scenePos(), QPointF(x,y));
    setRect(rec);
    selectionRect->setRect(boundingRect());

    markers[MarkerType::TopLeft]->setPos(boundingRect().topLeft());
    markers[MarkerType::TopRight]->setPos(boundingRect().topRight());
    markers[MarkerType::BottomLeft]->setPos(boundingRect().bottomLeft());
    markers[MarkerType::BottomRight]->setPos(boundingRect().bottomRight());
}

void Ellipse::mousePress(double, double, Qt::KeyboardModifiers ) {
}

QGraphicsItem *Ellipse::getParent() {
    return this;
}

void Ellipse::select(bool flag) {
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

bool Ellipse::isItemSelected() {
    return itemSelected;
}

void Ellipse::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    moveHelper = pos() - event->scenePos();
}

void Ellipse::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if(isItemSelected())
        setPos(event->scenePos() + moveHelper);
}

void Ellipse::mouseReleaseEvent(QGraphicsSceneMouseEvent *) {
}

void Ellipse::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *) {
    itemSelected = !itemSelected;
    select(itemSelected);
}

//--------------------------------------------------------------------------//
// PROPERTY

QString Ellipse::qml() const
{
    return m_qml;
}

void Ellipse::setQml(const QString &newQml)
{
    if (m_qml == newQml)
        return;
    m_qml = newQml;
    emit qmlChanged();
}

double Ellipse::width() const
{
    return m_width;
}

void Ellipse::setWidth(double newWidth)
{
    if (qFuzzyCompare(m_width, newWidth))
        return;
    m_width = newWidth;
    emit widthChanged();
}

double Ellipse::height() const
{
    return m_height;
}

void Ellipse::setHeight(double newHeight)
{
    if (qFuzzyCompare(m_height, newHeight))
        return;
    m_height = newHeight;
    emit heightChanged();
}

// PROPERTY
//--------------------------------------------------------------------------//
