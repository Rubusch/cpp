// image.cpp
/*
 * @author: Lothar Rubusch
 * @date: 2013-May-16
 */
#include <QtGui>
#include <QtCore>
#include <QCoreApplication>

int main(int argc, char *argv[])
{
        // qt settings
        QApplication app( argc, argv );

        // 1) read image: init png
        QImage png_orig( "a09_gray.png" );
        QImage png = png_orig.convertToFormat( QImage::Format_RGB32 );


        // 2) preparation: set information to png
        for( int ycoord = 0; ycoord < png.height(); ++ycoord ){
                for( int xcoord = 0; xcoord < png.width(); ++xcoord ){

                        // Returns the color of the pixel at the given position.
                        int pixel = png.pixel( xcoord, ycoord );

                        //  Returns a gray value (0 to 255) from the (r, g, b) triplet.
                        //  The gray value is calculated using the formula (r * 11 + g * 16 + b * 5)/32.
                        int gray  = qGray( pixel );

                        // filter black pieces, and invert colors
                        if( 12 > gray ){ gray = 255-gray; }
                        else{ gray = 0; }

                        // Returns the alpha component of the ARGB quadruplet rgba
                        int alpha = qAlpha( pixel );

                        // Sets the pixel index or color at the given position to index_or_rgb.
                        png.setPixel( xcoord, ycoord, qRgba( gray, gray, gray, alpha ) );
                }
        }

        // 3) init result: set up a png_new by png data
        QPixmap png_new( png.width(), png.height() );
        png_new.fill();


        // 4) operation: write png_new
        QPainter painter;
        // init painter with png_new (where the result will be)
        painter.begin( &png_new );
        // can be set also - the render hint for the painter
        painter.setRenderHint( QPainter::Antialiasing );
        painter.drawImage( 0, 0, png );
        painter.end();

        // 6) save
        png_new.save( "a09_threshold_black.png" );

        // 5) display image
        QLabel *label = new QLabel();
        label->setPixmap( png_new );
        label->show();
        return app.exec();
};
