#include "whitenoisewindow.h"
#include "ui_whitenoisewindow.h"

WhiteNoiseWindow::WhiteNoiseWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WhiteNoiseWindow)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::Popup);
    this->setStyleSheet("QWidget#WhiteNoiseWindow {\n	border-radius: 5px;\n	font: 12pt 方正小标宋;\n}");

    QVBoxLayout* layout = new QVBoxLayout(this);
    buttonGroup = new QButtonGroup(this);
    QRadioButton* radioBtns[8];
    QString names[8] = {"峡谷听雨", "惬意竹棚", "古镇滴雨", "帐篷录雨", "松林小雪", "漓江流水", "泉水叮当", "城市喧嚣"};
    for (int i = 0; i < 8; ++i) {
        radioBtns[i] = new QRadioButton(names[i]);
        buttonGroup->addButton(radioBtns[i], i);
        layout->addWidget(radioBtns[i]);
        connect(radioBtns[i], SIGNAL(clicked(bool)), this, SLOT(selectChanged()));
    }
    radioBtns[0]->setChecked(true);
    buttonGroup->setExclusive(true);

    playBtn = new QPushButton();
    playBtn->setIcon(QIcon::fromTheme("media-playback-start"));
    connect(playBtn, SIGNAL(clicked(bool)), this, SLOT(playMusic()));
    playBtn->setStyleSheet("QPushButton {\n	border-radius: 5px; \n	background-color: #c4dae2; \n	border-style: none;\n	color: #333333;\n}\nQPushButton:hover{\n    background-color: #9cb2c7;\n}\nQPushButton:pressed{\n    background-color: #e9edee;\n}");
    layout->addWidget(playBtn);
    this->setLayout(layout);
    player = new QMediaPlayer();
    audioOutput = new QAudioOutput(this); // chooses the default audio routing
    player->setAudioOutput(audioOutput);

    isPlaying = false;
}

WhiteNoiseWindow::~WhiteNoiseWindow()
{
    qDebug() << "white noise window distructed";
    delete player;
    delete audioOutput;
    delete buttonGroup;
    delete ui;
}

void WhiteNoiseWindow::playMusic() {
    if (isPlaying) {
        playBtn->setIcon(QIcon::fromTheme("media-playback-start"));
        player->stop();
        isPlaying = false;
    }
    else {
        playBtn->setIcon(QIcon::fromTheme("media-playback-pause"));

        int id = buttonGroup->checkedId();
        player->setSource(QUrl(QString("qrc:/audio/audio/%1.mp3").arg(id)));
        qDebug() << player->source();
        player->setLoops(QMediaPlayer::Infinite);
        player->play();
        qDebug() << player->mediaStatus();
        isPlaying = true;
    }
}

void WhiteNoiseWindow::selectChanged() {
    qDebug() << "select changed";
    if (isPlaying) {
        isPlaying = false;
        playMusic();
    }
}
