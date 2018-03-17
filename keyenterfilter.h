#ifndef KEYENTERFILTER_H
#define KEYENTERFILTER_H

#include <QObject>
#include <QEvent>
#include <QKeyEvent>
#include <QTableWidget>

class KeyEnterFilter : public QObject
{
    Q_OBJECT
public:
    explicit KeyEnterFilter(QObject *parent = nullptr);

protected:
    bool eventFilter(QObject *obj, QEvent *event);
signals:

public slots:

private:
    QTableWidget *parent;
};


#endif // KEYENTERFILTER_H
