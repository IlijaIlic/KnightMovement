#include "poljacont.h"
#include <QFile>
#include <QTextStream>
#include <QTime>

PoljaCont::PoljaCont() {}

PoljaCont::PoljaCont(int brojPolja, int velicinaPolja)
{
    this->brojPolja = brojPolja;
    this->velicinaPolja = velicinaPolja;
    this->matricaPolja.resize(brojPolja);

    for (int i{}; i < brojPolja; i++) {
        this->matricaPolja[i].resize(brojPolja);
        for (int j{}; j < brojPolja; j++) {
            this->matricaPolja[i][j] = nullptr;
        }
    }

    this->lokacija.x = 0;
    this->lokacija.y = 0;

    this->slobodnihPolja = brojPolja * brojPolja;
}

void PoljaCont::setUpPolja(MainWindow &w, int count, int size)
{
    int counter = 0;
    this->window = &w;

    for (int i = count; i > 0; i--) {
        for (int j{}; j < count; j++) {
            Polje *p = new Polje(&w, (i + j) % 2);
            this->matricaPolja[counter][j] = p;
            this->matricaPolja[counter][j]->x = counter;
            this->matricaPolja[counter][j]->y = j;

            QObject::connect(p, &QPushButton::clicked, [this, counter, j](bool) {
                if (!this->busy) {
                    moveKnight(matricaPolja[counter][j]->x, matricaPolja[counter][j]->y);
                }
            });

            p->setGeometry(j * size + size, i * size, size, size);
            p->show();
        }
        counter++;
    }
}

void delay(int time)
{
    QTime dieTime = QTime::currentTime().addMSecs(time);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void PoljaCont::moveKnight(int x, int y)
{
    this->matricaPolja[this->lokacija.x][this->lokacija.y]->setText("");

    this->lokacija.x = x;
    this->lokacija.y = y;

    this->matricaPolja[x][y]->setText("♘");
}

void PoljaCont::start()
{
    if (!busy && this->slobodnihPolja != 0) {
        this->window->titleLabel->setText("Knight Tour");
        this->window->titleLabel->adjustSize();

        this->window->titleLabel->move(this->window->width() / 2
                                           - this->window->titleLabel->width() / 2,
                                       this->velicinaPolja / 2
                                           - this->window->titleLabel->height() / 2);
        this->busy = true;

        this->matricaPolja[this->lokacija.x][this->lokacija.y]->slobodno = false;
        this->matricaPolja[this->lokacija.x][this->lokacija.y]->changeColor(true);
        this->slobodnihPolja--;
        delay(this->delaySpeed);

        Lokacija pocetnaPozicija = {this->lokacija.x, this->lokacija.y};

        PossibleMove bestMove;

        QString filename = "KnightTour.txt";
        QFile file(filename);

        QVector<QString> stringUpis;
        stringUpis.append("KnightTour Start");

        while (this->slobodnihPolja > 0) {
            QVector<PossibleMove> possibleMoves = checkPossibleMoves(this->lokacija.x,
                                                                     this->lokacija.y,
                                                                     this->lokacija.x,
                                                                     this->lokacija.y);

            if (possibleMoves.isEmpty()) {
                this->window->titleLabel->setText("Tour not found");
                this->window->titleLabel->adjustSize();

                this->window->titleLabel->move(this->window->width() / 2
                                                   - this->window->titleLabel->width() / 2,
                                               this->velicinaPolja / 2
                                                   - this->window->titleLabel->height() / 2);

                stringUpis.append("Tour Not Found");

                if (file.open(QIODevice::ReadWrite)) {
                    QTextStream stream(&file);
                    for (auto &str : stringUpis) {
                        stream << str << "\n";
                    }
                }
                this->busy = false;
                return;
            }

            for (auto &move : possibleMoves) {
                move.numOfMoves = checkPossibleMoves(move.possibleLoc.x,
                                                     move.possibleLoc.y,
                                                     this->lokacija.x,
                                                     this->lokacija.y)
                                      .count();
            }

            bestMove = possibleMoves[0];

            for (auto &move : possibleMoves) {
                if (move.numOfMoves < bestMove.numOfMoves) {
                    bestMove = move;
                }
            }

            stringUpis.append(getRed(lokacija.y) + QString::number(lokacija.x + 1) + "->"
                              + getRed(bestMove.possibleLoc.y)
                              + QString::number(bestMove.possibleLoc.x + 1));
            moveKnight(bestMove.possibleLoc.x, bestMove.possibleLoc.y);
            this->matricaPolja[bestMove.possibleLoc.x][bestMove.possibleLoc.y]->slobodno = false;
            this->matricaPolja[bestMove.possibleLoc.x][bestMove.possibleLoc.y]->changeColor(false);
            this->slobodnihPolja--;
            delay(this->delaySpeed);
        }

        // Cekirati closed-knight tour
        if (checkClosedKnightTour(pocetnaPozicija, bestMove)) {
            this->window->titleLabel->setText("Closed Knight Tour");
            moveKnight(pocetnaPozicija.x, pocetnaPozicija.y);
            stringUpis.append(getRed(bestMove.possibleLoc.y)
                              + QString::number(bestMove.possibleLoc.x + 1) + "->"
                              + getRed(pocetnaPozicija.y) + QString::number(pocetnaPozicija.x + 1));
            stringUpis.append("Closed Knight Tour");
        } else {
            this->window->titleLabel->setText("Open Knight Tour");
            stringUpis.append("Open Knight Tour");
        }
        this->window->titleLabel->adjustSize();

        this->window->titleLabel->move(this->window->width() / 2
                                           - this->window->titleLabel->width() / 2,
                                       this->velicinaPolja / 2
                                           - this->window->titleLabel->height() / 2);

        if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
            QTextStream stream(&file);
            for (auto &str : stringUpis) {
                stream << str << "\n";
            }
        }

        this->busy = false;
    }
}

QVector<PossibleMove> PoljaCont::checkPossibleMoves(int x, int y, int startPosX, int startPosY)
{
    QVector<PossibleMove> possibleMoves;

    const QVector<QPair<int, int>> offsets
        = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};

    for (const auto &offset : offsets) {
        int newX = x + offset.first;
        int newY = y + offset.second;

        if (newX >= 0 && newX < this->brojPolja && newY >= 0 && newY < this->brojPolja) {
            if (this->matricaPolja[newX][newY]->slobodno == true) {
                PossibleMove mov;

                mov.possibleLoc = {newX, newY};
                mov.numOfMoves = 0;

                possibleMoves.append(mov);
            }
        }
    }
    return possibleMoves;
}

void PoljaCont::reset()
{
    if (!busy) {
        this->slobodnihPolja = brojPolja * brojPolja;

        for (int i{}; i < brojPolja; i++) {
            for (int j{}; j < brojPolja; j++) {
                this->matricaPolja[i][j]->resetPolje();
            }
        }
    }
}

bool PoljaCont::checkClosedKnightTour(Lokacija poc, PossibleMove lastmove)
{
    QVector<PossibleMove> lastMoves;

    const QVector<QPair<int, int>> offsets
        = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};

    for (const auto &offset : offsets) {
        int newX = lastmove.possibleLoc.x + offset.first;
        int newY = lastmove.possibleLoc.y + offset.second;

        if (newX >= 0 && newX < this->brojPolja && newY >= 0 && newY < this->brojPolja) {
            PossibleMove mov;
            mov.possibleLoc = {newX, newY};
            mov.numOfMoves = 0;

            lastMoves.append(mov);
        }
    }

    for (const auto &move : lastMoves) {
        if (poc.x == move.possibleLoc.x && poc.y == move.possibleLoc.y) {
            return true;
        }
    }

    return false;
}

char PoljaCont::getRed(int numb)
{
    return 'A' + numb;
}
