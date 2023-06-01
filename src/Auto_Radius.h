
/*
Calculate the X/Y coords by using sine cosine
store the result in an array
the total number of array positions equals the amount of steps to take, this should be a user input
calculate the arrays before starting the spindle
have the user place the tool on the end of the work, tool position will create an origin of x == r and y == -radius

left hand or right hand?

ending point is at 270 degrees on the OD (x = -radius, -y = OD / 2 )
    right hand goes to 0 degrees  (+x = radius)
    left hand goes to  180 degres (-x = radius)
start of cut starts at Z,-Y (X,-Y)


user input: left/right ,steps (max of 100), radius, depth of cut

----Fillet Variables----
  const int Radius_Max_steps = 100;
  double Radius_X[Radius_Max_steps];
  double Radius_Y[Radius_Max_steps];
  int Radius_type = 3;         // 0 = left Convex 1 = right Convex 2 = left concave 3 = right concave
  double in_Radius_Radius = .5;
  double mm_Radius_Radius = 12;
  int Radius_Steps = 100;
  double R_Step_Angle = 0;
*/

void Auto_Radius() {
  R_Step_Angle = 90 / Radius_Steps;
}





void Build_X() {                        // Build Radius_X[Radius_Max_steps] array

}

double X_Chord(double X_Chord) {       // X Chord function
  X_Chord =1;
  return X_Chord;
}

void Build_Y() {                        // Build Radius_Y[Radius_Max_steps] array
  
}

double Y_Chord(double Y_Chord) {       // Y Chord function
  Y_Chord =1;
  return Y_Chord;
}