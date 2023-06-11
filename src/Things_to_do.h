/*
Mode_6_SubMenu_Controls() is missing two submenu pages

-in auto thread, add spring pass functionality - with display as such
    -also add a feature to keepcutting and user selection on how much
auto thread needs cut pass calculations
    -repurpose the auto fillet version as it is unused
due to the 2 steppers going on the crossslide and lead screw axis, in threading this could cause the cutter to cut on both sides
    -to fix this calculate the extra lead that the lead screw should start, and start it early so the cut stays on the leading edge of the tool
track spindle position in order to start stop lead screw at the same angular value?
    -Code is done, needs to be tested

add a test function aka move .100" and stop

auto radius final pass functionality
auto radius, redo the cut pass functionality to work by subtracting the final pass from the radius and rebuilding the array with a lower resolution
    -cut depth indicates initial array length
    -then rebuild the array with the correct radius and a higher resolution and travel that as a path

make a function to calculate max speed, and run in the main loop of each mode
   - auto radius currently works off of max speed, add in calculation for chipload or feed/rev once this note is taken care of


Add Gear Ratio Calculation with Inputs: Gear_Teeth_Spindle and Gear_Teeth_Encoder
add menu selections as negative mode values aka direction
Move to position based off of metric numbers may have significant rounding errors  .01mm = 3.15 steps.  run stepper driver in the higherst resolution possible

external and internal threading
internal and external boring
internal and external radius
internal and external chamfer
ball turning
taper turning
Knurling?  https:ww.youtube.com/watch?v=E2niXyOQSOA

*/
