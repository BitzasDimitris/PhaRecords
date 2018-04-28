#ifndef CHARTVIEWER_H
#define CHARTVIEWER_H

#include <QMainWindow>
#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <QBarSeries>
#include <QStackedBarSeries>
#include <QBarCategoryAxis>
#include <QBarSet>
#include <QPieSeries>
#include <QPieSlice>
#include <QDateTimeAxis>
#include <QValueAxis>
#include <QLocale>
#include "record.h"
#include "chart.h"
#include "collection.h"

QT_CHARTS_USE_NAMESPACE
namespace Ui {
class ChartViewer;
}

class ChartViewer : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChartViewer(int index=0,QWidget *parent = 0);
    ~ChartViewer();

private slots:
    void on_perComboBox_currentIndexChanged(int index);

    void on_fromDate_userDateChanged(const QDate &date);

    void on_toDate_userDateChanged(const QDate &date);

private:

    void setInitialDates();

    std::vector<Collection> getDatasets();

    void createChart();

    void clearChart();

    void createLineChart(std::vector<Collection> collections);
    void createBarChart(std::vector<Collection> collections);
    void createStackedBarChart(std::vector<Collection> collections);
    void createPieChart(std::vector<Collection> collections);

    void blockDateSignals(bool state);


    void fromP_M_P_Y();
    void fromO_M_P_Y();
    void fromP_M_O_Y();
    void fromP_Y();

    void toP_M_P_Y();
    void toO_M_P_Y();
    void toP_M_O_Y();
    void toP_Y();

    QChartView* chartView;
    QChart* mainChart;

    QLocale locale=QLocale::Greek;

    Ui::ChartViewer *ui;
    int chartIndex;
    int dateTypeIndex=0;
    int minimumYear;
    int minimumMonth;
    int maximumYear;
    int maximumMonth;
};

#endif // CHARTVIEWER_H
