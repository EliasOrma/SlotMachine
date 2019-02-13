#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QGraphicsScene>
#include <map>
#include <QGraphicsPixmapItem>

#include <spinreel.hh>
#include <spinnerpicitem.hh>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void addMoney(double money);

private slots:
    void spinWheels();
    void changeBet();

private:
    Ui::MainWindow *ui;

    QGraphicsScene *_scene;
    spinReel *_reels;

    void setUpBoard();

    QString getPicPath(int index);
    int getIndex();

    double _money;
    double _currentBet;
    int _betIndex;

    bool _spinninggoing; // Flag for spinning.
};

#endif // MAINWINDOW_HH
