#include "template_motor.h"
#include "profile_motor.h"
#include "math.h"
/******************************************************************************
 * @brief function converting Luos messages innto data and reverse.
 * @param service the target service
 * @param msg the received message
 * @param motor the data struct to update
 * @return None
 ******************************************************************************/
static void MotorConfig_Handler(service_t *service, msg_t *msg, profile_motor_t *motor_profile)
{
    if (msg->header.cmd == PARAMETERS)
    {
        // check the message size
        // fill the message infos
        memcpy((void *)&motor_profile->mode, msg->data, sizeof(motor_mode_t));
        return;
    }
}
/******************************************************************************
 * @brief Msg Handler call backed by Luos when a msg receive for this service
 * @param Service destination
 * @param Msg receive
 * @return None
 ******************************************************************************/
static void TemplateMotor_MsgHandler(service_t *service, msg_t *msg)
{
    template_motor_t *motor_template = (template_motor_t *)service->template_context;
    ProfileMotor_Handler(service, msg, &motor_template->profile);
    MotorConfig_Handler(service, msg, &motor_template->profile);
    if (motor_template->self != 0)
    {
        motor_template->self(service, msg);
    }
}
/******************************************************************************
 * @brief Service creation following the template
 * @param service_cb is an optional user callback called on every massage for this service
 * @param motor_struct template object pointer
 * @param alias for the service string (15 caracters max).
 * @param revision FW for the service (tab[MajorVersion,MinorVersion,Patch])
 * @return None
 ******************************************************************************/
service_t *TemplateMotor_CreateService(SERVICE_CB service_cb, template_motor_t *motor_template, const char *alias, revision_t revision)
{
    motor_template->self      = service_cb;
    service_t *service        = Luos_CreateService(TemplateMotor_MsgHandler, MOTOR_TYPE, alias, revision);
    service->template_context = (void *)motor_template;
    return service;
}
/******************************************************************************
 * @brief function converting Luos messages innto data and reverse.
 * @param service the target service
 * @param msg the received message
 * @param motor_struct the data struct to update
 * @return None
 ******************************************************************************/
void ProfileMotor_Handler(service_t *service, msg_t *msg, profile_motor_t *profile_motor)
{
    switch (msg->header.cmd)
    {
        case GET_CMD:
        {
            msg_t pub_msg;
            pub_msg.header.target_mode = msg->header.target_mode;
            pub_msg.header.target      = msg->header.source;
            if (profile_motor->mode.current)
            {
                ElectricOD_CurrentToMsg((current_t *)&profile_motor->current, &pub_msg);
                Luos_SendMsg(service, &pub_msg);
            }
            if (profile_motor->mode.temperature)
            {
                TemperatureOD_TemperatureToMsg((current_t *)&profile_motor->temperature, &pub_msg);
                Luos_SendMsg(service, &pub_msg);
            }
        }
        break;
        case RATIO:
        {
            // get the motor power ratio
            RatioOD_RatioFromMsg(&profile_motor->power, msg);
            if (profile_motor->power > 100.0)
                profile_motor->power = 100.0;
            if (profile_motor->power < -100.0)
                profile_motor->power = -100.0;
        }
        break;
        case RATIO_LIMIT:
        {
            // set the motor power ratio limit
            RatioOD_RatioFromMsg(&profile_motor->limit_ratio, msg);
            profile_motor->limit_ratio = fabs(profile_motor->limit_ratio);
            if (profile_motor->limit_ratio > 100.0)
                profile_motor->limit_ratio = 100.0;
        }
        break;
        case CURRENT_LIMIT:
        {
            // set the motor current limit
            ElectricOD_CurrentFromMsg((current_t *)&profile_motor->limit_current, msg);
            profile_motor->limit_current = fabs(profile_motor->limit_current);
        }
        break;
        case TEMPERATURE_LIMIT:
        {
            // set the motor power ratio limit
            TemperatureOD_TemperatureFromMsg(&profile_motor->limit_temperature, msg);
            profile_motor->limit_temperature = fabs(profile_motor->limit_temperature);
        }
        break;
    }
}
