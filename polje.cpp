#include "polje.h"
#include <QPushButton>

Polje::Polje() {}

Polje::Polje(QWidget *parent, int color)
    : QPushButton(parent)
{
    this->clr = color;

    if (color == 0) {
        setStyleSheet("QPushButton {"

                      " background-color: #779556; "
                      "font-family: 'Cascadia Mono';"
                      "font-size: 50px;"
                      "color : black;"

                      "}");
    } else {
        setStyleSheet("QPushButton {"

                      " background-color: #EBECD0; "
                      "font-family: 'Cascadia Mono';"
                      "font-size: 50px;"
                      "color : black;"

                      "}");
    }
}

void Polje::enterEvent(QEnterEvent *event)
{
    if (slobodno) {
        setStyleSheet("QPushButton {"

                      " background-color: #989299; "
                      "font-family: 'Cascadia Mono';"
                      "font-size: 50px;"
                      "color : black;"

                      "}");

        QPushButton::enterEvent(event);
    }
}

void Polje::leaveEvent(QEvent *event)
{
    if (slobodno) {
        if (this->clr == 0) {
            setStyleSheet("QPushButton {"

                          " background-color: #779556; "
                          "font-family: 'Cascadia Mono';"
                          "font-size: 50px;"
                          "color : black;"

                          "}");
        } else {
            setStyleSheet("QPushButton {"

                          " background-color: #EBECD0; "
                          "font-family: 'Cascadia Mono';"
                          "font-size: 50px;"
                          "color : black;"

                          "}");
        }
    }
    QPushButton::leaveEvent(event);
}

void Polje::changeColor(bool start)
{
    if (start) {
        setStyleSheet("QPushButton {"

                      " background-color: #e5ae22; "
                      "font-family: 'Cascadia Mono';"
                      "font-size: 50px;"
                      "color : black;"

                      "}");
    } else {
        setStyleSheet("QPushButton {"

                      " background-color: #D28846; "
                      "font-family: 'Cascadia Mono';"
                      "font-size: 50px;"
                      "color : black;"

                      "}");
    }
}

void Polje::resetPolje()
{
    this->slobodno = true;

    if (clr == 0) {
        setStyleSheet("QPushButton {"

                      " background-color: #779556; "
                      "font-family: 'Cascadia Mono';"
                      "font-size: 50px;"
                      "color : black;"

                      "}");
    } else {
        setStyleSheet("QPushButton {"

                      " background-color: #EBECD0; "
                      "font-family: 'Cascadia Mono';"
                      "font-size: 50px;"
                      "color : black;"

                      "}");
    }
}
