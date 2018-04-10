#include "addrecord.h"
#include "ui_addrecord.h"

AddRecord::AddRecord(int Year, int Month,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddRecord)
{
    ui->setupUi(this);
    edit=true;
    this->Year=Year;
    this->Month=Month;
    ui->Month->setDate(QDate(2000,Month,1));
    ui->Year->setDate(QDate(Year,1,1));
    SetupEntries();
    ui->Entries->setFocus();
}

AddRecord::AddRecord(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddRecord)
{
    ui->setupUi(this);
    UpdateLastRecordDate();

    SetupEntries();
    ui->Entries->setFocus();
    ui->Entries->setCurrentCell(0,1);
}

AddRecord::~AddRecord()
{
    delete ui;
}


void AddRecord::UpdateLastRecordDate(){
    int Month,Year;
    Month=XMLParser::GetLastMonth();
    Year=XMLParser::GetLastYear();
    if(Month<0){
        this->Month=1;
        this->Year=1991;
        ui->Month->setDate(QDate(2000,Month,1));
        ui->Year->setDate(QDate(Year,1,1));
        return;
    }
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
}

void AddRecord::UpdateValues(Record rec){
    QTableWidget *table=ui->Entries;
    for(int i=0;i<Record::EntriesNumber;i++){
        QTableWidgetItem *entry=new QTableWidgetItem();
        if(Record::EntriesType.at(i)){
            entry->setText(QString::number(rec.entries.at(i)));
        }
        else{
            entry->setText(QString::number((int)rec.entries.at(i)));
        }
        table->setItem(i,1,entry);
    }
}

void AddRecord::SetupEntries(){

    QTableWidget *table=ui->Entries;
    table->setColumnCount(2);
    table->setRowCount(Record::EntriesNumber);
    table->blockSignals(true);
    for(int i=0;i<table->rowCount();i++){
        QTableWidgetItem *curitem=new QTableWidgetItem();
        curitem->font().setBold(true);
        curitem->setText(Record::EntriesLabels.at(i));
        curitem->setFlags(curitem->flags()^Qt::ItemIsEditable);
        table->setItem(i,0,curitem);
        QTableWidgetItem *edit = new QTableWidgetItem();
        edit->setText("0");
        table->setItem(i,1,edit);
    }
    table->installEventFilter(new KeyEnterFilter());
    table->blockSignals(false);
    QTableWidgetItem *h1=new QTableWidgetItem();
    QTableWidgetItem *h2=new QTableWidgetItem();
    h1->setText("Είδος");
    h1->setText("Τιμή");
    table->setHorizontalHeaderItem(0,h1);
    table->setHorizontalHeaderItem(1,h2);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    if(edit){
        int result;
        Record rec=Record::GetRecord(Year,Month,&result);
        if(result!=-1){
            UpdateValues(rec);
        }
    }
}


void AddRecord::on_ConfirmButton_clicked()
{
    std::vector<float> entries=std::vector<float>();
    QTableWidget* table =ui->Entries;
    for(int i=0;i<ui->Entries->rowCount();i++){
        entries.push_back(table->item(i,1)->text().toFloat());
        if(!edit){
            table->item(i,1)->setText("0");
        }
    }
    if(edit){
        Record::SetRecord(ui->Year->date().year(),ui->Month->date().month(),entries);
    }
    else{
        Record newrec= Record(ui->Year->date().year(),ui->Month->date().month(),entries);
        Record::Records.push_back(newrec);
        data_added=true;
        Year=ui->Year->date().year();
        Month=ui->Month->date().month();
        emit MainWindowUpdateLastRecordDate();
        QDate curdate=QDate::currentDate();
        if(Year==curdate.year()&&Month==curdate.month()){
            XMLParser::SaveData();
            this->close();
        }
        else{
            if(Month==12){
                Month=1;
                Year++;
            }
            else{
                Month++;
            }
            ui->Month->setDate(QDate(2000,Month,1));
            ui->Year->setDate(QDate(Year,1,1));
        }
    }

}

void AddRecord::on_CancelButton_clicked()
{
    if(data_added){
        XMLParser::SaveData();
    }
    this->close();
}

void AddRecord::on_Month_dateChanged(const QDate &date)
{
    int m,y;
    QDate curdate=QDate::currentDate();
    m=date.month();
    y=ui->Year->date().year();
    if(edit){
        if(y==curdate.year()&&m>curdate.month()){
           ui->Month->setDate(QDate(2000,Month,1));
        }
        int result;
        Record rec=Record::GetRecord(y,m,&result);
        if(result!=-1){
            UpdateValues(rec);
        }
        else{
           ui->Month->setDate(QDate(2000,Month,1));
        }
    }
    else{
        if(m<Month&&y<=Year){
            ui->Month->setDate(QDate(2000,Month,1));
        }
    }

}

void AddRecord::on_Year_userDateChanged(const QDate &date)
{
    int m,y;
    QDate curdate=QDate::currentDate();
    y=date.year();
    m=ui->Month->date().month();
    if(edit){
        if(y>curdate.year()){
            ui->Year->setDate(QDate(curdate.year(),1,1));
        }

        if(y==curdate.year()&&m>curdate.month()){
           ui->Month->setDate(QDate(2000,curdate.month()+1,1));
        }
        int result;
        Record rec=Record::GetRecord(y,m,&result);
        if(result!=-1){
            UpdateValues(rec);
        }
        else{
           ui->Year->setDate(QDate(Year,1,1));
        }
    }
    else{
        if(y<Year){
            ui->Year->setDate(QDate(Year,1,1));
        }
        if(y==Year&&m<Month){
            ui->Month->setDate(QDate(2000,Month,1));
        }

        if(y>curdate.year()){
            ui->Year->setDate(QDate(curdate.year(),1,1));
        }

        if(y==curdate.year()&&m>curdate.month()){
           ui->Month->setDate(QDate(2000,curdate.month()+1,1));
        }
    }
}

void AddRecord::on_Entries_cellChanged(int row, int column)
{
    QTableWidget *table=ui->Entries;
    QString text=table->item(row,column)->text();
    bool b;
    if(Record::EntriesType.at(row)){
        do{
            text.toFloat(&b);
            if(!b){
                text=text.left(text.size()-1);
            }
        }while(!b&& text.size()>0);
    }
    else{
        do{
            text.toInt(&b);
            if(!b){
                text=text.left(text.size()-1);
            }
        }while(!b&& text.size()>0);
    }
    table->item(row,column)->setText(text);
}
