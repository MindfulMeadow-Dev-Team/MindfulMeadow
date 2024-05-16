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
    explicit MatterBox(Matter* matter, MatterHandler* handler, QWidget *parent = nullptr);
    ~MatterBox();
    Matter* matter;
    MatterHandler* handler;

private:
    Ui::MatterBox *ui;
};

#endif // MATTERBOX_H
