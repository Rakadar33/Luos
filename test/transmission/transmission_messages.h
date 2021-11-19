/******************************************************************************
 * @file Transmission messages
 * @brief messages for Tx unit tests
 * @author Luos
 * @version 0.0.0
 ******************************************************************************/
#ifndef _TRANSMISSION_MESSAGES_H_
#define _TRANSMISSION_MESSAGES_H_

#include "../test/unit_test.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
typedef struct
{
    char *name;
    msg_t msg;
    uint16_t crc;
} dummy_message;

#define MESSAGE_NUMBER 6

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Function
*******************************************************************************/
void init_Tx_messages(void);
dummy_message *get_Tx_message(char *name);

#endif /* _TRANSMISSION_MESSAGES_H_ */
