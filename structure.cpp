#include "structure.h"
#include "ui_structure.h"

Structure::Structure(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Structure)
{
    ui->setupUi(this);
    SetupStructureTable();
}

Structure::~Structure()
{
    delete ui;
}

void Structure::SetupStructureTable(){
    QTableWidget *table=ui->StructureTable;
    QTableWidgetItem *h1,*h2,*h3;
    h1=new QTableWidgetItem();
    h2=new QTableWidgetItem();
    h3=new QTableWidgetItem();
    h1->setText("Ετικέτα");
    h2->setText("Δεκαδικός");
    h3->setText("Αρητικές\nΤιμές");
    table->setHorizontalHeaderItem(0,h1);
    table->setHorizontalHeaderItem(1,h2);
    table->setHorizontalHeaderItem(2,h3);
    if(XMLParser::StructureExists()){
        for(int i=0;i<Record::EntriesNumber;i++){
            QTableWidgetItem *currentLabel,*currentType,*currentNegative;
            currentLabel=new QTableWidgetItem();
            currentType=new QTableWidgetItem();
            currentNegative=new QTableWidgetItem();
            currentLabel->setText(Record::EntriesLabels.at(i));
            currentType->setCheckState(Record::EntriesType.at(i)?Qt::Checked:Qt::Unchecked);
            currentNegative->setCheckState(Record::EntriesNegative.at(i)?Qt::Checked:Qt::Unchecked);
            currentLabel->setFlags(currentLabel->flags() ^ Qt::ItemIsEditable);
            currentType->setFlags(currentType->flags() ^ Qt::ItemIsEditable);
            currentNegative->setFlags(currentNegative->flags() ^ Qt::ItemIsEditable);
            table->insertRow(i);
            table->setItem(0,i,currentLabel);
            table->setItem(1,i,currentType);
            table->setItem(2,i,currentNegative);

        }
    }
}

void Structure::on_ConfirmButton_clicked()
{
    if(XMLParser::StructureExists()){

    }
    else{
        std::vector<QString> Labels;
        std::vector<bool> Types;
        std::vector<bool> Negatives;
        QTableWidget *table=ui->StructureTable;
        for(int i=0;i<table->rowCount();i++){
            if(table->item(i,0)->text().compare("")!=0){
                Labels.push_back(table->item(i,0)->text());
                Types.push_back(table->item(i,1)->checkState()?true:false);
                Negatives.push_back(table->item(i,2)->checkState()?true:false);
            }
        }
        XMLParser::CreateStructure(Labels,Types,Negatives);
        XMLParser::LoadStructure();
    }
    this->close();
}

void Structure::on_AddButton_clicked()
{
    QTableWidget *table=ui->StructureTable;
    QTableWidgetItem *currentLabel,*currentType,*currentNegative;
    currentLabel=new QTableWidgetItem();
    currentType=new QTableWidgetItem();
    currentNegative=new QTableWidgetItem();
    currentLabel->setText("");
    currentType->setCheckState(Qt::Unchecked);
    currentNegative->setCheckState(Qt::Unchecked);
    table->insertRow(table->rowCount());
    table->setItem(table->rowCount()-1,0,currentLabel);
    table->setItem(table->rowCount()-1,1,currentType);
    table->setItem(table->rowCount()-1,2,currentNegative);
}

void Structure::on_DeleteButton_clicked()
{
    QTableWidget *table=ui->StructureTable;
    if(table->selectedItems().size()>0){
        int row=table->selectedItems().at(0)->row();
        table->removeRow(row);
    }
    else{
        table->removeRow(table->rowCount()-1);
    }
}

void Structure::on_CancelButton_clicked()
{
    this->close();
}

void Structure::on_checkBox_stateChanged(int arg1)
{
    QMessageBox *msg=new QMessageBox();
    msg->addButton("Αποδοχή",QMessageBox::AcceptRole);
    msg->addButton("Ακύρωση",QMessageBox::RejectRole);
    msg->setText("Αν ξεκλειδώσετε τη δομή θα χρειαστεί να διαγραφούν τα παλιά δεδομένα.");
    msg->show();
    int result= msg->result();
    if(result==QMessageBox::Accepted){
        ui->Locker->setChecked(true);
        //TODO delete/backup old records
    }
    else{
        ui->Locker->setChecked(false);
    }
}
