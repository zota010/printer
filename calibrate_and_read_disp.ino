#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES     10 // Number of snowflakes in the animation example


#include <MQ131.h>

void setup() {
  Serial.begin(115200);
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.display();
  delay(2000); // Pause for 2 seconds

  display.clearDisplay();

  display.drawPixel(10, 10, SSD1306_WHITE);

  display.display();
  delay(2000);

  // Init the sensor
  // - Heater control on pin 2
  // - Sensor analog read on pin A0
  // - Model LOW_CONCENTRATION
  // - Load resistance RL of 1MOhms (1000000 Ohms)
  MQ131.begin(2,A0, HIGH_CONCENTRATION,100000);  

  Serial.println("Calibration in progress...");
  
  cal();
  
   MQ131.calibrate();
  
  
  Serial.println("Calibration done!");
  Serial.print("R0 = ");
  Serial.print(MQ131.getR0());
  Serial.println(" Ohms");
  Serial.print("Time to heat = ");
  Serial.print(MQ131.getTimeToRead());
  Serial.println(" s");  
}

void loop() {

  

 sampling();
  
  Serial.println("Sampling...");
  MQ131.sample();
  Serial.print("Concentration O3 : ");
  Serial.print(MQ131.getO3(PPM));
  Serial.println(" ppm");
  Serial.print("Concentration O3 : ");
  Serial.print(MQ131.getO3(PPB));
  Serial.println(" ppb");
  Serial.print("Concentration O3 : ");
  Serial.print(MQ131.getO3(MG_M3));
  Serial.println(" mg/m3");
  Serial.print("Concentration O3 : ");
  Serial.print(MQ131.getO3(UG_M3));
  Serial.println(" ug/m3");
result();
  delay(6000);
}


void sampling(void) {
  display.clearDisplay();

  display.setTextSize(1.5);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("Sampling"));
  display.println(F("......"));
  display.println(F("R0 = "));display.println(MQ131.getR0()); 
display.setTextSize(1.5);

 display.setCursor(60, 20);
 display.println(F("O3:")) ;
   display.setCursor(60, 10);
 display.println(MQ131.getO3(MG_M3)); 
 display.setCursor(90, 10);
  display.println(F("mg/m3")) ;
display.setTextSize(1.5);
 display.setCursor(60, 20);
 display.println(F("Time=")) ;
 display.setCursor(94, 20);
 display.println(MQ131.getTimeToRead()); 
 display.setCursor(116, 20);
 display.println(F("S")) ;
  display.display();     
  delay(1000);
}

void cal(void) {
  display.clearDisplay();

  display.setTextSize(1.5);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("caling"));
  display.println(F("......"));
  display.println(F("R0 = "));display.println(MQ131.getR0()); 
 display.setTextSize(1.5); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(60, 0);
 display.println(F("O3:")) ;
   display.setCursor(60, 10);
 display.println(MQ131.getO3(MG_M3)); 
 display.setCursor(90, 10);
  display.println(F("mg/m3")) ;
display.setTextSize(1.5);
 display.setCursor(60, 20);
 display.println(F("Time=")) ;
 display.setCursor(94, 20);
 display.println(MQ131.getTimeToRead()); 
 display.setCursor(116, 20);
 display.println(F("S")) ;
  display.display();     
  delay(1000);
}


void result(void) {
  display.clearDisplay();

  display.setTextSize(1.5);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("result"));
  display.println(F("......"));
  display.println(F("R0 = "));display.println(MQ131.getR0()); 
 display.setTextSize(1.5); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(60, 0);
 display.println(F("O3:")) ;
   display.setCursor(60, 10);
 display.println(MQ131.getO3(MG_M3)); 
 display.setCursor(90, 10);
  display.println(F("mg/m3")) ;
  display.display();     
  delay(1000);
}
