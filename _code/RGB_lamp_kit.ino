#include <Adafruit_NeoPixel.h>

int RED 	 = 0;
int GREEN  = 1;
int BLUE   = 2;
int RGBled = 2; 
int num = 12;
Adafruit_NeoPixel pixels(num, RGBled, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin();
}

void loop() {
  int valRED   = analogRead(RED);
  int valGREEN = analogRead(GREEN);
  int valBLUE  = analogRead(BLUE);

  for (int i=0 ; i<num ; i++)
     pixels.setPixelColor(i, pixels.Color(valRED/4, valGREEN/4, valBLUE/4));

  pixels.show();
}
