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

}

void loop() {
  LeadScrew.loop();
  //if (SpindleRPM == 0) {LeadScrew.stop();}
  //Serial.println(LeadSpeed.speed());

  if (Mode_Array_Pos == 0){                       // Feed should be adjustable while spindle is running
    Feed();
  } else if (Mode_Array_Pos == 1) {
    Thread();
  } /*else if (Mode == 3) {
    Auto_Thread();
  } else if (Mode == 4) {
    Turn_to_Diameter();
  } else if (Mode == 5) {
    Manual_Z();
  } else if (Mode == 6) {
    Manual_X();
  } else if (Mode == 7) {
    Radius();
  } else if (Mode == 8) {
    Chamfer();
  }*/
}

void Turn_to_Diameter(){
}
void Manual_Z() {
}
void Manual_X() {
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
#include "functions.h"
#include <string>