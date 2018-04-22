#ifndef COLLECTION_H
#define COLLECTION_H
#include <QDate>
#include <QDateTime>
#include <QTime>
#include <vector>

class Collection
{
public:
    Collection();
    void add(QDate date,float value);
    QDateTime getDateTime(int i);
    long getMillis(int i);

    std::vector<QDate> dates;
    std::vector<float> values;
};

#endif // COLLECTION_H
