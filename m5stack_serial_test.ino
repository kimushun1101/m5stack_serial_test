/*
    Name:       m5stack_serial_test.ino
    Created:    2020/10/20 20:20:15
    Author:     kimushun1101
*/

#include <M5Stack.h>

#define NOTE_D0 -1
#define NOTE_D1 294
#define NOTE_D2 330
#define NOTE_D3 350
#define NOTE_D4 393
#define NOTE_D5 441
#define NOTE_D6 495
#define NOTE_D7 556

#define NOTE_DL1 147
#define NOTE_DL2 165
#define NOTE_DL3 175
#define NOTE_DL4 196
#define NOTE_DL5 221
#define NOTE_DL6 248
#define NOTE_DL7 278

#define NOTE_DH1 589
#define NOTE_DH2 661
#define NOTE_DH3 700
#define NOTE_DH4 786
#define NOTE_DH5 882
#define NOTE_DH6 990
#define NOTE_DH7 112

void setup() {
  // init lcd, serial, but don't init sd card
  M5.begin(true, false, true);
  Serial.begin(57600);

  /*
    Power chip connected to gpio21, gpio22, I2C device
    Set battery charging voltage and current
    If used battery, please call this function in your project
  */
  M5.Power.begin();

  M5.Lcd.clear(BLACK);
  M5.Lcd.setTextColor(YELLOW);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(65, 10);
  M5.Lcd.println("Button example");
  M5.Lcd.setCursor(3, 35);
  M5.Lcd.println("Press button B for 700ms");
  M5.Lcd.println("to clear screen.");
  M5.Lcd.setTextColor(RED);
}

// Add the main program code into the continuous loop() function
void loop() {
  // update button state
  M5.update();

  if ( Serial.available() > 0 ) {
    String str = Serial.readStringUntil('\n');
    Serial.print("recieved -> ");
    Serial.println(str);
    M5.Lcd.print(str);
  }
  // if you want to use Releasefor("was released for"), use .wasReleasefor(int time) below
  if (M5.BtnA.wasReleased()) {
    M5.Lcd.print('A');
    M5.Speaker.tone(NOTE_DH2, 200);
  } else if (M5.BtnB.wasReleased()) {
    M5.Speaker.setVolume(3);
    M5.Lcd.print('B');
  } else if (M5.BtnC.wasReleased()) {
    M5.Speaker.setVolume(10);
    M5.Lcd.print('C');
  } else if (M5.BtnB.wasReleasefor(700)) {
    M5.Lcd.clear(BLACK);
    M5.Lcd.setCursor(0, 0);
  }
}
