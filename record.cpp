#include "record.h"

int Record::EntriesNumber=0;
std::vector<QString> Record::EntriesLabels=std::vector<QString>();
std::vector<bool> Record::EntriesType=std::vector<bool>();
std::vector<bool> Record::EntriesNegative=std::vector<bool>();
std::vector<Record> Record::Records=std::vector<Record>();

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

Record Record::GetRecord(int Year, int Month,int *result){
    for(int i=0;i<Records.size();i++){
        if(Year==Records.at(i).Year&&Month==Records.at(i).Month){
            result=0;
            return Records.at(i);
        }
    }
    *result=-1;
    return Record(Year,Month);
}

bool Record::SetRecord(int Year, int Month, std::vector<float> entries){
    for(int i=0;i<Records.size();i++){
        if(Year==Records.at(i).Year&&Month==Records.at(i).Month){
            Records.at(i).entries=entries;
            return true;
        }
    }
    return false;
}

QString Record::getDate(){
    return QString::number(Month).append("/").append(QString::number(Year));
}
