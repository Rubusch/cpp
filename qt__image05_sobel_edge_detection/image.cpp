// image.cpp
/*
 * @author: Lothar Rubusch
 * @date: 2013-may-16
 */

#include <QtGui>
#include <QtCore>
#include <QCoreApplication>

/*
 * resources:
 * Jeremy Fix, http://jeremy.fix.free.fr/spip.php?article21
 * Ken Earle, http://www.dewtell.com/code/cpp/sobel.htm
 * http://blog.moblivion.net/2011/02/05/3-channel-sobel-operator-in-qt/
 * http://en.wikipedia.org/wiki/Sobel_operator
 */
void sobel( QImage& image )
{
        // init
        int xsum, ysum, SUM = 0;

        // sobel matrix
        QGenericMatrix< 3, 3, int > GX, GY;

        GX(0,0) = -1; GX(0,1) = 0; GX(0,2) = 1;
        GX(1,0) = -2; GX(1,1) = 0; GX(1,2) = 2;
        GX(2,0) = -1; GX(2,1) = 0; GX(2,2) = 1;

        GY(0,0) =  1; GY(0,1) = 2; GY(0,2) = 1;
        GY(1,0) =  0; GY(1,1) = 0; GY(1,2) = 0;
        GY(2,0) = -1; GY(2,1) = -2; GY(2,2) = -1;

        // apply
        for( int ycoord=0; ycoord < image.height(); ycoord++ ){
                for( int xcoord=0; xcoord < image.width(); xcoord++ ){
                        xsum = 0;
                        ysum = 0;
                        if( ycoord == 0
                            || ycoord == image.height()-1
                            || xcoord == 0
                            || xcoord == image.width() - 1
                          ){
                                // outside
                                SUM = 0;
                        }else{
                                // inside - apply algorithm
                                for( int idx=-1; idx<=1; idx++ ){
                                        for( int jdx=-1; jdx<=1; jdx++ ){

                                                QRgb currentPixel = image.pixel( QPoint( jdx + xcoord, idx + ycoord ) );

                                                int NC = ( qRed( currentPixel )
                                                           + qGreen( currentPixel )
                                                           + qBlue( currentPixel )
                                                        ) / 3;

                                                xsum = xsum + (NC) * GX(jdx+1, idx+1);
                                                ysum = ysum + (NC) * GY(jdx+1, idx+1);
                                        }
                                }
                                SUM = abs(xsum) + abs(ysum);
                        }

                        // borders
                        if(SUM > 255) SUM=255;
                        if(SUM < 0) SUM=0;

                        // invert
                        int newPixel = (255 - (uchar) (SUM) );

                        // draw pixel
                        image.setPixel( xcoord, ycoord, qRgb( newPixel, newPixel, newPixel ) );
                }
        }
}


int main( int argc, char *argv[] ){
        QApplication app( argc, argv );

//        QImage png_orig( "a09_threshold_white.png" );
        QImage png_orig( "a09_threshold_black.png" );
        QImage png = png_orig.convertToFormat( QImage::Format_RGB32 );

        // do the sobel..
        sobel( png );

        // save
// TODO
//        png_new.save( "a09_gray.png" );

        // display image
        // ..back from QPixmap to QImage: pixmap.toImage()
        QPixmap png_res( png.width(), png.height() );
        png_res.fill();
        QPainter painter;
        painter.begin( &png_res );
        painter.drawImage( 0, 0, png );
        painter.end();

        QLabel *label = new QLabel();
        label->setPixmap( png_res );
        label->show();
        return app.exec();
};
