#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    DatabaseInitialize();
    // Trick to resize buttons when startup
    QTimer::singleShot(0,this,SLOT(ButtonResize()));


}

MainWindow::~MainWindow()
{
    delete ui;

}


void MainWindow::DatabaseInitialize(){
    if(!XMLParser::StructureExists()){
        Structure *StructureWindow= new Structure();
        StructureWindow->show();
    }
    else{
        XMLParser::LoadStructure();
    }
    if(XMLParser::DataExists()){
        XMLParser::LoadData();
    }
    UpdateLastRecordDate();
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);
    ResizeButtonsImages();
}

void MainWindow::on_AddButton_clicked()
{
    AddRecord *AddRecordWindow= new AddRecord();
    connect(AddRecordWindow,SIGNAL(MainWindowUpdateLastRecordDate()),this,SLOT(UpdateLastRecordDate()));
    connect(AddRecordWindow,SIGNAL(MainWindowReSurface()),this,SLOT(ReSurface()));
    AddRecordWindow->show();
    this->setEnabled(false);
}

void MainWindow::ResizeButtonsImages(){
    ui->AddButton->setIconSize(ui->AddButton->size());
    ui->EditButton->setIconSize(ui->EditButton->size());
    ui->StatisticsButton->setIconSize(ui->StatisticsButton->size());
}

void MainWindow::ButtonResize(){
    ResizeButtonsImages();
}


void MainWindow::UpdateLastRecordDate(){
    LastRecordMonth=XMLParser::GetLastMonth();
    LastRecordYear=XMLParser::GetLastYear();
    if(LastRecordMonth>0){
        ui->LastRecordsLabel->setText(ui->LastRecordsLabel->text().append(Record::Records.at(Record::Records.size()-1).getDate()));
    }
}

void MainWindow::on_action_2_triggered()
{
    Structure *StructureWindow= new Structure();
    connect(StructureWindow,SIGNAL(MainWindowReSurface()),this,SLOT(ReSurface()));
    StructureWindow->show();

    this->setEnabled(false);
}

void MainWindow::on_EditButton_clicked()
{
    if(XMLParser::DataExists()){
        AddRecord *AddRecordWindow= new AddRecord(LastRecordYear,LastRecordMonth);
        connect(AddRecordWindow,SIGNAL(MainWindowUpdateLastRecordDate()),this,SLOT(UpdateLastRecordDate()));
        connect(AddRecordWindow,SIGNAL(MainWindowReSurface()),this,SLOT(ReSurface()));
        AddRecordWindow->show();
        this->setEnabled(false);
    }
}


void MainWindow::ReSurface(){
    qDebug()<<"called";
    this->setEnabled(true);
}

void MainWindow::on_StatisticsButton_clicked()
{
    if(XMLParser::DataExists()){
        ChartSelector *ChartSelectorWindow=new ChartSelector();
        connect(ChartSelectorWindow,SIGNAL(MainWindowReSurface()),this,SLOT(ReSurface()));
        ChartSelectorWindow->show();
        this->setEnabled(false);
    }
}
