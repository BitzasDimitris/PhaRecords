#include "addrecord.h"
#include "ui_addrecord.h"

AddRecord::AddRecord(int Year, int Month,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddRecord)
{
    ui->setupUi(this);
    if(Month==12){
        Month=1;
        Year++;
    }
    else{
        Month++;
    }
    this->Year=Year;
    this->Month=Month;
    ui->Month->setDate(QDate(2000,Month,1));
    ui->Year->setDate(QDate(Year,1,1));
    SetupEntries();
    ui->Entries->setFocus();
}

AddRecord::~AddRecord()
{
    delete ui;
}

void AddRecord::SetupEntries(){

    QTableWidget *table=ui->Entries;
    table->setColumnCount(2);
    table->setRowCount(Record::EntriesNumber);
    for(int i=0;i<table->rowCount();i++){
        QTableWidgetItem *curitem=new QTableWidgetItem();
        curitem->setText(Record::EntriesLabels.at(i));
        curitem->setFlags(curitem->flags()^Qt::ItemIsEditable);
        table->setItem(i,0,curitem);
        QLineEdit *edit = new QLineEdit(table);
        Input *input=new Input();
        input->Setup(Record::EntriesType.at(i),Record::EntriesNegative.at(i));
        edit->setValidator(input);
        edit->setProperty("row",i);
        table->setCellWidget(i,1,edit);
    }
    table->installEventFilter(new KeyEnterFilter());

}


void AddRecord::on_ConfirmButton_clicked()
{

}

void AddRecord::on_CancelButton_clicked()
{

}

void AddRecord::on_Month_dateChanged(const QDate &date)
{
    int m,y;
    m=date.month();
    y=ui->Year->date().year();
    if(m<Month&&y<=Year){
        ui->Month->setDate(QDate(2000,Month,1));
    }
}

void AddRecord::on_Year_userDateChanged(const QDate &date)
{
    int m,y;
    y=date.year();
    m=ui->Month->date().month();
    if(y<Year){
        ui->Year->setDate(QDate(Year,1,1));
    }
    if(y==Year&&m<Month){
        ui->Month->setDate(QDate(2000,Month,1));
    }
}
