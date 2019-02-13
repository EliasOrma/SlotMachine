#ifndef SPINREEL_HH
#define SPINREEL_HH

#include <QGraphicsScene>
#include <QTime>
#include <QCoreApplication>
#include <QEventLoop>

#include <spinnerpicitem.hh>

class spinReel
{
public:
    spinReel(QGraphicsScene *scene);

    // spins and returns amount of winnings
    double spin();
private:
    void init();
    int getIndex();
    QString getPicPath(int index);
    void wait();

    int useWinRecursion();
    int calculateWin(int x, int y,int depth, int lastIndex);
    double getWinAmount(int inrow,int index);
    bool checkBonus();
    double countfromreels();

    // returns -1 if bonusgame is started
    double getwinnings();

    QGraphicsScene *_scene;


    std::vector<std::vector<spinnerPicItem*>> picVec;
    std::vector<bool> _lockList; // List for locking reels
};

#endif // SPINREEL_HH
