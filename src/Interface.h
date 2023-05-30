void Interface() {

  Mode_Selection();                                           // mode selection routine using Enc1
    Mode_0_Feed_Controls();                                   // Feed menu controls
    Mode_1_Thread_Controls();                                 // Thread menu controls
    Mode_2_Auto_Thread_Controls();                            // Thread menu controls
      if (Mode_Array_Pos ==2) {Mode_2_SubMenu_Controls();}    // Sub Menu for Mode 2, ran only when Mode = 2
    Mode_3_Auto_Turn_Controls();                              // Auto Turn controls
      if (Mode_Array_Pos ==3) {Mode_3_SubMenu_Controls();}    // Sub Menu for Mode 2, ran only when Mode = 2
}

//long click to go into submenu for autothread inputs? or use Enc1 click?

void Mode_Selection() {
  //----Select Mode with Encoder 1----//
    if (submenu == 0) {
      if (Enc1.getEncoderPosition() > Mode_Array_Pos) {
        Mode_Array_Pos --;
        Enc1.setEncoderPosition(Mode_Array_Pos);
      } else if (Enc1.getEncoderPosition() < Mode_Array_Pos ) {
        Mode_Array_Pos ++;
        Enc1.setEncoderPosition(Mode_Array_Pos);
      }
      if (Mode_Array_Pos == Mode_Array_Size) {
        Mode_Array_Pos --;
        Enc1.setEncoderPosition(Mode_Array_Pos);
      } else if (Mode_Array_Pos < 0) {
        Mode_Array_Pos = 0;
        Enc1.setEncoderPosition(Mode_Array_Pos);
      }
    }

}

void Mode_0_Feed_Controls() {
//----Mode 0 (Feed) Controls----//
  if (Mode_Array_Pos == 0) {
    if (! Enc2.digitalRead(Enc_Button) && SpindleRPM == 0) {        //do stuff if Encoder button is pressed and spindle speed is zero
      delay(200);
      if (Measure_Array_Pos == 0) {
        Measure_Array_Pos = 1;
        Metric = 1;                               // set metric flag to 1 (Metric)
      } else {
        Measure_Array_Pos = 0;
        Metric = 0;                               // set metric flag to 0 (Inch)
      }
    }
  //----Inch----//
    if (Metric == 0) {
      if (Enc2.getEncoderPosition() < 0) {
        In_FeedRate = In_FeedRate + .001;
        if (Enc2.getEncoderPosition() < -1) { In_FeedRate = In_FeedRate + .014;}          // Fast Scroll
        Enc2.setEncoderPosition(0);
      } 
      if (Enc2.getEncoderPosition() > 0) {
        In_FeedRate = In_FeedRate - .001;
        if (Enc2.getEncoderPosition() > 1) { In_FeedRate = In_FeedRate - .014;}          // Fast Scroll

        Enc2.setEncoderPosition(0);
      } 
      if (In_FeedRate < .001) {In_FeedRate = .001;}
  }
  //----Metric----//
    if (Metric == 1) {
      if (Enc2.getEncoderPosition() < 0) {
        mm_FeedRate = mm_FeedRate + .01;
        if (Enc2.getEncoderPosition() < -1) { mm_FeedRate = mm_FeedRate + .09;}           // Fast Scroll
        Enc2.setEncoderPosition(0);
      } 
      if (Enc2.getEncoderPosition() > 0) {
        mm_FeedRate = mm_FeedRate - .01;
        if (Enc2.getEncoderPosition() > 1) { mm_FeedRate = mm_FeedRate - .09;}           // Fast Scroll
        Enc2.setEncoderPosition(0);
      } 
      if (mm_FeedRate < .01) {mm_FeedRate = .01;}
    }
  }
}

void Mode_1_Thread_Controls() {
//----Mode 1 (Thread) Controls----//
  if (Mode_Array_Pos == 1) {
    if (! Enc2.digitalRead(Enc_Button)) {
      delay(200);
      if (Thread_Mode == 0) {
        Thread_Mode = 1;
      } else {
        Thread_Mode = 0;
      }
    }
  //----TPI----//
    if (Thread_Mode == 0) {
      if (Enc2.getEncoderPosition() < 0) {
        TPI_Array_Pos++;
        if (Enc2.getEncoderPosition() < -1) { TPI_Array_Pos = TPI_Array_Pos + 4;}           // Fast Scroll
        if (TPI_Array_Pos >= TPI_Array_Size) {TPI_Array_Pos = TPI_Array_Size - 1;}            // keeps array position inside the bounds of the array
        Enc2.setEncoderPosition(0);
      } 
      if (Enc2.getEncoderPosition() > 0) {
        TPI_Array_Pos--;
        if (Enc2.getEncoderPosition() > 1) { TPI_Array_Pos = TPI_Array_Pos - 4;}             // Fast Scroll
        if (TPI_Array_Pos < 0) {TPI_Array_Pos = 0;}                                          // keeps array position inside the bounds of the array
        Enc2.setEncoderPosition(0);
      } 
  }
  //----Pitch----//
    if (Thread_Mode == 1) {
      if (Enc2.getEncoderPosition() < 0) {
        Pitch_Array_Pos++;
        if (Enc2.getEncoderPosition() < -1) { Pitch_Array_Pos = Pitch_Array_Pos + 4;}           // Fast Scroll
        if (Pitch_Array_Pos >= Pitch_Array_Size) {Pitch_Array_Pos = Pitch_Array_Size - 1;}        // keeps array position inside the bounds of the array
        Enc2.setEncoderPosition(0);
      } 
      if (Enc2.getEncoderPosition() > 0) {
        Pitch_Array_Pos--;
        if (Enc2.getEncoderPosition() > 1) { Pitch_Array_Pos = Pitch_Array_Pos - 4;}             // Fast Scroll
        if (Pitch_Array_Pos < 0) {Pitch_Array_Pos = 0;}                                          // keeps array position inside the bounds of the array
        Enc2.setEncoderPosition(0);
      }
    }
  }
}

void Mode_2_Auto_Thread_Controls() {
//----Mode 2 (Auto Thread) Controls----//
  if (Mode_Array_Pos == 2 && submenu == 0) {
    if (! Enc2.digitalRead(Enc_Button)) {
      delay(200);
      if (Thread_Mode == 0) {
        Thread_Mode = 1;
      } else {
        Thread_Mode = 0;
      }
    }
  //----TPI----//
    if (Thread_Mode == 0) {
      if (Enc2.getEncoderPosition() < 0) {
        TPI_Array_Pos++;
        if (Enc2.getEncoderPosition() < -1) { TPI_Array_Pos = TPI_Array_Pos + 4;}           // Fast Scroll
        if (TPI_Array_Pos >= TPI_Array_Size) {TPI_Array_Pos = TPI_Array_Size - 1;}            // keeps array position inside the bounds of the array
        Enc2.setEncoderPosition(0);
      } 
      if (Enc2.getEncoderPosition() > 0) {
        TPI_Array_Pos--;
        if (Enc2.getEncoderPosition() > 1) { TPI_Array_Pos = TPI_Array_Pos - 4;}             // Fast Scroll
        if (TPI_Array_Pos < 0) {TPI_Array_Pos = 0;}                                          // keeps array position inside the bounds of the array
        Enc2.setEncoderPosition(0);
      } 
  }
  //----Pitch----//
    if (Thread_Mode == 1) {
      if (Enc2.getEncoderPosition() < 0) {
        Pitch_Array_Pos++;
        if (Enc2.getEncoderPosition() < -1) { Pitch_Array_Pos = Pitch_Array_Pos + 4;}           // Fast Scroll
        if (Pitch_Array_Pos >= Pitch_Array_Size) {Pitch_Array_Pos = Pitch_Array_Size - 1;}        // keeps array position inside the bounds of the array
        Enc2.setEncoderPosition(0);
      } 
      if (Enc2.getEncoderPosition() > 0) {
        Pitch_Array_Pos--;
        if (Enc2.getEncoderPosition() > 1) { Pitch_Array_Pos = Pitch_Array_Pos - 4;}             // Fast Scroll
        if (Pitch_Array_Pos < 0) {Pitch_Array_Pos = 0;}                                          // keeps array position inside the bounds of the array
        Enc2.setEncoderPosition(0);
      }
    }
  }
}

void Mode_3_Auto_Turn_Controls() {
//----Mode 0 (Feed) Controls----//
  if (Mode_Array_Pos == 3) {
    if (! Enc2.digitalRead(Enc_Button) && SpindleRPM == 0) {        //do stuff if Encoder button is pressed and spindle speed is zero
      delay(200);
      if (Measure_Array_Pos == 0) {
        Measure_Array_Pos = 1;
        Metric = 1;                               // set metric flag to 1 (Metric)
      } else {
        Measure_Array_Pos = 0;
        Metric = 0;                               // set metric flag to 0 (Inch)
      }
    }
  //----Inch----//
    if (Metric == 0) {
      if (Enc2.getEncoderPosition() < 0) {
        In_FeedRate = In_FeedRate + .001;
        if (Enc2.getEncoderPosition() < -1) { In_FeedRate = In_FeedRate + .014;}          // Fast Scroll
        Enc2.setEncoderPosition(0);
      } 
      if (Enc2.getEncoderPosition() > 0) {
        In_FeedRate = In_FeedRate - .001;
        if (Enc2.getEncoderPosition() > 1) { In_FeedRate = In_FeedRate - .014;}          // Fast Scroll

        Enc2.setEncoderPosition(0);
      } 
      if (In_FeedRate < .001) {In_FeedRate = .001;}
  }
  //----Metric----//
    if (Metric == 1) {
      if (Enc2.getEncoderPosition() < 0) {
        mm_FeedRate = mm_FeedRate + .01;
        if (Enc2.getEncoderPosition() < -1) { mm_FeedRate = mm_FeedRate + .09;}           // Fast Scroll
        Enc2.setEncoderPosition(0);
      } 
      if (Enc2.getEncoderPosition() > 0) {
        mm_FeedRate = mm_FeedRate - .01;
        if (Enc2.getEncoderPosition() > 1) { mm_FeedRate = mm_FeedRate - .09;}           // Fast Scroll
        Enc2.setEncoderPosition(0);
      } 
      if (mm_FeedRate < .01) {mm_FeedRate = .01;}
    }
  }
}

void Mode_2_SubMenu_Controls() {
  // use Enc1 button to activate sub menu
  // use Enc1 encoder to traverse menu
  // use Enc2 button to exit menu
  // use Enc2 encoder to modify values
  //   attempt a coarse medium and fine adjustment

  if (! Enc1.digitalRead(Enc_Button) && Mode_Array_Pos == 2 && submenu == 0) {    // submenu button control
    delay(200); 
    submenu = 1;
    Enc1.setEncoderPosition(submenu);
  }

  if (submenu >= 1) {                                                             // submenu display control
      if (Enc1.getEncoderPosition() > submenu && submenu > 1) {
        submenu --;
        Enc1.setEncoderPosition(submenu);
      } else if (Enc1.getEncoderPosition() < submenu ) {
        submenu ++;
        Enc1.setEncoderPosition(submenu);
      }
      if (submenu > 3) {
        submenu = 0;
        Enc1.setEncoderPosition(Mode_Array_Pos);
        Main_Menu(); Feed_Display.display(); delay(400);                          // reduces the chance of changing mode when leaving submenu
      }
    }
  
  if (submenu == 1) {                                                           // submenu 1 thread length value adjustment
    //----Inch----//
    if (Thread_Mode == 0) {
      if (Enc2.getEncoderPosition() < 0) {
        in_length_of_cut = in_length_of_cut + .001;
        if (Enc2.getEncoderPosition() < -1) { in_length_of_cut = in_length_of_cut + .01;}           // Fast Scroll
        if (Enc2.getEncoderPosition() < -3) { in_length_of_cut = in_length_of_cut + .25;}           // Faster Scroll
        Enc2.setEncoderPosition(0);
      } 
      if (Enc2.getEncoderPosition() > 0) {
        in_length_of_cut = in_length_of_cut -.001;
        if (Enc2.getEncoderPosition() > 1) { in_length_of_cut = in_length_of_cut - .01;}            // Fast Scroll
        if (Enc2.getEncoderPosition() > 3) { in_length_of_cut = in_length_of_cut - .25;}            // Faster Scroll
        if (in_length_of_cut < .001) {in_length_of_cut = .001;}                                     // limits the lower bound of length of cut
        Enc2.setEncoderPosition(0);
      } 
    }
    //----mm----//
    if (Thread_Mode == 1) {
      if (Enc2.getEncoderPosition() < 0) {
        mm_length_of_cut = mm_length_of_cut + .01;
        if (Enc2.getEncoderPosition() < -1) { mm_length_of_cut = mm_length_of_cut + .1;}           // Fast Scroll
        if (Enc2.getEncoderPosition() < -3) { mm_length_of_cut = mm_length_of_cut + 1;}            // Faster Scroll
        Enc2.setEncoderPosition(0);
      } 
      if (Enc2.getEncoderPosition() > 0) {
        mm_length_of_cut = mm_length_of_cut -.01;
        if (Enc2.getEncoderPosition() > 1) { mm_length_of_cut = mm_length_of_cut - .1;}            // Fast Scroll
        if (Enc2.getEncoderPosition() > 3) { mm_length_of_cut = mm_length_of_cut - 1;}             // Faster Scroll
        if (mm_length_of_cut < .01) {mm_length_of_cut = .01;}                                    // limits the lower bound of length of cut
        Enc2.setEncoderPosition(0);
      } 
    }
  }
  if (submenu == 2) {                                                           // submenu 2 thread Diameter value adjustment
    //----Inch----//
    if (Thread_Mode == 0) {
      if (Enc2.getEncoderPosition() < 0) {
        in_Outside_Diameter = in_Outside_Diameter + .001;
        if (Enc2.getEncoderPosition() < -1) { in_Outside_Diameter = in_Outside_Diameter + .01;}           // Fast Scroll
        if (Enc2.getEncoderPosition() < -3) { in_Outside_Diameter = in_Outside_Diameter + .25;}           // Faster Scroll
        Enc2.setEncoderPosition(0);
      } 
      if (Enc2.getEncoderPosition() > 0) {
        in_Outside_Diameter = in_Outside_Diameter -.001;
        if (Enc2.getEncoderPosition() > 1) { in_Outside_Diameter = in_Outside_Diameter - .01;}            // Fast Scroll
        if (Enc2.getEncoderPosition() > 3) { in_Outside_Diameter = in_Outside_Diameter - .25;}            // Faster Scroll
        if (in_Outside_Diameter < .001) {in_Outside_Diameter = .001;}                                     // limits the lower bound of length of cut
        Enc2.setEncoderPosition(0);
      } 
    }
    //----mm----//
    if (Thread_Mode == 1) {
      if (Enc2.getEncoderPosition() < 0) {
        mm_Outside_Diameter = mm_Outside_Diameter + .01;
        if (Enc2.getEncoderPosition() < -1) { mm_Outside_Diameter = mm_Outside_Diameter + .1;}           // Fast Scroll
        if (Enc2.getEncoderPosition() < -3) { mm_Outside_Diameter = mm_Outside_Diameter + 1.5;}            // Faster Scroll
        Enc2.setEncoderPosition(0);
      } 
      if (Enc2.getEncoderPosition() > 0) {
        mm_Outside_Diameter = mm_Outside_Diameter -.01;
        if (Enc2.getEncoderPosition() > 1) { mm_Outside_Diameter = mm_Outside_Diameter - .1;}            // Fast Scroll
        if (Enc2.getEncoderPosition() > 3) { mm_Outside_Diameter = mm_Outside_Diameter - 1.5;}             // Faster Scroll
        if (mm_Outside_Diameter < .01) {mm_Outside_Diameter = .01;}                                    // limits the lower bound of length of cut
        Enc2.setEncoderPosition(0);
      } 
    }
  }
  if (submenu == 3) {                                                           // submenu 3 thread Depth of cut value adjustment
    //----Inch----//
    if (Thread_Mode == 0) {
      if (Enc2.getEncoderPosition() < 0) {
        in_DOC = in_DOC + .001;
        if (Enc2.getEncoderPosition() < -1) { in_DOC = in_DOC + .01;}           // Fast Scroll
        if (Enc2.getEncoderPosition() < -3) { in_DOC = in_DOC + .25;}           // Faster Scroll
        Enc2.setEncoderPosition(0);
      } 
      if (Enc2.getEncoderPosition() > 0) {
        in_DOC = in_DOC -.001;
        if (Enc2.getEncoderPosition() > 1) { in_DOC = in_DOC - .01;}            // Fast Scroll
        if (Enc2.getEncoderPosition() > 3) { in_DOC = in_DOC - .25;}            // Faster Scroll
        if (in_DOC < .001) {in_DOC = .001;}                                     // limits the lower bound of length of cut
        Enc2.setEncoderPosition(0);
      } 
    }
    //----mm----//
    if (Thread_Mode == 1) {
      if (Enc2.getEncoderPosition() < 0) {
        mm_DOC = mm_DOC + .01;
        if (Enc2.getEncoderPosition() < -1) { mm_DOC = mm_DOC + .1;}           // Fast Scroll
        if (Enc2.getEncoderPosition() < -3) { mm_DOC = mm_DOC + 1;}            // Faster Scroll
        Enc2.setEncoderPosition(0);
      } 
      if (Enc2.getEncoderPosition() > 0) {
        mm_DOC = mm_DOC -.01;
        if (Enc2.getEncoderPosition() > 1) { mm_DOC = mm_DOC - .1;}            // Fast Scroll
        if (Enc2.getEncoderPosition() > 3) { mm_DOC = mm_DOC - 1;}             // Faster Scroll
        if (mm_DOC < .01) {mm_DOC = .01;}                                    // limits the lower bound of length of cut
        Enc2.setEncoderPosition(0);
      } 
    }
  }
}
void Mode_3_SubMenu_Controls() {

}