#ifndef CHARTSELECTOR_H
#define CHARTSELECTOR_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QPushButton>
#include <QToolButton>
#include <QSignalMapper>
#include <QTimer>
#include <vector>
#include <QDebug>
#include "chart.h"
#include "chartcreator.h"
#include "chartviewer.h"

namespace Ui {
class ChartSelector;
}

class ChartSelector : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChartSelector(QWidget *parent = 0);
    ~ChartSelector();

signals:
    void MainWindowReSurface();
public slots:
    void updateChartbuttons();
private slots:
    void on_addButton_Clicked();
    void on_chartButton_Clicked(int i);
protected:
    void closeEvent(QCloseEvent *event)override;
private:
    void LoadChartButtons();

    QSignalMapper* signalMapper;
    QPushButton* addButton;
    std::vector<QToolButton*> chartButtons;
    Ui::ChartSelector *ui;
};

#endif // CHARTSELECTOR_H
