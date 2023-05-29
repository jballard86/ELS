

void Thread() {
  
  if (Thread_Mode == 0) {            //----Inch Threading----//
    TPI = TPI_Array[TPI_Array_Pos];
    rpm = ((LeadScrew_TPI*(SpindleRPM))/(TPI * TPI));        // This outputs Leadscrew RPM
    rpm = ((rpm/60)*LeadSPR);                                 // This outputs rotations/second in steps
    rpm = rpm;                                               // This is where Forward and Reverse is dictaded, SpindleRPM will change this, however there may be a need to change it manually
    LeadScrew.spin(rpm);
    //Serial.println(rpm);
    //Serial.println(digitalRead(LeadDir));
  } 
  else if (Thread_Mode == 1) {    //----Metric Threading----//
    Pitch = Pitch_Array[Pitch_Array_Pos];
    rpm = .00155*SpindleRPM*LeadScrew_TPI*(Pitch*Pitch);
    rpm = ((rpm/60)*LeadSPR);
    LeadScrew.spin(rpm);  //this should output RPM in steps/sec  
  }
}

void mm_Minor_Diameter() {
  // only ran when called for in menu, not while lathe is running
  // May have to add a fit class calculation
  mm_Thread_Height = Pitch * (sqrt(3)/2);                      //perfect thread depth
  Minor_Diameter = Outside_Diameter - 2 *(5/8) * mm_Thread_Height;
  mm_Thread_Height = (Outside_Diameter - Minor_Diameter) / 2;               //actual thread depth
}

void in_Minor_Diameter() {
  // only ran when called for in menu, not while lathe is running
  // May have to add a fit class calculation
  Minor_Diameter = Outside_Diameter - .625 * sqrt(3) * (1/TPI);
  in_Thread_Height = Minor_Diameter / 2;
}

void Auto_Thread() {
  //use "Encoder_Angle" to save the spindle angle when starting the thread, and then use the saved value to start the thread
  //may have to parse info to and from "Spindle_Angle()"
  //mm_Thread_Height will give the cutting depth for the thread (radius)
  //in_Thread_Height will give the cutting depth for the thread (radius)
}
 