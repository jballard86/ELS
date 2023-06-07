#include "Arduino.h"

#include <QuadEncoder.h>
#include <Encoder.h>
#include <avr/io.h>
#include <SPI.h>
#include <avr/interrupt.h>              //https://www.pjrc.com/teensy/interrupts.html
#include <AccelStepper.h>
#include <MultiStepper.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1327.h>
#include "Adafruit_LEDBackpack.h"
#include "TeensyTimerTool.h"
#include "Adafruit_seesaw.h"
#include <Metro.h>
//#include <seesaw_neopixel.h> 



using namespace TeensyTimerTool;
using namespace std;

#define OLED_RESET -1
#define ENCODER_OPTIMIZE_INTERRUPTS
volatile double RPM_Check_INTERVAL_MS = 100000;
double Refresh_Rate = 200000;

//----Machine Specific----//
  const double LeadScrew_TPI = 8; 
  volatile double SpindleCPR = 3416.00; //4096;               // Spindle Counts per rev  include any gear ratios
  const double LeadSPR = 6400;                                // LeadScrew Steps per rev  include any gear ratios and microstepping =steps/rev * microstepping * gear ratio
  const double MaxLeadRPM = 600;                              // Leadscrew Max RPM
  const double CrossSPR = 6400;                               // Cross slide steps per rev
  const double MaxCrossRPM = 250;                             // Cross slide max RPM

//----Menu Specific----//
  int Metric = 0;                                      // Metric designation 0=Inch 1=Metric
  int Thread_Mode =  0;                                // Thread Mode Designation 0=TPI  1=Pitch
  int Mode;                                             // 1=feed 2=thread 3=auto thread 4=turn to diameter 5=manual_Z 6=manual_X 7=radius 8=chamfer
  volatile int S_Dir = 2;                              // set direction to park, 0=left 1=right 2=park
  int Menu_pos = 3;
  double In_FeedRate = .001;                             // Initial Inch Feed Rate
  double mm_FeedRate = .01;                              // Initial mm Feed Rate
  int submenu = 0;

//-----Threading/Feed Variables----//
  // MAny of the threading variables have an in/mm equvilant inorder to allow saving between selections
  double Inch_Thread_RPM = 0;
  double mm_Thread_RPM = 0;
  double TPI;
  double Pitch;
  double in_Outside_Diameter = 1;
  double mm_Outside_Diameter = 12;
  double in_Final_Diameter = 1;
  double mm_Final_Diameter = 12;
  double Minor_Diameter;
  double mm_Thread_Depth;
  double in_Thread_Depth;
  double in_DOC = .01;
  double mm_DOC = .25;
  double in_length_of_cut = .5;
  double mm_length_of_cut = 12;
  double Steps_Per_Thou = 0;
  double Steps_Per_hundredth_mm = 0;
  double rpm;

//----Radius Variables----//
  const int Radius_Max_steps = 100;
  double Radius_Z[Radius_Max_steps];
  double Radius_Y[Radius_Max_steps];
  int Radius_type = 1;         // 0=left Convex; 1=right Convex; 2=left concave; 3=right concave
  double in_Radius = .25;
  double mm_Radius = 6;
  int Radius_Steps = 40;
  volatile double R_Step_Angle = 0;
  int Build_ZY = 0;
  double Cut_Depth;
  int Cut_Passes;

//----Position Variables----//
  double CrossZ;
  double LeadY;
  double Start_Pos[2];
  double End_Pos[2];

//----setup Interface Encoders thir variables and pins----//
  Adafruit_seesaw Enc1;
    int Enc1_Pos = 0;
    int Enc1_New_Pos = 0;
    int Enc1_dir = 0;               // -1=cw 1=ccw 0=no movement
    int Enc1_Button = 0;
  Adafruit_seesaw Enc2;
    int Enc2_Pos = 0;
    int Enc2_New_Pos = 0;
    int Enc2_dir = 0;               // -1=cw 1=ccw 0=no movement
  const int  Enc_Button = 24;   //pin number

//---- Pins ----//
  const int EncA = 7;               // encoder channel A pin              
  const int EncB = 8;               // encoder channel B pin    
  const int LeadDir = 3;            // Leadscrew Stepper Direction Pin    
  const int LeadStp = 4;            // Leadscrew Stepper Step Pin       
  const int CrossDir = 5;           // Cross slide Stepper Direction Pin    
  const int CrossStp = 6;           // Cross slide Stepper Step Pin     
  const int Stepper_Enable = 2;     // Leadscrew Stepper Enable pin       
  const int SDA_Pin = 18;           // I2C SDA Pin
  const int SCL_Pin = 19;           // I2C SCL Pin
  //const byte SDA1_Pin = 17;       // I2C SDA1 Pin
  //const byte SCL1_Pin = 16;       // I2C SCL1 Pin

//----All Other Variables----//
  int LeadRPM = 0;
  volatile double SpindleRPM = 0;
  volatile double Encoder_Angle = 0;                    // Encoder angle for spindle, used for auto threading not an actual angle in degrees, this is the encoder angle
  double LeadSpeed;                                     // Leadscrew Max Steps/sec
  double Cross_Speed;                                   // Cross slide max steps/sec
  float ctr;                                            // value for center of oled screen
  volatile double oldSpindle;
  volatile double Spindle_Rotations;
  volatile double newSpindle;
  volatile double TotalRotations;
  volatile int TotalRot_noDEC;

  QuadEncoder spindle(1, EncA, EncB);

//----Timer Initialization----//
  IntervalTimer RPM_Check;                              // Interval timer tp check RPM of the spindle
  PeriodicTimer Refresh_Rate_Timer(TCK);                // Software Timer to call the 7seg display routine
  Metro S_Timer = Metro(1000);                          // Basic Timer for debuging

//----Display Initialization----//
  Adafruit_7segment matrix = Adafruit_7segment();
  Adafruit_SSD1327 Feed_Display(128, 128, &Wire, OLED_RESET, 1000000);
  Adafruit_SSD1327 Graph_Display(128, 128, &Wire, OLED_RESET, 1000000);

//----Stepper Initilization----//
  AccelStepper LeadScrew(AccelStepper::DRIVER, LeadStp, LeadDir);
  AccelStepper CrossSlide(AccelStepper::DRIVER, CrossStp, CrossDir);
  int Step_Pulse_Width = 5;
  MultiStepper ZY_Steppers;             // Sets up a multistepper enviroment for coordinated movement of the leadscrew and crossslide

//----Menu Strings----//
  //----Direction Options----//
    const int Direction_Array_Size = 2;      //total amount of mode options
    int Direction_Array_Pos = 0;
    const String Direction_Array[Direction_Array_Size] = {"Forward", "Reverse"};
  //----Mode Options----//
    const int Mode_Array_Size = 8;      //total amount of mode options
    int Mode_Array_Pos = 0;
    const String Mode_Array[Mode_Array_Size] = {"Feed", "Thread", "A-Thread", "A-Turn", "Manual Z", "Manual X", "Radius", "Chamfer"};
  //----Measurement Options----//
    const int Measure_Array_Size = 2;      //total amount of mode options
    int Measure_Array_Pos = 0;
    const String Measure_Array[Measure_Array_Size] = {"In", "mm"};
  //----TPI Options----//
    const int TPI_Array_Size = 38;
    int TPI_Array_Pos = 17;
    const int TPI_Array[TPI_Array_Size] = {1,2,4,5,6,7,8,9,10,11,12,13,14,16,18,19,20,22,24,26,27,28,30,32,34,36,38,40,42,44,46,48,50,54,56,60,72,80};
  //----Pitch Options----//
    const int Pitch_Array_Size = 37;
    int Pitch_Array_Pos = 5;
    const float Pitch_Array[Pitch_Array_Size] = {.2, .3, .4, .5, .6, .7, .75, .8, .9, 1, 1.1, 1.25, 1.3, 1.4, 1.5, 1.75, 2, 2.25, 2.5, 2.75, 3, 3.5, 4, 4.5, 5, 6, 7, 8, 9, 10, 12, 14, 16, 18, 20, 22, 24};

double Current_time = 0;
double oldTime;

void Seven_Segment();
void Interface();
void Main_Menu();
void Mode_0_Feed_Controls();
void Feed_Clear();  
void Feed_Adjust();
void Mode_Selection();
void Mode_0_Feed_Controls();
void Mode_1_Thread_Controls();
void Mode_2_Auto_Thread_Controls();
void Start_Feed_Display();
void Feed();
void Thread();
void Feed_Clear();
int center(int ctr_int);
void RPM_Calc();
void Refresh();
void mm_Minor_Diameter();
void in_Minor_Diameter();
void Auto_Thread();
void Mode_2_SubMenu_Controls();
void Turn_to_Diameter();
void Mode_3_Auto_Turn_Controls();
void Auto_Feed_Adjust();
void Mode_3_SubMenu_Controls();
void Mode_2_SubMenu();
void Mode_3_SubMenu();
void Spindle_Angle();
void Manual_Z();
void Manual_X();
void Chamfer();
void Auto_Feed_Clear();
void Mode_6_SubMenu();
void Auto_Radius();
double  Z_Coord(double X_Coord);
double  Y_Coord(double Y_Coord);
void Build_ZY_Array();
void Start_Graph_Display();
void graph_Radius_Array();
void Mode_6_Auto_Radius_Controls();
void Mode_6_SubMenu_Controls();
void testgraph();
void Cut_Pass();
