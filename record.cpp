#include "record.h"

int Record::EntriesNumber=0;
std::vector<QString> Record::EntriesLabels=std::vector<QString>();
std::vector<bool> Record::EntriesType=std::vector<bool>();
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


QString Record::getDate(){
    return QString::number(Month).append("/").append(QString::number(Year));
}
