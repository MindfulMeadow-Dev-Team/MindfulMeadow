#include "matter.h"

Matter::Matter(QString _name,
               QString _description,
               QDate _date,
               QString tag)
            : name{_name},
            description{_description},
            date{_date},
            tag{tag}
            { }

QString Matter::getName() const {
    return name;
}

QString Matter::getDescription() const {
    return description;
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
