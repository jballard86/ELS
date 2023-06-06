
//----This is activated every "RPM_Check_INTERVAL_MS" interval in order to calculate an accurate PRM---//
void RPM_Calc() {   //calculate RPM w/fastest optimizations

  long long SpindleChange;

  cli();    //disable interrupts
  newSpindle = spindle.read();
  sei();    //re-enable interrupts

  SpindleChange = newSpindle - oldSpindle;
  double num;
  double den;
  num = (60000*SpindleChange);
  den = (SpindleCPR*(RPM_Check_INTERVAL_MS/1000));
  SpindleRPM = num/den;
  oldSpindle = newSpindle;
}

//----This is polled when a specific angle is needed to be stored----//
void Spindle_Angle() {
  cli();
  newSpindle = spindle.read();
  sei();

  TotalRotations = newSpindle / SpindleCPR;
  TotalRot_noDEC = TotalRotations;                                // Convert the value to an int, so that the whole number can be easily removed
  Encoder_Angle = ((TotalRotations - TotalRot_noDEC))*360;
  
  //if encoder angle = original start angle then start leadscrew
}