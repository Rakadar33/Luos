/******************************************************************************
 * @file robus_utils
 * @brief some tools used to debug
 * @author Luos
 * @version 0.0.0
 ******************************************************************************/
#include "luos_utils.h"
#include "luos.h"
#include "port_manager.h"
#include "string.h"
#include "luos_hal.h"
#include "msg_alloc.h"
#include "stdbool.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/
#ifdef UNIT_TEST
ut_luos_assert_t ut_assert = {.state = 0, .enable = 1};
#endif

/*******************************************************************************
 * Function
 ******************************************************************************/

/******************************************************************************
 * @brief This function can be redefine by users to manage specifi procedure on assert
 * @param file name as a string
 * @param line number
 * @return None
 ******************************************************************************/
__attribute__((weak)) void node_assert(char *file, uint32_t line)
{
    return;
}

/******************************************************************************
 * @brief Luos assertion management
 * @param file name as a string
 * @param line number
 * @return None
 ******************************************************************************/
void Luos_assert(char *file, uint32_t line)
{
    // prepare a message as a node.
    // To do that we have to reset the service ID and clear PTP states to unlock others.
    PortMng_Init();
    // completely reinit the allocator
    MsgAlloc_Init(NULL);
    msg_t msg;
    msg.header.target_mode = BROADCAST;
    msg.header.target      = BROADCAST_VAL;
    msg.header.cmd         = ASSERT;
    msg.header.size        = sizeof(line) + strlen(file);
    memcpy(msg.data, &line, sizeof(line));
    memcpy(&msg.data[sizeof(line)], file, strlen(file));
    while (Luos_SendMsg(0, &msg) != SUCCEED)
        ;
    node_assert(file, line);
    // wait for the transmission to finish before killing IRQ
    while (MsgAlloc_TxAllComplete() == FAILED)
        ;
    LuosHAL_SetIrqState(false);
    while (1)
    {
    }
}

#ifdef UNIT_TEST
/******************************************************************************
 * @brief Luos assertion management for unit testing
 * @param file name as a string
 * @param line number
 * @return None
 ******************************************************************************/
void Luos_unittest_assert(char *file, uint32_t line)
{
    // completely reinit the allocator
    MsgAlloc_Init(NULL);
    msg_t msg;

    ut_assert.state     = 1;
    ut_assert.line_size = sizeof(line);
    ut_assert.file_size = strlen(file);

    msg.header.target_mode = BROADCAST;
    msg.header.target      = BROADCAST_VAL;
    msg.header.cmd         = ASSERT;
    msg.header.size        = sizeof(line) + strlen(file);
    memcpy(msg.data, &line, sizeof(line));
    memcpy(&msg.data[sizeof(line)], file, strlen(file));

    ut_assert.msg = msg;

    LuosHAL_SetIrqState(false);
}
#endif
