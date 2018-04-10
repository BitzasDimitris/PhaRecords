#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <QDialog>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QMessageBox>
#include "xmlparser.h"
#include "record.h"

namespace Ui {
class Structure;
}

class Structure : public QDialog
{
    Q_OBJECT

public:
    explicit Structure(QWidget *parent = 0);
    ~Structure();

private slots:
    void on_ConfirmButton_clicked();

    void on_AddButton_clicked();

    void on_DeleteButton_clicked();

    void on_CancelButton_clicked();

    void on_checkBox_stateChanged(int arg1);

private:
    void SetupStructureTable();

    Ui::Structure *ui;
};

#endif // STRUCUTRE_H
