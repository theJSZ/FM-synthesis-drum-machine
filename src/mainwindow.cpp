#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , audioThread(nullptr)
{
    ui->setupUi(this);

    // audioThread = new AudioThread();
    // audioThread->start(QThread::HighPriority);

}


MainWindow::~MainWindow()
{
    delete ui;
}

