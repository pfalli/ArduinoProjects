# Traffic Lights

This project simulates a traffic light with red, yellow, and green LEDs. The sketch turns each LED on and off in sequence with a one-second delay.

## Code used

The code defines a pin for each LED, configures them as outputs with `pinMode()`, and controls them using `digitalWrite()`. A reusable `blinkLED()` function avoids repeating the same timing logic for every color.

## What I learned

- How to configure and control digital output pins.
- How `HIGH`, `LOW`, and `delay()` affect an LED.
- How functions make repeated code shorter and easier to understand.

## Project GIF

![Traffic lights project](trafficLights.gif)
