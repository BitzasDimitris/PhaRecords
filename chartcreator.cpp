#include "chartcreator.h"
#include "ui_chartcreator.h"

ChartCreator::ChartCreator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChartCreator)
{
    ui->setupUi(this);
    populateLabels();
    exampleChart=new QChart();
    populateThemeBox();

    exampleChart->setTheme((QChart::ChartTheme)theme);
    exampleChart->setAnimationOptions(QChart::SeriesAnimations);
    chartView=new QChartView();
    chartView->setRenderHint(QPainter::Antialiasing);
    SetupLineChart();

}

ChartCreator::~ChartCreator()
{
    delete ui;
}

void ChartCreator::SetupLineChart(){
    QLineSeries *series = new QLineSeries();
    *series << QPointF(1, 5) << QPointF(3, 7) << QPointF(7, 6) << QPointF(9, 7) << QPointF(12, 6)
                 << QPointF(16, 7) << QPointF(18, 5);
    if(exampleChart->series().size()>0){
        exampleChart->removeAllSeries();
        exampleChart->removeAxis(exampleChart->axisX());
        exampleChart->removeAxis(exampleChart->axisY());
    }
    exampleChart->addSeries(series);
    exampleChart->setTitle("Γραμμή");
    exampleChart->createDefaultAxes();
    exampleChart->axisX()->setRange(0, 20);
    exampleChart->axisY()->setRange(0, 10);
    chartView->setChart(exampleChart);

    ui->ChartContainer->layout()->addWidget(chartView);
}


void ChartCreator::SetupBarChart(){
    std::vector<QBarSet*> sets=std::vector<QBarSet*>();
    QBarSeries *series = new QBarSeries();
    for(int i=0;i<Record::EntriesNumber;i++){
        sets.push_back(new QBarSet(Record::EntriesLabels.at(i)));
        for(int j=0;j<12;j++){
            *(sets.at(i))<<i+j+qrand()%10;
        }
        series->append(sets.at(i));
    }

    if(exampleChart->series().size()>0){
        exampleChart->removeAllSeries();
        exampleChart->removeAxis(exampleChart->axisX());
        exampleChart->removeAxis(exampleChart->axisY());
    }
    exampleChart->addSeries(series);
    exampleChart->setTitle("Μπάρες");

    QStringList categories;
    categories << "Ιανουάριος" << "Φεβρουάριος" << "Μάρτιος" << "Απρίλιος" << "Μάιος" << "Ιούνιος"<<
                  "Ιούλιος"<<"Αύγουστος"<<"Σεπτέμβριος"<<"Οκτώβριος"<<"Νοέμβριος"<<"Δεκέμβριος";
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    exampleChart->createDefaultAxes();
    exampleChart->setAxisX(axis, series);
    exampleChart->legend()->setVisible(true);
    exampleChart->legend()->setAlignment(Qt::AlignBottom);
    chartView->setChart(exampleChart);
}

void ChartCreator::SetupStackedBarChart(){
    std::vector<QBarSet*> sets=std::vector<QBarSet*>();
    QStackedBarSeries *series = new QStackedBarSeries();
    for(int i=0;i<Record::EntriesNumber;i++){
        sets.push_back(new QBarSet(Record::EntriesLabels.at(i)));
        for(int j=0;j<12;j++){
            *(sets.at(i))<<i+j+qrand()%10;
        }
        series->append(sets.at(i));
    }
    if(exampleChart->series().size()>0){
        exampleChart->removeAllSeries();
        exampleChart->removeAxis(exampleChart->axisX());
        exampleChart->removeAxis(exampleChart->axisY());
    }

    exampleChart->addSeries(series);
    exampleChart->setTitle("Στοίβα");

    QStringList categories;
    categories << "Ιανουάριος" << "Φεβρουάριος" << "Μάρτιος" << "Απρίλιος" << "Μάιος" << "Ιούνιος"<<
                  "Ιούλιος"<<"Αύγουστος"<<"Σεπτέμβριος"<<"Οκτώβριος"<<"Νοέμβριος"<<"Δεκέμβριος";
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    exampleChart->createDefaultAxes();
    exampleChart->setAxisX(axis, series);
    exampleChart->legend()->setVisible(true);
    exampleChart->legend()->setAlignment(Qt::AlignBottom);
}

void ChartCreator::SetupPieChart(){
    QPieSeries *series = new QPieSeries();
    series->append("Ιανουάριος", 1);
    series->append("Φεβρουάριος", 2);
    series->append("Μάρτιος", 3);
    series->append("Απρίλιος", 4);
    series->append("Μάιος", 5);

    for(int i=0;i<series->slices().size();i++){
        QPieSlice *slice = series->slices().at(i);
        slice->setLabelVisible();
        if(i==1){
            slice->setExploded();
        }
    }


    if(exampleChart->series().size()>0){
        exampleChart->removeAllSeries();
        exampleChart->removeAxis(exampleChart->axisX());
        exampleChart->removeAxis(exampleChart->axisY());
    }

    exampleChart->addSeries(series);
    exampleChart->setTitle("Πίτα");
    exampleChart->legend()->hide();

    chartView->setChart(exampleChart);
}



void ChartCreator::populateThemeBox(){
    ui->chartTheme->addItem("Light", QChart::ChartThemeLight);
    ui->chartTheme->addItem("Blue Cerulean", QChart::ChartThemeBlueCerulean);
    ui->chartTheme->addItem("Dark", QChart::ChartThemeDark);
    ui->chartTheme->addItem("Brown Sand", QChart::ChartThemeBrownSand);
    ui->chartTheme->addItem("Blue NCS", QChart::ChartThemeBlueNcs);
    ui->chartTheme->addItem("High Contrast", QChart::ChartThemeHighContrast);
    ui->chartTheme->addItem("Blue Icy", QChart::ChartThemeBlueIcy);
    ui->chartTheme->addItem("Qt", QChart::ChartThemeQt);
}

void ChartCreator::on_chartTheme_currentIndexChanged(int index)
{
    switch(index){
    case 0:
        theme=QChart::ChartThemeLight;
        break;
    case 1:
        theme=QChart::ChartThemeBlueCerulean;
        break;
    case 2:
        theme=QChart::ChartThemeDark;
        break;
    case 3:
        theme=QChart::ChartThemeBrownSand;
        break;
    case 4:
        theme=QChart::ChartThemeBlueNcs;
        break;
    case 5:
        theme=QChart::ChartThemeHighContrast;
        break;
    case 6:
        theme=QChart::ChartThemeBlueIcy;
        break;
    case 7:
        theme=QChart::ChartThemeQt;
        break;
    }
    exampleChart->setTheme((QChart::ChartTheme)theme);
}

void ChartCreator::on_chartType_currentIndexChanged(int index)
{
    switch(index){
    case 0:
        SetupLineChart();
        break;
    case 1:
        SetupBarChart();
        break;
    case 2:
        SetupStackedBarChart();
        break;
    case 3:
        SetupPieChart();
        break;
    default:
        SetupLineChart();
        break;
    }
}

void ChartCreator::populateLabels(){
    QSignalMapper *signalMapper=new QSignalMapper();
    connect(signalMapper,SIGNAL(mapped(int)),this,SLOT(on_labelButton_clicked(int)));
    for(int i=0;i<Record::EntriesNumber;i++){
        QPushButton *labelbutton=new QPushButton(Record::EntriesLabels.at(i));
        signalMapper->setMapping(labelbutton,i);
        connect(labelbutton, SIGNAL(clicked()), signalMapper, SLOT(map()));
        ui->labelsContainer->addWidget(labelbutton);
    }
}

void ChartCreator::on_labelButton_clicked(int index){
    QString exp=ui->expression->toPlainText();
    ui->expression->setText(exp+Record::EntriesLabels.at(index));
}

void ChartCreator::on_allButton_clicked(){
    QString exp=ui->expression->toPlainText();
    if(exp.compare("")!=0&&!exp.endsWith(",")){
        exp+=",";
    }
    for(int i=0;i<Record::EntriesNumber;i++){
        exp+=Record::EntriesLabels.at(i);
        if(i<Record::EntriesNumber-1){
            exp+=",";
        }
    }
    ui->expression->setText(exp);
}

void ChartCreator::on_delimiterButton_clicked(){
    QString exp=ui->expression->toPlainText();
    if(exp.endsWith(",")){
        return;
    }
    ui->expression->setText(exp+",");
}
