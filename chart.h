#ifndef CHART_H
#define CHART_H

#include <QString>
#include <QDataStream>
#include <vector>
#include <QFile>
#include <QDebug>

class Chart
{
public:
    const static int OK=0;
    const static int FILE_NOT_FOUND=1;
    const static int FILE_NOT_OPENED=2;
    const static int FILE_NOT_PARCABLE=3;
    const static int NO_CHARTS=4;


    static std::vector<Chart> Charts;

    Chart();
    Chart(int type,QString expression,int theme=0,QString iconPath=defaultIconPath);
    int getType(){return type;}
    QString getExpression(){return expression;}
    int getTheme(){return theme;}
    QString getIconPath(){return iconPath;}

    static void AddChart(int type,QString expression,int theme=0,QString iconPath=defaultIconPath);
    static void AddChart(Chart c);
    static int LoadCharts();
    static int SaveCharts();
    static bool ChartFileExists();


private:

    int type;
    QString expression;
    int theme;
    QString iconPath;


    static QString ChartFile;
    static QString defaultIconPath;

};

QDataStream &operator<<(QDataStream &out, Chart &chart);
QDataStream &operator>>(QDataStream &in, Chart &chart);

#endif // CHART_H
