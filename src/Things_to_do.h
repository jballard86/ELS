/*
due to the 2 steppers going on the crossslide and lead screw axis, in threading this could cause the cutter to cut on both sides
    -to fix this calculate the extra lead that the lead screw should start, and start it early so the cut stays on the leading edge of the tool
Add Gear Ratio Calculation with Inputs: Gear_Teeth_Spindle and Gear_Teeth_Encoder
Add OD submenu to auto radius, this will be used to draw the projected action
possible to track spindle position in order to start stop lead screw at the same angular value?
    -Code is done, needs to be tested
add menu selections as negative mode values aka direction
Move to position based off of metric numbers may have significant rounding errors  .01mm = 3.15 steps.  run stepper driver in the higherst resolution possible
external and internal threading
internal and external boring
internal and external radius
internal and external chamfer
ball turning
Knurling?  https:ww.youtube.com/watch?v=E2niXyOQSOA

https://www.airspayce.com/mikem/arduino/AccelStepper/classAccelStepper.html#ac62cae590c2f9c303519a3a1c4adc8ab
*/
