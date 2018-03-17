#ifndef ADDRECORD_H
#define ADDRECORD_H

#include <QMainWindow>
#include <QTableWidget>
#include <QLIneEdit>
#include <QDate>
#include "record.h"
#include "input.h"
#include "keyenterfilter.h"

namespace Ui {
class AddRecord;
}

class AddRecord : public QMainWindow
{
    Q_OBJECT

public:
    explicit AddRecord(int year,int month,QWidget *parent = 0);
    ~AddRecord();

private slots:
    void on_ConfirmButton_clicked();

    void on_CancelButton_clicked();

    void on_Month_dateChanged(const QDate &date);

    void on_Year_userDateChanged(const QDate &date);

private:
    Ui::AddRecord *ui;

    int Year,Month;
    void SetupEntries();
};

#endif // ADDRECORD_H
