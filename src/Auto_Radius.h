void Auto_Radius() {
  R_Step_Angle = 1.5708 / Radius_Steps;  // 90 degrees in radians / radius step value
  Build_X();
  //Build_Y;
}


void Build_X() {                        // Build Radius_X[Radius_Max_steps] array
  int array_step = 0;
  while (array_step != Radius_Steps - 1) {
    array_step++;
    X_Chord(array_step);  //embed this into the array it is the x value of array pos 0++
    
    }
}

double X_Chord(double X_Chord) {       // X Chord function
  X_Chord = in_Radius * cos(R_Step_Angle * X_Chord);
  return X_Chord;
}


/*
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