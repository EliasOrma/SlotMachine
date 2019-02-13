#ifndef SPINNERPICITEM_HH
#define SPINNERPICITEM_HH

#include <QGraphicsPixmapItem>


class spinnerPicItem : public QGraphicsPixmapItem
{
public:
    spinnerPicItem(QPixmap pic, int picIndex);
    void changePic(QPixmap pic,int newIndex);
    int getIndex();
private:
    int _picIndex;
};

#endif // SPINNERPICITEM_HH
