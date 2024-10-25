#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    // , audioThread(this, nullptr)
    , groupBoxes()
    , mutateAmount(0)
{
    audioThread = new AudioThread(this);
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

    // assign step buttons
    for (int i = 0; i < 8; ++i) {
        QGroupBox *groupBox = groupBoxes[i];
        for (int j = 0; j < 4; ++j) {
            QPushButton *button = groupBox->findChild<QPushButton *>(QString("btn_step_%1").arg(i+1 + j*8));
            stepButtons[i + j*8] = button;
        }
    }

    audioThread->start();

    // connect master pitch
    connect(ui->dial_master_pitch, &QDial::valueChanged, [=](int dialValue) {
        float scaledDialValue = (float) dialValue / 500; // -1 .. 1
        scaledDialValue += 1.5;   //  0.5 .. 2.5
        for (int i = 0; i < 8; ++i) {
            audioThread->voices->voices[i]->setMasterFrequencyMultiplier(scaledDialValue);
        }
    });

    // connect master volume
    connect(ui->dial_master_volume, &QDial::valueChanged, [=](int value) {
        audioThread->setMasterVolume((float) value / 1000);
    });

    // connect swing
    connect(ui->dial_swing, &QDial::valueChanged, [=](int value) {
        audioThread->setSwing(value / 2);
    });

    // connect tempo
    connect(ui->dial_tempo, &QDial::valueChanged, [=](int value) {
        audioThread->setBpm((float) value);
        ui->label_tempo_numeric->setText(QString::number(value));
        ui->label_tempo_numeric->setAlignment(Qt::AlignCenter);
    });

    ui->dial_tempo->setValue(130);

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
                // pitch
                connect(dials[j], &QDial::valueChanged, [=](int dialValue) {
                    float scaledDialValue = (float) dialValue / 500;
                    scaledDialValue += 1;   //  0 .. 2
                    audioThread->sequencer->steps[i]->frequencyMultiplier = scaledDialValue;
                });
                break;
            case 1:
                // ramp amount
                connect(dials[j], &QDial::valueChanged, [=](int dialValue) {
                    float scaledDialValue = (float) dialValue / 1000;
                    audioThread->sequencer->steps[i]->rampAmount = scaledDialValue;
                });
                break;
            case 2:
                // ramp decay
                connect(dials[j], &QDial::valueChanged, [=](int dialValue) {
                    float scaledDialValue = (float) dialValue / 1000 + 0.01;
                    audioThread->sequencer->steps[i]->rampDecay = scaledDialValue * scaledDialValue;
                });
                break;
            case 3:
                // fm amount
                connect(dials[j], &QDial::valueChanged, [=](int dialValue) {
                    float scaledDialValue = (float) dialValue / 4000;
                    audioThread->sequencer->steps[i]->fmAmount = scaledDialValue * scaledDialValue;
                });
                break;
            case 4:
                // fm frequency
                connect(dials[j], &QDial::valueChanged, [=](int dialValue) {
                    float scaledDialValue = (float) dialValue / 500;
                    scaledDialValue += 0.5;   //  0 .. 1.5
                    audioThread->sequencer->steps[i]->fmFrequencyMultiplier = scaledDialValue;
                });
                break;
            case 5:
                // fm decay
                connect(dials[j], &QDial::valueChanged, [=](int dialValue) {
                    float scaledDialValue = (float) dialValue / 1000 + 0.01;
                    audioThread->sequencer->steps[i]->fmDecay = scaledDialValue * scaledDialValue;
                });
                break;
            case 6:
                // fm feedback
                connect(dials[j], &QDial::valueChanged, [=](int dialValue) {
                    float scaledDialValue = (float) dialValue / 1000;
                    audioThread->sequencer->steps[i]->fmFeedback = scaledDialValue;
                });
                break;
            case 7:
                // amp decay
                connect(dials[j], &QDial::valueChanged, [=](int dialValue) {
                    float scaledDialValue = (float) dialValue / 1000 + 0.01;
                    audioThread->sequencer->steps[i]->aegDecay = scaledDialValue * scaledDialValue;
                });
                break;
            case 8:
                // volume
                connect(dials[j], &QDial::valueChanged, [=](int dialValue) {
                    float scaledDialValue = (float) dialValue / 1000;
                    audioThread->sequencer->steps[i]->volume = scaledDialValue * scaledDialValue;
                });
                break;
            case 9:
                // randomness
                connect(dials[j], &QDial::valueChanged, [=](int dialValue) {
                    int scaledDialValue = dialValue / 2;
                    audioThread->sequencer->steps[i]->randomness = scaledDialValue;
                });
                break;
            default:
                break;
            }
        }

        // randomize dials
        for (int i = 0; i < N_STEPS; ++i) {

            QList<QDial *> dials = groupBoxes[i]->findChildren<QDial *>();
            for (int j = 0; j < dials.size()-1; ++j) { // don't randomize %
                int randNum = rand()%(dials[j]->maximum() - dials[j]->minimum() + 1) + dials[j]->minimum();

                dials[j]->setValue(randNum);
            }
        }
    }

    // connect mutate
    connect(ui->dial_mutate, &QDial::valueChanged, this, &MainWindow::setMutateAmount);

    // sequencer :current step changed
    connect(audioThread->sequencer, &Sequencer::currentStepChanged, this, &MainWindow::handleStepChanged, Qt::UniqueConnection);

    // sequencer: step active status changed
    connect(audioThread->sequencer, &Sequencer::stepActiveStatusChanged, this, [=](int step, bool on) {
        QString style;
        if (on) style = "border-radius:3; border: 1px solid black;background-color: red";
        else style = "border-radius:3; border: 1px solid black;background-color: gray";
        stepButtons[step]->setStyleSheet(style);
    }, Qt::UniqueConnection);
} // MainWindow()

void MainWindow::setMutateAmount(int dialValue) {
    this->mutateAmount = dialValue;
}

void MainWindow::handleStepChanged(int stepNumber) {
    if (this->mutateAmount) {

        // MUTATION
        QList<QDial *> dials = groupBoxes[(stepNumber+1) % 8]->findChildren<QDial *>();
            for (int j = 0; j < dials.size()-1; ++j) { // don't mutate probability
                if (j == dials.size() - 4) continue; // don't mutate fb
                int minimum = dials[j]->minimum();
                int maximum = dials[j]->maximum();
                int randNum = rand()%(maximum - minimum + 1) + minimum;
                int currentValue = dials[j]->value();

                int diff = randNum - currentValue;
                int newValue = (int) currentValue + diff * ((float) mutateAmount / 1000);
                dials[j]->setValue(newValue);
            }
    }

    // light up current step, return previous step to default
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

void MainWindow::keyPressEvent(QKeyEvent *event) {
    // 49 is 1. 33 is shift+1
    if (event->key() >= 33 && event->key() <= 40) {
        loadPattern(event->key() - 33);
    }
    if (event->key() == 164) loadPattern(3);
    if (event->key() == 47) loadPattern(6);

    if (event->key() >= 49 && event->key() <= 56) {
        savePattern(event->key() - 49);
    }
}

void MainWindow::savePattern(int slot) {
    std::cout << "saving to slot " << slot << std::endl;
    int i = 0;
    int parameters[14*8];

    for (auto groupBox : groupBoxes) {
        QList<QDial *> dials = groupBox->findChildren<QDial *>();
        for (auto dial : dials) {
            parameters[i++] = dial->value();
        }
    }
    for (auto step : audioThread->sequencer->activeStep) {
        parameters[i++] = (int) step;
    }
    audioThread->sequencer->patterns[slot]->setPatternParameters(parameters);
}

void MainWindow::loadPattern(int slot) {
    std::cout << "loading from slot " << slot << std::endl;
    int *parameters = audioThread->sequencer->patterns[slot]->getPatternParameters();
    int i = 0;
    for (auto groupBox : groupBoxes) {
        QList<QDial *> dials = groupBox->findChildren<QDial *>();
        for (auto dial : dials) {
            dial->setValue(parameters[i++]);
        }
    }
    for (int step = 0; step < 32; ++step) {
        audioThread->sequencer->activeStep[step] = parameters[i++];
        setStepButtonLight(step, audioThread->sequencer->activeStep[step]);
    }

}



// all this stuff not working yet
void MainWindow::shiftPattern(int shiftAmount) {
    QGroupBox *tempBox = groupBoxes[0];
    for (int i = 7; i > 0; --i) {
        groupBoxes[(i+1) % 8] = groupBoxes[i];
    }
    groupBoxes[1] = tempBox;
    updateLayout();
}

void MainWindow::updateLayout() {
    // Example: If using a layout manager
    for (int i = 0; i < 8; ++i) {
        QList<QDial *> dials = groupBoxes[i]->findChildren<QDial *>();
        for (QDial *dial : dials) {
            dial->update();
        }
    }
}