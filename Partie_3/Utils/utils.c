#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

#define MAX_ITER 85

PixelMap *createPixelMap(int largeur, int hauteur, int maxval)
{
    PixelMap *pixelMap = (PixelMap *)malloc(sizeof(PixelMap));
    if (pixelMap == NULL)
    {
        return NULL;
    }

    snprintf(pixelMap->format, sizeof(pixelMap->format), "P6");

    pixelMap->largeur = largeur;
    pixelMap->hauteur = hauteur;
    pixelMap->maxval = maxval;

    pixelMap->pixels = (Pixel *)malloc(largeur * hauteur * sizeof(Pixel));
    if (pixelMap->pixels == NULL)
    {
        free(pixelMap);
        return NULL;
    }

    return pixelMap;
}

void freePixelMap(PixelMap *pixelMap)
{
    if (pixelMap != NULL)
    {
        free(pixelMap->pixels);
        free(pixelMap);
    }
}

void writePixelMapToFile(const char *filename, const PixelMap *pixelMap)
{
    FILE *fichier = fopen(filename, "wb");
    if (fichier == NULL)
    {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }
    fprintf(fichier, "%s\n", pixelMap->format);
    fprintf(fichier, "%d %d\n", pixelMap->largeur, pixelMap->hauteur);
    fprintf(fichier, "%d\n", pixelMap->maxval);
    int largeur = pixelMap->largeur;
    int hauteur = pixelMap->hauteur;
    fwrite(pixelMap->pixels, sizeof(Pixel), largeur * hauteur, fichier);
    fclose(fichier);
}

void setPixelToPixelMap(PixelMap *pixelMap, unsigned char r, unsigned char g, unsigned char b)
{
    int largeur = pixelMap->largeur;
    int hauteur = pixelMap->hauteur;
    for (int i = 0; i < largeur * hauteur; i++)
    {
        pixelMap->pixels[i].r = r;
        pixelMap->pixels[i].g = g;
        pixelMap->pixels[i].b = b;
    }
}

int convergence(double x, double y)
{
    double complex z = x + I * y;
    double complex u = 0 + 0 * I;

    for (int n = 0; n < MAX_ITER; n++)
    {
        u = u * u + z;
        if (cabs(u) >= 2.0)
        {
            return n;
        }
    }
    return 0;
}

void pixel_to_coord(int px, int py, double *x, double *y, double x_min, double x_max, double y_min, double y_max)
{
    *x = x_min + (x_max - x_min) * px / (LARGEUR - 1);
    *y = y_min + (y_max - y_min) * py / (HAUTEUR - 1);
}

void drawMandelbrot(PixelMap *pixelMap, unsigned char r, unsigned char b, double x_min, double x_max, double y_min, double y_max)
{
    int largeur = pixelMap->largeur;
    int hauteur = pixelMap->hauteur;

    for (int py = 0; py < hauteur; py++)
    {
        for (int px = 0; px < largeur; px++)
        {
            double x, y;
            pixel_to_coord(px, py, &x, &y, x_min, x_max, y_min, y_max);
            int n = convergence(x, y);

            int index = py * largeur + px;
            pixelMap->pixels[index].r = r;
            pixelMap->pixels[index].g = (unsigned char)(n * 3);
            pixelMap->pixels[index].b = b;
        }
    }
}
