#include "PS4_Controller.h"

PS4_Controller::PS4_Controller() {
    //ESP32 Bluetooth MAC-Address
    PS4.begin("C8:C9:A3:C8:3B:EE");
    new_x_movement = 0;
    new_y_movement = 0;
    new_z_movement = 0;
}

int8_t PS4_Controller::controller_2_RobotFrameMove(int8_t controllerMovement) {
  int8_t worldMovement = 0;

  if(controllerMovement <= 10 && controllerMovement >= -10) {
      worldMovement = 0;
    }
    else if(controllerMovement <= 32 && controllerMovement > 10) {
      worldMovement = 8;
    }
    else if(controllerMovement <= 56 && controllerMovement > 32) {
      worldMovement = 16;
    }
    else if(controllerMovement <= 80 && controllerMovement > 56) {
      worldMovement = 24;
    }
    else if(controllerMovement <= 104 && controllerMovement > 80) {
      worldMovement = 32;
    }
    else if(controllerMovement <= 127 && controllerMovement > 104) {
      worldMovement = 40;
    }
    else if(controllerMovement < -10 && controllerMovement >= -32) {
      worldMovement = -40;
    }
    else if(controllerMovement < -32 && controllerMovement >= -56) {
      worldMovement = -32;
    }
    else if(controllerMovement < -56 && controllerMovement >= -80) {
      worldMovement = -24;
    }
    else if(controllerMovement < -80 && controllerMovement >= -104) {
      worldMovement = -16;
    }
    else if(controllerMovement < -104 && controllerMovement >= -128) {
      worldMovement = -8;
    }
    return worldMovement;
}

int8_t PS4_Controller::controller_2_RobotFrameRot(int8_t controllerMovement) {
  int8_t worldMovement = 0;

  if(controllerMovement <= 10 && controllerMovement >= -10) {
      worldMovement = 0;
    }
    else if(controllerMovement <= 32 && controllerMovement > 10) {
      worldMovement = 8;
    }
    else if(controllerMovement <= 56 && controllerMovement > 32) {
      worldMovement = 16;
    }
    else if(controllerMovement <= 80 && controllerMovement > 56) {
      worldMovement = 24;
    }
    else if(controllerMovement <= 104 && controllerMovement > 80) {
      worldMovement = 32;
    }
    else if(controllerMovement <= 127 && controllerMovement > 104) {
      worldMovement = 40;
    }
    else if(controllerMovement < -10 && controllerMovement >= -32) {
      worldMovement = -8;
    }
    else if(controllerMovement < -32 && controllerMovement >= -56) {
      worldMovement = -16;
    }
    else if(controllerMovement < -56 && controllerMovement >= -80) {
      worldMovement = -24;
    }
    else if(controllerMovement < -80 && controllerMovement >= -104) {
      worldMovement = -32;
    }
    else if(controllerMovement < -104 && controllerMovement >= -128) {
      worldMovement = -40;
    }
    return worldMovement;
}

void PS4_Controller::set_new_x(int8_t worldMovement) {
    new_x_movement = -1*worldMovement;
}
void PS4_Controller::set_new_y(int8_t worldMovement) {
    new_y_movement = worldMovement;
}

int8_t PS4_Controller::get_x() {
    return new_x_movement;
}

int8_t PS4_Controller::get_y() {
    return new_y_movement;
}

int8_t PS4_Controller::get_z() {
    return new_z_movement;
}

boolean PS4_Controller::check_movement(int8_t x, int8_t y, int8_t rot, boolean up, boolean down) {
    if(x >= 10 || x <= -10 || y >= 10 || y <= -10 || rot >= 10 || rot <= -10 ||  up || down) {
        return true;
    }
    else {
        return false;
    }
}



