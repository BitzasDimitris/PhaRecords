#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <QtXml>
#include <QFile>
#include <vector>
#include "record.h"

class XMLParser
{
public:
    const static int OK=0;
    const static int FILE_NOT_FOUND=1;
    const static int FILE_NOT_OPENED=2;
    const static int FILE_NOT_PARCABLE=3;

    static std::vector<Record> Records;


    static int LoadStructure();
    static int CreateStructure(std::vector<QString> Labels);
    static int LoadData();
    static bool ChangeStructure();
    static bool AddData();
    static bool EditData();

    static bool StructureExists();
    static bool DataExists();
private:
    static QString StructurePath,DataPath;
};

#endif // XMLPARSER_H
