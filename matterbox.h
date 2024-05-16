#ifndef MATTERBOX_H
#define MATTERBOX_H

#include <QWidget>
#include "matterhandler.h"

namespace Ui {
class MatterBox;
}

class MatterBox : public QWidget
{
    Q_OBJECT

public:
    explicit MatterBox(Matter matter, int matterId, MatterHandler* handler, QWidget *parent = nullptr);
    ~MatterBox();

private slots:
    void on_checkBox_stateChanged(int state);

    void on_checkBox_clicked();

private:
    Ui::MatterBox *ui;
    Matter matter;
    int matterId;
    MatterHandler* handler;

};

#endif // MATTERBOX_H
