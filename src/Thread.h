// https://www.machiningdoctor.com/charts/metric-thread-charts/
// https://www.machiningdoctor.com/charts/unified-inch-threads-charts/

void Thread() {
  
  if (Thread_Mode == 0) {            //----Inch Threading----//
    TPI = TPI_Array[TPI_Array_Pos];
    double rpm = ((LeadScrew_TPI*(SpindleRPM))/(TPI * TPI));        // This outputs Leadscrew RPM
    rpm = ((rpm/60)*LeadSPR);                                 // This outputs rotations/second in steps
    rpm = rpm;                                               // This is where Forward and Reverse is dictaded, SpindleRPM will change this, however there may be a need to change it manually
    //LeadScrew.spin(rpm);
    LeadScrew.setSpeed(rpm);
    //Serial.println(rpm);
    //Serial.println(digitalRead(LeadDir));
  } 
  else if (Thread_Mode == 1) {    //----Metric Threading----//
    Pitch = Pitch_Array[Pitch_Array_Pos];
    double rpm = .00155*SpindleRPM*LeadScrew_TPI*(Pitch*Pitch);
    rpm = ((rpm/60)*LeadSPR);
    //LeadScrew.spin(rpm);  //this should output RPM in steps/sec  
    LeadScrew.setSpeed(rpm);
  }
}

void Auto_Thread() {
  // use "Encoder_Angle" to save the spindle angle when starting the thread, and then use the saved value to start the thread
  // may have to parse info to and from "Spindle_Angle()"
  // add a thread root? calculate proper dims based off of thread?

  /* Variables that are already declared: 
      in_DOC / mm_DOC - depth of cutting pass - user input
      in_Outside_Diameter / mm_Outside_Diameter - Outer Diameter of thread - user input
      in_length_of_cut / mm_length_of_cut - Length of thread - user input
      in_Thread_Depth / mm_Thread_Depth - total depth of thread - calculated
  */

  Spindle_Angle();                      // will need to be continuously polled inorder to start at the same angle with each restart
  //----Calculate Thread Depth----//
  if (Thread_Mode == 0 && SpindleRPM == 0) {in_Minor_Diameter();}  // dont want to do unneccessary calcs while the spindle is turning
  if (Thread_Mode == 1 && SpindleRPM == 0) {mm_Minor_Diameter();}  // dont want to do unneccessary calcs while the spindle is turning

  //start feed if Current Encoder angle == original encoder angle

}

void mm_Minor_Diameter() {
  // only ran when called for in menu, not while lathe is running
  // May have to add a fit class calculation
  Pitch = Pitch_Array[Pitch_Array_Pos];
  float Height = .866025404 * Pitch;
  mm_Thread_Depth = .625 * Height;
}

void in_Minor_Diameter() {
  // only ran when called for in menu, not while lathe is running
  // May have to add a fit class calculation
  TPI = TPI_Array[TPI_Array_Pos];
  float in_Pitch = 1/TPI;
  float Height = .866025404 * in_Pitch;
  in_Thread_Depth = .625 * Height;
} 