void Auto_Radius() {
  double stepsPerSec;

  if (Build_ZY == 0) {
    R_Step_Angle = 1.5708 / Radius_Steps;   // 90 degrees in radians / radius step value
    Build_ZY_Array();                       // Build coordinate array of the radius

    //set feedrate (chip load?)

    Set_Radius_Start_Postion();             // Set motor start position in Steps, mm/in conversion already done
  }
  
//----Will this work for all radius types?----//

if (SpindleRPM != 0) {            //auto radius rough cut
  if (Z_step <= Radius_Steps) {
    if (LeadScrew.distanceToGo() == 0 && CrossSlide.distanceToGo() == 0) {
      if (status == 0){
        End_Pos[0] = Steps_per_Move(Radius_Z[Z_step]); 
        End_Pos[1] = Steps_per_Move(Radius_Y[Y_step]);
        ZY_Steppers.moveTo(End_Pos);
        status = 1;
        Serial.print("works"); Serial.println(Z_step);
      }
      if (status == 1) {
        ZY_Steppers.moveTo(Start_Pos);
      Z_step++;
      Y_step++; 
      status = 0;
      if (Z_step == Radius_Steps) {status = 3;}
      }
    } 
  } 
  if (LeadScrew.distanceToGo() == 0 && CrossSlide.distanceToGo() == 0) {        // auto radius finaly pass
    if (status == 3) {
      Z_step = 0;
      Y_step = 0;
      //final pass
    }
  }
  //Serial.print(Z_step);
  //Z_step = 0;
  //Y_step = 0;
  //run final pass
}

  // Set home position based off of Radius_Type
  // loop * cut_passes
      //start at x=0, y=radius and move to x = radius, y = y-DOC, repeat cut_passes, add allowance for final pass
  // loop * final pass
      // This cuts Build_XY_Array() with out and modifiers

    // Setup Start_Pos array with current position
    // Setup End_Pos array with desired move cordinate:
      // Position = finish pass - DOC/Material to be removed 
      // End_Pos[0] = Radius_Z[0];
      // End_Pos[1] = Radius_Y[0];
      // use: ZY_Steppers.moveTo(End_Pos);
    // Finish Pass

}
/**
  @brief Builds two arrays: Radius_Z and Radius_Y
*/
void Build_ZY_Array() {                       
  double modZ;
  double modY;
  double Radius;
  if (Metric == 0) {Radius = in_Radius;} else {Radius = mm_Radius;}
  if (Radius_type == 0) {modZ = -1;}    // left hand convex modifier
  if (Radius_type == 1) {modZ =  1;}    // Right hand convex modifier
  if (Radius_type == 2) {modZ =  1; modY = -1;}    // Right hand convex modifier
  if (Radius_type == 3) {modZ =  -1; modY = -1;}    // Right hand convex modifier

  if (Radius_type <= 1) {
    for (int array_step = 0; array_step < Radius_Steps; array_step++) {
      Radius_Z[array_step] = modZ * Z_Coord(array_step);  // Z coordinate
      Radius_Y[array_step] = Y_Coord(array_step);  // Y coordinate
      Serial.print(Radius_Z[array_step], DEC);Serial.print(", ");Serial.print(Radius_Y[array_step], DEC);Serial.print("    ");Serial.println(array_step);
    }
  }

  if (Radius_type >= 2) {
    for (int array_step = 0; array_step < Radius_Steps; array_step++) {
      Radius_Z[array_step] = modZ * Z_Coord(array_step);  // Z coordinate
      Radius_Y[array_step] = (modY * Y_Coord(array_step))-(Radius);  // Y coordinate
      Serial.print(Radius_Z[array_step], DEC);Serial.print(" ");Serial.print(Radius_Y[array_step], DEC);Serial.print("    ");Serial.println(array_step);
    }
  }

  Build_ZY = 1;
}

/**
  @brief Provides a single coordinate in the Radius_Z array
  @param Z_Coord  : A modified step angle within a quadrant of a circle
*/
double Z_Coord(double Z_Coord) {        // X Coord function
  Z_Coord = in_Radius * cos((R_Step_Angle * Z_Coord) + 4.71239);  // 4.71239 = 270 degrees in Radians
  return Z_Coord;
}

/**
  @brief Provides a single coordinate in the Radius_Y array
  @param Y_Coord  : A modified step angle within a quadrant of a circle
*/
double Y_Coord(double Y_Coord) {        // Y Coord function
  Y_Coord = in_Radius * sin((-R_Step_Angle * Y_Coord) + 4.71239);  // 4.71239 = 270 degrees in Radians
  return Y_Coord;
}

void Cut_Pass() {       // This is only calculated while the Depth of Cut Submenu is active
  double Radius;
  double DOC;
  double hypotenuse;
  if (Metric == 0) {Radius = in_Radius;} else {Radius = mm_Radius;}
  if (Metric == 0) {DOC = in_DOC;} else {DOC = mm_DOC;}
  if (Radius_type <= 1) {
    hypotenuse = sqrt(2*(Radius*Radius));
    Cut_Depth = hypotenuse - Radius;
  }
  if (Radius_type >= 2) {
    Cut_Depth = Radius;
  }
  Cut_Passes = Cut_Depth / DOC;
}

void Set_Radius_Start_Postion(){
  double Radius;
  if (Metric == 0) {Radius = in_Radius;} else {Radius = mm_Radius;}
  if (Radius_type == 0) {
    LeadScrew.setCurrentPosition(-Steps_per_Move(Radius));
    CrossSlide.setCurrentPosition(-Steps_per_Move(Radius));
    }
  if (Radius_type == 1) {
    LeadScrew.setCurrentPosition(Steps_per_Move(Radius));
    CrossSlide.setCurrentPosition(-Steps_per_Move(Radius));
  }
  if (Radius_type == 2) {
    LeadScrew.setCurrentPosition(0);
    CrossSlide.setCurrentPosition(-Steps_per_Move(Radius));
  }
  if (Radius_type == 3) {
    LeadScrew.setCurrentPosition(0);
    CrossSlide.setCurrentPosition(-Steps_per_Move(Radius));
  }

  Start_Pos[0] = LeadScrew.currentPosition();
  Start_Pos[1] = CrossSlide.currentPosition();
}
/*
//----Position Variables----//
  double CrossZ;
  double LeadY;
  double Start_Pos[2];
  double End_Pos[2];

  move example:
    ZY_Steppers.moveTo(End_Pos);
*/