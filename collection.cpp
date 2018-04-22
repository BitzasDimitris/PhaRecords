#include "collection.h"

Collection::Collection()
{
    dates=std::vector<QDate>();
    values=std::vector<float>();
}

void Collection::add(QDate date,float value){
    dates.push_back(date);
    values.push_back(value);
}

QDateTime Collection::getDateTime(int i){
    QDateTime dateTime(dates.at(i));
    return dateTime;
}

long Collection::getMillis(int i){
    return getDateTime(i).toMSecsSinceEpoch();
}
