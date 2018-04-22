#ifndef CHART_H
#define CHART_H

#include <QString>
#include <QDataStream>
#include <vector>
#include <QFile>
#include <QStringList>
#include <QDate>
#include <QDebug>
#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <QBarSeries>
#include <QStackedBarSeries>
#include <QBarCategoryAxis>
#include <QBarSet>
#include <QPieSeries>
#include <QPieSlice>
#include "record.h"
#include "collection.h"

QT_CHARTS_USE_NAMESPACE

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
    Chart(QString name,int type,QString expression,int theme=0,QString iconPath=defaultIconPath);
    int getType(){return type;}
    QString getExpression(){return expression;}
    int getTheme(){return theme;}
    QString getIconPath(){return iconPath;}
    QString getName(){return name;}

    bool validateExpression();
    std::vector<Collection> evaluateExpression(QDate from,QDate to);

    static void AddChart(QString name,int type,QString expression,int theme=0,QString iconPath=defaultIconPath);
    static void AddChart(Chart c);
    static int LoadCharts();
    static int SaveCharts();
    static bool ChartFileExists();


private:


    int type;
    QString expression;
    int theme;
    QString iconPath;
    QString name;

    static bool loaded;
    static QString ChartFile;
    static QString defaultIconPath;

};

QDataStream &operator<<(QDataStream &out, Chart &chart);
QDataStream &operator>>(QDataStream &in, Chart &chart);

#endif // CHART_H
