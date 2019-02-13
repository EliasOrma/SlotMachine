#ifndef GRAPHICSVIEW_HH
#define GRAPHICSVIEW_HH

#include <QGraphicsView>

class GraphicsView : public QGraphicsView
{
public:
    GraphicsView(QWidget *parent);
protected:
    void scrollContentsBy(int, int) override;
};

#endif // GRAPHICSVIEW_HH
