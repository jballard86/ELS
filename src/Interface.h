void Interface() {

  Mode_Selection();                 // mode selection routine using Enc1
    Mode_0_Feed_Controls();         // Feed menu controls
    Mode_1_Thread_Controls();       // Thread menu controls
    Mode_2_Thread_Controls();       // Thread menu controls
      Mode_2_SubMenu_Controls();    // Sub Menu for Mode 2
    Mode_3_Auto_Turn_Controls();
      Mode_3_SubMenu_Controls();
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

void Mode_2_Thread_Controls() {
//----Mode 2 (Auto Thread) Controls----//
  if (Mode_Array_Pos == 2) {
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

  if (! Enc1.digitalRead(Enc_Button) && Mode_Array_Pos == 2 && submenu == 0) {
    delay(200); 
    submenu = 1;
  }
  if (! Enc1.digitalRead(Enc_Button) && Mode_Array_Pos == 2 && submenu == 1) {
    delay(200); 
    submenu = 0;
    Enc1.setEncoderPosition(Mode_Array_Pos);
  }
}
void Mode_3_SubMenu_Controls() {

}