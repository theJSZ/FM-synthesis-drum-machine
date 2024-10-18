#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , audioThread(nullptr)
    , groupBoxes()
{
    ui->setupUi(this);


    groupBoxes[0]  = ui->groupBox_1;
    groupBoxes[1]  = ui->groupBox_2;
    groupBoxes[2]  = ui->groupBox_3;
    groupBoxes[3]  = ui->groupBox_4;
    groupBoxes[4]  = ui->groupBox_5;
    groupBoxes[5]  = ui->groupBox_6;
    groupBoxes[6]  = ui->groupBox_7;
    groupBoxes[7]  = ui->groupBox_8;

    audioThread = new AudioThread();
    audioThread->start();

    for (int i = 0; i < N_STEPS; ++i) {

        QList<QDial *> dials = groupBoxes[i]->findChildren<QDial *>();
        for (int j = 0; j < dials.size(); ++j) {
            switch (j)
            {
            case 0:
                connect(dials[j], &QDial::valueChanged, [=](int dialValue) {
                    float scaledDialValue = (float) dialValue / 500;
                    scaledDialValue += 1;   //  0 .. 2
                    audioThread->sequencer->steps[i]->frequencyMultiplier = scaledDialValue;
                });
                // pitch
                break;
            case 1:
                connect(dials[j], &QDial::valueChanged, [=](int dialValue) {
                    float scaledDialValue = (float) dialValue / 1000;
                    audioThread->sequencer->steps[i]->rampAmount = scaledDialValue;
                });
                // ramp amount
                break;
            case 2:
                connect(dials[j], &QDial::valueChanged, [=](int dialValue) {
                    float scaledDialValue = (float) dialValue / 1000 + 0.01;
                    audioThread->sequencer->steps[i]->rampDecay = scaledDialValue * scaledDialValue;
                });
                // ramp decay
                break;
            case 3:
                connect(dials[j], &QDial::valueChanged, [=](int dialValue) {
                    float scaledDialValue = (float) dialValue / 4000;
                    audioThread->sequencer->steps[i]->fmAmount = scaledDialValue * scaledDialValue;
                });
                // fm amount
                break;
            case 4:
                connect(dials[j], &QDial::valueChanged, [=](int dialValue) {
                    float scaledDialValue = (float) dialValue / 500;
                    scaledDialValue += 0.5;   //  0 .. 1.5
                    audioThread->sequencer->steps[i]->fmFrequencyMultiplier = scaledDialValue;
                });
                // fm frequency
                break;
            case 5:
                connect(dials[j], &QDial::valueChanged, [=](int dialValue) {
                    float scaledDialValue = (float) dialValue / 1000 + 0.01;
                    audioThread->sequencer->steps[i]->fmDecay = scaledDialValue * scaledDialValue;
                });
                // fm decay
                break;
            case 6:
                connect(dials[j], &QDial::valueChanged, [=](int dialValue) {
                    float scaledDialValue = (float) dialValue / 1000;
                    audioThread->sequencer->steps[i]->fmFeedback = scaledDialValue * scaledDialValue;
                });
                // fm feedback
                break;
            case 7:
                connect(dials[j], &QDial::valueChanged, [=](int dialValue) {
                    float scaledDialValue = (float) dialValue / 1000 + 0.01;
                    audioThread->sequencer->steps[i]->aegDecay = scaledDialValue * scaledDialValue;
                });
                // amp decay
                break;
            case 8:
                connect(dials[j], &QDial::valueChanged, [=](int dialValue) {
                    float scaledDialValue = (float) dialValue / 1000;
                    audioThread->sequencer->steps[i]->volume = scaledDialValue * scaledDialValue;
                });
                // volume
                break;

            default:
                break;
            }
        }

    ClickDetector *clickDetector = new ClickDetector(groupBoxes, this);

    connect(clickDetector, &ClickDetector::groupBoxIndexClicked, this, [=](int index) {
        audioThread->sequencer->steps[index]->toggleActive();
        if (audioThread->sequencer->steps[index]->active) {
            groupBoxes[index]->setStyleSheet(QString::fromStdString(STEP_STYLESHEET_DEFAULT));
        } else {
            groupBoxes[index]->setStyleSheet(QString::fromStdString(STEP_STYLESHEET_DISABLED));
        }
    });

    connect(audioThread->sequencer, &Sequencer::currentStepChanged, this, [=](int stepNumber) {
        for (int i = 0; i < N_STEPS; ++i) {
            if (audioThread->sequencer->steps[i]->active) {
                groupBoxes[i]->setStyleSheet(QString::fromStdString(STEP_STYLESHEET_DEFAULT));
            } else {
                groupBoxes[i]->setStyleSheet(QString::fromStdString(STEP_STYLESHEET_DISABLED));
            }
        }
        groupBoxes[stepNumber]->setStyleSheet(QString::fromStdString(STEP_STYLESHEET_CURRENT));

    });
    }

    // setBackgroundColor(ui->groupBox_2, "pink");
    // ui->groupBox_11->setStyleSheet(QString::fromStdString(STEP_STYLESHEET_DEFAULT));
    // ui->groupBox_10->setStyleSheet(QString::fromStdString(STEP_STYLESHEET_DISABLED));
    // ui->groupBox_9->setStyleSheet(QString::fromStdString(STEP_STYLESHEET_CURRENT));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setBackgroundColor(QWidget* element, std::string color) {
    element->setStyleSheet(QString("background-color:pink"));
}