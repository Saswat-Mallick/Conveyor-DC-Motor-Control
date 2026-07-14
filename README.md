# Closed-Loop DC Motor Speed & Direction Control (Conveyor System)

## Overview
Arduino-based conveyor system controlling a DC motor's speed (0-100%) 
and direction via potentiometer input, with real-time status displayed 
on a 16x2 LCD. Built in TinkerCAD.

## Features
- PWM-based speed control (0-255 duty cycle, mapped from potentiometer)
- H-bridge (L293D) direction control
- Simulated closed-loop feedback (see Design Notes below)
- Real-time LCD display of target vs. actual speed
- Buzzer alert when target speed is reached

## Hardware
- Arduino Uno
- L293D Motor Driver IC
- DC Motor
- Potentiometer (speed input) + Potentiometer (LCD contrast)
- 16x2 LCD
- Piezo buzzer
- 9V battery (motor power) + Arduino 5V (logic power) — kept on 
  separate rails, sharing only common ground

## Design Notes
- **Closed-loop simulation:** TinkerCAD's motor component has no 
  real RPM sensor output, so "actual speed" is simulated in code 
  (gradually approaching target speed rather than jumping instantly), 
  demonstrating the control-loop logic that would apply with a real 
  encoder/feedback sensor on physical hardware.
- **Single motor, single H-bridge channel:** direction reversal is 
  achieved via input-pin polarity flip on one channel — no second 
  motor needed for bidirectional control.

## Debugging Journey
This started from a provided reference circuit, which had a couple 
of real issues worked through during build:
- Found and fixed a 5V/9V rail short (motor power and logic power 
  were unintentionally tied to the same rail)
- Resolved a pin conflict between the LCD and motor direction control 
  sharing the same Arduino pin
- Fixed LCD contrast (backlight was on, but characters were invisible 
  until contrast was tuned)
- Removed per-loop `lcd.clear()` calls causing display flicker, 
  replaced with fixed-position overwrites

Debugged with Claude (Anthropic) as a technical sounding board — 
used for verifying circuit logic, tracing wiring issues, and 
reviewing code, while all wiring changes and testing were done 
hands-on in TinkerCAD. (Most of the code was written by me.
Doubts like should this be connected here and there, what should be changed
to fix the bug, can find error in my code was clarified by Claude).

## Known Quirks
- **Contrast pot:** needs to be turned to (near) maximum for 
  characters to actually display — backlight will look "on" 
  regardless, so if the screen looks blank, check this first before 
  assuming a wiring/code issue.
- **The alert tone:** originally attempted a Rick Astley "Never 
  Gonna Give You Up" tune for the target-speed-reached alert. What 
  actually plays sounds nothing like it — but it's got character. 
  Consider it a bonus feature.

## Files
- `motor_control.ino` — main Arduino sketch
- `circuit_diagram.png` — TinkerCAD wiring screenshot
