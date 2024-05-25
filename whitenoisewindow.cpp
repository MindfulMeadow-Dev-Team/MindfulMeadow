#include "whitenoisewindow.h"
#include "ui_whitenoisewindow.h"

WhiteNoiseWindow::WhiteNoiseWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WhiteNoiseWindow)
{
    ui->setupUi(this);

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
    radioBtns[0]->setChecked(true);
    buttonGroup->setExclusive(true);
    this->setLayout(layout);
}

WhiteNoiseWindow::~WhiteNoiseWindow()
{
    delete ui;
}

void WhiteNoiseWindow::selectedChanged() {
    emit playMusic(buttonGroup->checkedId());
}
