// main.cpp

#include <QApplication>
#include "PlotterFrame.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    PlotterFrame frame;
    frame.show();
    return app.exec();
}
