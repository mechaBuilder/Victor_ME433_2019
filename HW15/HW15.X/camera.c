#include <xc.h>
#include "camera.h"
#include<math.h>


void LCDprintRow(unsigned short pixelArray, unsigned short colorRow, unsigned short colorBackground) {
    unsigned short i, j, pixel[240];
    for (i = 0; i <= 240; i++) {
        pixel[i] = pixelArray[i] >> 5;      //remove 5 least significant bits (keep 3 most significant bits), resolution
        for (j = 0; j <=7; j++) {
            
        }
        if (colorRow == ILI9341_RED) {
            
        }
    }
    
}

