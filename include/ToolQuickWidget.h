#ifndef TOOLQUICKWIDGET_H
#define TOOLQUICKWIDGET_H

#include <QQuickWidget>

class ToolQuickWidget: public QQuickWidget {
public:
    ToolQuickWidget (QWidget* parent = nullptr): QQuickWidget(parent) {
        isDrag = false;
    }

private:
    bool isDrag;
    QPointF moveHelper;
    void mousePressEvent(QMouseEvent *event) override {
        isDrag = true;
        moveHelper = event->pos();
        QQuickWidget::mousePressEvent(event);
    }

    void mouseReleaseEvent(QMouseEvent *event) override {
        isDrag = false;
        QQuickWidget::mouseReleaseEvent(event);
    }

    void mouseMoveEvent(QMouseEvent *event) override {
        if(isDrag) {
            QPointF newTopLeft = mapToParent(event->pos() - moveHelper);
            QRect rt = geometry();
            setGeometry(newTopLeft.x(), newTopLeft.y(), rt.width(), rt.height());
        }
        QQuickWidget::mouseMoveEvent(event);
    }
};

#endif // TOOLQUICKWIDGET_H
