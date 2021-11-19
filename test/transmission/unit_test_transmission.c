#include "transmission_messages.h"

extern dummy_message tx_messages[MESSAGE_NUMBER];
extern const char *message_name_array[];

/*******************************************************************************
 * Function
 ******************************************************************************/
#define TEMP_SIZE 32
void unittest_compute_crc()
{
    NEW_TEST_CASE("Void case");
    MsgAlloc_Init(NULL);
    {
        NEW_STEP("Check Nothing");
        uint16_t temp = 1;
        TEST_ASSERT_EQUAL(temp, temp);
    }

    NEW_TEST_CASE("Compute CRC");
    MsgAlloc_Init(NULL);
    {
        NEW_STEP("Compute CRC");

        uint8_t data[TEMP_SIZE];
        uint32_t crc_val          = 0;
        uint32_t expected_crc_val = 63510; //0xFFFF;

        for (uint8_t i = 0; i < TEMP_SIZE; i++)
        {
            data[i] = i;
        }
        /*for (uint8_t i = 0; i < TEMP_SIZE; i++)
        {
            printf("- %d ", data[i]);
        }
        printf("\n\n");*/

        for (uint8_t i = 0; i < TEMP_SIZE; i++)
        {
            LuosHAL_ComputeCRC(&data[i], (uint8_t *)&crc_val);
        }

        printf("\nExpected CRC Value %d\n", expected_crc_val);
        printf("Computed CRC Value %d\n", crc_val);
        TEST_ASSERT_EQUAL(expected_crc_val, crc_val);
    }
}

void unittest_message()
{
    NEW_TEST_CASE("Compute message");
    MsgAlloc_Init(NULL);
    {
        NEW_STEP("Check message names");
        for (size_t i = 0; i < MESSAGE_NUMBER; i++)
        {
            //TEST_ASSERT_EQUAL_STRING("Smallest", tx_messages[0].name);
            TEST_ASSERT_EQUAL_STRING(message_name_array[i], tx_messages[i].name);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
void unittest_Transmit_GetLockStatus()
{
    /*NEW_TEST_CASE("Dummy");
    MsgAlloc_Init(NULL);
    {
        NEW_STEP("Check Nothing");
        uint16_t temp = 1;
        TEST_ASSERT_EQUAL(temp, temp);
    }*/
}

void unittest_Transmit_SendAck()
{
}

void unittest_Transmit_Process()
{
}

void unittest_Transmit_End()
{
}

/*******************************************************************************
 * MAIN
 ******************************************************************************/
int main(int argc, char **argv)
{
    UNITY_BEGIN();

    // Fill structure with dummy Tx messages
    init_Tx_messages();

    // Enable Luos Asserts
    ASSERT_ACTIVATION(1);

    // A deplacer
    UNIT_TEST_RUN(unittest_compute_crc);
    UNIT_TEST_RUN(unittest_message);

    // Unit tests for transmission
    UNIT_TEST_RUN(unittest_Transmit_GetLockStatus);
    UNIT_TEST_RUN(unittest_Transmit_SendAck);
    UNIT_TEST_RUN(unittest_Transmit_Process);
    UNIT_TEST_RUN(unittest_Transmit_End);

    UNITY_END();
}
