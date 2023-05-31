#include "Header.h"

//using: https://www.pjrc.com/teensy/td_timing_IntervalTimer.html

void setup() {
  Mode = Mode_Array_Pos;
  TPI = TPI_Array[TPI_Array_Pos];
  Pitch = Pitch_Array[Pitch_Array_Pos];
  LeadSpeed = MaxLeadRPM * LeadSPR / 60;         // Leadscrew Max Steps/sec

  spindle.setInitConfig();  //start spindle encoder
  spindle.init();

  LeadScrew.begin(LeadStp, LeadDir);
  //LeadScrew.setEnablePin(Stepper_Enable);
  //pinMode(Stepper_Enable, HIGH);    //enables drive

//----Setup Various Display Methods----//
  Serial.begin(115200);             // starts serial
    delay(200);
  Wire.begin();                     // starts I2C
    Wire.setSDA(SDA_Pin);           //setting up I2C Pins, if others are needed setup Wire1, Wire2, etc
    Wire.setSCL(SCL_Pin);
    
  matrix.begin(0x70);               // starts 7 segment display, the () is the address
    matrix.setBrightness(15);       // sets 7 segment brightness to max, applicable values are 0-15
  Start_Feed_Display();             //runs display start routine
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

Spindle_Angle();
if (S_Timer.check() == 1) {Serial.print(TotalRotations,4); Serial.print("  "); Serial.print(TotalRot_noDEC, DEC);
Serial.print("  "); Serial.println(Encoder_Angle, 4);
}

  LeadScrew.loop();             // Call this as often as possible for stepper control

  if (Mode_Array_Pos == 0) {Feed();} 
  if (Mode_Array_Pos == 1) {Thread();} 
  if (Mode_Array_Pos == 2) {Auto_Thread();}
  if (Mode_Array_Pos == 3) {Turn_to_Diameter();}
  if (Mode_Array_Pos == 5) {Manual_Z();}
  if (Mode_Array_Pos == 6) {Manual_X();}
  if (Mode_Array_Pos == 7) {Radius();}
  if (Mode_Array_Pos == 8) {Chamfer();}
}


void Radius() {
}
void Chamfer() {
}


#include "Display.h"
#include "Feed.h"
#include "Interface.h"
#include "Interrupts.h"
#include "Menu.h"
#include "Thread.h"
#include <string>