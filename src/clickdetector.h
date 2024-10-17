#ifndef CLICKDETECTOR_H
#define CLICKDETECTOR_H

#include <QObject>
#include <QWidget>
#include <QGroupBox>
#include <QEvent>
#include <QMouseEvent>
#include <iostream>
#include "constants.h"

class ClickDetector : public QObject {
    Q_OBJECT

public:
    explicit ClickDetector(QGroupBox **groupBoxes, QObject *parent = nullptr);

signals:
    void groupBoxClicked(QGroupBox *groupBox, QMouseEvent *event);
    void groupBoxIndexClicked(int i);

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    QGroupBox *groupBoxes[16];
};

#endif