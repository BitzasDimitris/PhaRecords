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

float Record::evaluate(QString expression){
    for(int i=0;i<EntriesNumber;i++){
        expression.replace(EntriesLabels.at(i),QString::number(entries.at(i)));
    }
    QScriptEngine engine;
    return engine.evaluate(expression).toNumber();
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

void Record::getMinMaxYearMonth(int &minYear,int &minMonth,int &maxYear,int &maxMonth){
    if(Records.size()==0){
        minYear=0;
        minMonth=0;
        maxYear=0;
        maxMonth=0;
        return;
    }
    minYear=maxYear=Records.at(0).Year;
    minMonth=maxMonth=Records.at(0).Month;
    for(int i=1;i<Records.size();i++){
        int Year=Records.at(i).Year;
        int Month=Records.at(i).Month;
        if(minYear>Year){
            minYear=Year;
            minMonth=Month;
        }
        if(maxYear<Year){
            maxYear=Year;
            maxMonth=Month;
        }
        if(minYear==Year&&minMonth>Month){
            minMonth=Month;
        }
        if(maxYear==Year&&maxMonth<Month){
            maxMonth=Month;
        }
    }

}
