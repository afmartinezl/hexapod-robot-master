#include "I2C.h"
#include <Arduino.h>

I2C::I2C() {
    Wire.begin();
}

void I2C::send_new_Pos(int8_t add, int8_t x, int8_t y, int8_t z, int8_t rotZ) {
  Wire.beginTransmission(add);

   if(x>50) {
    x = 50;
  }
  else if(x<-50) {
    x = -50;
  }

  if(y>50) {
    y = 50;
  }
  else if(y<-50) {
    y = -50;
  } 

  Wire.write(0);
  Wire.write(x+50);
  Wire.write(y+50);
  Wire.write(z+50);
  Wire.write(rotZ+50);
  Wire.endTransmission();
} 

int16_t I2C::getRequestResponse(int8_t address, int8_t id) {
  int16_t returnValue = 0;
  Wire.beginTransmission(address);
  Wire.write(id);
  Wire.endTransmission();

  // Voltage or current request
  if(id == 21 || id == 22 || id == 23 || id == 31 || id == 32 || id ==33) {
    Wire.requestFrom(address, 2);
    int8_t highB = Wire.read();
    int8_t lowB = Wire.read();
    returnValue = ((highB << 8) | lowB);
  }
  // Temperature request
  else if (id == 11 || id == 12 || id == 13) {
    Wire.requestFrom(address, 1);
    returnValue = Wire.read();
  }
  return returnValue;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// TEMPERATURE FUNCTIONS
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void I2C::setLegTemp(int leg, int motor, int8_t temp) {
  switch(leg) {
    case 1:
    if(motor == 1) {
      temperatures[0] = temp;
    }
    else if(motor == 2) {
      temperatures[1] = temp;
    }
    else if(motor == 3) {
      temperatures[2] = temp;
    }
    break;

    case 2:
    if(motor == 1) {
      temperatures[3] = temp;
    }
    else if(motor == 2) {
      temperatures[4] = temp;
    }
    else if(motor == 3) {
      temperatures[5] = temp;
    }
    break;

    case 3:
    if(motor == 1) {
      temperatures[6] = temp;
    }
    else if(motor == 2) {
      temperatures[7] = temp;
    }
    else if(motor == 3) {
      temperatures[8] = temp;
    }
    break;

    case 4:
    if(motor == 1) {
      temperatures[9] = temp;
    }
    else if(motor == 2) {
      temperatures[10] = temp;
    }
    else if(motor == 3) {
      temperatures[11] = temp;
    }
    break;

    case 5:
    if(motor == 1) {
      temperatures[12] = temp;
    }
    else if(motor == 2) {
      temperatures[13] = temp;
    }
    else if(motor == 3) {
      temperatures[14] = temp;
    }
    break;

    case 6:
    if(motor == 1) {
      temperatures[15] = temp;
    }
    else if(motor == 2) {
      temperatures[16] = temp;
    }
    else if(motor == 3) {
      temperatures[17] = temp;
    }
    break;
  }
}

void I2C::setHighest_Temp_and_Pos() {
  int8_t tempHigh = 0;
  int i = 0;
  int arrSize = sizeof(temperatures);
  for(auto myItr : temperatures) {
    if(myItr > tempHigh) {
      tempHigh = myItr;
    }
  }
  highestTemperature = tempHigh;

  while(i<arrSize) {
    if(temperatures[i] == highestTemperature) {
      break;
    }
    i++;
  }
  if(i<arrSize) {
    switch(i) {
      case 0:
      highestTemperature_Pos = "Leg 1 - Motor 1";
      break;
      case 1:
      highestTemperature_Pos = "Leg 1 - Motor 2";
      break;
      case 2:
      highestTemperature_Pos = "Leg 1 - Motor 3";
      break;
      case 3:
      highestTemperature_Pos = "Leg 2 - Motor 1";
      break;
      case 4:
      highestTemperature_Pos = "Leg 2 - Motor 2";
      break;
      case 5:
      highestTemperature_Pos = "Leg 2 - Motor 3";
      break;
      case 6:
      highestTemperature_Pos = "Leg 3 - Motor 1";
      break;
      case 7:
      highestTemperature_Pos = "Leg 3 - Motor 2";
      break;
      case 8:
      highestTemperature_Pos = "Leg 3 - Motor 3";
      break;
      case 9:
      highestTemperature_Pos = "Leg 4 - Motor 1";
      break;
      case 10:
      highestTemperature_Pos = "Leg 4 - Motor 2";
      break;
      case 11:
      highestTemperature_Pos = "Leg 4 - Motor 3";
      break;
      case 12:
      highestTemperature_Pos = "Leg 5 - Motor 1";
      break;
      case 13:
      highestTemperature_Pos = "Leg 5 - Motor 2";
      break;
      case 14:
      highestTemperature_Pos = "Leg 5 - Motor 3";
      break;
      case 15:
      highestTemperature_Pos = "Leg 6 - Motor 1";
      break;
      case 16:
      highestTemperature_Pos = "Leg 6 - Motor 2";
      break;
      case 17:
      highestTemperature_Pos = "Leg 6 - Motor 3";
      break;
      
    }
  }
}

int8_t I2C::getHighestTemp() {
  return highestTemperature;
}

String I2C::getHighestTemp_Pos() {
  return highestTemperature_Pos;
}

int8_t I2C::getTemp(int leg, int motor) {
  int8_t temp = 0;
  switch(leg) {
    case 1:
    if(motor == 1) {
      temp = temperatures[1];
    }
    else if(motor == 2) {
      temp = temperatures[2];
    }
    else if(motor == 3) {
      temp = temperatures[3];
    }
    break;

    case 2:
    if(motor == 1) {
      temp = temperatures[4];
    }
    else if(motor == 2) {
      temp = temperatures[5];
    }
    else if(motor == 3) {
      temp = temperatures[6];
    }
    break;

    case 3:
    if(motor == 1) {
      temp = temperatures[7];
    }
    else if(motor == 2) {
      temp = temperatures[8];
    }
    else if(motor == 3) {
      temp = temperatures[9];
    }
    break;

    case 4:
    if(motor == 1) {
      temp = temperatures[10];
    }
    else if(motor == 2) {
      temp = temperatures[11];
    }
    else if(motor == 3) {
      temp = temperatures[12];
    }
    break; 

    case 5:
    if(motor == 1) {
      temp = temperatures[13];
    }
    else if(motor == 2) {
      temp = temperatures[14];
    }
    else if(motor == 3) {
      temp = temperatures[15];
    }
    break;

    case 6:
    if(motor == 1) {
      temp = temperatures[16];
    }
    else if(motor == 2) {
      temp = temperatures[17];
    }
    else if(motor == 3) {
      temp = temperatures[18];
    }
    break;  
  }
  return temp;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// VOLTAGE FUNCTIONS
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


void I2C::setLegVol(int leg, int motor, uint16_t vol) {
  switch(leg) {
    case 1:
    if(motor == 1) {
      voltages[0] =vol;
    }
    else if(motor == 2) {
      voltages[1] =vol;
    }
    else if(motor == 3) {
      voltages[2] =vol;
    }
    break;

    case 2:
    if(motor == 1) {
      voltages[3] =vol;
    }
    else if(motor == 2) {
      voltages[4] =vol;
    }
    else if(motor == 3) {
      voltages[5] =vol;
    }
    break;

    case 3:
    if(motor == 1) {
      voltages[6] =vol;
    }
    else if(motor == 2) {
      voltages[7] =vol;
    }
    else if(motor == 3) {
      voltages[8] =vol;
    }
    break;

    case 4:
    if(motor == 1) {
      voltages[9] =vol;
    }
    else if(motor == 2) {
      voltages[10] =vol;
    }
    else if(motor == 3) {
      voltages[11] =vol;
    }
    break;

    case 5:
    if(motor == 1) {
      voltages[12] =vol;
    }
    else if(motor == 2) {
      voltages[13] =vol;
    }
    else if(motor == 3) {
      voltages[14] =vol;
    }
    break;

    case 6:
    if(motor == 1) {
      voltages[15] =vol;
    }
    else if(motor == 2) {
      voltages[16] =vol;
    }
    else if(motor == 3) {
      voltages[17] =vol;
    }
    break;
  }
}

void I2C::setHighest_Vol_and_Pos() {
  uint16_t volHigh = 0;
  int i = 0;
  int arrSize = sizeof(voltages);
  for(auto myItr : voltages) {
    if(myItr > volHigh) {
      volHigh = myItr;
    }
  }
  highestVoltage = volHigh;

  while(i<arrSize) {
    if(voltages[i] == highestVoltage) {
      break;
    }
    i++;
  }
  if(i<arrSize) {
    switch(i) {
      case 0:
      highestVoltage_Pos = "Leg 1 - Motor 1";
      break;
      case 1:
      highestVoltage_Pos = "Leg 1 - Motor 2";
      break;
      case 2:
      highestVoltage_Pos = "Leg 1 - Motor 3";
      break;
      case 3:
      highestVoltage_Pos = "Leg 2 - Motor 1";
      break;
      case 4:
      highestVoltage_Pos = "Leg 2 - Motor 2";
      break;
      case 5:
      highestVoltage_Pos = "Leg 2 - Motor 3";
      break;
      case 6:
      highestVoltage_Pos = "Leg 3 - Motor 1";
      break;
      case 7:
      highestVoltage_Pos = "Leg 3 - Motor 2";
      break;
      case 8:
      highestVoltage_Pos = "Leg 3 - Motor 3";
      break;
      case 9:
      highestVoltage_Pos = "Leg 4 - Motor 1";
      break;
      case 10:
      highestVoltage_Pos = "Leg 4 - Motor 2";
      break;
      case 11:
      highestVoltage_Pos = "Leg 4 - Motor 3";
      break;
      case 12:
      highestVoltage_Pos = "Leg 5 - Motor 1";
      break;
      case 13:
      highestVoltage_Pos = "Leg 5 - Motor 2";
      break;
      case 14:
      highestVoltage_Pos = "Leg 5 - Motor 3";
      break;
      case 15:
      highestVoltage_Pos = "Leg 6 - Motor 1";
      break;
      case 16:
      highestVoltage_Pos = "Leg 6 - Motor 2";
      break;
      case 17:
      highestVoltage_Pos = "Leg 6 - Motor 3";
      break;
      
    }
  }
}

uint16_t I2C::getVol(int leg, int motor){
  uint16_t vol = 0;
    switch(leg) {
    case 1:
    if(motor == 1) {
      vol = voltages[0];
    }
    else if(motor == 2) {
      vol = voltages[1];
    }
    else if(motor == 3) {
      vol = voltages[2];
    }
    break;

    case 2:
    if(motor == 1) {
      vol = voltages[3];
    }
    else if(motor == 2) {
      vol = voltages[4];
    }
    else if(motor == 3) {
      vol = voltages[5];
    }
    break;

    case 3:
    if(motor == 1) {
      vol = voltages[6];
    }
    else if(motor == 2) {
      vol = voltages[7];
    }
    else if(motor == 3) {
      vol = voltages[8];
    }
    break;

    case 4:
    if(motor == 1) {
      vol = voltages[9];
    }
    else if(motor == 2) {
      vol = voltages[10];
    }
    else if(motor == 3) {
      vol = voltages[11];
    }
    break; 

    case 5:
    if(motor == 1) {
      vol = voltages[12];
    }
    else if(motor == 2) {
      vol = voltages[13];
    }
    else if(motor == 3) {
      vol = voltages[14];
    }
    break;

    case 6:
    if(motor == 1) {
      vol = voltages[15];
    }
    else if(motor == 2) {
      vol = voltages[16];
    }
    else if(motor == 3) {
      vol = voltages[17];
    }
    break;  
  }
  return vol;
}

uint16_t I2C::getHighestVol() {
  return highestVoltage;
}

String I2C::getHighestVol_Pos() {
  return highestVoltage_Pos;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// CURRENT FUNCTIONS
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void I2C::setLegCurr(int leg, int motor, int16_t curr) {
  switch(leg) {
    case 1:
    if(motor == 1) {
      currents[0] = curr;
    }
    else if(motor == 2) {
      currents[1] = curr;
    }
    else if(motor == 3) {
      currents[2] = curr;
    }
    break;

    case 2:
    if(motor == 1) {
      currents[3] = curr;
    }
    else if(motor == 2) {
      currents[4] = curr;
    }
    else if(motor == 3) {
      currents[5] = curr;
    }
    break;

    case 3:
    if(motor == 1) {
      currents[6] = curr;
    }
    else if(motor == 2) {
      currents[7] = curr;
    }
    else if(motor == 3) {
      currents[8] = curr;
    }
    break;

    case 4:
    if(motor == 1) {
      currents[9] = curr;
    }
    else if(motor == 2) {
      currents[10] = curr;
    }
    else if(motor == 3) {
      currents[11] = curr;
    }
    break;

    case 5:
    if(motor == 1) {
      currents[12] = curr;
    }
    else if(motor == 2) {
      currents[13] = curr;
    }
    else if(motor == 3) {
      currents[14] = curr;
    }
    break;

    case 6:
    if(motor == 1) {
      currents[15] = curr;
    }
    else if(motor == 2) {
      currents[16] = curr;
    }
    else if(motor == 3) {
      currents[17] = curr;
    }
    break;
  }
}

void I2C::setHighest_Curr_and_Pos() {
  uint16_t currHigh = 0;
  int i = 0;
  int arrSize = sizeof(currents);
  for(auto myItr : currents) {
    if(myItr > currHigh) {
      currHigh = myItr;
    }
  }
  highestVoltage = currHigh;

  while(i<arrSize) {
    if(currents[i] == highestVoltage) {
      break;
    }
    i++;
  }
  if(i<arrSize) {
    switch(i) {
      case 0:
      highestCurrent_Pos = "Leg 1 - Motor 1";
      break;
      case 1:
      highestCurrent_Pos = "Leg 1 - Motor 2";
      break;
      case 2:
      highestCurrent_Pos = "Leg 1 - Motor 3";
      break;
      case 3:
      highestCurrent_Pos = "Leg 2 - Motor 1";
      break;
      case 4:
      highestCurrent_Pos = "Leg 2 - Motor 2";
      break;
      case 5:
      highestCurrent_Pos = "Leg 2 - Motor 3";
      break;
      case 6:
      highestCurrent_Pos = "Leg 3 - Motor 1";
      break;
      case 7:
      highestCurrent_Pos = "Leg 3 - Motor 2";
      break;
      case 8:
      highestCurrent_Pos = "Leg 3 - Motor 3";
      break;
      case 9:
      highestCurrent_Pos = "Leg 4 - Motor 1";
      break;
      case 10:
      highestCurrent_Pos = "Leg 4 - Motor 2";
      break;
      case 11:
      highestCurrent_Pos = "Leg 4 - Motor 3";
      break;
      case 12:
      highestCurrent_Pos = "Leg 5 - Motor 1";
      break;
      case 13:
      highestCurrent_Pos = "Leg 5 - Motor 2";
      break;
      case 14:
      highestCurrent_Pos = "Leg 5 - Motor 3";
      break;
      case 15:
      highestCurrent_Pos = "Leg 6 - Motor 1";
      break;
      case 16:
      highestCurrent_Pos = "Leg 6 - Motor 2";
      break;
      case 17:
      highestCurrent_Pos = "Leg 6 - Motor 3";
      break;
      
    }
  }
}

uint16_t I2C::getCurr(int leg, int motor) {
  uint16_t curr = 0;
    switch(leg) {
    case 1:
    if(motor == 1) {
      curr = currents[0];
    }
    else if(motor == 2) {
      curr = currents[1];
    }
    else if(motor == 3) {
      curr = currents[2];
    }
    break;

    case 2:
    if(motor == 1) {
      curr = currents[3];
    }
    else if(motor == 2) {
      curr = currents[4];
    }
    else if(motor == 3) {
      curr = currents[5];
    }
    break;

    case 3:
    if(motor == 1) {
      curr = currents[6];
    }
    else if(motor == 2) {
      curr = currents[7];
    }
    else if(motor == 3) {
      curr = currents[8];
    }
    break;

    case 4:
    if(motor == 1) {
      curr = currents[9];
    }
    else if(motor == 2) {
      curr = currents[10];
    }
    else if(motor == 3) {
      curr = currents[11];
    }
    break; 

    case 5:
    if(motor == 1) {
      curr = currents[12];
    }
    else if(motor == 2) {
      curr = currents[13];
    }
    else if(motor == 3) {
      curr = currents[14];
    }
    break;

    case 6:
    if(motor == 1) {
      curr = currents[15];
    }
    else if(motor == 2) {
      curr = currents[16];
    }
    else if(motor == 3) {
      curr = currents[17];
    }
    break;  
  }
  return curr;
}

uint16_t I2C::getHighestCurr() {
  return highestCurrent;
}

String I2C::getHighestCurr_Pos() {
  return highestCurrent_Pos;
}