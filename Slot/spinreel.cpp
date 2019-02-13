#include "spinreel.hh"

spinReel::spinReel(QGraphicsScene *scene) : _scene(scene)
{
    init();
}

void spinReel::init()
{
    // Places for lines calculated from positions of images
    for(int i = 0; i < 3; i++)
    {
        QLine line(0,60+115*i,4000,60+115*i);
        _scene->addLine(line);
    }
    QLine line1(61,60,351,290);
    _scene->addLine(line1);

    QLine line2(61,290,351,60);
    _scene->addLine(line2);

    QLine line3(353,60,621,290);
    _scene->addLine(line3);

    QLine line4(351,290,621,60);
    _scene->addLine(line4);

    int startingIndex = 3; // Diamonds index
    QString pic = getPicPath(startingIndex);

    // Makes images to vector and inits the board.
    for(int x = 0; x < 5; x++)
    {
        std::vector<spinnerPicItem*> innerVec;
        for(int y = 0; y < 4; y++)
        {
            spinnerPicItem *item = new spinnerPicItem(pic,startingIndex);
            item->setScale(0.22);
            item->setPos(10 + 140*x,10 + 115 * y);
            innerVec.push_back(item);
            _scene->addItem(item);
        }
        picVec.push_back(innerVec);
        _lockList.push_back(false);
    }
}

double spinReel::spin()
{
    // Pics are 512x512 (*0.22)
    int roundIndex = 0;
    // Amount of steps that it takes to spin one reel round
    int roundTime = 460;
    // Spin all reels and lock them.
    for(int movement = 0; movement != 6*roundTime; movement++)
    {
        // Locks the reels in spesific amount of rounds spinned
        if(movement == (roundIndex+1)*roundTime)
        {
            _lockList[roundIndex] = true;
            roundIndex++;
        }
        // Iterates trough every Image position
        for(int i = (int)picVec.size() - 1; i >= 0; i--)
        {
            // Doesnt move the reel or iterate trough the images in it if the reel is locked
            if(_lockList[i] != true)
            {
                // For one column
                for(int j = (int)picVec[i].size() - 1; j >= 0; j--)
                {
                    // Moves one picture at the time
                    picVec[i][j]->moveBy(0,1);

                    // Moves picture back up if it is out of sight. Also changes to a new icon.
                    if(picVec[i][j]->pos().y() > 355)
                    {
                        int newIndex = getIndex();
                        picVec[i][j]->changePic(getPicPath(newIndex),newIndex);
                        picVec[i][j]->moveBy(0,-460);
                    }
                }
            }
        }
        // Function waits one millisecond before another iteration to create animation.
        wait();
    }
    // Opens every reel
    for(int i = 0; i !=  (int) _lockList.size(); i++)
    {
        _lockList[i] = false;
    }
    return getwinnings();
}

QString spinReel::getPicPath(int index)
{
    if(index == 0){return R"(:/kuvat/strawberry.png)";}
    else if(index == 1){return R"(:/kuvat/cherry.png)";}
    else if(index == 2){return R"(:/kuvat/cherries.png)";}
    else if(index == 3){return R"(:/kuvat/diamond.png)";}
    else if(index == 4){return R"(:/kuvat/bigwin.png)";}
    else if(index == 5){return R"(:/kuvat/jackpot.png)";}
    else {return R"(:/kuvat/slot-machine.png)";}
}

void spinReel::wait()
{
    // For freezing the program for one ms. Used for spinning reels animation
    QTime waitTime = QTime::currentTime().addMSecs(1);
    while (QTime::currentTime() < waitTime)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

double spinReel::getWinAmount(int inrow, int index)
{
    // Calculates winnings (multiplier) later on the real
    // win amount is calculated in mainwindow
    double indexMultiplier [7] = {0.25,0.25,0.5,1,2,5,1};
    return ((double) inrow * indexMultiplier[index]);
}

bool spinReel::checkBonus()
{
    //TODO
    return false;
}

double spinReel::countfromreels()
{
    int lastIndex;
    int depth;
    double totalWin = 0;

    // Checks every row for winnings and calls getWin Amount to calulate the win if needed
    // Iterates every row
    for(int y = 0; y < 3; y++)
    {
        int depth = 1;
        lastIndex = picVec[0][y]->getIndex();

        // Iterates every picitem from one column
        for(int x = 1; x < 5; x++)
        {
            // If the icon doesnt have the same value than the last one
            // Iteration is stopped and winnngs are calculated and added to totalwin
            if(picVec[x][y]->getIndex() != lastIndex)
            {
                if(depth > 1)
                {
                    totalWin += getWinAmount(depth,lastIndex);
                }
                break;
            }
            else
            {
                depth++;
            }
        }
    }

    int ind_down [5] = {0,1,2,1,0};
    int ind_up [5] = {2,1,0,1,2};
    int last_down = picVec[0][ind_down[0]]->getIndex();
    int last_up = picVec[0][ind_up[0]]->getIndex();
    depth = 1;
    // Iterates from top left to center and from center to top right
    // and calls getWin Amount to calulate the win if needed
    for(int x = 1; x < 5; x++)
    {
        // If the icon doesnt have the same value than the last one
        // Iteration is stopped and winnngs are calculated and added to totalwin
        if(picVec[x][ind_down[x]]->getIndex() != last_down)
        {
            if(depth > 1)
            {
                totalWin += getWinAmount(depth,last_down);
            }
            break;
        }
        else
        {
            depth++;
        }
    }

    depth = 1;
    // Iterates from bottom left to center and from center to bottom right
    // and calls getWin Amount to calulate the win if needed
    for(int x = 1; x < 5; x++)
    {
        // If the icon doesnt have the same value than the last one
        // Iteration is stopped and winnngs are calculated and added to totalwin
        if(picVec[x][ind_up[x]]->getIndex() != last_up)
        {
            if(depth > 1)
            {
                totalWin += getWinAmount(depth,last_up);
            }
            break;
        }
        else
        {
            depth++;
        }
    }
    return totalWin;
}

double spinReel::getwinnings()
{
    if(checkBonus())
    {
        return -1;
    }
    else
    {
        return countfromreels();
    }
}

int spinReel::getIndex()
{
    int randomGen = rand() % 100 + 1;
    int randomIndex;
    if(randomGen < 20){randomIndex = 0;}
    else if(randomGen < 40){randomIndex = 1;}
    else if(randomGen < 60){randomIndex = 2;}
    else if(randomGen < 80){randomIndex = 3;}
    else if(randomGen < 90){randomIndex = 4;}
    else if(randomGen < 95){randomIndex = 5;}
    else {randomIndex = 6;}
    return randomIndex;
}
