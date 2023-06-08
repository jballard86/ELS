#include "Header.h"

//using: https://www.pjrc.com/teensy/td_timing_IntervalTimer.html

void setup() {
  Mode = Mode_Array_Pos;
  TPI = TPI_Array[TPI_Array_Pos];
  Pitch = Pitch_Array[Pitch_Array_Pos];
  Steps_Per_Thou = (LeadSPR * LeadScrew_TPI) / 1000;
  Steps_Per_hundredth_mm = 0.000393701 * LeadSPR * LeadScrew_TPI;   //0.000393701 is from the simplified equation: (LeadSPR/((1/LeadScrew_TPI)*25.4))/100

  spindle.setInitConfig();  //start spindle encoder
  spindle.init();

//----Stepper Setup----//
  //----Leadscrew----//
    LeadSpeed = MaxLeadRPM * LeadSPR / 60;         // Leadscrew Max Steps/sec
    LeadScrew.setMinPulseWidth(Step_Pulse_Width);
    LeadScrew.setMaxSpeed(LeadSpeed);
  //----Cross Slide----//
    Cross_Speed = MaxCrossRPM * CrossSPR / 60;         // CrossSlide Max Steps/sec
    CrossSlide.setMinPulseWidth(Step_Pulse_Width);
    CrossSlide.setMaxSpeed(Cross_Speed);
  //----MultiStepper Setup----//
    ZY_Steppers.addStepper(LeadScrew);
    ZY_Steppers.addStepper(CrossSlide);

//----Setup Various Display Methods----//
  Serial.begin(115200);             // starts serial
    delay(200);
  Wire.begin();                     // starts I2C
    Wire.setSDA(SDA_Pin);           //setting up I2C Pins, if others are needed setup Wire1, Wire2, etc
    Wire.setSCL(SCL_Pin);
    
  matrix.begin(0x70);               // starts 7 segment display, the () is the address
    matrix.setBrightness(15);       // sets 7 segment brightness to max, applicable values are 0-15
  Start_Feed_Display();             //runs display start routine
  Start_Graph_Display();
  delay(500);

//----Start I2C Encoder Interface----//
  Enc1.begin(0x36);
    Enc1.pinMode(Enc_Button, INPUT_PULLUP);  // Set Pin for encoder switch
    Enc1_Pos = Enc1.getEncoderPosition();     // get starting position
  Enc2.begin(0x37);
    Enc2_Pos = Enc2.getEncoderPosition();       
  Enc1.setEncoderPosition(Menu_pos);
  Enc1.setGPIOInterrupts(Enc_Button, 1);
  //Enc1.enableEncoderInterrupt();
  Enc2.setGPIOInterrupts(Enc_Button, 1);
  //Enc2.enableEncoderInterrupt();
 
//----Timer Setup----// 
  RPM_Check.begin(RPM_Calc, RPM_Check_INTERVAL_MS);       // Sets up an interrupt timer to run every "RPM_Check_INTERVAL_MS" (milli)
  Refresh_Rate_Timer.begin(Refresh, Refresh_Rate);        // Display Refresh Rate
  S_Timer.interval((124/60)*1000);
  S_Timer.reset();
}

void loop() {
  /* 
    -Display "Refresh()" is called every "Refresh_rate" milliseconds
      This allows interface, and menu to be ran
      Some functions inside of them are called on in special cases to update the display
    -Spindle Encoder is tracked using interrupts on the A/B pin changes
    -RPM_Calc runs on an interrupt timer in order to stay accurate with the RPM calculation
  */

//----Serial output for current debuging----//
  /*if (S_Timer.check() == 1) {Serial.print(CrossSlide.distanceToGo(),DEC); Serial.print("  "); Serial.print(LeadScrew.distanceToGo(),DEC);
    Serial.print("  "); Serial.println(LeadScrew.speed(),DEC);
  }*/

//----Feature/Mode Sub Routines----//             Proper Accelstepper run command for each feature
  if (Mode_Array_Pos == 0) {Feed();               LeadScrew.runSpeed();} 
  if (Mode_Array_Pos == 1) {Thread();             LeadScrew.runSpeed();} 
  if (Mode_Array_Pos == 2) {Auto_Thread();        ZY_Steppers.run();}
  if (Mode_Array_Pos == 3) {Turn_to_Diameter();   ZY_Steppers.run();}
  if (Mode_Array_Pos == 4) {Manual_Z();           LeadScrew.run();}
  if (Mode_Array_Pos == 5) {Manual_X();           CrossSlide.run();}
  if (Mode_Array_Pos == 6) {Auto_Radius();        ZY_Steppers.run();}
  if (Mode_Array_Pos == 7) {Chamfer();            ZY_Steppers.run();}
  //if (Mode_Array_Pos == 8) {Taper();              ZY_Steppers.run();}
  //if (Mode_Array_Pos == 9) {Knurling();           ZY_Steppers.run();}

}

/**
  @brief Calculates the total number of steps to get from A to B
  @param move_length  : length of move (in on mm)
*/
double Steps_per_Move(double move_length) {    
  double StepsPer;
  if (Metric == 0) {
    move_length = move_length / .001;
    StepsPer = move_length * Steps_Per_Thou;
  } 
  else {
    move_length = move_length / .01;
    StepsPer = move_length * Steps_Per_hundredth_mm;
  }
  return StepsPer;
}

#include "Display.h"
#include "Feed.h"
#include "Interface.h"
#include "Interrupts.h"
#include "Menu.h"
#include "Thread.h"
#include <string>
#include "Auto_Radius.h"
#include "Chamfer.h"
