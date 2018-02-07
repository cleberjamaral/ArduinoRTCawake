//------------------------------------------------------------------------------------------
// Author: Cleber Jorge Amaral
// Organization: IFSC - Instituto Federal de Santa Catarina
// Date: 07/02/2018
//------------------------------------------------------------------------------------------
// This sample was based on the following publications:
// * http://www.instructables.com/id/Arduino-Sleep-and-Wakeup-Test-With-DS3231-RTC/ 
// * https://github.com/FabioCuomo/FabioCuomo-DS3231
//------------------------------------------------------------------------------------------
// This code was teste uding Arduino Mega 2560 and DS3231 module with following wiring
// connections:
// DS3231 GND ----- Arduino GND pin in power connector
// DS3231 VCC ----- Arduino 5V pin in power connector
// DS3231 SDA ----- Arduino SDA 20 pin in communication connector
// DS3231 SCL ----- Arduino SCL 21 pin in communication connector
// DS3231 SQW ----- Arduino 2 pin in PWM connector
// DS3231 32K unconnected
//------------------------------------------------------------------------------------------

#include <Wire.h>
#include "RTClibExtended.h"
#include "LowPower.h"

#define wakePin 2    //use interrupt 0 (pin 2) and run function wakeUp when pin 2 gets LOW
#define ledPin 13    //use arduino on-board led for indicating sleep or wakeup status
RTC_DS3231 rtc;      //we are using the DS3231 RTC

//------------------------------------------------------------------------------------------

void wakeUp()        // here the interrupt is handled after wakeup
{

}

//------------------------------------------------------------------------------------------

void setup() {
  //Set pin 2 (wakePin) as INPUT to receive awake signal from RTC
  pinMode(wakePin, INPUT);
  //Set pin 13 (LedPin) as OUTPUT to indicate when running
  pinMode(ledPin, OUTPUT);

  //Initialize RTC
  Wire.begin();
  rtc.begin();
  
  //Adjust RTC datetime to computer's current datetime
  rtc.adjust(DateTime(__DATE__, __TIME__));
  
  //clear any pending alarms
  rtc.armAlarm(1, false);
  rtc.clearAlarm(1);
  rtc.alarmInterrupt(1, false);
  rtc.armAlarm(2, false);
  rtc.clearAlarm(2);
  rtc.alarmInterrupt(2, false);

  //SQW pin should be connecter to INT4 of Arduino (labeled pin 2 - coded here as interrupt 0)
  rtc.writeSqwPinMode(DS3231_OFF);

  //Set alarm2 for every minute
  //Description: RTC_DS3231::setAlarm(Ds3231_ALARM_TYPES_t alarmType, byte minutes, byte hours, byte daydate)
  rtc.setAlarm(ALM2_EVERY_MINUTE, 0, 0, 0);   //set your wake-up time here

  //Enable alarm 2
  rtc.alarmInterrupt(2, true);

  //Start Led in OFF
  digitalWrite(ledPin, LOW);
}

//----------------------------------------------------------------------
//In the beggining of the loop arduino goes to sleep, so the following 
//code will really run once every minute, after arduino is awake by 
//RTC
//----------------------------------------------------------------------

void loop() {
  //Make RTC alarm when it should be done and arduino go to rest...
  rtc.clearAlarm(2);
  attachInterrupt(0, wakeUp, LOW);                       //run wakeUp function when pin 2 gets low
  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);   //arduino goes to sleep
  detachInterrupt(0);                                    //resumes here after wake-up
  
  //Blink two times - Put here your code
  digitalWrite(ledPin, HIGH);
  delay(500);
  digitalWrite(ledPin, LOW);
  delay(500);
  digitalWrite(ledPin, HIGH);
  delay(500);
  digitalWrite(ledPin, LOW);
}

//------------------------------------------------------------------------------------------
