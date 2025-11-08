#include "Rectangle.h"
using namespace Shapes;

Rectangle::Rectangle(const QPointF &pos, QGraphicsItem *parent) : QGraphicsRectItem(parent) {
    setPos(pos);
    selectionRect->setParentItem(this);
    setPen(currentPen);
    setBrush(currentBrush);

    auto square = [&](QPointF center, QPointF mousePos) -> QRectF {
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

    auto rectangle = [&](QPointF center, QPointF mousePos) -> QRectF {
        QLineF line(center, mousePos);
        double hypotenuse = line.length();
        double theta = line.angle() + rotation();

        double width = hypotenuse * abs(cos(qDegreesToRadians(theta)));
        double height = hypotenuse * abs(sin(qDegreesToRadians(theta)));
        handleAngle = line.angle();
        prevRotation = -rotation();

        return QRectF(-width, -height, 2 * width, 2 * height);
    };

    typeStore[0] = rectangle;
    typeStore[1] = square;
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsMovable);

    for(int ii = 0; ii < 4; ++ii) {
        markers[ii] = std::make_unique<Shapes::Marker>(QPointF(), this);
    }
}

void Rectangle::mouseMove(double x, double y, Qt::KeyboardModifiers key) {
    bool ctrlPressed = (key & Qt::ControlModifier);

    if(ctrlPressed) {
        QLineF ln(scenePos(), QPointF(x,y));
        qreal delta = ln.angle() - handleAngle;
        setRotation(-(prevRotation + delta));
        return;
    }

    bool shiftPressed = key & Qt::ShiftModifier;
    QRectF rec = typeStore[shiftPressed](scenePos(), QPointF(x,y));
    setRect(rec);
    selectionRect->setRect(boundingRect());

    markers[MarkerType::TopLeft]->setPos(boundingRect().topLeft());
    markers[MarkerType::TopRight]->setPos(boundingRect().topRight());
    markers[MarkerType::BottomLeft]->setPos(boundingRect().bottomLeft());
    markers[MarkerType::BottomRight]->setPos(boundingRect().bottomRight());
}

void Ellipse::mousePress(double x, double y, Qt::KeyboardModifiers ) {
    QLineF ln(scenePos(), QPointF(x,y));
    handleAngle = ln.angle();
    prevRotation = -rotation();
    qDebug() << " handleAngle, prevRotation " << handleAngle << prevRotation;
}

QGraphicsItem *Rectangle::getParent() {
    return this;
}

void Rectangle::select(bool flag) {
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

bool Rectangle::isItemSelected() {
    return itemSelected;
}

void Rectangle::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    moveHelper = pos() - event->scenePos();
}

void Rectangle::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if(isItemSelected())
        setPos(event->scenePos() + moveHelper);
}

void Rectangle::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
}

void Rectangle::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
    itemSelected = !itemSelected;
    select(itemSelected);
}

//--------------------------------------------------------------------------//
// PROPERTY

QString Rectangle::qml() const
{
    return m_qml;
}

void Rectangle::setQml(const QString &newQml)
{
    if (m_qml == newQml)
        return;
    m_qml = newQml;
    emit qmlChanged();
}

double Rectangle::width() const
{
    return m_width;
}

void Rectangle::setWidth(double newWidth)
{
    if (qFuzzyCompare(m_width, newWidth))
        return;
    m_width = newWidth;
    emit widthChanged();
}

double Rectangle::height() const
{
    return m_height;
}

void Rectangle::setHeight(double newHeight)
{
    if (qFuzzyCompare(m_height, newHeight))
        return;
    m_height = newHeight;
    emit heightChanged();
}

// PROPERTY
//--------------------------------------------------------------------------//
