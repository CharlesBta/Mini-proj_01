# Compile Partie 1
/
```
gcc -o main main.c ./utils/utils.c
./main
```
# Compile Partie 2
/
```
gcc -o main main.c ./utils/utils.c -lm
./main
```
# Compile Partie 3
/
```
gcc -o main main.c ./utils/utils.c -lm
./main
```
convert imgs to video (need ffmpeg ```brew install ffmpeg```)
```
ffmpeg -framerate 1 -i image_%02d.ppm -c:v libx264 -pix_fmt yuv420p video.mp4
```