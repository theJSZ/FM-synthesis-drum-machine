#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGroupBox>
#include <QList>
#include <QString>
#include <QPushButton>
#include <QKeyEvent>
#include <QLayout>
#include <QFontDatabase>

#include <string>
#include <math.h>
#include <random>
#include <time.h>

#include "audiothread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class AudioThread;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setStepButtonLight(int step, bool on);

signals:
    void keyPressed(QKeyEvent *event);

protected:
    void keyPressEvent(QKeyEvent *event) override; /* override {
        emit keyPressed(event);
        QMainWindow::keyPressEvent(event); // Call base class implementation
    }*/
    QGroupBox *groupBoxes[16];

private:
    Ui::MainWindow *ui;
    AudioThread *audioThread;
    void setBackgroundColor(QWidget*, std::string);
    QPushButton *stepButtons[32];
    void initializeConnections();
    void handleStepChanged(int StepNumber);
    int mutateAmount;
    void setMutateAmount(int dialValue);
    void shiftPattern(int shiftAmount);
    void updateLayout();

    void savePattern(int slot);
    void loadPattern(int slot);
};
#endif // MAINWINDOW_H
