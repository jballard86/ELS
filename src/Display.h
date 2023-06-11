/**
  @brief Refreshes the Display periodically based the  Refresh_Rate_Timer timer
*/
void Refresh() {
  if (Enc1.getEncoderPosition() != Mode_Array_Pos && SpindleRPM !=0) {Enc1.setEncoderPosition(Mode_Array_Pos);}  //this keeps the mode from being adjusted while the spindle is running
  
  Seven_Segment();                // Update Seven Segment Display with current RPM

  if (SpindleRPM == 0) {
    Interface();
    Main_Menu();
    Feed_Display.display();
    }
  if (Mode_Array_Pos == 0 && SpindleRPM != 0) {   // Feed rates dont need to be as accurate as threading, so feedrates can be adjustable on the fly
    Mode_0_Feed_Controls();       //  read if feed encoder has been turned
    Feed_Clear();                 //  clear feed value from OLED
    Feed_Adjust();                //  Redraw Feed value
    Feed_Display.display();
  }
  if (Mode_Array_Pos == 3 && SpindleRPM != 0) {   // Feed rates dont need to be as accurate as threading, so feedrates can be adjustable on the fly
    Mode_3_Auto_Turn_Controls();       //  read if feed encoder has been turned
    Auto_Feed_Clear();                 //  clear feed value from OLED
    Auto_Feed_Adjust();                //  Redraw Feed value
    Feed_Display.display();
  }

  if (SpindleRPM == 0) {                //do a full screen on feed display as the last sub menu option, draw the bar stock, and do an accurate fillet/radius, show where tool should go to start feature
    Graph_Display.clearDisplay();
    graph_Radius_Array();
    Graph_Display.display();
  }
  if (Mode_Array_Pos == 6 && submenu == 5 && SpindleRPM != 0){    //this allows the operation to be stopped when running
    start_or_stop();
    Radius_Update();
    Feed_Display.display();
  }
  
}

void Start_Feed_Display() {
  Feed_Display.begin(0x3D);   // starts the feed display oled
  delay(100);
  Feed_Display.clearDisplay();
  Feed_Display.setTextSize(1);                  // sizes 1-8
  Feed_Display.setTextColor(SSD1327_WHITE);     
  Feed_Display.setCursor(0,0);
  Feed_Display.println("Jefferson ELS v1.1");
  Feed_Display.display();
}

void Start_Graph_Display() {
  Graph_Display.begin(0x3C);   // starts the feed display oled
  delay(100);
  Graph_Display.clearDisplay();
  Graph_Display.setTextSize(1);                  // sizes 1-8
  Graph_Display.setTextColor(SSD1327_WHITE);     
  Graph_Display.setCursor(0,0);
  Graph_Display.println("Jefferson ELS v1.1");
  Graph_Display.display();

  Graph_Display.display();
}

void Seven_Segment() {
  
  int DisplayRPM = SpindleRPM;        // converts the double to a Int and gets rid of the decimal, rounding is irrelevant for this action
  matrix.print(DisplayRPM);           // This will display the RPM on the seven segment display
  matrix.writeDisplay();              // This will send the RPM data to the 7 segment display
}

// OLED greyscale values (white to black): 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x10, 0x18, 0x20, 0x2f, 0x38, 0x3f

void graph_Radius_Array(){
  double scale = 128 / in_Radius;
  
  for (int array_step = 0; array_step < Radius_Steps; array_step++) {
      Graph_Display.drawPixel(Radius_Z[array_step] * scale, Radius_Y[array_step] * -scale, SSD1327_WHITE);
      //Serial.println(array_step);
  }
  
}

void Auto_Radius_Draw() {

  if (Radius_type == 0) {
    Feed_Display.fillRect(28,45,128,40,SSD1327_WHITE);
    Feed_Display.fillCircle(28,85,18,SSD1327_BLACK);  //y = y1+y2 from fillrect
    
  }
  if (Radius_type == 1) {
    Feed_Display.fillRect(0,45,100,40,SSD1327_WHITE);
    Feed_Display.fillCircle(100,85,18,SSD1327_BLACK);  //y = y1+y2 from fillrect
    
  }
  if (Radius_type == 2) {
    Feed_Display.fillRect(28,45,128,40,SSD1327_WHITE);
    Feed_Display.fillCircle(28,85,18,SSD1327_BLACK);  //y = y1+y2 from fillrect
    Feed_Display.fillCircle(28+19,85-19,18,SSD1327_WHITE);  //y = y1+y2 from fillrect
    
  }
  if (Radius_type == 3) {
    Feed_Display.fillRect(0,45,100,40,SSD1327_WHITE);
    Feed_Display.fillCircle(100,85,18,SSD1327_BLACK);  //y = y1+y2 from fillrect
    Feed_Display.fillCircle(100-19,85-19,18,SSD1327_WHITE);  //y = y1+y2 from fillrect
    
  }
  Feed_Display.setTextSize(1);
  Feed_Display.setCursor(0,90);
  Feed_Display.println("Press Right Encoder  to start");
  Feed_Display.println("Scroll Left Wheel to stop");

  
}