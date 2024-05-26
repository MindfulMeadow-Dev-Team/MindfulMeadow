#ifndef WHITENOISEWINDOW_H
#define WHITENOISEWINDOW_H

#include <QWidget>
#include <QLayout>
#include <QRadioButton>
#include <QButtonGroup>
#include <QPushButton>
#include <QtMultimedia>
#include <QGraphicsDropShadowEffect>

namespace Ui {
class WhiteNoiseWindow;
}

class WhiteNoiseWindow : public QWidget
{
    Q_OBJECT

public:
    explicit WhiteNoiseWindow(QWidget *parent = nullptr);
    ~WhiteNoiseWindow();

private:
    Ui::WhiteNoiseWindow *ui;

    QButtonGroup* buttonGroup;
    QPushButton* playBtn;
    QMediaPlayer* player;
    QAudioOutput* audioOutput;
    bool isPlaying;

private slots:
    void playMusic();
    void selectChanged();
};

#endif // WHITENOISEWINDOW_H
