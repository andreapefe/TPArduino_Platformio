#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>


#include <ChainableLED.h>

#include <math.h>

const int B = 4275;               // B value of the thermistor
const int R0 = 100000;            // R0 = 100k
const int pinTempSensor = A0;

#if defined(ARDUINO_ARCH_AVR)
#define debug  Serial
#elif defined(ARDUINO_ARCH_SAMD) ||  defined(ARDUINO_ARCH_SAM)
#define debug  SerialUSB
#else
#define debug  Serial
#endif

#define NUM_LEDS 1
U8G2_SH1107_SEEED_128X128_1_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);
//ChainableLED leds(9, 10, NUM_LEDS);

void setup(void) {

    Serial.begin(9600);
    u8g2.begin();
    //leds.init();
    //leds.setColorRGB(1,0,253,0);

}

//ceci est le main
void loop(void) {

    Serial.println("Hello world!");
    //leds.setColorRGB(0,0,253,0);
    //delay(1000);

    int a = analogRead(pinTempSensor);

    float R = 1023.0/a-1.0;
    R = R0*R;

    float temperature = 1.0/(log(R/R0)/B+1/298.15)-273.15;
    Serial.print("T=");
    Serial.println(temperature);

    u8g2.firstPage();
    do {
        u8g2.setFont(u8g2_font_ncenB10_tr);
        u8g2.drawStr(0,24,"ELLE MARCHE");
        u8g2.drawStr(0,50,"ENFIN");
        u8g2.drawStr(0,100,"T=");
        u8g2.drawStr(20,100,String(temperature).c_str());
    } while ( u8g2.nextPage() );

    delay(1000);

}