# RFID Access System

These sketches develop an RFID access system in stages: reading card UIDs, checking known cards, showing results on a 16×2 LCD, and finally moving a servo to simulate locking and unlocking a door.

## Code used

The project uses the `SPI` and `MFRC522` libraries to communicate with the RFID reader. Card UIDs are compared byte by byte with saved values. Later versions add the `LiquidCrystal` library for messages and the `Servo` library for the door mechanism. Helper functions separate UID checking, screen updates, and door control.

## What I learned

- How SPI communication and RFID card reading work.
- How to store and compare UID byte arrays.
- How to combine several components and libraries in one program.
- How to divide a larger program into reusable functions and states.

## Project photo

> Add a photo of the RFID reader, LCD, and servo setup here.
