#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtDebug>
#include <QTimer>
#include "addrecord.h"
#include "structure.h"
#include "xmlparser.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void UpdateLastRecordDate();

private slots:
    void on_AddButton_clicked();
    void ButtonResize();
    void on_action_2_triggered();

    void on_EditButton_clicked();

protected:
    void resizeEvent(QResizeEvent* event)override;
private:
    Ui::MainWindow *ui;

    int LastRecordYear,LastRecordMonth;


    void DatabaseInitialize();
    void ResizeButtonsImages();
};

#endif // MAINWINDOW_H
