#ifndef WHITENOISEWINDOW_H
#define WHITENOISEWINDOW_H

#include <QWidget>
#include <QLayout>
#include <QRadioButton>
#include <QButtonGroup>
#include <QtMultimedia>

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
    QMediaPlayer* player;
    QAudioOutput* audioOutput;

private slots:
    void selectedChanged();

// signals:
//     void playMusic(int);
};

#endif // WHITENOISEWINDOW_H
