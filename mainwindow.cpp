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
        //OpenStructureEditor
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
    connect(AddRecordWindow,SIGNAL(UpdateLastRecordDate(void)),this,SLOT(UpdateLastRecordDate(void)));
    AddRecordWindow->show();
    //hide();
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
        ui->LastRecordsLabel->setText(ui->LastRecordsLabel->text().append(XMLParser::Records.at(XMLParser::Records.size()-1).getDate()));
    }
}
