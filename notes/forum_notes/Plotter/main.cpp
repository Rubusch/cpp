#include <QtGui>

#include "plotter.h"

void readFlightCurves(Plotter *plotter, const QString &fileName)
{
  // list of points (float)
  QVector< QPointF > data[6];

  // ???
  double factX = 0.0013;

  // ???
  double factY[6] = {0.0008, 0.1, 0.2, 0.2, 0.1, 0.8};

  // ???
  double offsY[6] = {+500, -55, +309, +308, 0, 0};

  // ???
  int pos[6] = {3, 6, 7, 8, 9, 10};

  // txt file containing the data
  QFile file(fileName);

  // ???
  double offsX = 0.0;

  if (file.open(QIODevice::ReadOnly)) {
    QTextStream in(&file);
    while (!in.atEnd()) {
      QString line = in.readLine();
      QStringList coords = line.split(' ', QString::SkipEmptyParts);
      if (coords.count() >= 6) {

        // load point
        double x = factX * coords[0].toDouble();
        if (data[0].isEmpty())
          offsX = x;
        for (int i = 0; i < 6; ++i) {
          double y = coords[pos[i]].toDouble();
          data[i].append(QPointF(x - offsX, factY[i] * (y - offsY[i])));
        }
      }
    }
  }


  // set curve
  plotter->setCurveData(0, data[0]);
  plotter->setCurveData(1, data[1]);
  plotter->setCurveData(2, data[2]);
  plotter->setCurveData(3, data[3]);
  plotter->setCurveData(4, data[4]);
  plotter->setCurveData(5, data[5]);
}

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  Plotter plotter;
  plotter.setWindowTitle(QObject::tr("Plotter"));

  // function above - set data and paint plotter curves
  readFlightCurves(&plotter, "in1.txt");

  plotter.show();
  return app.exec();
}
