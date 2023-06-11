void Auto_Radius() {
  double final_pass;
  if (Build_ZY == 0) {
    R_Step_Angle = 1.5708 / Radius_Steps;   // 90 degrees in radians / radius step value
    Build_ZY_Array();                       // Build coordinate array of the radius

    //set feedrate (chip load?)

    Set_Radius_Start_Postion();             // Set motor start position in Steps, mm/in conversion already done
  }
  
//----Should work for all radius types----// 
  if (SpindleRPM != 0) {            //auto radius rough cut
    if (Z_step <= Radius_Steps) {
      if (ZY_Movement() == 0 && status == 0) {
        if (Metric == 0) {final_pass = final_pass_in;} else {final_pass = final_pass_mm;}  // Sets up amount to be left for final pass
        if (Radius_type == 0 || Radius_type == 2) {final_pass = final_pass * -1;}          // Radius type 0 and 2 requres Z to move in the opposite direction 
        End_Pos[0] = Steps_per_Move(Radius_Z[Z_step]) + Steps_per_Move(final_pass);        // Leaves material for the final pass
        End_Pos[1] = Steps_per_Move(Radius_Y[Y_step]);
        ZY_Steppers.moveTo(End_Pos);                   // Move to "End Position"  This is closest to the feature
        status = 1;
      }
      if (ZY_Movement() == 0 && status == 1) {  // this starts the cut in the opposite direction
        Z_step++;
        Y_step++;
        Start_Pos[1] = Steps_per_Move(Radius_Y[Y_step]);                            // Resets the Y position to be current, and not at 0.0
        ZY_Steppers.moveTo(Start_Pos); 
        status = 0;
      }
      if (Z_step == Radius_Steps) {
        status = 3;
        Z_step = 0;                    // reset X and Y counters now that all roughing passes are complete
        Y_step = 0;
      } 
    } 
    if (ZY_Movement() == 0 && status == 3) {        // auto radius final pass
      //final pass
    }
    if (ZY_Movement() == 0 && status == 4) {        // auto radius return to start positon
      Set_Radius_Start_Postion();
    }
  }
}

/** @brief Builds two arrays: Radius_Z and Radius_Y
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

/** @brief Provides a single coordinate in the Radius_Z array
    @param Z_Coord  : A modified step angle within a quadrant of a circle
*/
double Z_Coord(double Z_Coord) {        // X Coord function
  Z_Coord = in_Radius * cos((R_Step_Angle * Z_Coord) + 4.71239);  // 4.71239 = 270 degrees in Radians
  return Z_Coord;
}

/** @brief Provides a single coordinate in the Radius_Y array
    @param Y_Coord  : A modified step angle within a quadrant of a circle
*/
double Y_Coord(double Y_Coord) {        // Y Coord function
  Y_Coord = in_Radius * sin((-R_Step_Angle * Y_Coord) + 4.71239);  // 4.71239 = 270 degrees in Radians
  return Y_Coord;
}

/** @brief Determains how many total cut passes there should be, possibly depreciated */
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

/** @brief  sets the starting position of each radius type using the current tool position */
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

