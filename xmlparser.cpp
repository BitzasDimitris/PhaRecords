#include "xmlparser.h"
QString XMLParser::StructurePath="Structure.xml",XMLParser::DataPath="Data.xml";
std::vector<Record> XMLParser::Records=std::vector<Record>();


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
            int type=domElement.attribute("type").toInt(&b);
            if(b){
               Record::EntriesType.push_back(type);
            }
            else{
               Record::EntriesType.push_back(0);
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

int XMLParser::CreateStructure(std::vector<QString> Labels){
    QFile Structure(StructurePath);
    if(Structure.exists()){
        Structure.remove();
    }
    if(!Structure.open(QFile::WriteOnly|QFile::Text)){
        return FILE_NOT_OPENED;
    }
    QDomDocument document;
    QDomElement topElement=document.createElement("Structure");
    for(int i=0;i<Labels.size();i++){
        QDomElement curElement= document.createElement(Labels.at(i));
        QDomText text=document.createTextNode(Labels.at(i));
        curElement.appendChild(text);
        topElement.appendChild(curElement);
    }
    document.appendChild(topElement);
    QTextStream out(&Structure);
    out<<document.toString();
    return OK;
}

bool XMLParser::StructureExists(){
    return QFile(StructurePath).exists();
}

bool XMLParser::DataExists(){
    return QFile(DataPath).exists();
}
