void Feed() {
  double stepsPerSec;
  if (Metric == 0) {    // Inch Feedrate
    rpm = SpindleRPM*(In_FeedRate*In_FeedRate)*LeadScrew_TPI;
    stepsPerSec = ((rpm/60)*LeadSPR);                                 // This outputs rotations/second in steps
    stepsPerSec = stepsPerSec;                                               // This is where Forward and Reverse is dictaded, SpindleRPM will change this, however there may be a need to change it manually
    LeadScrew.setSpeed(stepsPerSec);
  }
  else if (Metric == 1) {     // Metric Feed Rate
    rpm = .00155*SpindleRPM*(mm_FeedRate*mm_FeedRate)*LeadScrew_TPI;
    stepsPerSec = ((rpm/60)*LeadSPR);                                 // This outputs rotations/second in steps
    stepsPerSec = stepsPerSec;                                               // This is where Forward and Reverse is dictaded, SpindleRPM will change this, however there may be a need to change it manually
    LeadScrew.setSpeed(stepsPerSec);
  }
}

void Turn_to_Diameter(){
 
}

void Manual_Z() {
//use Steps_Per_Thou or Steps_Per_hundredth_mm
}

void Manual_X() {

}

