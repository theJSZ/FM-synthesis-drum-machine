#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "audiothread.h"
#include <math.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void toggleStep(int step);

private:
    Ui::MainWindow *ui;
    AudioThread *audioThread;
    void setCoarseTune(int);
    void setFineTune(int);
    void changeOscillator();
    void setNoiseLevel(int);
    void on_dialCutoff_valueChanged(int value);
    void setFegAmount(int);
    void setFegDecay(int);
    void updateStepButtons(int);




};
#endif // MAINWINDOW_H
