#ifndef POLJACONT_H
#define POLJACONT_H

#include <QVector>
#include <mainwindow.h>
#include <polje.h>


struct Lokacija{
    int x;
    int y;
};

struct PossibleMove{
    int numOfMoves;
    Lokacija possibleLoc;
};

class PoljaCont
{
protected:
    QVector<QVector<Polje *>> matricaPolja;
    MainWindow *window = nullptr;
    Lokacija lokacija;
    int brojPolja;
    int velicinaPolja;
    int slobodnihPolja;
    bool busy = false;


public:
    int delaySpeed = 100;
    PoljaCont();
    PoljaCont(int brojPolja, int velicinaPolja);


    void setUpPolja(MainWindow &w, int count = 6, int size = 100);
    QVector<QVector<Polje *>> getMatrica() { return matricaPolja; }
    void moveKnight(int x, int y);
    void start();
    void reset();
    QVector<PossibleMove> checkPossibleMoves(int x, int y, int startPosX, int startPosY);
    bool checkClosedKnightTour(Lokacija poc, PossibleMove lastmove);
    char getRed(int numb);
};

#endif // POLJACONT_H
