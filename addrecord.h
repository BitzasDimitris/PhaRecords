#ifndef ADDRECORD_H
#define ADDRECORD_H

#include <QMainWindow>
#include <QTableWidget>
#include <QModelIndex>
#include <QDate>
#include "record.h"
#include "keyenterfilter.h"
#include "xmlparser.h"

namespace Ui {
class AddRecord;
}

class AddRecord : public QMainWindow
{
    Q_OBJECT

public:
    AddRecord(int year,int month,QWidget *parent = 0);
    AddRecord(QWidget *parent = 0);
    ~AddRecord();

signals:
    void MainWindowUpdateLastRecordDate();


private slots:
    void on_ConfirmButton_clicked();

    void on_CancelButton_clicked();

    void on_Month_dateChanged(const QDate &date);

    void on_Year_userDateChanged(const QDate &date);

    void on_Entries_cellChanged(int row, int column);

private:
    Ui::AddRecord *ui;

    int Year,Month;
    bool data_added=false;

    void SetupEntries();
    void UpdateLastRecordDate();
};

#endif // ADDRECORD_H
