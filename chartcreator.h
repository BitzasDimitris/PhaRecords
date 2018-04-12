#ifndef CHARTCREATOR_H
#define CHARTCREATOR_H

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
#include <QSignalMapper>
#include "record.h"
#include "chart.h"

QT_CHARTS_USE_NAMESPACE
namespace Ui {
class ChartCreator;
}

class ChartCreator : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChartCreator(QWidget *parent = 0);
    ~ChartCreator();

signals:
    void updateChartButtons();
private slots:
    void on_labelButton_clicked(int index);

    void on_chartTheme_currentIndexChanged(int index);

    void on_chartType_currentIndexChanged(int index);

    void on_allButton_clicked();

    void on_delimiterButton_clicked();

    void on_divideButton_clicked();

    void on_multiplyButton_clicked();

    void on_subtractButton_clicked();

    void on_addButton_clicked();

    void on_clearButton_clicked();

    void on_pushButton_clicked();

    void on_CancelButton_clicked();

    void on_ConfirmButton_clicked();

    void on_iconChooseButton_clicked();

private:

    void populateThemeBox();
    void populateLabels();
    void SetupLineChart();
    void SetupBarChart();
    void SetupStackedBarChart();
    void SetupPieChart();


    Ui::ChartCreator *ui;
    QChartView* chartView;
    QChart* exampleChart;
    int currentTheme=QChart::ChartThemeLight;
};

#endif // CHARTCREATOR_H
