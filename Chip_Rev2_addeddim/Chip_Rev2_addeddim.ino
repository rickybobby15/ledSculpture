// Ricky Aguiar
// Lighting for the Blankenship Stand

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN            2
#define NUMPIXELS      256
#define PIX_PER_ROW     8
#define COLUMNS     32

//--


Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
uint32_t whiteColor = pixels.Color(200, 200, 200);

int delayval = 50; // delay

void setup() {
  delay(2000);
  pixels.begin(); // This initializes the NeoPixel library.
  pixels.clear();
}

void loop() {
    static int tick = 0;    // tick increments each time through until 
    wave(tick, 10, 200);
    pixelClear();
    delay(delayval);
    tick++;
    tick%=COLUMNS;    // does result of "ticks" = the number of columns ?
}

void wave(int tick, int brightnessInitial, int brightnessFinal) { 
    // % 249 is just for error checking. It prevents the below from happening.
    // 249 + 8 = 257. There exist no pixel with that address. 
    int startingRow = (tick * PIX_PER_ROW) % 249;
    
    for(int whiteFade = brightnessInitial; whiteFade < brightnessFinal; whiteFade++) { // brightness level incrementation
    
    for (int i = 0; i < PIX_PER_ROW; i++) {  // position incrementation
        pixels.setPixelColor(startingRow + i, pixels.Color(whiteFade, whiteFade, whiteFade)); // (Adress of Pixel, Color to Pixel); 
        pixels.show();
    }
   
    delay(delayval);
}  
    
}


void pixelClear() { 
    pixels.clear();
}






