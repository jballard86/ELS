# Electronic Lead Screw
    By Jeff Ballard

Anticipated features:
  - Metric / Inch threading
  - Metric / Inch feeding
  - Auto threading with 2 steppers
  - Auto turn to a specified diameter
  - Pendent Control with:
    - Manual Z control
    - Manual X control
  - Radius cutting
  - Ball cutting
  - chamfer cutting
  - Digital Dial replacements (pipe dream)


This Lead Screw is 100% untested at this point, the code works on a test stand that has the following:
  - 24v power supply
  - 12v power supply
  - Custom PCB w/ a Teensy 4.0
  - 1 stepper motor w/Driver
  - 1 DC motor w/encoder
  - various display/interface hardware

The code seams to work as intended on the test board with the exception of stepper motor direction.  This seems to be a PCB trace error, and should be fixed in a revision that is currently in production (5/30/23).

Once the direction issue is fixed, this will be installed on my lathe to start testing.
