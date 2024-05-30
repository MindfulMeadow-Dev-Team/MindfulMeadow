#ifndef clickablelable_H
#define clickablelable_H

#include <QLabel>
#include <QWidget>
#include <Qt>
#include <QDateTime>

class clickablelable : public QLabel {
    Q_OBJECT

public:
    explicit clickablelable(QWidget* parent = nullptr);
    ~clickablelable() = default;

    void setPlantDate(const QDateTime& date);

signals:
    void clicked(const QDateTime& date);

protected:
    void mousePressEvent(QMouseEvent* event);

private:
    QDateTime plantDate;
};

#endif // clickablelable_H
