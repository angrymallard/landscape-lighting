//run three landscape lights in front of the house using an ATtiny45, internal 1 MHz clock
//programmed in Arduino IDE
//the microcontroller gets power when the sun sets, but waits a set amount of time before turning the lights on
//once the lights are on, if the microcontroller loses main power, it goes into sleep mode while being powered by a 1F capacitor
//if it goes into sleep mode, it turns the lights off and will not turn them back on until the next day.

#include <avr/sleep.h>

// Utility macros
#define adc_disable() (ADCSRA &= ~(1<<ADEN)) // disable ADC (before power-off)
#define adc_enable()  (ADCSRA |=  (1<<ADEN)) // re-enable ADC

const int relayPin = 0;
const int ledPin =  1;

int ledState = LOW;             // ledState used to set the LED
long previousMillis = 0;        // will store last time LED was updated
int i = 0;
int j =0;

long interval = 1000;           // interval at which to blink (milliseconds)

void setup() {
  pinMode(relayPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
}

void loop()
{
  if (i == 0) { //do this once when power is first turned on
    digitalWrite(ledPin, HIGH);  //turn the LED on
    while (j < 1920) { //2400 seconds in 40 minutes
      delay(1000);
      j++;
    }
    i++;
  }

  //calculate the voltage on analog input 2, to determine state of power
  int sensorValue = analogRead(A2);
  float voltage = sensorValue * (5.0 / 1023.0);
  if (voltage < 2.0) {  //if the power goes out
    go_to_sleep();
  }
  else {   //if the power is still on
    digitalWrite(relayPin, HIGH);
    //start blinking the LED
    unsigned long currentMillis = millis();
    if(currentMillis - previousMillis > interval) {
      previousMillis = currentMillis;   
      if (ledState == LOW)
        ledState = HIGH;
      else
        ledState = LOW;
      digitalWrite(ledPin, ledState);
    }
  }
}

void go_to_sleep() {
  digitalWrite(ledPin, LOW);
  digitalWrite(relayPin, LOW);
  //sleep function, this disables the microcontroller until fully power cycled
  //i.e. power is removed and the capacitor discharges
  adc_disable();
  pinMode(relayPin, INPUT);
  pinMode(ledPin, INPUT);
  sleep_enable();
  sleep_cpu();
}
