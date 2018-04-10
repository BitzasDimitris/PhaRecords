#include "xmlparser.h"
QString XMLParser::StructurePath="Structure.xml",XMLParser::DataPath="Data.xml";
std::vector<Record> XMLParser::Records=std::vector<Record>();

int XMLParser::GetLastMonth(){
    if(Records.size()==0){
        return -1;
    }
    else{
        return Records.at(Records.size()-1).Month;
    }
}

int XMLParser::GetLastYear(){
    if(Records.size()==0){
        return -1;
    }
    else{
        return Records.at(Records.size()-1).Year;
    }
}

int XMLParser::CreateStructure(std::vector<QString> Labels, std::vector<bool> Types, std::vector<bool> Negatives){
    QFile Structure(StructurePath);
    if(!Structure.open(QFile::WriteOnly|QFile::Text)){
        return FILE_NOT_OPENED;
    }
    QDomDocument document=QDomDocument();
    QDomElement topElement=document.createElement("Structure");
    for(int i=0;i<Labels.size();i++){
        QDomElement currentLabel=document.createElement(Labels.at(i));
        currentLabel.setAttribute("type",Types.at(i)?1:0);
        currentLabel.setAttribute("negative",Negatives.at(i)?1:0);
        QDomText currentLabelText=document.createTextNode(Labels.at(i));
        currentLabelText.setData(Labels.at(i));
        currentLabel.appendChild(currentLabelText);
        topElement.appendChild(currentLabel);
    }
    document.appendChild(topElement);
    QTextStream out(&Structure);
    out.setCodec( "utf-8" );
    out<<document.toString().toUtf8();
    Structure.close();
    return OK;
}

int XMLParser::LoadStructure(){
    QFile Structure(StructurePath);
    if(!Structure.exists()){
        return FILE_NOT_FOUND;
    }
    if(!Structure.open(QFile::ReadOnly|QFile::Text)){
        return FILE_NOT_OPENED;
    }

    QDomDocument document;
    if(!document.setContent(&Structure)){
       Structure.close();
       return FILE_NOT_PARCABLE;
    }
    Structure.close();
    QDomElement topElement=document.documentElement();
    QDomNode domNode=topElement.firstChild();
    while(!domNode.isNull()){
        QDomElement domElement=domNode.toElement();
        if(!domElement.isNull()){
            Record::EntriesNumber++;
            Record::EntriesLabels.push_back(domElement.text());
            bool b;
            bool type=domElement.attribute("type").toInt(&b);
            if(b){
               Record::EntriesType.push_back(type);
            }
            else{
               Record::EntriesType.push_back(false);
            }
            bool negative=domElement.attribute("negative").toInt(&b);
            if(b){
               Record::EntriesNegative.push_back(negative);
            }
            else{
               Record::EntriesNegative.push_back(false);
            }
        }
        domNode=domNode.nextSibling();
    }
    return OK;
}

int XMLParser::LoadData(){
    QFile Data(DataPath);
    if(!Data.exists()){
        return FILE_NOT_FOUND;
    }
    if(!Data.open(QFile::ReadOnly|QFile::Text)){
        return FILE_NOT_OPENED;
    }
    QDomDocument document;
    if(!document.setContent(&Data)){
       Data.close();
       return FILE_NOT_PARCABLE;
    }
    Data.close();
    QDomElement topElement=document.documentElement();
    QDomNode domNode=topElement.firstChild();
    while(!domNode.isNull()){
        int year,month;
        std::vector<float> e=std::vector<float>();
        QDomNodeList curnodelist=domNode.toElement().childNodes();
        bool b,final=true;
        month=curnodelist.at(0).toElement().text().toInt(&b);
        if(!b){
            final=false;
        }
        year=curnodelist.at(1).toElement().text().toInt(&b);
        if(!b){
            final=false;
        }
        QDomNodeList entries=curnodelist.at(2).toElement().childNodes();
        if(entries.size()!=Record::EntriesNumber){
            final=false;
        }
        for(int j=0;j<entries.size();j++){
            e.push_back(entries.at(j).toElement().text().toFloat(&b));
            if(!b){
                final=false;
                break;
            }
        }
        if(final){
            Records.push_back(Record(year,month,e));
        }
        domNode=domNode.nextSibling();

    }
    return OK;
}

int XMLParser::SaveData(){
    QFile Data(DataPath);
    if(!Data.open(QFile::WriteOnly|QFile::Text)){
        return FILE_NOT_OPENED;
    }
    QDomDocument document=QDomDocument();
    QDomElement topElement=document.createElement("Data");
    for(int i=0;i<Records.size();i++){
        Record r=Records.at(i);
        QDomElement curRecord= document.createElement("Record");
        QDomElement curmonth= document.createElement("Month");
        QDomText curmontht= document.createTextNode("Month");
        curmontht.setData(QString::number(r.Month));
        curmonth.appendChild(curmontht);
        curRecord.appendChild(curmonth);
        QDomElement curyear= document.createElement("Year");
        QDomText curyeart= document.createTextNode("Year");
        curyeart.setData(QString::number(r.Year));
        curyear.appendChild(curyeart);
        curRecord.appendChild(curyear);
        QDomElement curentries= document.createElement("Entries");
        for(int j=0;j<Record::EntriesNumber;j++){
            QDomElement curelement= document.createElement("element");
            QDomText text=document.createTextNode("element");
            float val=r.entries.at(j);
            text.setData(QString::number(val));
            curelement.appendChild(text);
            curentries.appendChild(curelement);
        }
        curRecord.appendChild(curentries);
        topElement.appendChild(curRecord);
     }
     document.appendChild(topElement);
     QTextStream out(&Data);
     out<<document.toString();
     Data.close();
     return OK;
}

bool XMLParser::StructureExists(){
    return QFile(StructurePath).exists();
}

bool XMLParser::DataExists(){
    return QFile(DataPath).exists();
}
