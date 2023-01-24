#include <math.h>
#include <ArduinoEigen.h>


/**
 * @brief Class which has all transformation matrices.
 * 
 */
class Transformation {

     public:
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW
        /**
         * @brief Construct a new Transformation object.
         * 
         */
        Transformation();

        /**
         * @brief Get the transformation matrix from leg1 to robot base.
         * 
         * @return Eigen::Matrix2d rotation matrix T_1toB.
         */
        Eigen::Matrix2d get_T1B();

        /**
         * @brief Get the transformation matrix from leg2 to robot base.
         * 
         * @return Eigen::Matrix2d rotation matrix T_2toB.
         */
        Eigen::Matrix2d get_T2B();

        /**
         * @brief Get the transformation matrix from leg3 to robot base.
         * 
         * @return Eigen::Matrix2d rotation matrix T_3toB.
         */
        Eigen::Matrix2d get_T3B();

        /**
         * @brief Get the transformation matrix from leg4 to robot base.
         * 
         * @return Eigen::Matrix2d rotation matrix T_4toB.
         */
        Eigen::Matrix2d get_T4B();

        /**
         * @brief Get the transformation matrix from leg5 to robot base.
         * 
         * @return Eigen::Matrix2d rotation matrix T_5toB.
         */
        Eigen::Matrix2d get_T5B();

        /**
         * @brief Get the transformation matrix from leg6 to robot base.
         * 
         * @return Eigen::Matrix2d rotation matrix T_6toB.
         */
        Eigen::Matrix2d get_T6B();


        //---------------------------------------------------------------------------------------------------
        //------------------- DELETE -----------------------------------------------------------------------
        //--------------------------------------------------------------------------------------------------
        Eigen::Matrix2d createROTz(int8_t angle);
     
     private:

        /**
         * @brief Angle which comes from the baseplate design (60°).
         * 
         */
        float alpha = M_PI/3;
        //float l1, l2 = 87.3;

        /**
         * @brief Rotation matrix from leg1 to robot base.
         * 
         */
        Eigen::Matrix2d T_1B;

        /**
         * @brief Rotation matrix from leg2 to robot base.
         * 
         */
        Eigen::Matrix2d T_2B;

        /**
         * @brief Rotation matrix from leg3 to robot base.
         * 
         */
        Eigen::Matrix2d T_3B;

        /**
         * @brief Rotation matrix from leg4 to robot base.
         * 
         */
        Eigen::Matrix2d T_4B;

        /**
         * @brief Rotation matrix from leg5 to robot base.
         * 
         */
        Eigen::Matrix2d T_5B;

        /**
         * @brief Rotation matrix from leg6 to robot base.
         * 
         */
        Eigen::Matrix2d T_6B;
         
};