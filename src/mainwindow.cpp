#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , audioThread(nullptr)
{
    ui->setupUi(this);

    audioThread = new AudioThread();
    audioThread->start();

    // setBackgroundColor(ui->groupBox_2, "pink");
    ui->groupBox_11->setStyleSheet(QString::fromStdString(STEP_STYLESHEET_DEFAULT));
    ui->groupBox_10->setStyleSheet(QString::fromStdString(STEP_STYLESHEET_DISABLED));
    ui->groupBox_9->setStyleSheet(QString::fromStdString(STEP_STYLESHEET_CURRENT));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setBackgroundColor(QWidget* element, std::string color) {
    element->setStyleSheet(QString("background-color:pink"));
}