// main.cpp

#include "PlotterFrame.h"
#include <QApplication>

int main(int argc, char **argv)
{
  QApplication app(argc, argv);
  PlotterFrame frame;
  frame.show();
  return app.exec();
}
