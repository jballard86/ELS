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


*/