void Auto_Radius() {
  if (Build_XY == 0) {
    R_Step_Angle = 1.5708 / Radius_Steps;  // 90 degrees in radians / radius step value
    Build_XY_Array();
  }

// Setup Start_Pos array with current position
// Setup End_Pos array with desired move cordinate - a finish pass - DOC/Material to be removed
  //use: ZY_Steppers.moveTo(End_Pos);
// Finish Pass


}


void Build_XY_Array() {                        // Build Radius_X[Radius_Max_steps] array
  for (int array_step = 0; array_step < Radius_Steps; array_step++) {
    Radius_X[array_step] = X_Coord(array_step);  // X coordinate
    Radius_Y[array_step] = Y_Coord(array_step);  // Y coordinate
    //Serial.print(Radius_X[array_step], DEC);Serial.print(", ");Serial.print(Radius_Y[array_step], DEC);Serial.print("    ");Serial.println(array_step);
  }
  Build_XY = 1;
  //graph_Radius_Array();
}

double X_Coord(double X_Coord) {        // X Coord function
  X_Coord = in_Radius * cos((R_Step_Angle * X_Coord) + 4.71239);  // 4.71239 = 270 degrees in Radians
  return X_Coord;
}

double Y_Coord(double Y_Coord) {        // Y Coord function
  Y_Coord = in_Radius * sin((-R_Step_Angle * Y_Coord) + 4.71239);  // 4.71239 = 270 degrees in Radians
  return Y_Coord;
}

/*
plot x and y on oled on last page of settings to verify settings
have the user place the tool on the end of the work, tool position will create an origin of x == r and y == -radius

ending point is at 270 degrees (4.71239 Rad) on the OD (x = -radius, -y = OD / 2 )
    right hand goes to 0 degrees (O.00000 Rad)  (+x = radius)
    left hand goes to  180 degres (3.14159 Rad) (-x = radius)
start of cut starts at Z,-Y (X,-Y)

90 degress is 1.5708 rad


//----Position Variables----//
  double CrossZ;
  double LeadY;
  double Start_Pos[2];
  double End_Pos[2];

  move example:
    ZY_Steppers.moveTo(End_Pos);
*/