#ifndef MATTER_H
#define MATTER_H

#include <QDate>
#include <QDateTime>
#include <QString>

class Matter
{
    QString name;
    QString description;
    QDate date;
    QString tag;
    bool isDone;
    bool setDue;
    QTime dueTime;
    // QImage image;
    // QTime time;
public:
    Matter(QString _name = "",
           QString _description = "",
           QDate _date = QDate::currentDate(),
           QString tag = "",
           bool isDone = false,
           bool setDue = false,
           QTime dueTime = QTime(23, 59, 59));

    QString getName() const;
    QString getDescription() const;
    bool getState() const;
    bool getSetDue() const;
    QTime getDueTime() const;
    QDate getDate() const;

    void changeName(QString newName);
    void changeDescription(QString newDes);
    void changeDate(QDate newDate);
    void changeTag(QString newTag);
    void changeState(bool state);
    void changeDueTime(QTime newTime);
    void changeSetDue(bool newSetDue);

    friend class MatterHandler;

};

#endif // MATTER_H
