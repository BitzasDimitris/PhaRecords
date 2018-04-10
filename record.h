#ifndef RECORD_H
#define RECORD_H

#include <vector>
#include <QString>

class Record
{
public:
    static int EntriesNumber;
    static std::vector<QString> EntriesLabels;
    static std::vector<bool> EntriesType;
    static std::vector<bool> EntriesNegative;
    static std::vector<Record> Records;
    Record(int y,int m);
    Record(int y,int m,std::vector<float> e);

    static Record GetRecord(int Year,int Month,int *result);
    static bool SetRecord(int Year,int Month,std::vector<float> entries);
    int Year,Month;
    std::vector<float> entries;
    QString getDate();

private:

};

#endif // RECORD_H
