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
    // QImage image;
    // QTime time;
public:
    // TODO: change default values.
    Matter(QString _name = "",
           QString _description = "",
           QDate _date = QDate::currentDate(),
           QString tag = "");

    QString getName() const;
    QString getDescription() const;
    void changeName(QString newName);
    void changeDescription(QString newDes);
    void changeDate(QDate newDate);
    void changeTag(QString newTag);

    friend class MatterHandler;

};

#endif // MATTER_H
