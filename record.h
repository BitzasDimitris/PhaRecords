#ifndef RECORD_H
#define RECORD_H

#include <vector>
#include <QString>

class Record
{
public:
    static int EntriesNumber;
    static std::vector<QString> EntriesLabels;
    static std::vector<int> EntriesType;
    static std::vector<bool> EntriesNegative;
    Record(int y,int m);
    Record(int y,int m,std::vector<float> e);

    int getMonth();
    int getYear();
    QString getDate();

private:
    int Year,Month;
    std::vector<float> entries;
};

#endif // RECORD_H
