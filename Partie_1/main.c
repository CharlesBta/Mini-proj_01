#include <stdio.h>
#include <stdlib.h>

#include "./Utils/utils.h"

#define LARGEUR 600
#define HAUTEUR 400
#define MAXVAL 255

#define CENTER_X (LARGEUR / 2)
#define CENTER_Y (HAUTEUR / 2)
#define RADIUS 200

int main() {
    // Création d'une image unie
    PixelMap* pixelMap = createPixelMap(LARGEUR, HAUTEUR, MAXVAL);
    if (pixelMap == NULL) {
        fprintf(stderr, "Erreur lors de la création de la PixelMap\n");
        return 1;
    }

    setPixelToPixelMap(pixelMap, 0, 0, 255); 
    writePixelMapToFile("image.ppm", pixelMap);
    freePixelMap(pixelMap);

    // Création d'une image avec un cercle
    PixelMap* pixelMapCircle = createPixelMap(LARGEUR, HAUTEUR, MAXVAL);
    if (pixelMapCircle == NULL) {
        fprintf(stderr, "Erreur lors de la création de la PixelMap\n");
        return 1;
    }
    setPixelToPixelMap(pixelMapCircle, 0, 255, 255); 
    drowCircle(pixelMapCircle, CENTER_X, CENTER_Y, RADIUS, 255, 100, 255); 
    writePixelMapToFile("circle.ppm", pixelMapCircle);
    freePixelMap(pixelMapCircle);

    return 0;
}