/******************************************************************************
 * @file luos list
 * @brief list luos specific type and commands
 * @author Luos
 * @version 0.0.0
 ******************************************************************************/
#ifndef LUOS_LIST_H
#define LUOS_LIST_H

#include <robus.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/
typedef enum
{
    VOID_TYPE,
    GATE_TYPE,
    COLOR_TYPE,
    ANGLE_TYPE,
    STATE_TYPE,
    DISTANCE_TYPE,
    VOLTAGE_TYPE,
    IMU_TYPE,
    LIGHT_TYPE,
    LOAD_TYPE,
    PIPE_TYPE,
    MOTOR_TYPE,
    SERVO_MOTOR_TYPE,
    SERVO_TYPE, // To remove
    LUOS_LAST_TYPE
} luos_type_t;

typedef enum
{
    // Luos specific registers
    RTB_CMD = ROBUS_PROTOCOL_NB, // Ask(size == 0), generate(size == 2), or share(size > 2) a routing_table.
    WRITE_ALIAS,                 // Get and save a new given alias.
    UPDATE_PUB,                  // Ask to update a sensor value each time duration to the sender
    NODE_UUID,                   // luos_uuid_t

    // Revision management
    REVISION,        // service sends its firmware revision
    LUOS_REVISION,   // service sends its luos revision
    LUOS_STATISTICS, // service sends its luos revision

    // bootloader command and response
    BOOTLOADER_CMD,
    BOOTLOADER_RESP,

    // ************* End of Luos managed commands ****************

    // Common register for all services
    GET_CMD, // asks a service to publish its data
    SET_CMD, // set some undefined data

    // Generic data
    COLOR,       // color_t (R, G, B)
    COMPLIANT,   // char (True/False)
    IO_STATE,    // char (True/False)
    RATIO,       // ratio_t (percentage %)
    PEDOMETER,   // long[2] (step number and step time millisecond)
    ILLUMINANCE, // illuminance_t (lx)
    VOLTAGE,     // voltage_t (Volt)
    CURRENT,     // current_t (Ampere)
    POWER,       // power_t (Watt)
    TEMPERATURE, // temperature_t (??C)
    TIME,        // time Second (float)
    FORCE,       // force_t (Newton N)
    MOMENT,      // moment_t (Newton meter N.m)
    CONTROL,     // control_mode (control_mode_t)

    // Configuration commands
    REGISTER,   // a register data [reg_add, data[]]
    REINIT,     // char (True/False)
    PID,        // pid_t float[3] = {p, i, d}
    RESOLUTION, // resolution parameter for a sensor float
    REDUCTION,  // reduction factor (mechanical for example) float
    DIMENSION,  // dimention of an element m linear_position_t
    OFFSET,     // decay float
    SETID,      // Set Dynamixel ID

    // Space positioning
    ANGULAR_POSITION, // angular_position_t (deg)
    ANGULAR_SPEED,    // angular_speed_t (deg/s)
    LINEAR_POSITION,  // linear_position_t (m)
    LINEAR_SPEED,     // linear_speed_t (m/s)
    ACCEL_3D,         // long[3](X, Y, Z axis linear acceleration data in Gees)
    GYRO_3D,          // long[3](X, Y, Z axis rotational acceleration data in degrees per second)
    QUATERNION,       // long[4] (sensor fused w, x, y, z rotational angles)
    COMPASS_3D,       // long[3](magnetic field data in micro tesla on each axis)
    EULER_3D,         // long[3](Pitch, roll, yaw based in degrees with frame reference)
    ROT_MAT,          // short[9] (linear math 9 element matrix representation)
    LINEAR_ACCEL,     // float[3] (linear acceleration in body frame coordinates)
    GRAVITY_VECTOR,   // float[3] (Which access gravity effects)
    HEADING,          // long (360 degrees from North with Y+ axis as the pointer)

    // Space positioning limits
    ANGULAR_POSITION_LIMIT, // min angular_position_t (deg), max angular_position_t (deg)
    LINEAR_POSITION_LIMIT,  // min linear_position_t (m), max linear_position_t (m)
    RATIO_LIMIT,            // float(%)
    CURRENT_LIMIT,          // float(A)
    ANGULAR_SPEED_LIMIT,    // min angular_speed_t (deg/s), max angular_speed_t (deg/s)
    LINEAR_SPEED_LIMIT,     // min linear_speed_t (m/s), max linear_speed_t (m/s)
    TORQUE_LIMIT,           // max moment_t (Nm)
    TEMPERATURE_LIMIT,      // Max temperature_t (??C)

    // Specific register
    PARAMETERS, // depend on the service, can be : servo_parameters_t, imu_report_t, motor_mode_t
    ERROR_CMD,

    // compatibility area
    LUOS_PROTOCOL_NB,
} luos_cmd_t;

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Function
 ******************************************************************************/

#endif /* LUOS_LIST_H */
