#include "clickdetector.h"

ClickDetector::ClickDetector(QGroupBox **groupBoxes, QObject *parent) : QObject(parent) {
    for (int i = 0; i < 16; ++i) {
        this->groupBoxes[i] = groupBoxes[i];
        groupBoxes[i]->installEventFilter(this);
    }
}

bool ClickDetector::eventFilter(QObject *obj, QEvent *event) {
    if (obj->inherits("QGroupBox") && event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        QGroupBox *groupBox = qobject_cast<QGroupBox*>(obj);

        if (groupBox) {
            for (int i = 0; i < 16; ++i) {
                if (groupBox == groupBoxes[i]) emit groupBoxIndexClicked(i);
            }
            return true;
        }
    }
    return QObject::eventFilter(obj, event);
}
