#include "input.h"

Input::Input(QWidget *parent) : QValidator(parent)
{

}


void Input::Setup(int type){
    this->type=type;
    this->negative=false;
}

void Input::Setup(int type, bool negative){
    this->type=type;
    this->negative=negative;
}
