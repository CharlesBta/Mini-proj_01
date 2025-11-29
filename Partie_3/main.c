#include <stdio.h>
#include "./Utils/utils.h"

int main() {
    double x_min = X_MIN;
    double y_min = Y_MIN;
    double x_max = X_MAX;
    double y_max = Y_MAX;

    // Création d'une image 
    PixelMap* pixelMap = createPixelMap(LARGEUR, HAUTEUR, MAXVAL);
    if (pixelMap == NULL) {
        fprintf(stderr, "Erreur lors de la création de la PixelMap\n");
        return 1;
    }

    for (int i = 0; i < 10; i++) {
        x_min = x_min + (TARGET_X - x_min) * 0.2;  
        y_min = y_min + (TARGET_Y - y_min) * 0.2;
        x_max = x_max + (TARGET_X - x_max) * 0.2;
        y_max = y_max + (TARGET_Y - y_max) * 0.2;

        drawMandelbrot(pixelMap, 0, 0, x_min, x_max, y_min, y_max);
        char filename[20];
        snprintf(filename, sizeof(filename), "image_%02d.ppm", i);
        writePixelMapToFile(filename, pixelMap);
    }
    
    freePixelMap(pixelMap);
    return 0;
}

