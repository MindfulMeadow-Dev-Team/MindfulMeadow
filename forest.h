#ifndef FOREST_H
#define FOREST_H

#include <QWidget>

namespace Ui {
class forest;
}

class forest : public QWidget
{
    Q_OBJECT

public:
    explicit forest(QWidget *parent = nullptr);
    ~forest();

private:
    Ui::forest *ui;
};

#endif // FOREST_H
