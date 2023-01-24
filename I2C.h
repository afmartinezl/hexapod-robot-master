#include <Wire.h>

/**
 * @brief Class in charge of the sending the movement commands to the slave, and also in charge of the request handling (temperature and current).
 * 
 */

class I2C {
     public:
        /**
         * @brief Construct a new I2C object.
         * 
         */
        I2C();

        /**
         * @brief Send new coordinates to the desired slave.
         * 
         * @param add The address of the slave.
         * @param x The new x-coordinate (left-right).
         * @param y The new y-coordinate (forward-backward).
         * @param z The new z-coordinate (height).
         */
        void send_new_Pos(int8_t add, int8_t x, int8_t y, int8_t z, int8_t rotZ);

        /**
         * @brief Get the request response object.
         * 
         * @param address Address of the slave.
         * @param id ID of the motor.
         * @return int16_t temperature, voltage or current of the desired motor.
         */
        int16_t getRequestResponse(int8_t address, int8_t id);

        // Temperature functions ----------------------------------------------------------------------------------------------------------------------------------------------------
        /**
         * @brief Writes the temperature to the specific position in an array.
         * 
         * @param leg Leg for which the temperature should be set.
         * @param motor Motor for which the temperature should be set.
         * @param temp The temperature value.
         */
        void setLegTemp(int leg, int motor, int8_t temp);

        /**
         * @brief Set the variables for the highest temperature and the corresponding position.
         * 
         */
        void setHighest_Temp_and_Pos();

        /**
         * @brief Get the temperature of a motor.
         * 
         * @param leg Leg number for which the temperature is needed.
         * @param motor Motor number for which the temperature is needed.
         * @return int8_t temperature value of the desired motor.
         */
        int8_t getTemp(int leg, int motor);

        /**
         * @brief Get the highest temperature of all motors.
         * 
         * @return int8_t value of the highest temperature.
         */
        int8_t getHighestTemp();

        /**
         * @brief Get the position of the highest temperature.
         * 
         * @return String leg and motor where the highest temperature occured.
         */
        String getHighestTemp_Pos();

        // Voltage functions --------------------------------------------------------------------------------------------------------------------------------------------------------

        /**
         * @brief Writes the voltage to the specific position in an array.
         * 
         * @param leg Leg for which the voltage should be set.
         * @param motor Motor for which the voltage should be set.
         * @param vol The voltage value. 
         */
        void setLegVol(int leg, int motor, uint16_t vol);
        
        /**
         * @brief Set the variables for the highest voltage and the corresponding position.
         * 
         */
        void setHighest_Vol_and_Pos();

        /**
         * @brief Get the voltage of a motor.
         * 
         * @param leg Leg number for which the voltage is needed.
         * @param motor Motor number for which the voltage is needed.
         * @return uint16_t voltage value of the desired motor. 
         */
        uint16_t getVol(int leg, int motor);

        /**
         * @brief Get the highest voltage of all motors.
         * 
         * @return uint16_t value of the highest voltage.
         */
        uint16_t getHighestVol();

        /**
         * @brief Get the position of the highest voltage.
         * 
         * @return String leg and motor where the highest voltage occured.
         */
        String getHighestVol_Pos();


        // Current functions --------------------------------------------------------------------------------------------------------------------------------------------------------

        /**
         * @brief Writes the current to the specific position in an array.
         * 
         * @param leg Leg for which the current should be set.
         * @param motor Motor for which the current should be set.
         * @param curr The current value 
         */
        void setLegCurr(int leg, int motor, int16_t curr);

        /**
         * @brief Set the variables for the highest current and the corresponding position.
         * 
         */
        void setHighest_Curr_and_Pos();

        /**
         * @brief Get the current of a motor.
         * 
         * @param leg Leg number for which the current is needed.
         * @param motor Motor number for which the current is needed.
         * @return uint16_t current value of the desired motor.
         */
        uint16_t getCurr(int leg, int motor);

        /**
         * @brief Get the highest current of all motors.
         * 
         * @return uint16_t value of the highest current.
         */
        uint16_t getHighestCurr();

        /**
         * @brief Get the position of the highest current.
         * 
         * @return String leg and motor where the highest current occured. 
         */
        String getHighestCurr_Pos();
        

     private:

      /**
       * @brief Array which holds the temperatures of each motor.
       * 
       */
      int8_t temperatures[18];

      /**
       * @brief Value of the highest temperature of all motors.
       * 
       */
      int8_t highestTemperature; 

      /**
       * @brief Position of the highest temperature.
       * 
       */
      String highestTemperature_Pos;

      /**
       * @brief Array which holds the voltages for all motors.
       * 
       */
      uint16_t voltages[18];

      /**
       * @brief Value of the highest voltage of all motors.
       * 
       */
      uint16_t highestVoltage;

      /**
       * @brief Position of the highest voltage.
       * 
       */
      String highestVoltage_Pos;

      /**
       * @brief Array which holds the currents for all motors.
       * 
       */
      uint16_t currents[18];

      /**
       * @brief Value of the highest current of all motors.
       * 
       */
      uint16_t highestCurrent;

      /**
       * @brief Position of the highest current.
       * 
       */
      String highestCurrent_Pos;
     
};
