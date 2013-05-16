// sobel edge detection
#include "qimagehandler.h"

 

QImageHandler::QImageHandler(QImage *image) : m_Image(image)

{

  this->start();

}

 

QImageHandler::~QImageHandler()

{

  delete m_Image;

  this->quit();

  this->wait();

}

 

 

void QImageHandler::run()

{

  qDebug() << "thread id " << (int) QThread::currentThreadId();

 

  quint32 kernelSize = 3;

  qint32 kern = (kernelSize-1)/2.0;

  quint32 r1=0, r2=0, g1=0, g2=0, b1=0, b2=0;

 

  int kernelx[] = {-1,0,1,-2,0,2,-1,0,1};

  int kernely[] = {-1,-2,-1,0,0,0,1,2,1};

 

  quint8 z=0, r=0, g=0, b=0;

 

  m_Image->convertToFormat(QImage::Format_ARGB32);

 

  QRgb *peekScanLine;

  QImage result(m_Image->width(), m_Image->height(), m_Image->format());

  QPoint point;

 

  for (quint32 y = kern; y < m_Image->height() - kern; ++y) {

    for (quint32 x = kern; x < m_Image->width() - kern; ++x) {

      for(qint32 ky = -kern; ky <= kern; ++ky) {

        // Could be optimized by keeping scanlines in memory and

        // not calling scanLine ky times for each pixel

        peekScanLine = (QRgb *)m_Image->scanLine(y+ky);

 

        for(qint32 kx = -kern; kx <= kern; ++kx) {

          r1 += kernelx[z] * qRed(peekScanLine[x+kx]);

          g1 += kernelx[z] * qGreen(peekScanLine[x+kx]);

          b1 += kernelx[z] * qBlue(peekScanLine[x+kx]);

 

          r2 += kernely[z] * qRed(peekScanLine[x+kx]);

          g2 += kernely[z] * qGreen(peekScanLine[x+kx]);

          b2 += kernely[z] * qBlue(peekScanLine[x+kx]);

 

          z++;

        }

      }

 

      r = abs(r1) + abs(r2);

      g = abs(g1) + abs(g2);

      b = abs(b1) + abs(b2);

 

      r1=0, r2=0, g1=0, g2=0, b1=0, b2=0, z=0;

 

      point.setX(x);

      point.setY(y);

 

      result.setPixel(point, qRgba(r,g,b,255));

    }

  }

 

  *m_Image = result.copy(0,0, result.width(), result.height());

  emit manipulationDone();

}

// TODO
