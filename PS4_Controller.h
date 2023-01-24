#include "..\lib\PS4-esp32-master\src\PS4Controller.h"

/**
 * @brief Class that allows using the PS4 Dualschock controller as the hexapod movement controller.
 * 
 */
class PS4_Controller {
     public:
        /**
         * @brief Construct a new PS4-Controller object.
         * 
         */
        PS4_Controller();

        /**
         * @brief Set the new desired x-coordinate of the robot base.
         * 
         * @param worldMovement Movement in world coordiante system.
         */
        void set_new_x(int8_t worldMovement);

        /**
         * @brief Set the new desired y-coordinate of the robot base.
         * 
         * @param worldMovement Movement in world coordinate system.
         */
        void set_new_y(int8_t worldMovement);

        /**
         * @brief Get the desired x-coordinate of the robot base.
         * 
         * @return int8_t value of the x-coordinate.
         */
        int8_t get_x();

        /**
         * @brief Get the desired y-coordinate of the robot base.
         * 
         * @return int8_t value of the y-coordinate.
         */
        int8_t get_y();

        /**
         * @brief Get the desired z-coordinate of the robot base.
         * 
         * @return int8_t value of the z-coordinate.
         */
        int8_t get_z();

        /**
         * @brief Check if movement is detected from the controller.
         * 
         * @param x Desired movement along the x-axis.
         * @param y Desired movement along the y-axis.
         * @param rot Desired movement around the z-axis.
         * @param up Desired movement up the z-axis.
         * @param down Desired movement down the z-axis.
         * @return boolean true if any kind of movement is detected otherwise false.
         */
        boolean check_movement(int8_t x, int8_t y, int8_t rot, boolean up, boolean down);

        /**
         * @brief Convert the controller joystick movement to a world movement.
         * 
         * @param controllerMovement The movement value which is read from the joystick.
         * @return int8_t converted movement in robot base coordinate system.
         */
        int8_t controller_2_RobotFrameMove(int8_t controllerMovement);

        /**
         * @brief Convert the controller joystick rotation to a worrld rotation.
         * 
         * @param controllerMovement The rotation value which is read from the joystick.
         * @return int8_t converted rotation in robot base coordinate system.
         */
        int8_t controller_2_RobotFrameRot(int8_t controllerMovement);


     private:

        /**
         * @brief Relative x-coordinate of the target point for the robot base.
         * 
         */
        int8_t new_x_movement;

        /**
         * @brief Relative y-coordinate of the target point for the robot base.
         * 
         */
        int8_t new_y_movement;

        /**
         * @brief Relative z-coordinate of the target point for the robot base.
         * 
         */
        int8_t new_z_movement;
        
};
    
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
