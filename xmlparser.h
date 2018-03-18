#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <QtXml>
#include <QFile>
#include <QString>
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

    static int GetLastMonth();
    static int GetLastYear();

    static int LoadStructure();
    static int CreateStructure(std::vector<QString> Labels,std::vector<int> Types,std::vector<bool>Negatives);
    static int LoadData();
    static bool ChangeStructure();

    static int SaveData();

    static bool StructureExists();
    static bool DataExists();
private:
    static QString StructurePath,DataPath;
};

#endif // XMLPARSER_H
