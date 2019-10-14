// PlotterFrame.h

#ifndef PLOTTERFRAME
#define PLOTTERFRAME

#include <QtGui>

class Plotter;
class PlotSettings;


class PlotterFrame : public QMainWindow
{
  Q_OBJECT

private slots:
  void slotAccept();

private:
  Plotter *pnPlotter;
  QLineEdit *leX;
  QLineEdit *leY;
  QPushButton *btAccept;

  void initGUI();

public:
  PlotterFrame();
  ~PlotterFrame(){};
};
#endif
