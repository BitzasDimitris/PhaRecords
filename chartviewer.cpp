#include "chartviewer.h"
#include "ui_chartviewer.h"

ChartViewer::ChartViewer(int index,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChartViewer)
{
    ui->setupUi(this);
    blockDateSignals(true);
    chartIndex=index;
    Record::getMinMaxYearMonth(minimumYear,minimumMonth,maximumYear,maximumMonth);
    ui->fromDate->setMinimumDate(QDate(minimumYear,minimumMonth,1));
    ui->fromDate->setMaximumDate(QDate(maximumYear,maximumMonth,1));
    ui->toDate->setMinimumDate(QDate(minimumYear,minimumMonth,1));
    ui->toDate->setMaximumDate(QDate(maximumYear,maximumMonth,1));
    setInitialDates();
    blockDateSignals(false);
    // Setup initial chart objects and settings.
    mainChart=new QChart();
    mainChart->setTheme((QChart::ChartTheme)Chart::Charts.at(chartIndex).getTheme());
    mainChart->setAnimationOptions(QChart::SeriesAnimations);
    chartView= new QChartView();
    chartView->setRenderHint(QPainter::Antialiasing);
    createChart();
}
ChartViewer::~ChartViewer()
{
    delete ui;
}


void ChartViewer::setInitialDates(){
    blockDateSignals(true);
    ui->fromDate->setDate(QDate(maximumYear,1,1));
    ui->toDate->setDate(QDate(maximumYear,maximumMonth,1));
    blockDateSignals(false);
}


void ChartViewer::blockDateSignals(bool state){
    ui->fromDate->blockSignals(state);
    ui->toDate->blockSignals(state);
}

void ChartViewer::on_perComboBox_currentIndexChanged(int index)
{
    if(dateTypeIndex==index){
        return;
    }
    dateTypeIndex=index;
    createChart();
}

std::vector<Collection> ChartViewer::getDatasets(){
    QDate from,to;
    from=ui->fromDate->date();
    to=ui->toDate->date();
    return Chart::Charts.at(chartIndex).evaluateExpression(from,to);
}


void ChartViewer::createChart(){
    switch(Chart::Charts.at(chartIndex).getType()){
    case 0:
        createLineChart(getDatasets());
        break;
    case 1:
        createBarChart(getDatasets());
        break;
    case 2:
        createStackedBarChart(getDatasets());
        break;
    case 3:
        createPieChart(getDatasets());
        break;
    default:
        createLineChart(getDatasets());
        break;
    }
}

void ChartViewer::createLineChart(std::vector<Collection> collections){
    clearChart();
    mainChart->setTitleFont(QFont("Arial",30,2,false));
    //TODO title according to datetype and AxisX
    mainChart->setTitle(Chart::Charts.at(chartIndex).getName()+" - "+locale.toString(ui->fromDate->date(),"yyyy"));
    QDateTimeAxis *axisX=new QDateTimeAxis();
    axisX->setTickCount(10);
    axisX->setFormat("MMM");
    axisX->setLabelsFont(QFont("Arial",15,0,true));
    axisX->setTitleText(("Μήνας"));
    axisX->setTitleFont(QFont("Arial",30,2,false));
    mainChart->addAxis(axisX,Qt::AlignBottom);
    QValueAxis *axisY=new QValueAxis();
    axisY->setLabelFormat("%.2f");
    axisY->setLabelsFont(QFont("Arial",15,0,true));
    axisY->setTitleText("Τιμή");
    axisY->setTitleFont(QFont("Arial",30,2,false));
    mainChart->addAxis(axisY,Qt::AlignLeft);
    mainChart->legend()->setVisible(true);
    mainChart->legend()->setFont(QFont("Arial",20,2,false));
    float minimumValue=collections.at(0).values.at(0);
    float maximumValue=minimumValue;

    for(int i=0;i<collections.size();i++){
        QLineSeries *series = new QLineSeries();
        for(int j=0;j<collections.at(i).values.size();j++){
            series->append(QPointF(QDateTime(collections.at(i).dates.at(j)).toMSecsSinceEpoch(),collections.at(i).values.at(j)));
            if(maximumValue<collections.at(i).values.at(j)){
                maximumValue=collections.at(i).values.at(j);
            }
            if(minimumValue>collections.at(i).values.at(j)){
                minimumValue=collections.at(i).values.at(j);
            }
        }
        series->setName(Chart::Charts.at(chartIndex).getExpression(i));
        mainChart->addSeries(series);
        series->attachAxis(axisX);
    }
    axisY->setRange(minimumValue,maximumValue);
    chartView->setChart(mainChart);
    ui->chartContainer->layout()->addWidget(chartView);
}


void ChartViewer::createBarChart(std::vector<Collection> collections){


    clearChart();
    QBarSeries *series=new QBarSeries();
    std::vector<QBarSet*> sets= std::vector<QBarSet*>();
    QStringList categories;
    for(int i=0;i<collections.size();i++){
        sets.push_back(new QBarSet(Chart::Charts.at(chartIndex).getExpression(i)));
        for(int j=0;j<collections.at(i).values.size();j++){
            sets.at(i)->append(collections.at(i).values.at(j));
            if(i==0){
                //TODO update according datetype
                categories.append(locale.toString(collections.at(i).dates.at(j),"MMM"));
            }
        }
        series->append(sets.at(i));
    }
    mainChart->addSeries(series);
    mainChart->setTitleFont(QFont("Arial",30,2,false));
    //TODO title according to datetype and AxisX
    mainChart->setTitle(Chart::Charts.at(chartIndex).getName()+" - "+locale.toString(ui->fromDate->date(),"yyyy"));
    //TODO update axis according to values types and ranges for each barset.
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    axisX->setLabelsFont(QFont("Arial",15,0,true));
    QValueAxis *axisY=new QValueAxis();
    axisY->setLabelFormat("%.2f");
    axisY->setLabelsFont(QFont("Arial",15,0,true));
    axisY->setTitleText("Τιμή");
    axisY->setTitleFont(QFont("Arial",30,2,false));
    series->attachAxis(axisX);
    series->attachAxis(axisY);
    mainChart->createDefaultAxes();
    mainChart->setAxisX(axisX, series);
    mainChart->setAxisY(axisY,series);
    mainChart->legend()->setVisible(true);
    mainChart->legend()->setAlignment(Qt::AlignBottom);
    mainChart->legend()->setFont(QFont("Arial",30,2,false));
    chartView->setChart(mainChart);
    ui->chartContainer->layout()->addWidget(chartView);
}

void ChartViewer::createStackedBarChart(std::vector<Collection> collections){

    clearChart();
    std::vector<QBarSet*> sets=std::vector<QBarSet*>();
    QStackedBarSeries *series = new QStackedBarSeries();
    QStringList categories;
    for(int i=0;i<collections.at(0).values.size();i++){
        sets.push_back(new QBarSet(Chart::Charts.at(chartIndex).getExpression(i)));
        for(int j=0;j<collections.size();j++){
            sets.at(i)->append(collections.at(j).values.at(i));
            if(j==0){
                //TODO update according datetype
                categories.append(locale.toString(collections.at(i).dates.at(j),"MMM"));
            }
        }
        series->append(sets.at(i));
    }
    mainChart->addSeries(series);
    mainChart->setTitleFont(QFont("Arial",30,2,false));
    //TODO title according to datetype and AxisX
    mainChart->setTitle(Chart::Charts.at(chartIndex).getName()+" - "+locale.toString(ui->fromDate->date(),"yyyy"));

    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    mainChart->createDefaultAxes();
    mainChart->setAxisX(axis,series);
    mainChart->legend()->setVisible(true);
    mainChart->legend()->setAlignment(Qt::AlignBottom);
    chartView->setChart(mainChart);
    ui->chartContainer->layout()->addWidget(chartView);
}

void ChartViewer::createPieChart(std::vector<Collection> collections){


    clearChart();
    QPieSeries *series=new QPieSeries();
    float maximumValue=collections.at(0).values.at(0);
    int maximumIndex=0;
    for(int j=0;j<collections.at(0).values.size();j++){
        if(maximumValue<=collections.at(0).values.at(j)){
            maximumValue=collections.at(0).values.at(j);
            maximumIndex=j;
        }
        //TODO update according to datetype
        series->append(locale.toString(collections.at(0).dates.at(j),"MMM"),collections.at(0).values.at(j));
    }
    series->slices().at(maximumIndex)->setExploded();
    mainChart->addSeries(series);
    mainChart->setTitleFont(QFont("Arial",30,2,false));

    mainChart->setTitle(Chart::Charts.at(chartIndex).getName()+" - "+locale.toString(ui->fromDate->date(),"yyyy"));
    chartView->setChart(mainChart);
    ui->chartContainer->layout()->addWidget(chartView);
}

void ChartViewer::clearChart(){
    if(mainChart->series().size()>0){
        mainChart->removeAllSeries();
        mainChart->removeAxis(mainChart->axisX());
        mainChart->removeAxis(mainChart->axisY());
    }
}

void ChartViewer::on_fromDate_userDateChanged(const QDate &date)
{
    blockDateSignals(true);
    switch(dateTypeIndex){
    case 0:
        fromP_M_O_Y();
        break;
    case 1:
        fromO_M_P_Y();
        break;
    case 2:
        fromP_M_P_Y();
        break;
    case 3:
        fromP_Y();
        break;
    }
    createChart();
    blockDateSignals(false);
}

void ChartViewer::on_toDate_userDateChanged(const QDate &date)
{
    blockDateSignals(true);
    switch(dateTypeIndex){
    case 0:
        toP_M_O_Y();
        break;
    case 1:
        toO_M_P_Y();
        break;
    case 2:
        toP_M_P_Y();
        break;
    case 3:
        toP_Y();
        break;
    }
    createChart();
    blockDateSignals(false);
}


void ChartViewer::fromP_M_P_Y(){
    QDate from=ui->fromDate->date();
    QDate to=ui->toDate->date();
    if(to.year()<from.year()||to.year()==from.year()&&to.month()<from.month()){
        ui->toDate->setDate(QDate(ui->fromDate->date()));
    }
}

void ChartViewer::fromO_M_P_Y(){
    QDate from=ui->fromDate->date();
    QDate to=ui->toDate->date();
    if(to.year()<from.year()){
        ui->toDate->setDate(QDate(ui->fromDate->date()));
    }
    if(to.month()!=from.month()){
        ui->toDate->setDate(QDate(to.year(),from.month(),1));
    }
}

void ChartViewer::fromP_M_O_Y(){
    QDate from=ui->fromDate->date();
    QDate to=ui->toDate->date();
    if(from.year()!=to.year()){
        ui->toDate->setDate(QDate(from.year(),to.month(),1));
    }
    to=ui->toDate->date();
    if(from.month()>to.month()){
        ui->toDate->setDate(ui->fromDate->date());
    }

}

void ChartViewer::fromP_Y(){
    QDate from=ui->fromDate->date();
    QDate to=ui->toDate->date();
    if(from.year()>to.year()){
        ui->toDate->setDate(QDate(from.year(),1,1));
    }
}

void ChartViewer::toP_M_P_Y(){
    QDate from=ui->fromDate->date();
    QDate to=ui->toDate->date();
    if(to.year()<from.year()||to.year()==from.year()&&to.month()<from.month()){
        ui->fromDate->setDate(QDate(ui->toDate->date()));
    }
}

void ChartViewer::toO_M_P_Y(){
    QDate from=ui->fromDate->date();
    QDate to=ui->toDate->date();

    if(to.year()<from.year()){
        ui->fromDate->setDate(QDate(ui->toDate->date()));
    }
    if(from.month()!=to.month()){
        ui->fromDate->setDate(QDate(from.year(),to.month(),1));
    }
}

void ChartViewer::toP_M_O_Y(){
    QDate from=ui->fromDate->date();
    QDate to=ui->toDate->date();
    if(from.year()!=to.year()){
        ui->fromDate->setDate(QDate(to.year(),from.month(),1));
    }
    from=ui->fromDate->date();
    if(from.month()>to.month()){
        ui->fromDate->setDate(ui->toDate->date());
    }

}

void ChartViewer::toP_Y(){
    QDate from=ui->fromDate->date();
    QDate to=ui->toDate->date();
    if(from.year()>to.year()){
        ui->fromDate->setDate(QDate(to.year(),1,1));
    }
}
