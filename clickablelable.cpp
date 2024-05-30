#include "clickablelable.h"

clickablelable::clickablelable(QWidget* parent)
    : QLabel(parent)
{
}

void clickablelable::setPlantDate(const QDateTime& date) {
    plantDate = date;
}

void clickablelable::mousePressEvent(QMouseEvent* event) {
    emit clicked(plantDate);
}
