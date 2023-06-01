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

//----Fillet Variables----//
  const int Fillet_Max_steps = 100;
  double Fillet_X[Fillet_Max_steps];
  double Fillet_Y[Fillet_Max_steps];
  int Fillet_type = 3;         // 0 = left Convex 1 = right Convex 2 = left concave 3 = right concave
  double in_Fillet_Radius = .5;
  double mm_Fillet_Radius = 12;
  int Fillet_Steps = 100;
  double R_Step_Angle = 0;
*/

void Auto_Radius() {
  R_Step_Angle = 1;
}
