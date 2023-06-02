void Auto_Radius() {
  R_Step_Angle = 1.5708 / Radius_Steps;  // 90 degrees in radians / radius step value
  if (Build_XY == 0) {Build_XY_Array();}
  //Build_Y;
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
Calculate the X/Y coords by using sine cosine
store the result in an array
the total number of array positions equals the amount of steps to take, this should be a user input
calculate the arrays before starting the spindle
have the user place the tool on the end of the work, tool position will create an origin of x == r and y == -radius

left hand or right hand?

ending point is at 270 degrees (4.71239 Rad) on the OD (x = -radius, -y = OD / 2 )
    right hand goes to 0 degrees (O.00000 Rad)  (+x = radius)
    left hand goes to  180 degres (3.14159 Rad) (-x = radius)
start of cut starts at Z,-Y (X,-Y)

90 degress is 1.5708 rad

user input: left/right ,steps (max of 100), radius, depth of cut

----Fillet Variables----
  const int Radius_Max_steps = 100;
  double Radius_X[Radius_Max_steps];
  double Radius_Y[Radius_Max_steps];
  int Radius_type = 3;         // 0 = left Convex 1 = right Convex 2 = left concave 3 = right concave
  double in_Radius = .5;
  double mm_Radius = 12;
  int Radius_Steps = 100;
  double R_Step_Angle = 0;
*/ 