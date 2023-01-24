#include <Arduino.h>

#include "Transformation.h"
#include "PS4_Controller.h"
#include "I2C.h"
#include <SSD1306Wire.h>

SSD1306Wire myDisplay(0x3C, SDA, SCL);
uint64_t loopCounter = 0;

bool debug = true;

void setup() {
  myDisplay.init();
  myDisplay.setFont(ArialMT_Plain_10);
  myDisplay.flipScreenVertically();
  //pinMode(32, OUTPUT);
  Serial.begin(115200);
  Serial.println("Ready");
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void loop() {
  PS4_Controller myPS4 = PS4_Controller();
  I2C myI2C = I2C();

  Transformation myTransform = Transformation();
  boolean body_up, body_down = false;
  int8_t temp_Z = 0;

  Eigen::Vector2d move1(0, 0);
  Eigen::Vector2d move2(0, 0);
  Eigen::Vector2d move3(0, 0);
  Eigen::Vector2d move4(0, 0);
  Eigen::Vector2d move5(0, 0);
  Eigen::Vector2d move6(0, 0);

  while(true){
    if(!PS4.isConnected()) {
      myDisplay.clear();
      myDisplay.setFont(ArialMT_Plain_24);
      myDisplay.drawString(0, 0, "Connect");
      myDisplay.drawString(0, 30, "Controller");
      myDisplay.display();
    }

    else {
      myDisplay.clear();

      // Read input from controller and convert to world coordinates
      int8_t move_x = myPS4.controller_2_RobotFrameMove(PS4.LStickX()); //left-right
      int8_t move_y = myPS4.controller_2_RobotFrameMove(PS4.LStickY()); //forward-backwards
      int8_t rot_z = myPS4.controller_2_RobotFrameRot(PS4.RStickY()); //left-right rotation
      body_up = PS4.Up();
      body_down = PS4.Down();

      // Check if movement is detected
      if(myPS4.check_movement(move_x, move_y, rot_z, body_up, body_down)) {
        myPS4.set_new_x(move_x);
        myPS4.set_new_y(move_y);
        if(body_up) {
          temp_Z = 10;
        }
        else if(body_down) {
          temp_Z = -10;
        }

        // Calculate new position for each leg base coordinate system
        Eigen::Vector2d moveBase(myPS4.get_x(), myPS4.get_y());

        // Only movement
        if(moveBase.x() != 0 || moveBase.y() != 0 || temp_Z != 0) {
          move1 = myTransform.get_T1B() * moveBase;
          move2 = myTransform.get_T2B() * moveBase;
          move3 = myTransform.get_T3B() * moveBase;
          move4 = myTransform.get_T4B() * moveBase;
          move5 = myTransform.get_T5B() * moveBase;
          move6 = myTransform.get_T6B() * moveBase;

          // Send new coordinates to the slaves
          myI2C.send_new_Pos(10, round(move1.x()), round(move1.y()), temp_Z, rot_z);
          myI2C.send_new_Pos(30, round(move3.x()), round(move3.y()), temp_Z, rot_z);
          myI2C.send_new_Pos(50, round(move5.x()), round(move5.y()), temp_Z, rot_z);
          delay(50);
          myI2C.send_new_Pos(20, round(move2.x()), round(move2.y()), temp_Z, rot_z);
          myI2C.send_new_Pos(40, round(move4.x()), round(move4.y()), temp_Z, rot_z);
          myI2C.send_new_Pos(60, round(move6.x()), round(move6.y()), temp_Z, rot_z); 

          temp_Z = 0;
          delay(50);
        }
      }
      
      
      // Ask all slaves for motor temperatures
      if(PS4.Triangle()) {

        for(int legCounter = 1; legCounter < 7; legCounter ++) {
          for(int motorCounter = 1; motorCounter < 4; motorCounter ++) {
            myI2C.setLegTemp(legCounter, motorCounter, myI2C.getRequestResponse(legCounter*10, motorCounter+10));
          }
        }
        
        myI2C.setHighest_Temp_and_Pos();
        myDisplay.clear();
        myDisplay.setFont(ArialMT_Plain_16);

        // Write highest temperature on the display
        myDisplay.drawString(0, 0, "Highest Temp.:");
        myDisplay.drawString(0, 20, String(myI2C.getHighestTemp()) + " °C");
        myDisplay.drawString(0, 40, myI2C.getHighestTemp_Pos());
        myDisplay.display();

        if(PS4.Triangle()) {
          int legTempCounter = 1;
          while(legTempCounter < 7) {
            myDisplay.clear();
            myDisplay.setFont(ArialMT_Plain_10);

            myDisplay.drawString(0, 0, "Leg " + String(legTempCounter));
            myDisplay.drawString(0, 20, String(myI2C.getTemp(legTempCounter, 1)) + " °C");
            myDisplay.drawString(0, 30, String(myI2C.getTemp(legTempCounter, 2)) + " °C");
            myDisplay.drawString(0, 40, String(myI2C.getTemp(legTempCounter, 3)) + " °C");
            myDisplay.display();

            if(PS4.Triangle()) {
              legTempCounter ++;
            }
          } 

          myDisplay.clear();
        } 
      }
      
      // Ask all slaves for motor Voltages
      if(PS4.Circle()) {

        for(int legCounter = 1; legCounter < 7; legCounter ++) {
          for(int motorCounter = 1; motorCounter < 4; motorCounter ++) {
            myI2C.setLegVol(legCounter, motorCounter, myI2C.getRequestResponse(legCounter*10, motorCounter+30));
          }
        }
        
        myI2C.setHighest_Vol_and_Pos();
        myDisplay.clear();
        myDisplay.setFont(ArialMT_Plain_16);

        myDisplay.drawString(0, 0, "Highest Voltage:");
        myDisplay.drawString(0, 20, String(myI2C.getHighestVol()) + " mV");
        myDisplay.drawString(0, 40, myI2C.getHighestVol_Pos());
        myDisplay.display();

        if(PS4.Circle()) {
          int legVolCounter = 1;
          while(legVolCounter < 7) {
            myDisplay.clear();
            myDisplay.setFont(ArialMT_Plain_10);

            myDisplay.drawString(0, 0, "Leg " + String(legVolCounter));
            myDisplay.drawString(0, 20, String(myI2C.getVol(legVolCounter, 1)) + " mV");
            myDisplay.drawString(0, 30, String(myI2C.getVol(legVolCounter, 2)) + " mV");
            myDisplay.drawString(0, 40, String(myI2C.getVol(legVolCounter, 3)) + " mV");
            myDisplay.display();

            if(PS4.Triangle()) {
              legVolCounter ++;
            }
          } 

          myDisplay.clear();
        }  
      }

      // Ask all slaves for motor currents
      if(PS4.Cross()) {
        for(int legCounter = 1; legCounter < 7; legCounter ++) {
          for(int motorCounter = 1; motorCounter < 4; motorCounter ++) {
            myI2C.setLegTemp(legCounter, motorCounter, myI2C.getRequestResponse(legCounter*10, motorCounter+20));
          }
        }

        myI2C.setHighest_Vol_and_Pos();
        myDisplay.clear();
        myDisplay.setFont(ArialMT_Plain_16);

        myDisplay.drawString(0, 0, "Highest Current:");
        myDisplay.drawString(0, 20, String(myI2C.getHighestCurr()) + " mA");
        myDisplay.drawString(0, 40, myI2C.getHighestCurr_Pos());
        myDisplay.display();

        if(PS4.Cross()) {
          int legCurrCounter = 1;
          while(legCurrCounter < 7) {
            myDisplay.clear();
            myDisplay.setFont(ArialMT_Plain_10);

            myDisplay.drawString(0, 0, "Leg " + String(legCurrCounter));
            myDisplay.drawString(0, 20, String(myI2C.getVol(legCurrCounter, 1)) + " mA");
            myDisplay.drawString(0, 30, String(myI2C.getVol(legCurrCounter, 2)) + " mA");
            myDisplay.drawString(0, 40, String(myI2C.getVol(legCurrCounter, 3)) + " mA");
            myDisplay.display();

            if(PS4.Triangle()) {
              legCurrCounter ++;
            }
          } 

          myDisplay.clear();
        }
      } 
    }
  }
}


