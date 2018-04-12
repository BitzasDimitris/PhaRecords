#include "chartselector.h"
#include "ui_chartselector.h"

ChartSelector::ChartSelector(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChartSelector)
{
    ui->setupUi(this);
    LoadChartButtons();
    // Trick to resize buttons when startup
    QTimer::singleShot(0,this,SLOT(ButtonResize()));
}

void ChartSelector::closeEvent(QCloseEvent *event){
    this->deleteLater();
}

ChartSelector::~ChartSelector()
{
    emit MainWindowReSurface();
    delete ui;
}

void ChartSelector::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);
    ResizeButtonsImages();
}

void ChartSelector::ResizeButtonsImages(){

    for(int i=0;i<chartButtons.size();i++){
        chartButtons.at(i)->setIconSize(chartButtons.at(i)->size());
    }
    addButton->setIconSize(addButton->size());
}

void ChartSelector::ButtonResize(){
    ResizeButtonsImages();
}

void ChartSelector::LoadChartButtons(){
    QGridLayout *glayout=(QGridLayout*)ui->centralwidget->layout();
    while (auto item = glayout->takeAt(0)) {
        delete item->widget();
    }
    signalMapper=new QSignalMapper(this);
    connect(signalMapper,SIGNAL(mapped(int)),this,SLOT(on_charButton_Clicked(int)));
    Chart::LoadCharts();
    chartButtons.clear();
    chartButtons=std::vector<QPushButton*>(Chart::Charts.size());
    for(int i=0;i<Chart::Charts.size();i++){
        chartButtons.at(i)=new QPushButton(QIcon(":/"+Chart::Charts.at(i).getIconPath()),Chart::Charts.at(i).getName(),this);
        chartButtons.at(i)->setMinimumSize(50,50);
        chartButtons.at(i)->setMaximumSize(1000,1000);
        signalMapper->setMapping(chartButtons.at(i), i);
        connect(chartButtons.at(i), SIGNAL(clicked()), signalMapper, SLOT(map()));
        glayout->addWidget(chartButtons.at(i),i%3,i/3,1,1);
    }
    addButton= new QPushButton(QIcon(":/add_icon.png"),"",this);
    addButton->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);
    addButton->setMinimumSize(50,50);
    addButton->setMaximumSize(1000,1000);
    connect(addButton,SIGNAL(clicked()),this,SLOT(on_addButton_Clicked()));
    glayout->addWidget(addButton,Chart::Charts.size()%3,Chart::Charts.size()/3,1,1);
}

void ChartSelector::on_addButton_Clicked(){
    ChartCreator* chartCreator=new ChartCreator();
    connect(chartCreator,SIGNAL(updateChartButtons()),this,SLOT(updateChartbuttons()));
    chartCreator->show();
}

void ChartSelector::on_charButton_Clicked(int i){
    //TODO Chart present window and call
}

void ChartSelector::updateChartbuttons(){
    LoadChartButtons();
    ButtonResize();
}
