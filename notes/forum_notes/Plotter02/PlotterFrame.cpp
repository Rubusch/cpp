// PlotterFrame.cpp

#include <QtGui>

#include <iostream>

#include "Plotter.h"
#include "PlotterFrame.h"


PlotterFrame::PlotterFrame() { initGUI(); };


void PlotterFrame::initGUI()
{
  std::cout << "initGUI()\n";
  setWindowTitle(QObject::tr("Plotter"));
  leX = new QLineEdit();
  leY = new QLineEdit();
  QHBoxLayout *loCoords = new QHBoxLayout;
  loCoords->addWidget(leX);
  loCoords->addWidget(leY);
  btAccept = new QPushButton(QObject::tr("Accept"));
  connect(btAccept, SIGNAL(clicked()), this, SLOT(slotAccept()));
  pnPlotter = new Plotter();
  QVBoxLayout *loMain = new QVBoxLayout;
  loMain->addLayout(loCoords);
  loMain->addWidget(btAccept);
  loMain->addWidget(pnPlotter);
  setCentralWidget(new QWidget());
  centralWidget()->setLayout(loMain);
};


void PlotterFrame::slotAccept()
{
  std::cout << "slotAccept()\n";
  QString szX = "";
  QString szY = "";

  szX = leX->text();
  if (szX.isEmpty())
    szX = "0.0";

  szY = leY->text();
  if (szY.isEmpty())
    szY = "0.0";

  std::cout << "X: " << szX.toStdString() << ", Y: " << szY.toStdString()
            << "\n";
  pnPlotter->addPoint(szX.toDouble(), szY.toDouble());
};
