void Main_Menu() {              // Main Menu
  
  Feed_Display.clearDisplay();
  Feed_Display.setTextColor(SSD1327_WHITE);
  Feed_Display.setTextSize(2); 
  Feed_Display.setCursor(center(Mode_Array[Mode_Array_Pos].length()),0);
  Feed_Display.println(Mode_Array[Mode_Array_Pos]);

  //----Feed----//
  if (Mode_Array_Pos == 0) {
    Feed_Display.setCursor(19,30);
      if (Measure_Array_Pos == 0) {
        Feed_Display.fillRect(18,29,Measure_Array[0].length() * 12 + 1,16,SSD1327_WHITE);       //fill selection with a contrasting rectangle
        Feed_Display.setTextColor(SSD1327_BLACK);
        Feed_Display.print(Measure_Array[0]);
        Feed_Display.setTextColor(SSD1327_WHITE);
      } else {
        Feed_Display.setTextColor(SSD1327_WHITE);
        Feed_Display.print(Measure_Array[0]);
      }
      Feed_Display.print(" / "); 
      if (Measure_Array_Pos == 1) {
        Feed_Display.fillRect(77,29,Measure_Array[1].length() * 12 + 2,16,SSD1327_WHITE);       //fill selection with a contrasting rectangle
        Feed_Display.setTextColor(SSD1327_BLACK);
        Feed_Display.print(Measure_Array[1]);
        Feed_Display.setTextColor(SSD1327_WHITE);        
      } else {
        Feed_Display.setTextColor(SSD1327_WHITE);
        Feed_Display.print(Measure_Array[1]);
      }
    Feed_Adjust();
  
  }

  //----Thread----//
  if (Mode_Array_Pos == 1) {
    Feed_Display.setTextSize(2);
    Feed_Display.setCursor(2,30);
      if (Thread_Mode == 0) {
        Feed_Display.fillRect(0,29,36,16,SSD1327_WHITE);       //fill selection with a contrasting rectangle
        Feed_Display.setTextColor(SSD1327_BLACK);
        Feed_Display.print("TPI ");
        Feed_Display.setTextColor(SSD1327_WHITE);
      } else {
        Feed_Display.setTextColor(SSD1327_WHITE);
        Feed_Display.print("TPI");
      }
      Feed_Display.print("/"); 
      if (Thread_Mode == 1) {
        Feed_Display.fillRect(59,29,64,16,SSD1327_WHITE);       //fill selection with a contrasting rectangle
        Feed_Display.setTextColor(SSD1327_BLACK);
        Feed_Display.print(" Pitch");
        Feed_Display.setTextColor(SSD1327_WHITE);
        
      } else {
        Feed_Display.setTextColor(SSD1327_WHITE);
        Feed_Display.print("Pitch");
      }
    Feed_Display.setTextSize(4);
    if (Thread_Mode == 0) {Feed_Display.setCursor(35,55); Feed_Display.print(TPI_Array[TPI_Array_Pos]);}
    else {
      int DECp;
      if (Pitch_Array[Pitch_Array_Pos] > 9) {DECp = 1;}   // this allows us to shorten the decimal point of the array when displayed so that we dont wrap the decimal to the next line
      else {DECp = 2;}
      Feed_Display.setCursor(10,55); Feed_Display.print(Pitch_Array[Pitch_Array_Pos], DECp); }
      Feed_Display.setTextSize(2); Feed_Display.setCursor(80,100); Feed_Display.println("(mm)");
  }

  //----Auto Thread----//
  if (Mode_Array_Pos == 2) {
    Feed_Display.setTextSize(2);
    Feed_Display.setCursor(2,20);
      if (Thread_Mode == 0) {
        Feed_Display.fillRect(0,19,36,16,SSD1327_WHITE);       //fill selection with a contrasting rectangle
        Feed_Display.setTextColor(SSD1327_BLACK);
        Feed_Display.print("TPI ");
        Feed_Display.setTextColor(SSD1327_WHITE);
      } else {
        Feed_Display.setTextColor(SSD1327_WHITE);
        Feed_Display.print("TPI");
      }
      Feed_Display.print("/"); 
      if (Thread_Mode == 1) {
        Feed_Display.fillRect(59,19,64,16,SSD1327_WHITE);       //fill selection with a contrasting rectangle
        Feed_Display.setTextColor(SSD1327_BLACK);
        Feed_Display.print(" Pitch");
        Feed_Display.setTextColor(SSD1327_WHITE);
        
      } else {
        Feed_Display.setTextColor(SSD1327_WHITE);
        Feed_Display.print("Pitch");
      }
    Feed_Display.setTextSize(4);
    if (Thread_Mode == 0) {Feed_Display.setCursor(35,45); Feed_Display.print(TPI_Array[TPI_Array_Pos]);}
    else {
      int DECp;
      if (Pitch_Array[Pitch_Array_Pos] > 9) {DECp = 1;} // this allows us to shorten the decimal point of the array when displayed so that we dont wrap the decimal to the next line
      else {DECp = 2;}
      Feed_Display.setCursor(10,45); Feed_Display.print(Pitch_Array[Pitch_Array_Pos], DECp); }
    Feed_Display.setTextSize(1); Feed_Display.setCursor(0,80); Feed_Display.print("Cut Depth:    ");
      if (Thread_Mode == 0) {Feed_Display.print(" "); Feed_Display.print(in_DOC,3);}
      if (Thread_Mode == 1) {Feed_Display.print(" "); Feed_Display.print(mm_DOC,2);} 
    Feed_Display.setTextSize(1); Feed_Display.setCursor(0,92); Feed_Display.print("Thread Dia:   ");
      if (Thread_Mode == 0) {Feed_Display.print(" "); Feed_Display.print(in_Outside_Diameter,3);}
      if (Thread_Mode == 1) {Feed_Display.print(" "); Feed_Display.print(mm_Outside_Diameter,2);}
    Feed_Display.setTextSize(1); Feed_Display.setCursor(0,104); Feed_Display.print("Thread Length:");
      if (Thread_Mode == 0) {Feed_Display.print(" "); Feed_Display.print(in_length_of_cut,3);}
      if (Thread_Mode == 1) {Feed_Display.print(" "); Feed_Display.print(mm_length_of_cut,3);}
    Feed_Display.setTextSize(1); Feed_Display.setCursor(0,116); Feed_Display.print("Thread Depth:  ");
      if (Thread_Mode == 0) {Feed_Display.println(in_Thread_Depth,4);}
      if (Thread_Mode == 1) {Feed_Display.println(mm_Thread_Depth,3);}
  }

  //----Auto Turn----//
  if (Mode_Array_Pos == 3) {
    Feed_Display.setTextSize(2);
    Feed_Display.setCursor(19,20);
      if (Thread_Mode == 0) {
        Feed_Display.fillRect(18,19,Measure_Array[0].length() * 12 + 1,16,SSD1327_WHITE);       //fill selection with a contrasting rectangle
        Feed_Display.setTextColor(SSD1327_BLACK);
        Feed_Display.print("In ");
        Feed_Display.setTextColor(SSD1327_WHITE);
      } else {
        Feed_Display.setTextColor(SSD1327_WHITE);
        Feed_Display.print("In ");
      }
      Feed_Display.print("/"); 
      if (Thread_Mode == 1) {
        Feed_Display.fillRect(77,19,Measure_Array[1].length() * 12 + 2,16,SSD1327_WHITE);       //fill selection with a contrasting rectangle
        Feed_Display.setTextColor(SSD1327_BLACK);
        Feed_Display.print(" mm");
        Feed_Display.setTextColor(SSD1327_WHITE);
        
      } else {
        Feed_Display.setTextColor(SSD1327_WHITE);
        Feed_Display.print(" mm");
      }
    Auto_Feed_Adjust();
    Feed_Display.setTextSize(1); Feed_Display.setCursor(0,80); Feed_Display.print("    D.O.C.:  ");
      if (Thread_Mode == 0) {Feed_Display.print(" "); Feed_Display.print(in_DOC,3);}
      if (Thread_Mode == 1) {Feed_Display.print(" "); Feed_Display.print(mm_DOC,2);} 
    Feed_Display.setTextSize(1); Feed_Display.setCursor(0,92); Feed_Display.print("Cut Length: ");
      if (Thread_Mode == 0) {Feed_Display.print(" "); Feed_Display.print(in_length_of_cut,3);}
      if (Thread_Mode == 1) {Feed_Display.print(" "); Feed_Display.print(mm_length_of_cut,3);}
    Feed_Display.setTextSize(1); Feed_Display.setCursor(0,104); Feed_Display.print("Current OD: ");
      if (Thread_Mode == 0) {Feed_Display.print(" "); Feed_Display.print(in_Outside_Diameter,3);}
      if (Thread_Mode == 1) {Feed_Display.print(" "); Feed_Display.print(mm_Outside_Diameter,2);}
    Feed_Display.setTextSize(1); Feed_Display.setCursor(0,116); Feed_Display.print("  Final OD: ");
      if (Thread_Mode == 0) {Feed_Display.print(" "); Feed_Display.print(in_Final_Diameter,3);}
      if (Thread_Mode == 1) {Feed_Display.print(" "); Feed_Display.print(mm_Final_Diameter,2);}
  }

  //----Place holder for unused modes----//
  if (Mode_Array_Pos > 3) {
    Feed_Display.setCursor(0 + Mode_Array_Pos * 6, 30 + Mode_Array_Pos * 5);
    Feed_Display.println("Coming");
    Feed_Display.setCursor(0 + Mode_Array_Pos * 10, 60 + Mode_Array_Pos * 5);
    Feed_Display.print("Soon");
  }
  
  Mode_2_SubMenu();
  Mode_3_SubMenu();
}

void Feed_Adjust(){             // Feed Adjust sub routine
  Feed_Display.setTextSize(4);
  Feed_Display.setCursor(0,55);
  if (Measure_Array_Pos == 0) {Feed_Display.print(In_FeedRate, 3);}
  else {Feed_Display.print(mm_FeedRate, 3);}
}

void Auto_Feed_Adjust() {       // Auto Feed Adjust sub Routine
  Feed_Display.setTextSize(4);
  Feed_Display.setCursor(0,45);
  if (Measure_Array_Pos == 0) {Feed_Display.print(In_FeedRate, 3);}
  else {Feed_Display.print(mm_FeedRate, 3);}
}

int center(int ctr_int) {       // Center of Sting Function     
  ctr = 55-((9 * ctr_int)/2);
  return ctr;
}

void Feed_Clear(){              // Clear Feed Rate on Main Menu
  Feed_Display.fillRect(0,55,128,30,SSD1327_BLACK);
}

void Mode_2_SubMenu() {         // Auto Thread Sub Menu
  // need DOC, Thread Diameter, Thread Length
  if (Mode_Array_Pos == 2 && submenu >= 1) {
    Feed_Display.clearDisplay();
      if (submenu >= 1 && Mode_Array_Pos == 2) {
        //Feed_Display.clearDisplay();
        Feed_Display.setTextColor(SSD1327_WHITE);
        Feed_Display.setTextSize(2); 
        Feed_Display.setCursor(0,0);
        Feed_Display.println("   Auto");
        Feed_Display.println("Threading");
      }
    if (submenu == 1) {                                   // submenu page one --- Thread Length
      Feed_Display.setCursor(0,45);
      Feed_Display.println("  Input");
      Feed_Display.setCursor(0,65);
      Feed_Display.println("Cut Length");
      Feed_Display.setCursor(0,100);
        if (Thread_Mode == 0) {Feed_Display.print(" "); Feed_Display.print(in_length_of_cut,3); Feed_Display.println(" in");}
        if (Thread_Mode == 1) {Feed_Display.print(" "); Feed_Display.print(mm_length_of_cut,3); Feed_Display.println(" mm");} 
    }
    if (submenu == 2) {                                   // submenu page two --- Thread Diameter
      Feed_Display.setCursor(0,45);
      Feed_Display.println("  Input");
      Feed_Display.setCursor(0,65);
      Feed_Display.println("Thread OD");
      Feed_Display.setCursor(0,100);
      if (Thread_Mode == 0) {Feed_Display.print(" "); Feed_Display.print(in_Outside_Diameter,3); Feed_Display.println(" in");}
      if (Thread_Mode == 1) {Feed_Display.print(" "); Feed_Display.print(mm_Outside_Diameter,2); Feed_Display.println(" mm");}
    }
    if (submenu == 3) {                                   // submenu page three --- Depth of cut
      Feed_Display.setCursor(0,45);
      Feed_Display.println("  Input");
      Feed_Display.setCursor(0,65);
      Feed_Display.println("  D.O.C.");
      Feed_Display.setCursor(0,100);
        if (Thread_Mode == 0) {Feed_Display.print(" "); Feed_Display.print(in_DOC,3); Feed_Display.println(" in");}
        if (Thread_Mode == 1) {Feed_Display.print(" "); Feed_Display.print(mm_DOC,2); Feed_Display.println(" mm");} 
    }
  }
}

void Mode_3_SubMenu() {         // Auto Thread Sub Menu
  if (Mode_Array_Pos == 3 && submenu >= 1) {
    if (submenu >= 1 && Mode_Array_Pos == 3) {
      Feed_Display.clearDisplay();
      Feed_Display.setTextColor(SSD1327_WHITE);
      Feed_Display.setTextSize(2); 
      Feed_Display.setCursor(0,0);
      Feed_Display.println("Auto Turn");
      Feed_Display.println("    OD   ");              // this could be a selection in the future for OD or ID
    }
    if (submenu == 1) {                                   // submenu page one --- Thread Length
      Feed_Display.setCursor(0,45);
      Feed_Display.println("  Input");
      Feed_Display.setCursor(0,65);
      Feed_Display.println("Cut Length");
      Feed_Display.setCursor(0,100);
        if (Thread_Mode == 0) {Feed_Display.print(" "); Feed_Display.print(in_length_of_cut,3); Feed_Display.println(" in");}
        if (Thread_Mode == 1) {Feed_Display.print(" "); Feed_Display.print(mm_length_of_cut,3); Feed_Display.println(" mm");} 
    }
    if (submenu == 2) {                                   // submenu page two --- Thread Diameter
      Feed_Display.setCursor(0,45);
      Feed_Display.println("  Input");
      Feed_Display.setCursor(0,65);
      Feed_Display.println("Current OD");
      Feed_Display.setCursor(0,100);
      if (Thread_Mode == 0) {Feed_Display.print(" "); Feed_Display.print(in_Outside_Diameter,3); Feed_Display.println(" in");}
      if (Thread_Mode == 1) {Feed_Display.print(" "); Feed_Display.print(mm_Outside_Diameter,2); Feed_Display.println(" mm");}
    }
    if (submenu == 3) {                                   // submenu page three --- Final Diameter
      Feed_Display.setCursor(0,45);
      Feed_Display.println("  Input");
      Feed_Display.setCursor(0,65);
      Feed_Display.println(" Final OD");
      Feed_Display.setCursor(0,100);
        if (Thread_Mode == 0) {Feed_Display.print(" "); Feed_Display.print(in_Final_Diameter,3); Feed_Display.println(" in");}
        if (Thread_Mode == 1) {Feed_Display.print(" "); Feed_Display.print(mm_Final_Diameter,2); Feed_Display.println(" mm");} 
    }
    if (submenu == 4) {                                   // submenu page four --- Depth of cut
      Feed_Display.setCursor(0,45);
      Feed_Display.println("  Input");
      Feed_Display.setCursor(0,65);
      Feed_Display.println("  D.O.C.");
      Feed_Display.setCursor(0,100);
        if (Thread_Mode == 0) {Feed_Display.print(" "); Feed_Display.print(in_DOC,3); Feed_Display.println(" in");}
        if (Thread_Mode == 1) {Feed_Display.print(" "); Feed_Display.print(mm_DOC,2); Feed_Display.println(" mm");} 
    }
  }
}