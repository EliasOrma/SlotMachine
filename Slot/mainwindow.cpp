#include "mainwindow.hh"
#include "ui_mainwindow.h"

#include <QColor>
#include <QTime>
#include <stdlib.h> //rand
#include "dialogstart.hh"
#include <graphicsview.hh>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _scene = new QGraphicsScene(this);

    ui->graphicsView->setScene(_scene);
    _reels = new spinReel(_scene);

    _money = 0;
    _betIndex = 0;
    _currentBet = 0.2;
    _spinninggoing = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addMoney(double money)
{
    _money += money;
    ui->Cash->setText(QString::number(_money));
}

void MainWindow::spinWheels()
{
    if(_spinninggoing)
    {
        return;
    }
    else if(_money >= _currentBet)
    {
        _money -= _currentBet;
        ui->Cash->setText(QString::number(_money));

        // Spin
        _spinninggoing = true;
        double win = _reels->spin() * _currentBet;
        if(win == -1)
        {
            //Start bonusgame
        }
        else
        {
            addMoney(win);
        }
        _spinninggoing = false;
    }
    // If you try to play without enough money
    else
    {
        DialogStart dlog;
        if(dlog.exec() == QDialog::Rejected)
        {
            destroy();
        }
        else
        {
            addMoney(dlog.getMoney());
        }
    }
}

void MainWindow::changeBet()
{
    double bets [6] = {0.20,0.40,0.80,1.20,1.60,2.00};
    if(_betIndex != 5)
    {
        _betIndex++;
    }
    else
    {
        _betIndex = 0;
    }
    _currentBet = bets[_betIndex];

    ui->Bet->setText("Bet \n " + QString::number(bets[_betIndex]));
}
