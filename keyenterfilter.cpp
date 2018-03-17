#include "keyenterfilter.h"

KeyEnterFilter::KeyEnterFilter(QObject *parent){
}

bool KeyEnterFilter::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent* key = static_cast<QKeyEvent*>(event);
        if ( (key->key()==Qt::Key_Enter) || (key->key()==Qt::Key_Return) ) {
            QTableWidget* table=static_cast<QTableWidget*>(obj);
            int row=table->focusWidget()->property("row").toInt();
            if(row<table->rowCount()-1){
                table->setCurrentIndex(table->model()->index(row+1,1));
            }
            else{
                table->setCurrentIndex(table->model()->index(0,1));
            }
        } else {
            return QObject::eventFilter(obj, event);
        }


        return true;
    } else {
        // standard event processing
        return QObject::eventFilter(obj, event);
    }

    return false;
}
