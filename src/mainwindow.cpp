#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , audioThread(nullptr)
    , groupBoxes()
{
    ui->setupUi(this);
    srand(time(NULL));

    groupBoxes[0]  = ui->groupBox_1;
    groupBoxes[1]  = ui->groupBox_2;
    groupBoxes[2]  = ui->groupBox_3;
    groupBoxes[3]  = ui->groupBox_4;
    groupBoxes[4]  = ui->groupBox_5;
    groupBoxes[5]  = ui->groupBox_6;
    groupBoxes[6]  = ui->groupBox_7;
    groupBoxes[7]  = ui->groupBox_8;

    stepButtons[0]  = ui->btn_step_1;
    stepButtons[1]  = ui->btn_step_2;
    stepButtons[2]  = ui->btn_step_3;
    stepButtons[3]  = ui->btn_step_4;
    stepButtons[4]  = ui->btn_step_5;
    stepButtons[5]  = ui->btn_step_6;
    stepButtons[6]  = ui->btn_step_7;
    stepButtons[7]  = ui->btn_step_8;
    stepButtons[8]  = ui->btn_step_9;
    stepButtons[9]  = ui->btn_step_10;
    stepButtons[10] = ui->btn_step_11;
    stepButtons[11] = ui->btn_step_12;
    stepButtons[12] = ui->btn_step_13;
    stepButtons[13] = ui->btn_step_14;
    stepButtons[14] = ui->btn_step_15;
    stepButtons[15] = ui->btn_step_16;
    stepButtons[16] = ui->btn_step_17;
    stepButtons[17] = ui->btn_step_18;
    stepButtons[18] = ui->btn_step_19;
    stepButtons[19] = ui->btn_step_20;
    stepButtons[20] = ui->btn_step_21;
    stepButtons[21] = ui->btn_step_22;
    stepButtons[22] = ui->btn_step_23;
    stepButtons[23] = ui->btn_step_24;
    stepButtons[24] = ui->btn_step_25;
    stepButtons[25] = ui->btn_step_26;
    stepButtons[26] = ui->btn_step_27;
    stepButtons[27] = ui->btn_step_28;
    stepButtons[28] = ui->btn_step_29;
    stepButtons[29] = ui->btn_step_30;
    stepButtons[30] = ui->btn_step_31;
    stepButtons[31] = ui->btn_step_32;

    audioThread = new AudioThread();
    audioThread->start();

    // connect master pitch
    connect(ui->dial_master_pitch, &QDial::valueChanged, [=](int dialValue) {
        float scaledDialValue = (float) dialValue / 500; // -1 .. 1
        scaledDialValue += 1.5;   //  0.5 .. 2.5
        audioThread->osc->setMasterFrequencyMultiplier(scaledDialValue);
    });

    // connect master volume
    connect(ui->dial_master_volume, &QDial::valueChanged, [=](int value) {
        std::cout << "master volume dial at " << value << std::endl;
        audioThread->setMasterVolume((float) value / 1000);
    });

    // connect tempo
    connect(ui->dial_tempo, &QDial::valueChanged, [=](int value) {
        audioThread->setBpm((float) value);
    });



    ui->dial_master_pitch->setValue(1);
    ui->dial_master_pitch->setValue(0);

    // connect reverb mix
    connect(ui->dial_reverb_mix, &QDial::valueChanged, [=](int value) {
        audioThread->setReverbMix((float) value / 1000);
    });

    // connect reverb damping
    connect(ui->dial_master_reverb_damp, &QDial::valueChanged, [=](int value) {
        audioThread->setReverbDamp((float) value / 1000);
    });

    // connect reverb decay
    connect(ui->dial_reverb_decay, &QDial::valueChanged, [=](int value) {
        audioThread->setReverbRoomSize((float) value / 1000);
    });


    // connect step buttons and sequence dials
    for (int i = 0; i < N_STEPS; ++i) {
        // step buttons
        QList<QPushButton *> stepButtons = groupBoxes[i]->findChildren<QPushButton *>();
        for (int j = 0; j < stepButtons.size(); ++j) {
            connect(stepButtons[j], &QPushButton::clicked, [=]() {
                audioThread->sequencer->toggleActiveStep(i + j*8);
            });
        }

        // sequence dials
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
            case 9:
                connect(dials[j], &QDial::valueChanged, [=](int dialValue) {
                    int scaledDialValue = dialValue / 2;
                    audioThread->sequencer->steps[i]->randomness = scaledDialValue;
                });
                // randomness
                break;
            default:
                break;
            }
        }

        // randomize dials
        for (int i = 0; i < N_STEPS; ++i) {

            QList<QDial *> dials = groupBoxes[i]->findChildren<QDial *>();
            for (int j = 0; j < dials.size(); ++j) {
                int randNum = rand()%(dials[j]->maximum() - dials[j]->minimum() + 1) + dials[j]->minimum();

                dials[j]->setValue(randNum);
            }
        }
    }

    // connect mutate
    connect(ui->dial_mutate, &QDial::valueChanged, this, &MainWindow::setMutateAmount);

    connect(audioThread->sequencer, &Sequencer::currentStepChanged, this, &MainWindow::handleStepChanged, Qt::UniqueConnection);

    connect(audioThread->sequencer, &Sequencer::stepActiveStatusChanged, this, [=](int step, bool on) {
        QString style;
        if (on) style = "border-radius:3; border: 1px solid black;background-color: red";
        else style = "border-radius:3; border: 1px solid black;background-color: gray";
        stepButtons[step]->setStyleSheet(style);
    }, Qt::UniqueConnection);
}

void MainWindow::setMutateAmount(int dialValue) {
    this->mutateAmount = dialValue;
}

void MainWindow::handleStepChanged(int stepNumber) {
    if (this->mutateAmount) {

        // MUTATION
        QList<QDial *> dials = groupBoxes[stepNumber % 8]->findChildren<QDial *>();
            for (int j = 0; j < dials.size()-1; ++j) { // don't mutate probability
                if (j == dials.size() - 4) continue; // don't mutate fb
                int minimum = dials[j]->minimum();
                int maximum = dials[j]->maximum();
                int randNum = rand()%(maximum - minimum + 1) + minimum;
                int currentValue = dials[j]->value();

                int diff = randNum - currentValue;
                int newValue = (int) currentValue + diff * ((float) mutateAmount / 1000);
                // std::cout << newValue << std::endl;
                dials[j]->setValue(newValue);
            }
    }
    stepButtons[stepNumber]->setStyleSheet(STEP_STYLESHEET_CURRENT);
    setStepButtonLight((stepNumber + 31) % 32, audioThread->sequencer->activeStep[(stepNumber + 31) % 32]);
}

void MainWindow::setStepButtonLight(int step, bool on) {
    QString style;
    if (on) style = STEP_STYLESHEET_ACTIVE;
    else style = STEP_STYLESHEET_NON_ACTIVE;

    stepButtons[step]->setStyleSheet(style);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setBackgroundColor(QWidget* element, std::string color) {
    element->setStyleSheet(QString("background-color:pink"));
}
