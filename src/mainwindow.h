#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGroupBox>
#include <QList>
#include <QString>
#include <QPushButton>
#include <string>
#include "audiothread.h"
#include <math.h>
// #include "clickdetector.h"
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
    void setStepButtonLight(int step, bool on);

private:
    Ui::MainWindow *ui;
    AudioThread *audioThread;
    void setBackgroundColor(QWidget*, std::string);
    QGroupBox *groupBoxes[16];
    QPushButton *stepButtons[32];
    void initializeConnections();
    void handleStepChanged(int StepNumber);
    int mutateAmount;
    void setMutateAmount(int dialValue);
};
#endif // MAINWINDOW_H
