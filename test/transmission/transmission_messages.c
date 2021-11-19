/******************************************************************************
 * @file Transmission messages
 * @brief messages for Tx unit tests
 * @author Luos
 * @version 0.0.0
 ******************************************************************************/
#include "transmission_messages.h"

/*******************************************************************************
 * Constants
 ******************************************************************************/
const char *message_name_array[] = {
    "Smallest", "Biggest", "Stream",
    "test", "xxx", "yyy"};

/*******************************************************************************
 * Variables
 ******************************************************************************/
dummy_message tx_messages[MESSAGE_NUMBER];

/*******************************************************************************
 * Function
*******************************************************************************/

/******************************************************************************
 * @brief init examples messages for unit tests
 * @param none
 * @return none
 ******************************************************************************/
void init_Tx_messages()
{
    for (uint8_t i = 0; i < MESSAGE_NUMBER; i++)
    {
        tx_messages[i].name = (char *)message_name_array[i];
    }

    /*tx_messages[0].msg.header.protocol    = x;
    tx_messages[0].msg.header.source      = x;
    tx_messages[0].msg.header.target      = x;
    tx_messages[0].msg.header.target_mode = x;
    tx_messages[0].msg.header.size        = x;
    tx_messages[0].msg.header.cmd         = LUOS_STATISTICS;
    tx_messages[0].msg.data               = x;
    tx_messages[0].crc                    = x;*/
}

/******************************************************************************
 * @brief find a message from its name
 * @param msg name to search in message list
 * @return pointer to an example message.
 ******************************************************************************/
dummy_message *get_Tx_message(char *name)
{
    for (uint8_t i = 0; i < MESSAGE_NUMBER; i++)
    {
        if (tx_messages[i].name)
        {
            return &tx_messages[i];
        }
    }
    return NULL;
}
