#include "spinnerpicitem.hh"

spinnerPicItem::spinnerPicItem(QPixmap pic, int picIndex)
{
    changePic(pic,picIndex);
}

void spinnerPicItem::changePic(QPixmap pic, int newIndex)
{
    this->setPixmap(pic);
    _picIndex = newIndex;
}

int spinnerPicItem::getIndex()
{
    return _picIndex;
}
