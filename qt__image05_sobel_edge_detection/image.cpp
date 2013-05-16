// image.cpp
/*
 * @author: Lothar Rubusch
 * @date: 2013-may-16
 */

/*
  Given image in source place Sobel edges in dest.
  Grayscale sort of, with (255,255,255) as brightest edge.
  sobelDestination should be same size and depth as source.
*/
void sobel( QImage& source, QImage& sobelDestination )
{
        int GX[3][3];
        int GY[3][3];

        /* 3x3 GX Sobel mask.  Ref: www.cee.hw.ac.uk/hipr/html/sobel.html */
        GX[0][0] = -1; GX[0][1] = 0; GX[0][2] = 1;
        GX[1][0] = -2; GX[1][1] = 0; GX[1][2] = 2;
        GX[2][0] = -1; GX[2][1] = 0; GX[2][2] = 1;

        /* 3x3 GY Sobel mask.  Ref: www.cee.hw.ac.uk/hipr/html/sobel.html */
        GY[0][0] =  1; GY[0][1] =  2; GY[0][2] =  1;
        GY[1][0] =  0; GY[1][1] =  0; GY[1][2] =  0;
        GY[2][0] = -1; GY[2][1] = -2; GY[2][2] = -1;

        int width = source.width();
        int height = source.height();
        uint blackPixel = qRgb(0, 0, 0);
        uchar **jumper = source.jumpTable();
        uchar **destJumper = sobelDestination.jumpTable();

        int I, J;
        long sumX, sumY;
        int SUM;
        uint rawColour;

        for( int y = 0; y < height; ++y ){
                uint *p  = (uint*) jumper[y];
                uint *dp = (uint*) destJumper[y];
                for( int x = 0; x < width; ++x ){
                        if( y == 0
                            || y >= height-1
                            || x == 0
                            || x >= width-1 ){
                                SUM = 0;

                        }else{
                                sumX = 0;
                                sumY = 0;

                                /*-------X and Y GRADIENT APPROXIMATION------*/
                                for( I=-1; I<=1; I++ ){
                                        for( J=-1; J<=1; J++ ){
                                                rawColour = *((uint *)jumper[y + J] + x + I);
                                                sumX = sumX + ((qRed(rawColour) + qGreen(rawColour) + qBlue(rawColour))/3) * GX[I+1][J+1];
                                                sumY = sumY + ((qRed(rawColour) + qGreen(rawColour) + qBlue(rawColour))/3) * GY[I+1][J+1];
                                                //sumX = sumX +(int)( (*(originalImage.data + X + I + (Y + J)*originalImage.cols)) * GX[I+1][J+1]);
                                                //sumY = sumY + (int)( (*(originalImage.data + X + I + (Y + J)*originalImage.cols)) * GY[I+1][J+1]);
                                        }
                                }
                                SUM = abs(sumX) + abs(sumY); /*---GRADIENT MAGNITUDE APPROXIMATION (Myler p.218)----*/
                                if (SUM > 255)
                                        SUM = 255;

                        }
                        *dp = qRgb( SUM, SUM, SUM );
                        ++p;
                        ++dp;
                }
        }
}


int main( int argc, char *argv[] ){
