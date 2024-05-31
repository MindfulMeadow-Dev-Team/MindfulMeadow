#ifndef ODBEXCEL_H
#define ODBEXCEL_H

#include <QMainWindow>

namespace Ui {
class odbexcel;
}

class odbexcel : public QMainWindow
{
    Q_OBJECT

public:
    explicit odbexcel(QWidget *parent = nullptr);
    ~odbexcel();

private:
    Ui::odbexcel *ui;
};

#endif // ODBEXCEL_H
