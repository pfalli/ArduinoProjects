# Joystick Reader

This project reads the X-axis, Y-axis, and push button of an analog joystick and prints their values to the Serial Monitor.

## Code used

The two joystick axes are connected to analog inputs and read with `analogRead()`. The switch is read with `digitalRead()` and held high using the pin's pull-up behavior. `Serial.print()` displays updated values every half second.

## What I learned

- How analog joystick positions are represented as numeric values.
- How to read a digital push button.
- How to use the Serial Monitor to inspect inputs and debug hardware.

