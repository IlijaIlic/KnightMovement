#include "mainwindow.h"

#include <QApplication>
#include <QLabel>
#include <QScreen>
#include "iostream"
#include "stdio.h"
#include <poljacont.h>

void setUpWindow(MainWindow &w, int count = 6, int size = 100)
{
    w.setStyleSheet("background-color: #5b704a;");
    w.resize((count + 2) * size, (count + 3) * size);

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->availableGeometry();

    int x = screenGeometry.x() + (screenGeometry.width() - w.width()) / 2;
    int y = screenGeometry.y() + (screenGeometry.height() - w.height()) / 2;

    w.move(x, y);
    w.show();
}

void setUpLabele(MainWindow &w, int count = 6, int size = 100)
{
    int counter = 1;

    for (int i = count; i > 0; i--) {
        QLabel *label = new QLabel(&w);
        label->setStyleSheet("QLabel {"

                             "font-family: 'Cascadia Mono';"
                             "font-size: 25px;"
                             "color: white;"

                             "}");

        label->setText(QString::number(counter));
        label->resize(20, 20);
        label->move(size / 2, i * size + size / 2 - label->height() / 2);
        label->show();
        counter++;
    }

    char red = 'A';
    for (int i = 0; i < count; i++) {
        QLabel *label = new QLabel(&w);
        label->setStyleSheet("QLabel {"

                             "font-family: 'Cascadia Mono';"
                             "font-size: 25px;"
                             "color: white;"
                             "}");

        label->setText(QString(QChar(red)));
        label->move((i + 2) * size - size / 2 - label->width() / 10, (count + 1.2) * size);
        label->show();
        red++;
    }

    w.titleLabel = new QLabel(&w);
    w.titleLabel->setStyleSheet("QLabel {"

                                "font-family: 'Cascadia Mono';"
                                "font-size: 50px;"
                                "font-weight: bold;"
                                "color: white;"
                                "}");

    w.titleLabel->setText("Knight Tour");

    w.titleLabel->adjustSize();

    w.titleLabel->move(w.width() / 2 - w.titleLabel->width() / 2,
                       size / 2 - w.titleLabel->height() / 2);
    w.titleLabel->show();
}

void setUpButtons(MainWindow &w, PoljaCont *polja, int count = 6, int size = 100)
{
    QPushButton *startButton = new QPushButton(&w);
    startButton->resize(100, 50);
    startButton->move(2 * size, (count + 2) * size);
    startButton->show();
    startButton->setText("Start");

    startButton->setStyleSheet("QPushButton {"

                               " background-color: #EBECD0; "
                               "font-family: 'Cascadia Mono';"
                               "font-size: 25px;"

                               "}");

    QObject::connect(startButton, QPushButton::clicked, [&w, polja]() { polja->start(); });

    QPushButton *resetButton = new QPushButton(&w);
    resetButton->resize(100, 50);
    resetButton->move((count - 1) * size, (count + 2) * size);
    resetButton->show();
    resetButton->setText("Reset");

    resetButton->setStyleSheet("QPushButton {"

                               " background-color: #EBECD0; "
                               "font-family: 'Cascadia Mono';"
                               "font-size: 25px;"

                               "}");

    QObject::connect(resetButton, QPushButton::clicked, [&w, polja]() { polja->reset(); });
}

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;

    int brojPolja = 6;
    int velicinaPolja;

    switch (brojPolja) {
    case 6:
        velicinaPolja = 100;
        break;
    case 8:
        velicinaPolja = 75;
        break;
    default:
        velicinaPolja = 100;
        break;
    }
    PoljaCont *polja = new PoljaCont(brojPolja, velicinaPolja);

    setUpWindow(w, brojPolja, velicinaPolja);
    polja->setUpPolja(w, brojPolja, velicinaPolja);
    setUpLabele(w, brojPolja, velicinaPolja);
    setUpButtons(w, polja, brojPolja, velicinaPolja);

    return a.exec();
}
