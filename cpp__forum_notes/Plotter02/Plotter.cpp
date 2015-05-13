// Plotter.cpp

#include "Plotter.h"

#include <iostream>
using namespace std;


Plotter::Plotter()
{
//    cout << "Plotter()\n"; // TODO rm    
    init();

    QVector< QPointF > vec;
    for(int idx = -5; idx <= 5; ++idx) 
        vec.append(QPointF((qreal) idx, (qreal) idx));

    setCurveData(vec);
};


void Plotter::init()
{
//    cout << "init()\n"; // TODO rm
    setBackgroundRole(QPalette::Dark);
    setAutoFillBackground(true);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setFocusPolicy(Qt::NoFocus);
    curveData.clear();
};


void Plotter::initPlotSettings()
{
//    cout << "initPlotSettings()\n"; // TODO rm
    if(curveData.isEmpty()) return;
    if(settings == 0) settings = new PlotSettings();
    
    qreal minX = curveData.at(0).x();
    qreal maxX = curveData.at(0).x();
    qreal minY = curveData.at(0).y();
    qreal maxY = curveData.at(0).y();
    if(curveData.size() <2){
        // nothing
    }else{
        for(int idx = 1; idx < curveData.size(); ++idx){
            minX = qMin(minX, curveData.at(idx).x());
            maxX = qMax(maxX, curveData.at(idx).x());
            minY = qMin(minY, curveData.at(idx).y());
            maxY = qMax(maxY, curveData.at(idx).y());
        }
    }    

    double extension = 0.1;
    double spanX = maxX - minX;
    settings->minX = minX - (extension * spanX);
    settings->maxX = maxX + (extension * spanX);
    settings->spanX = spanX + spanX * (2 * extension);
    settings->numXTicks = 10;
    double spanY = maxY - minY;    
    settings->minY = minY - (extension * spanY);
    settings->maxY = maxY + (extension * spanY);
    settings->spanY = spanY + spanY * (2 * extension);
    settings->numYTicks = 10;
/* DEBUG
    cout << "settings:\n"
         << "\tspanX = " << settings->spanX << "\n"
         << "\tminX = " << settings->minX << "\n"
         << "\tmaxX = " << settings->maxX << "\n"
         << "\tnumXTicks = " << settings->numXTicks << "\n"
         << "\tspanY = " << settings->spanY << "\n"
         << "\tminY = " << settings->minY << "\n"
         << "\tmaxY = " << settings->maxY << "\n"
         << "\tnumYTicks = " << settings->numYTicks << "\n";
//*/
    // size of the widget
    setMinimumWidth(((settings->numXTicks+1) * Margin) 
                    + (2 * Margin) 
                    - settings->numXTicks); // FIXME
    setMinimumHeight(((settings->numYTicks+1) * Margin) 
                     + (2 + Margin) 
                     - settings->numYTicks); // FIXME

    refreshPixmap();
};


void Plotter::setCurveData(QVector< QPointF > &data)
{
//    cout << "setCurveData()\n"; // TODO rm
    if(!curveData.isEmpty()) clearCurve();
    curveData = data;
    initPlotSettings();
};


void Plotter::clearCurve()
{
//    cout << "clearCurve()\n"; // TODO rm
    curveData.clear();
    refreshPixmap();
};


void Plotter::paintEvent(QPaintEvent* /*event*/)
{
//    cout << "paintEvent()\n"; // TODO rm
    QStylePainter painter(this);
    painter.drawPixmap(0, 0, pixmap);
};


void Plotter::refreshPixmap()
{
//    cout << "refreshPixmap()\n"; // TODO rm    
    pixmap = QPixmap(size());
    pixmap.fill(this, 0, 0);

    QPainter painter(&pixmap);
    painter.initFrom(this);
    drawGrid(&painter);

    // painting
    QRect rect(Margin, Margin, width() - 2 * Margin, height() - 2 * Margin);
//    drawCurve(&painter, rect);
    drawPoints(&painter, rect);
//    drawPoint(&painter, rect, 0, 3);
    update();
};


void Plotter::drawGrid(QPainter *painter)
{
    // Margin = 50
//    cout << "drawGrid()\n"; // TODO rm
//    cout << "Margin: " << Margin << "\n";
    
    // widget's main rect
    QRect rect(Margin, Margin, width() - 2 * Margin, height() - 2 * Margin);
    if (!rect.isValid()) return;

    QPen quiteDark = palette().dark().color().light();
    QPen light = palette().light().color();

    // X-axis
      for(int i = 0; i <= settings->numXTicks; ++i){
        int x = rect.left() + (i * (rect.width() - 1) / settings->numXTicks);
        double label = settings->minX + (i * settings->spanX / settings->numXTicks);
//        cout << "label = " << label << ", x = " << x << ", i = " << i << "\n"; // TODO rm

        // back
        painter->setPen(quiteDark);
        painter->drawLine(x, rect.top(), x, rect.bottom());

        // front
        painter->setPen(light);
        painter->drawLine(x, rect.bottom(), x, rect.bottom() + 5);
        painter->drawText(x - 50, rect.bottom() + 5, 100, 15
                          , Qt::AlignHCenter | Qt::AlignTop
                          , QString::number(label));
    }

    // Y-axis
    for(int j = 0; j <= settings->numYTicks; ++j){
        int y = rect.bottom() - (j * (rect.height() - 1) / settings->numYTicks);
        double label = settings->minY + (j * settings->spanY / settings->numYTicks);
//        cout << "label = " << label << ", y = " << y << ", j = " << j << "\n"; // TODO rm

        // back
        painter->setPen(quiteDark);
        painter->drawLine(rect.left(), y, rect.right(), y);

        // front
        painter->setPen(light);
        painter->drawLine(rect.left() - 5, y, rect.left(), y);
        painter->drawText(rect.left() - Margin, y - 10, Margin - 5, 20
                          , Qt::AlignRight | Qt::AlignVCenter
                          , QString::number(label));
    }
    painter->drawRect(rect.adjusted(0, 0, -1, -1));
};


void Plotter::drawCurve(QPainter *painter, QRect rect)
{
//    cout << "drawCurve()\n"; // TODO rm
    static const QColor curveColor = Qt::red;
    if(!rect.isValid()) return;
    painter->setClipRect(rect.adjusted(+1, +1, -1, -1));

//* draw line
    QPolygonF polyline(curveData.size());
    for (int j = 0; j < curveData.count(); ++j) {
        double dx = curveData[j].x() - settings->minX;
        double dy = curveData[j].y() - settings->minY;
        double x = rect.left() + (dx * (rect.width() - 1) / settings->spanX);
        double y = rect.bottom() - (dy * (rect.height() - 1) / settings->spanY);
        polyline[j] = QPointF(x, y);
    }
    painter->setPen(curveColor);
    painter->drawPolyline(polyline);
//*/
};


void Plotter::drawPoints(QPainter *painter, QRect rect)
{
    for (int j = 0; j < curveData.count(); ++j) {
        drawPoint(painter, rect, curveData.at(j).x(), curveData.at(j).y());
    }
};


void Plotter::drawPoint(QPainter *painter, QRect rect, const double xCoord, const double yCoord)
{
    static const QColor curveColor = Qt::red;
    if(!rect.isValid()) return;
    painter->setClipRect(rect.adjusted(+1, +1, -1, -1));

    // draw Points
    painter->setPen(curveColor);
    double dx = xCoord - settings->minX;
    double dy = yCoord - settings->minY;
    double x = rect.left() + (dx * (rect.width() - 1) / settings->spanX);
    double y = rect.bottom() - (dy * (rect.height() - 1) / settings->spanY);
    painter->setBrush(QBrush(curveColor));
    painter->drawEllipse( x-2, y-2, 4, 4);
};


void Plotter::addPoint(double x, double y)
{
    curveData.append(QPointF(x,y));
    QVector< QPointF > vec = curveData;
    clearCurve();
    setCurveData(vec);
    initPlotSettings();
};
