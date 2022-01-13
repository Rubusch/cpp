// Plotter.h
#ifndef PLOTTER
#define PLOTTER

#include <QtGui>


struct PlotSettings {
  double spanX;
  double spanY;
  double minX;
  double maxX;
  int numXTicks;
  double minY;
  double maxY;
  int numYTicks;

  PlotSettings()
  {
    minX = 0.0;
    maxX = 10.0;
    numXTicks = 5;
    minY = 0.0;
    maxY = 10.0;
    numYTicks = 5;
  };
};


class Plotter : public QWidget
{
  enum { Margin = 50 };
  QPixmap pixmap;
  QVector< QPointF > curveData;
  PlotSettings *settings;

  void init();
  void initPlotSettings();
  void refreshPixmap();
  void paintEvent(QPaintEvent *);
  void drawGrid(QPainter *);
  void drawCurve(QPainter *, QRect);
  void drawPoints(QPainter *, QRect);
  void drawPoint(QPainter *, QRect, double, double);
  void clearCurve();

public:
  Plotter();
  ~Plotter(){};

  void setCurveData(QVector< QPointF > &);
  void addPoint(double, double);
};
#endif
