#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , audioThread(nullptr)
{
    ui->setupUi(this);

    audioThread = new AudioThread();
    audioThread->start(QThread::HighPriority);
    connect(ui->dial_tune_coarse, &QDial::valueChanged, this, &MainWindow::setCoarseTune);
    connect(ui->dial_tune_fine, &QDial::valueChanged, this, &MainWindow::setFineTune);
    connect(ui->btn_waveform, &QPushButton::clicked, this, &MainWindow::changeOscillator);
    connect(ui->dial_noise, &QDial::valueChanged, this, &MainWindow::setNoiseLevel);

    // connect(ui->dial_cutoff, &QDial::valueChanged, audioThread, &AudioThread::setCutoff);
    connect(ui->dial_cutoff, &QDial::valueChanged, this, &MainWindow::on_dialCutoff_valueChanged);
    connect(ui->dial_resonance, &QDial::valueChanged, audioThread, &AudioThread::setResonance);
    connect(ui->dial_env_depth, &QDial::valueChanged, audioThread, &AudioThread::setFegAmount);
    connect(ui->dial_env_decay, &QDial::valueChanged, audioThread, &AudioThread::setFegDecay);

    connect(audioThread->sequencer, &Sequencer::currentStepChanged, this, &MainWindow::updateStepButtons);

    connect(ui->btn_step1, &QPushButton::clicked, [this]() { toggleStep(0); });
    connect(ui->btn_step2, &QPushButton::clicked, [this]() { toggleStep(1); });
    connect(ui->btn_step3, &QPushButton::clicked, [this]() { toggleStep(2); });
    connect(ui->btn_step4, &QPushButton::clicked, [this]() { toggleStep(3); });
    connect(ui->btn_step5, &QPushButton::clicked, [this]() { toggleStep(4); });
    connect(ui->btn_step6, &QPushButton::clicked, [this]() { toggleStep(5); });
    connect(ui->btn_step7, &QPushButton::clicked, [this]() { toggleStep(6); });
    connect(ui->btn_step8, &QPushButton::clicked, [this]() { toggleStep(7); });

}

void MainWindow::toggleStep(int step) {
    audioThread->sequencer->toggleActive(step);
}

void MainWindow::updateStepButtons(int step) {
    static QPushButton *buttons[8] = {
        ui->btn_step1,
        ui->btn_step2,
        ui->btn_step3,
        ui->btn_step4,
        ui->btn_step5,
        ui->btn_step6,
        ui->btn_step7,
        ui->btn_step8,
    };

    for (int i = 0; i < 8; ++i) {
        if (i == step) buttons[i]->setStyleSheet(QString("background-color: pink"));
        else if (audioThread->sequencer->steps[i].slide) buttons[i]->setStyleSheet(QString("background-color: lightgreen"));
        else if (audioThread->sequencer->steps[i].active) buttons[i]->setStyleSheet(QString("background-color: lightblue"));
        else buttons[i]->setStyleSheet(QString("background-color: white"));
    }
}

void MainWindow::setFegAmount(int value) {
    float fegAmount = static_cast<float>(value);
    audioThread->setFegAmount(fegAmount);
}

void MainWindow::setFegDecay(int value) {
    float fegAmount = static_cast<float>(value);
    audioThread->setFegDecay(fegAmount);
}

void MainWindow::on_dialCutoff_valueChanged(int value) {
    float cutoff = static_cast<float>(value);
    audioThread->setCutoff(cutoff);
}

void MainWindow::setCoarseTune(int value) {
    float freq = static_cast<float>(value);
    freq /= 1000; // 0 ..1
    freq = pow(freq, 1.6); // trying to get dial midpoint to be 120
    freq *= 180; // 0 .. 180
    freq += 60;   // 60 .. 240
    audioThread->osc->setFreq(freq);
}

void MainWindow::setFineTune(int value) {
    float fineTune = static_cast<float>(value);
    fineTune /= 1000; // 0 ..1
    fineTune = pow(fineTune, 1.6); // same curve as for coarse tune?
    fineTune /= 10;
    fineTune += 0.95;   // 0.95 .. 1.05
    audioThread->osc->setFineTune(fineTune);
}

void MainWindow::changeOscillator() {
    audioThread->osc->changeWave();
    ui->btn_waveform->setText(QString::fromStdString(audioThread->osc->getWave()));
}

void MainWindow::setNoiseLevel(int value) {
    float level = static_cast<float>(value);
    level /= 1000;
    level *= level;
    audioThread->osc->setNoiseLevel(level);
}

MainWindow::~MainWindow()
{
    delete ui;
}

