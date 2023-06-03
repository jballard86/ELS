void Feed() {
  if (Metric == 0) {    // Inch Feedrate
    double rpm = SpindleRPM*(In_FeedRate*In_FeedRate)*LeadScrew_TPI;
    rpm = ((rpm/60)*LeadSPR);                                 // This outputs rotations/second in steps
    rpm = rpm;                                               // This is where Forward and Reverse is dictaded, SpindleRPM will change this, however there may be a need to change it manually
    //LeadScrew.spin(rpm);
    LeadScrew.setSpeed(rpm);

  }
  else if (Metric == 1) {     // Metric Feed Rate
    double rpm = .00155*SpindleRPM*(mm_FeedRate*mm_FeedRate)*LeadScrew_TPI;
    rpm = ((rpm/60)*LeadSPR);                                 // This outputs rotations/second in steps
    rpm = rpm;                                               // This is where Forward and Reverse is dictaded, SpindleRPM will change this, however there may be a need to change it manually
    //LeadScrew.spin(rpm);    
    LeadScrew.setSpeed(rpm);
  }
}

void Turn_to_Diameter(){
 
}

void Manual_Z() {
//use Steps_Per_Thou or Steps_Per_hundredth_mm
}

void Manual_X() {

}

