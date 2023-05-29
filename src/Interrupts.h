
//----This is activated every "RPM_Check_INTERVAL_MS" interval in order to calculate an accurate PRM---//
void RPM_Calc() {   //calculate RPM w/fastest optimizations
  cli();    //disable interrupts
  newSpindle = spindle.read();
  sei();    //re-enable interrupts
  if (newSpindle > spindleCount) {
    S_Dir = 1;    //set Direction to forward
  } else if (newSpindle < spindleCount) {
    S_Dir = 0;    //set direction to reverse
  } else if (newSpindle == 0) {
    S_Dir = 2;    //set direction to park
  }
  spindleCount = newSpindle;
  double num;
  double den;
  num = (60000*spindleCount);
  den = (SpindleCPR*(RPM_Check_INTERVAL_MS/1000));
  SpindleRPM = num/den;

  //get rid of the cleanup variables  subtract new from old for calcs above
  spindleCount = 0;     //cleanup
  newSpindle = 0;       //cleanup
  spindle.write(0);     //cleanup
  //LeadScrew.runSpeed();   //run leadscrew stepper at whatever .setspeed() is set to.  Added to this interrupt timer function so that it is called as often as possible, 
  //                      //Add to Spindle_Angle() if it needs to be called more often
  //Serial.println(digitalRead(LeadDir));
}

//----This is Activated every time the A/B Channels on the encoder change state----//
void Spindle_Angle() {
  cli();
  Spindle_Rotations = spindle.read() / SpindleCPR;
  Encoder_Angle = spindle.read() - Spindle_Rotations;     //this will give the encoder position withing a single 360 degree rotation
  sei();
  //if encoder angle = original start angle then start leadscrew
}