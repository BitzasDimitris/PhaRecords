#ifndef CHARTSELECTOR_H
#define CHARTSELECTOR_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QPushButton>
#include <QSignalMapper>
#include <QTimer>
#include <vector>
#include <QDebug>
#include "chart.h"
#include "chartcreator.h"

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
    void ButtonResize();
    void on_addButton_Clicked();
    void on_charButton_Clicked(int i);
protected:
    void resizeEvent(QResizeEvent* event)override;
    void closeEvent(QCloseEvent *event)override;
private:
    void LoadChartButtons();
    void ResizeButtonsImages();

    QSignalMapper* signalMapper;
    QPushButton* addButton;
    std::vector<QPushButton*> chartButtons;
    Ui::ChartSelector *ui;


};

#endif // CHARTSELECTOR_H
