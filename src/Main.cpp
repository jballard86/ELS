#include "Header.h"
#include "Version.h"

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
  LeadSpeed = MaxLeadRPM * LeadSPR / 60;         // Leadscrew Max Steps/sec
  LeadScrew.setMinPulseWidth(Step_Pulse_Width);
  LeadScrew.setMaxSpeed(LeadSpeed);

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

Spindle_Angle();
if (S_Timer.check() == 1) {Serial.print(rpm,DEC); Serial.print("  "); Serial.print(LeadScrew.speed(),DEC);
Serial.print("  "); Serial.println(SpindleRPM,DEC);
}

  LeadScrew.runSpeed();
  //LeadScrew.run();

  if (Mode_Array_Pos == 0) {Feed();} 
  if (Mode_Array_Pos == 1) {Thread();} 
  if (Mode_Array_Pos == 2) {Auto_Thread();}
  if (Mode_Array_Pos == 3) {Turn_to_Diameter();}
  if (Mode_Array_Pos == 4) {Manual_Z();}
  if (Mode_Array_Pos == 5) {Manual_X();}
  if (Mode_Array_Pos == 6) {Auto_Radius();}
  if (Mode_Array_Pos == 7) {Chamfer();}

  /*for (int pop = 1; pop < 1000; pop++) {
    digitalWrite(LeadStp, HIGH);
    delayMicroseconds(2);
    digitalWrite(LeadStp, LOW);
    delayMicroseconds(2);
    //Serial.print(" z ");
  }*/
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
#include "Auto_Radius.h"
