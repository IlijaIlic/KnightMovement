#ifndef POLJE_H
#define POLJE_H

#include <QEnterEvent>
#include <QEvent>
#include <QPushButton>

class Polje : public QPushButton
{
    Q_OBJECT

public:
    int x;
    int y;
    int clr = 0;
    bool slobodno = true;

    explicit Polje();
    explicit Polje(QWidget *parent = nullptr, int color = 0);

    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void changeColor(bool start);
    void resetPolje();

};

#endif // POLJE_H
