#include <iostream>
#include <FreeImage.h>
#define WIDTH 2048
#define HEIGHT 2048
#define BPP 24        //Since we ' re outputting three 8 b i t RGB values
using namespace std;
int main(int argc, char* argv[]) {
  FreeImage_Initialise();
//  FIBITMAP* bitmap = FreeImage_Allocate(WIDTH, HEIGHT, BPP);
  FIBITMAP* bitmap = FreeImage_Load(FIF_PNG, "/Users/murphy/oz/models/lib_hand_model/hand_texture_image.png", 0);
  RGBQUAD color;
  if (! bitmap)
    exit (1); //WTF?! We can ' t even allocate images? Die !

  //Draws a gradient from blue to green :
  for ( int i =400; i< WIDTH; i++) {
    for ( int j =0; j< HEIGHT; j++) {
      color.rgbRed = 0;
      color.rgbGreen = (double) i / WIDTH * 255.0;
      color.rgbBlue = (double) j / HEIGHT * 255.0;
      FreeImage_SetPixelColor (bitmap,i,j,&color );
      //Notice how we ' re calling the & operator on "color"
      //so that we can pass a pointer to the color s t ruct .
    }
  }
  if (FreeImage_Save(FIF_PNG, bitmap, "test.png", 0))
    cout << "Image suc c e ssfully saved ! " << endl ;

  FreeImage_DeInitialise(); //Cleanup !
}
