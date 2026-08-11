# Joystick LCD Games

This folder combines an analog joystick with a 16×2 LCD. One sketch moves a custom smiley around the screen, while the other builds a compact Snake game with food, growth, collision detection, increasing speed, and button-controlled restart.

## Code used

The sketches use `analogRead()` with thresholds to detect direction and `INPUT_PULLUP` for the joystick button. The `LiquidCrystal` library displays custom characters. Snake positions are stored in arrays, while `millis()` controls movement without tying input directly to a long delay. Random food placement, screen wrapping, and collision checks provide the game logic.

## What I learned

- How to translate joystick readings into movement.
- How to store and update positions using arrays.
- How to build a simple game loop and manage game state.
- How to use `millis()`, randomness, collision detection, and custom LCD graphics.

## Project photo

> Add a photo of the joystick and LCD game here.
