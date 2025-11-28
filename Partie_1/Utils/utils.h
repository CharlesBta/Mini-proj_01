// structure des pixels liste chaînée
typedef struct 
{
    unsigned char r; // Composante rouge 0-255
    unsigned char g; // Composante verte 0-255
    unsigned char b; // Composante bleue 0-255
} Pixel;

// structure de l'image
typedef struct 
{
    char format[3]; // Format ex: "P3" + "\n" -> 3 chars
    int largeur; // Largeur de l'image en ASCII + "\0" -> max 4 chars
    int hauteur; // Hauteur de l'image en ASCII + "\0" -> max 4 chars
    int maxval; // Valeur max des couleurs en ASCII + "\n" -> max 3 chars ex: "255"
    Pixel *pixels; // Tableau 2D de pixels
} PixelMap;

PixelMap* createPixelMap(int largeur, int hauteur, int maxval);

void freePixelMap(PixelMap* pixelMap);

void writePixelMapToFile(const char* filename, const PixelMap* pixelMap);

void setPixelToPixelMap(PixelMap* pixelMap, unsigned char r, unsigned char g, unsigned char b);

void drowCircle(PixelMap* pixelMap, int centerX, int centerY, int radius, unsigned char r, unsigned char g, unsigned char b);