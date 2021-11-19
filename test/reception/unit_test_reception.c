#include "../test/unit_test.h"
#include "../../Robus/src/reception.c"

/*******************************************************************************
 * Function
 ******************************************************************************/
unittest_Recep_GetHeader()
{
    NEW_TEST_CASE("Compute CRC");
    MsgAlloc_Init(NULL);
    {
        NEW_STEP("Check Nothing");
        uint16_t temp = 1;
        TEST_ASSERT_EQUAL(temp, temp);
    }
}

unittest_Recep_GetData()
{
}

unittest_Recep_GetCollision()
{
}

unittest_Recep_Drop()
{
}

unittest_Recep_CatchAck()
{
}

unittest_Recep_Init()
{
}

unittest_Recep_EndMsg()
{
}

unittest_Recep_Reset()
{
}

unittest_Recep_Timeout()
{
}

unittest_Recep_InterpretMsgProtocol()
{
}

unittest_Recep_NodeConcerned()
{
}

unittest_Recep_GetConcernedLLService()
{
}

/*******************************************************************************
 * MAIN
 ******************************************************************************/
int main(int argc, char **argv)
{
    UNITY_BEGIN();

    ASSERT_ACTIVATION(1);
    UNIT_TEST_RUN(unittest_Recep_GetHeader);
    UNIT_TEST_RUN(unittest_Recep_GetData);
    UNIT_TEST_RUN(unittest_Recep_GetCollision);
    UNIT_TEST_RUN(unittest_Recep_Drop);
    UNIT_TEST_RUN(unittest_Recep_CatchAck);
    UNIT_TEST_RUN(unittest_Recep_Init);
    UNIT_TEST_RUN(unittest_Recep_EndMsg);
    UNIT_TEST_RUN(unittest_Recep_Reset);
    UNIT_TEST_RUN(unittest_Recep_Timeout);
    UNIT_TEST_RUN(unittest_Recep_InterpretMsgProtocol);
    UNIT_TEST_RUN(unittest_Recep_NodeConcerned);
    UNIT_TEST_RUN(unittest_Recep_GetConcernedLLService);
}
