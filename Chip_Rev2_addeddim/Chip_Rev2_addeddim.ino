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
#define OSCIL_VAL  425
//--


Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
uint32_t whiteColor = pixels.Color(200, 200, 200);

int delayval =2; // delay

void setup() {
  delay(2000);
  pixels.begin(); // This initializes the NeoPixel library.
  pixels.clear();
}

unsigned long past = millis();
void loop() {
    static int tickf = 0;    // tick increments each time through until 
    static int brightness = 0;
    
    wave(tickf-2, oscilPulse(brightness - 10));
    wave(tickf-1, oscilPulse(brightness - 5));
    wave(tickf, oscilPulse(brightness));

    brightness+=2;
    if ((millis() - past) > 1000) {
      tickf++;
      tickf%=COLUMNS;    // does result of "ticks" = the number of columns ?
      wave(tickf-2, 0);
      past = millis();

    }
}

void wave(int tick, int brightLevel) { 
    // % 249 is just for error checking. It prevents the below from happening.
    // 249 + 8 = 257. There exist no pixel with that address. 
    if (tick < 0) {
      return;
    }
    int startingRow = (tick * PIX_PER_ROW) % 249;
    
    for (int i = 0; i < PIX_PER_ROW; i++) {  // position incrementation
        pixels.setPixelColor(startingRow + i, pixels.Color(255, 255, 255)); // (Adress of Pixel, Color to Pixel); 
    }
    pixels.setBrightness(brightLevel);
    pixels.show();
}

//  This is the mathematical function that allows pulsing concurrently with any
//      existing processes that are being executed. 
uint8_t oscilPulse(long incVal) {
    //  Oscillation is divided into three parts.
    
    if (incVal < 0) {
      return 0;
    }

    //  This is the incremental range and increasing direction from 0 to OSCIL_VAL. 
    int incFun = incVal % OSCIL_VAL;

    //  This evaluates to be either 0 or 1 given incFun is 0 when less than
    //      OSCIL_VAL/2 and 1 when higher than OSCIL_VAL/2.
    //  This allows selective subtraction when whenToSub = 0 or 1.
    int whenToSub = incFun / (OSCIL_VAL / 2);

    //  This is the range to subtract given incFun, which is (0 - (OSCIL_VAL/2)) to
    //      (OSCIL_VAL - (OSCIL_VAL/2)) -> -(OSCIL_VAL/2) to OSCIL_VAL/3.
    //  Ultimately, this is what allows an incremental decrease upon reaching
    //      OSCIL_VAL.
    int decFun = ((incVal % OSCIL_VAL) - (OSCIL_VAL / 2));

    //  The final formula is as follows, where upon subtraction is allowed, 
    //      the range is doubled to offset the range [OSCIL_VAL/2, OSCIL_VAL]
    //      to allow a decreasing behaviour.
    int result = incFun - (whenToSub * decFun * 2);

    //  The final result.
    return (uint8_t) result;
}






