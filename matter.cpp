#include "matter.h"

Matter::Matter(QString _name,
               QString _description,
               QDate _date,
               QString tag,
               bool isDone,
               bool setDue,
               QTime dueTime)
            : name{_name},
            description{_description},
            date{_date},
            tag{tag},
            isDone{isDone},
            dueTime{dueTime},
            setDue{setDue}
            { }

QString Matter::getName() const {
    return name;
}

QString Matter::getDescription() const {
    return description;
}

QTime Matter::getDueTime() const {
    return dueTime;
}

QDate Matter::getDate() const {
    return date;
}

bool Matter::getSetDue() const {
    return setDue;
}

void Matter::changeName(QString newName) {
    name = newName;
}

void Matter::changeDescription(QString newDes) {
    description = newDes;
}

void Matter::changeDate(QDate newDate) {
    date = newDate;
}

void Matter::changeTag(QString newTag) {
    tag = newTag;
}

void Matter::changeState(bool state) {
    isDone = state;
}

bool Matter::getState() const {
    return isDone;
}

void Matter::changeDueTime(QTime newTime) {
    if (setDue == false) {
        setDue = true;
    }
    dueTime = newTime;
}

void Matter::changeSetDue(bool newSetDue) {
    setDue = newSetDue;
}
