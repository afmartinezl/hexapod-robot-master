#include "Transformation.h"

Transformation::Transformation() {
  T_1B(0,0) = cos(M_PI/2 - alpha);
  T_1B(0,1) = sin(M_PI/2 - alpha);
  T_1B(1,0) = -sin(M_PI/2 - alpha);
  T_1B(1,1) = cos(M_PI/2 - alpha);

  T_2B(0,0) = 0;
  T_2B(0,1) = 1;
  T_2B(1,0) = -1;
  T_2B(1,1) = 0;

  T_3B(0,0) = -cos(M_PI/2 - alpha);
  T_3B(0,1) = sin(M_PI/2 - alpha);
  T_3B(1,0) = -cos(alpha);
  T_3B(1,1) = -sin(M_PI/2 - alpha);
  
  T_4B(0,0) = -cos(M_PI/2 - alpha);
  T_4B(0,1) = -cos(alpha);
  T_4B(1,0) = cos(alpha);
  T_4B(1,1) = -cos(M_PI/2 - alpha);

  T_5B(0,0) = 0;
  T_5B(0,1) = -1;
  T_5B(1,0) = 1;
  T_5B(1,1) = 0;

  T_6B(0,0) = cos(M_PI/2 - alpha);
  T_6B(0,1) = -cos(alpha);
  T_6B(1,0) = cos(alpha);
  T_6B(1,1) = cos(M_PI/2 - alpha);
}

Eigen::Matrix2d Transformation::get_T1B() {

  return T_1B;
}

Eigen::Matrix2d Transformation::get_T2B() {
  
  return T_2B;
}

Eigen::Matrix2d Transformation::get_T3B() {
  
  return T_3B;
}

Eigen::Matrix2d Transformation::get_T4B() {

  return T_4B;
}

Eigen::Matrix2d Transformation::get_T5B() {

  return T_5B;
}

Eigen::Matrix2d Transformation::get_T6B() {

  return T_6B;    
}

Eigen::Matrix2d Transformation::createROTz(int8_t angle) {

    Eigen::Matrix2d rot;
    rot(0,0) = cos(angle);
    rot(0,1) = -sin(angle);
    rot(1,0) = sin(angle);
    rot(1,1) = cos(angle);
    return rot;
}