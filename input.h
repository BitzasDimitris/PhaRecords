#ifndef INPUT_H
#define INPUT_H

#include <QWidget>
#include <QValidator>

class Input : public QValidator
{
    Q_OBJECT
public:
    explicit Input(QWidget *parent = nullptr);

    void Setup(int type,bool negative);
    void Setup(int type);

    virtual State validate (QString & input ,int &pos) const{
        if(input.isEmpty()){
            return Acceptable;
        }

        bool b;
        switch(this->type){
        case 0:{
            float val=input.toFloat(&b);
            if(b&&((val>0&&!negative)||negative)){
                return Acceptable;
            }
            return Invalid;
            break;
        }
        case 1:{
            int ival=input.toInt(&b);
            if(b&&((ival>0&&!negative)||negative)){
                return Acceptable;
            }
            return Invalid;
            break;
        }
        }
    }

private:
    int type;
    bool negative;

signals:

public slots:

};

#endif // INPUT_H
