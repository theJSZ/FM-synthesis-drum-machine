#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGroupBox>
#include <QList>
#include <QString>
#include <string>
#include "audiothread.h"
#include <math.h>
#include "clickdetector.h"
#include <random>
#include <time.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    AudioThread *audioThread;
    void setBackgroundColor(QWidget*, std::string);
    QGroupBox *groupBoxes[16];
};
#endif // MAINWINDOW_H
