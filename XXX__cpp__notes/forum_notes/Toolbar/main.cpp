// main.cpp

#include "Toolbar.hpp"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    Toolbar* toolbar = new Toolbar();
    toolbar->show();
    return app.exec();
};
