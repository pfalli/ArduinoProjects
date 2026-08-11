# Thermometer

This project reads a 100 kΩ thermistor and shows the calculated temperature in degrees Celsius on a 16×2 LCD. The raw reading, resistance, and temperature are also sent to the Serial Monitor.

## Code used

The sketch uses `analogRead()` to measure a voltage divider, calculates the thermistor resistance, and applies the Beta equation to convert it to temperature. The `LiquidCrystal` library controls the LCD, while `math.h` provides the logarithm used in the calculation.

## What I learned

- How to read an analog sensor and work with a voltage divider.
- How a thermistor's resistance can be converted into temperature.
- How to format values on an LCD and use serial output for debugging.

## Project photo

> Add a photo of the finished circuit here.
