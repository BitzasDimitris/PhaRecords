#include "chartselector.h"
#include "ui_chartselector.h"

ChartSelector::ChartSelector(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChartSelector)
{
    ui->setupUi(this);
    LoadChartButtons();
}

void ChartSelector::closeEvent(QCloseEvent *event){
    this->deleteLater();
}

ChartSelector::~ChartSelector()
{
    emit MainWindowReSurface();
    delete ui;
}




void ChartSelector::LoadChartButtons(){
    QGridLayout *glayout=(QGridLayout*)ui->centralwidget->layout();
    while (auto item = glayout->takeAt(0)) {
        delete item->widget();
    }
    signalMapper=new QSignalMapper(this);
    connect(signalMapper,SIGNAL(mapped(int)),this,SLOT(on_chartButton_Clicked(int)));
    Chart::LoadCharts();
    chartButtons.clear();
    chartButtons=std::vector<QToolButton*>(Chart::Charts.size());
    for(int i=0;i<Chart::Charts.size();i++){
        chartButtons.at(i)=new QToolButton(this);
        chartButtons.at(i)->setGeometry(chartButtons.at(i)->geometry().x(),chartButtons.at(i)->geometry().y(),150,150);
        chartButtons.at(i)->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
        chartButtons.at(i)->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        chartButtons.at(i)->setIcon(QIcon(":/"+Chart::Charts.at(i).getIconPath()));
         chartButtons.at(i)->setIconSize(QSize(100,100));
        chartButtons.at(i)->setText(Chart::Charts.at(i).getName());
        signalMapper->setMapping(chartButtons.at(i), i);
        connect(chartButtons.at(i), SIGNAL(clicked()), signalMapper, SLOT(map()));
        glayout->addWidget(chartButtons.at(i),i%3,i/3,1,1);
    }
    addButton= new QPushButton(QIcon(":/add_icon.png"),"",this);
    addButton->setIconSize(QSize(100,100));
    addButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    addButton->setGeometry(addButton->geometry().x(),addButton->geometry().y(),150,150);
    connect(addButton,SIGNAL(clicked()),this,SLOT(on_addButton_Clicked()));
    glayout->addWidget(addButton,Chart::Charts.size()%3,Chart::Charts.size()/3,1,1);
}

void ChartSelector::on_addButton_Clicked(){
    ChartCreator* chartCreator=new ChartCreator();
    connect(chartCreator,SIGNAL(updateChartButtons()),this,SLOT(updateChartbuttons()));
    chartCreator->show();
}

void ChartSelector::on_chartButton_Clicked(int i){
    //TODO Chart present window and call
    ChartViewer *chartViewer=new ChartViewer(i);
    chartViewer->show();
}

void ChartSelector::updateChartbuttons(){
    LoadChartButtons();
}
