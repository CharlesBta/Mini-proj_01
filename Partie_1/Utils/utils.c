#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

PixelMap* createPixelMap(int largeur, int hauteur, int maxval)
{
    PixelMap* pixelMap = (PixelMap*)malloc(sizeof(PixelMap));
    if (pixelMap == NULL) {
        return NULL; 
    }

    snprintf(pixelMap->format, sizeof(pixelMap->format), "P6");
    snprintf(pixelMap->largeur, sizeof(pixelMap->largeur), "%d", largeur);
    snprintf(pixelMap->hauteur, sizeof(pixelMap->hauteur), "%d", hauteur);
    snprintf(pixelMap->maxval, sizeof(pixelMap->maxval), "%d", maxval);

    pixelMap->pixels = (Pixel*)malloc(largeur * hauteur * sizeof(Pixel));
    if (pixelMap->pixels == NULL) {
        free(pixelMap);
        return NULL; 
    }

    return pixelMap;
}

void freePixelMap(PixelMap* pixelMap){
    if (pixelMap != NULL) {
        free(pixelMap->pixels);
        free(pixelMap);
    }
}

void writePixelMapToFile(const char* filename, const PixelMap* pixelMap){
    FILE* fichier = fopen(filename, "wb");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }
    fprintf(fichier, "%s\n", pixelMap->format);
    fprintf(fichier, "%s %s\n", pixelMap->largeur, pixelMap->hauteur);
    fprintf(fichier, "%s\n", pixelMap->maxval);
    int largeur = atoi(pixelMap->largeur);
    int hauteur = atoi(pixelMap->hauteur);
    fwrite(pixelMap->pixels, sizeof(Pixel), largeur * hauteur, fichier);
    fclose(fichier);
}

void setPixelToPixelMap(PixelMap* pixelMap, unsigned char r, unsigned char g, unsigned char b)
{
    int largeur = atoi(pixelMap->largeur);
    int hauteur = atoi(pixelMap->hauteur);
    for (int i = 0; i < largeur * hauteur; i++) {
        pixelMap->pixels[i].r = r;
        pixelMap->pixels[i].g = g;
        pixelMap->pixels[i].b = b;
    }
}

void drowCircle(PixelMap* pixelMap, int centerX, int centerY, int radius, unsigned char r, unsigned char g, unsigned char b){
    int dx = 0;
    int dy = 0;
    int largeur = atoi(pixelMap->largeur);
    int hauteur = atoi(pixelMap->hauteur);
    for (int y = 0; y < hauteur; y++) {
        for (int x = 0; x < largeur; x++) {
            dx = x - centerX;
            dy = y - centerY;
            if (dx * dx + dy * dy <= radius * radius) {
                int index = y * largeur + x;
                pixelMap->pixels[index].r = r;
                pixelMap->pixels[index].g = g;
                pixelMap->pixels[index].b = b;
            }
        }
    }
}