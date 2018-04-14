#include "chartviewer.h"
#include "ui_chartviewer.h"

ChartViewer::ChartViewer(int index,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChartViewer)
{
    ui->setupUi(this);
    chartIndex=index;
    //TODO update minimum and maximum year and month
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
    switch(index){
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
    switch(index){
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
    if(from.year()<minimumYear||from.year()==minimumYear&&from.month()<minimumMonth){
        ui->fromDate->setDate(QDate(minimumYear,minimumMonth,1));
    }
    if(from.year()>maximumYear||from.year()==maximumYear&&from.month()>maximumMonth){
        ui->fromDate->setDate(QDate(maximumYear,maximumMonth,1));
    }
    if(to.year()<from.year()||to.year()==from.year()&&to.month()<from.month()){
        ui->toDate->setDate(QDate(ui->fromDate->date()));
    }
}

void ChartViewer::fromO_M_P_Y(){
    QDate from=ui->fromDate->date();
    QDate to=ui->toDate->date();
    if(from.year()<minimumYear){
        ui->fromDate->setDate(QDate(minimumYear,from.month(),1));
    }
    if(from.year()==minimumYear&&from.month()<minimumMonth){
        ui->fromDate->setDate(QDate(minimumYear+1,from.month(),1));
    }
    if(from.year()>maximumYear){
        ui->fromDate->setDate(QDate(maximumYear,maximumMonth,1));
    }
    if(from.year()==maximumYear&&from.month()>maximumMonth){

    }
    from=ui->fromDate->date();
    if(to.year()<from.year()){
        ui->toDate->setDate(QDate(ui->fromDate->date()));
    }
    to=ui->toDate->date();
    ui->toDate->setDate(QDate(to.year(),from.month(),1));
    to=ui->toDate->date();
    if(to.year()==maximumYear&&to.month()>maximumMonth){
        ui->toDate->setDate(QDate(to.year()-1,to.month(),1));
    }
}

void ChartViewer::fromP_M_O_Y(){
    QDate from=ui->fromDate->date();
    QDate to=ui->toDate->date();
    //if(from.year())
}

void ChartViewer::fromP_Y(){
    QDate from=ui->fromDate->date();
    QDate to=ui->toDate->date();
    if(from.year()<minimumYear){
        ui->fromDate->setDate(QDate(minimumYear,1,1));
    }
    if(from.year()>to.year()){
        ui->toDate->setDate(QDate(from.year(),1,1));
    }
}

void ChartViewer::toP_M_P_Y(){
    QDate from=ui->fromDate->date();
    QDate to=ui->toDate->date();
    if(to.year()>maximumYear||to.year()==maximumYear&&to.month()>maximumMonth){
        ui->toDate->setDate(QDate(maximumYear,maximumMonth,1));
    }
    if(to.year()<minimumYear||to.year()==minimumYear&&to.month()<minimumMonth){
        ui->toDate->setDate(QDate(minimumYear,minimumMonth,1));
    }
    if(to.year()<from.year()||to.year()==from.year()&&to.month()<from.month()){
        ui->fromDate->setDate(QDate(ui->toDate->date()));
    }
}

void ChartViewer::toO_M_P_Y(){
    QDate from=ui->fromDate->date();
    QDate to=ui->toDate->date();
    if(to.year()>maximumYear||to.year()==maximumYear&&to.month()>maximumMonth){
        ui->toDate->setDate(QDate(maximumYear,maximumMonth,1));
    }
    if(to.year()<minimumYear||to.year()==minimumYear&&to.month()<minimumMonth){
        ui->toDate->setDate(QDate(minimumYear,minimumMonth,1));
    }
    if(to.year()<from.year()){
        ui->fromDate->setDate(QDate(ui->toDate->date()));
    }
    from=ui->fromDate->date();
    ui->fromDate->setDate(QDate(from.year(),to.month(),1));
    from=ui->fromDate->date();
    if(from.year()==minimumYear&&from.month()<minimumMonth){
        ui->fromDate->setDate(QDate(from.year()+1,from.month(),1));
    }
}

void ChartViewer::toP_M_O_Y(){

}

void ChartViewer::toP_Y(){
    QDate from=ui->fromDate->date();
    QDate to=ui->toDate->date();
    if(to.year()>maximumYear){
        ui->toDate->setDate(QDate(maximumYear,1,1));
    }
    if(from.year()>to.year()){
        ui->fromDate->setDate(QDate(to.year(),1,1));
    }
}
