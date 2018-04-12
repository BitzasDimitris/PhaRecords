#include "chart.h"

std::vector<Chart> Chart::Charts=std::vector<Chart>();
QString Chart::ChartFile="Charts.charts";
QString Chart::defaultIconPath="statistics_icon.png";
bool Chart::loaded=false;

Chart::Chart()
{

}

Chart::Chart(QString name,int type, QString expression, int theme,QString iconPath){
    this->name=name;
    this->type=type;
    this->expression=expression;
    this->theme=theme;
    this->iconPath=iconPath;
}

void Chart::AddChart(QString name,int type,QString expression,int theme,QString iconPath){
    AddChart(Chart(name,type,expression,theme,iconPath));
}

void Chart::AddChart(Chart c){
    Charts.push_back(c);
}

int Chart::SaveCharts(){
    if(Charts.size()==0){
        return NO_CHARTS;
    }
    QFile chartFile(ChartFile);
    if(!chartFile.open(QIODevice::WriteOnly)){
        qDebug() << "Could not open " << ChartFile;
        return FILE_NOT_OPENED;
    }
    QDataStream out(&chartFile);

    for(int i=0;i<Charts.size();i++){
        out<<Charts.at(i);
    }

    chartFile.flush();
    chartFile.close();
    return OK;
}

int Chart::LoadCharts(){
    if(loaded)
        return OK;
    loaded=true;
    QFile chartFile(ChartFile);
    if(!chartFile.open(QIODevice::ReadOnly)){
        qDebug() << "Could not open " << ChartFile;
        return FILE_NOT_OPENED;
    }
    QDataStream in(&chartFile);

    while(!in.atEnd()){
        Chart currentChart;
        in>>currentChart;
        Charts.push_back(currentChart);
    }
    chartFile.close();
    return OK;
}

bool Chart::ChartFileExists(){
    return QFile(ChartFile).exists();
}

QDataStream &operator<<(QDataStream &out, Chart &chart)
{
    out << chart.getName() << quint32(chart.getType())<< chart.getExpression()
        << quint32(chart.getTheme())<<chart.getIconPath();
    return out;
}

QDataStream &operator>>(QDataStream &in, Chart &chart)
{
    QString name;
    quint32 type;
    QString expression;
    quint32 theme;
    QString iconPath;
    in >> name >> type >> expression >> theme >> iconPath;
    chart = Chart(name,type, expression, theme,iconPath);
    return in;
}
