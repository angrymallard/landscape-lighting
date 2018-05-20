//run three landscape lights in front of the house using an ATtiny45, internal 1 MHz clock
//programmed in Arduino IDE
//the microcontroller gets power when the sun sets, but waits a set amount of time before turning the lights on
//once the lights are on, if the microcontroller loses main power, it goes into sleep mode while being powered by a 1F capacitor
//if it goes into sleep mode, it turns the lights off and will not turn them back on until the next day.

