#include "record.h"

int Record::EntriesNumber=0;
std::vector<QString> Record::EntriesLabels=std::vector<QString>();
std::vector<int> Record::EntriesType=std::vector<int>();
std::vector<bool> Record::EntriesNegative=std::vector<bool>();

Record::Record(int y,int m)
{
    Year=y;
    Month=m;
    entries=std::vector<float>(EntriesNumber);
}


Record::Record(int y,int m,std::vector<float> e)
{
    Year=y;
    Month=m;
    if(e.size()==EntriesNumber){
        entries=e;
    }

}

int Record::getMonth(){
    return Month;
}

int Record::getYear(){
    return Year;
}

QString Record::getDate(){
    return QString::number(Month).append("/").append(QString::number(Year));
}
