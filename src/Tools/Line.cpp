#include "Line.h"
using namespace Shapes;

Line::Line(const QPointF &pos, QGraphicsItem *parent) : QGraphicsLineItem(parent) {
    initPos = pos;
    QPen pen(Qt::DotLine);
    pen.setWidth(1);
    selectionRect->setPen(pen);
    selectionRect->setParentItem(this);
    setPen(currentPen);

    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsMovable);
}

void Line::mouseMove(double x, double y, Qt::KeyboardModifiers key) {
    bool shiftPressed = key & Qt::ShiftModifier;
    QLineF ln(initPos, QPointF(x, y));
    if(shiftPressed) {
        double nearestAngle = round(ln.angle() / 45.0) * 45.0;
        ln.setAngle(nearestAngle);
    }
    setLine(ln);
    selectionRect->setRect(boundingRect());
}

void Line::mousePress(double x, double y, Qt::KeyboardModifiers key) {
}

QGraphicsItem *Line::getParent() {
    return this;
}

void Line::select(bool flag) {
    if(flag)
        selectionRect->setRect(boundingRect());
    else
        selectionRect->setRect(QRectF());
}

bool Line::isItemSelected() {
    return itemSelected;
}

void Line::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    moveHelper = pos() - event->scenePos();
}

void Line::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if(isItemSelected())
        setPos(event->scenePos() + moveHelper);
}

void Line::mouseReleaseEvent(QGraphicsSceneMouseEvent *) {
}

void Line::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *) {
    itemSelected = !itemSelected;
    select(itemSelected);
}


//--------------------------------------------------------------------------//
// PROPERTY

QString Line::qml() const
{
    return m_qml;
}

void Line::setQml(const QString &newQml)
{
    if (m_qml == newQml)
        return;
    m_qml = newQml;
    emit qmlChanged();
}

double Line::width() const
{
    return m_width;
}

void Line::setWidth(double newWidth)
{
    if (qFuzzyCompare(m_width, newWidth))
        return;
    m_width = newWidth;
    emit widthChanged();
}

double Line::height() const
{
    return m_height;
}

void Line::setHeight(double newHeight)
{
    if (qFuzzyCompare(m_height, newHeight))
        return;
    m_height = newHeight;
    emit heightChanged();
}

// PROPERTY
//--------------------------------------------------------------------------//
