#include "GraphicsScene.h"

GraphicsScene::GraphicsScene(QObject *parent)
    : QGraphicsScene(parent) {
    setSceneRect(-500, -500, 1000, 1000);
}

void GraphicsScene::drawBackground(QPainter *painter, const QRectF &rect) {
    // painter->save();
    // Fill background
    painter->fillRect(rect, QColor(245, 245, 245));
    QPen gridPen(QColor(220, 220, 220));
    gridPen.setCosmetic(true);
    painter->setPen(gridPen);

    const int gridSize = 50;
    const int left   = static_cast<int>(std::floor(rect.left() / gridSize)) * gridSize;
    const int right  = static_cast<int>(std::ceil(rect.right() / gridSize)) * gridSize;
    const int top    = static_cast<int>(std::floor(rect.top() / gridSize)) * gridSize;
    const int bottom = static_cast<int>(std::ceil(rect.bottom() / gridSize)) * gridSize;

    for (int x = left; x <= right; x += gridSize)
        painter->drawLine(x, top, x, bottom);

    for (int y = top; y <= bottom; y += gridSize)
        painter->drawLine(left, y, right, y);

    // Draw scene border
    QPen border(Qt::darkGray, 1);
    border.setCosmetic(true);
    painter->setPen(border);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(sceneRect());
    // painter->restore();
}
