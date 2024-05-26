#include "whitenoisewindow.h"
#include "ui_whitenoisewindow.h"

WhiteNoiseWindow::WhiteNoiseWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WhiteNoiseWindow)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint | Qt::SubWindow);

    QVBoxLayout* layout = new QVBoxLayout(this);
    buttonGroup = new QButtonGroup(this);
    QRadioButton* radioBtns[8];
    QString names[8] = {"峡谷听雨", "惬意竹棚", "古镇滴雨", "帐篷录雨", "松林小雪", "漓江流水", "泉水叮当", "城市喧嚣"};
    for (int i = 0; i < 8; ++i) {
        radioBtns[i] = new QRadioButton(names[i]);
        buttonGroup->addButton(radioBtns[i], i);
        layout->addWidget(radioBtns[i]);
        connect(radioBtns[i], SIGNAL(clicked(bool)), this, SLOT(selectedChanged()));
    }
    // radioBtns[0]->setChecked(true);
    buttonGroup->setExclusive(true);
    this->setLayout(layout);
    player = new QMediaPlayer();
    audioOutput = new QAudioOutput(this); // chooses the default audio routing
    player->setAudioOutput(audioOutput);

}

WhiteNoiseWindow::~WhiteNoiseWindow()
{
    delete ui;
}

void WhiteNoiseWindow::selectedChanged() {
    int id = buttonGroup->checkedId();
    qDebug() << QString("play music id: %1").arg(id);
    qDebug() << QUrl(QString("qrc:/audio/%1.mp3").arg(id));
    player->setSource(QUrl(QString("qrc:/audio/audio/%1.mp3").arg(id)));
    qDebug() << player->source();
    // player->setMedia(QUrl(QString(":/res/audio/%1.mp3").arg(id)));
    player->setLoops(QMediaPlayer::Infinite);
    player->play();
    qDebug() << player->mediaStatus();
}
