void Feed() {
  if (Metric == 0) {    // Inch Feedrate
    rpm = SpindleRPM*(In_FeedRate*In_FeedRate)*LeadScrew_TPI;
    rpm = ((rpm/60)*LeadSPR);                                 // This outputs rotations/second in steps
    rpm = rpm;                                               // This is where Forward and Reverse is dictaded, SpindleRPM will change this, however there may be a need to change it manually
    LeadScrew.spin(rpm);
  }
  else if (Metric == 1) {     // Metric Feed Rate
    rpm = .00155*SpindleRPM*(mm_FeedRate*mm_FeedRate)*LeadScrew_TPI;
    rpm = ((rpm/60)*LeadSPR);                                 // This outputs rotations/second in steps
    rpm = rpm;                                               // This is where Forward and Reverse is dictaded, SpindleRPM will change this, however there may be a need to change it manually
    LeadScrew.spin(rpm);    
  }
}