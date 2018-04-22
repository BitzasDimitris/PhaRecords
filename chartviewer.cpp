#include "chartviewer.h"
#include "ui_chartviewer.h"

ChartViewer::ChartViewer(int index,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChartViewer)
{
    ui->setupUi(this);
    chartIndex=index;
    Record::getMinMaxYearMonth(minimumYear,minimumMonth,maximumYear,maximumMonth);
    ui->fromDate->setMinimumDate(QDate(minimumYear,minimumMonth,1));
    ui->fromDate->setMaximumDate(QDate(maximumYear,maximumMonth,1));
    ui->toDate->setMinimumDate(QDate(minimumYear,minimumMonth,1));
    ui->toDate->setMaximumDate(QDate(maximumYear,maximumMonth,1));
    //TODO set dates for last year
    //TODO create chart
}
ChartViewer::~ChartViewer()
{
    delete ui;
}

void ChartViewer::on_perComboBox_currentIndexChanged(int index)
{
    if(dateTypeIndex==index){
        return;
    }
    dateTypeIndex=index;
    switch(index){
    case 0:
        perMonthOneYear();
        break;
    case 1:
        oneMonthPerYear();
        break;
    case 2:
        perMonthPerYear();
        break;
    case 3:
        perYear();
        break;
    }
}

void ChartViewer::perMonthOneYear(){

}

void ChartViewer::perMonthPerYear(){

}

void ChartViewer::oneMonthPerYear(){

}

void ChartViewer::perYear(){

}

void ChartViewer::on_fromDate_userDateChanged(const QDate &date)
{
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
}

void ChartViewer::on_toDate_userDateChanged(const QDate &date)
{
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
