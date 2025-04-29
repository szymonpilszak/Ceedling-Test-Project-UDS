/****************************************************************************/
/*! 
    @file   test_uds_services.c

    @brief  This part of file contains unit tests of 
            file: uds_service.c

            Containing functions:
            - Uds_Service_ReadDataByIdentifier()
            - *more functions to add in future*
 ****************************************************************************/


#include "unity.h"
#include "mock_lin_transport.h" // Mock lin_transport
#include "uds_services.h"

void setUp(void) {}
void tearDown(void) {}

void test_Uds_Service_ReadDataByIdentifier_request_is_null_should_return_E_NOT_OK(void)
{
    uint8_t response[8];
    uint8_t respLen;
    Std_ReturnType ret = Uds_Service_ReadDataByIdentifier(NULL, 3, response, &respLen);

    TEST_ASSERT_EQUAL_UINT8(E_NOT_OK, ret);
}

void test_Uds_Service_ReadDataByIdentifier_response_is_null_should_return_E_NOT_OK(void)
{
    uint8_t request[] = {0x22, 0x12, 0x34};
    uint8_t respLen;
    Std_ReturnType ret = Uds_Service_ReadDataByIdentifier(request, 3, NULL, &respLen);

    TEST_ASSERT_EQUAL_UINT8(E_NOT_OK, ret);
}

void test_Uds_Service_ReadDataByIdentifier_respLen_is_null_should_return_E_NOT_OK(void)
{
    uint8_t request[] = {0x22, 0x12, 0x34};
    uint8_t response[8];
    Std_ReturnType ret = Uds_Service_ReadDataByIdentifier(request, 3, response, NULL);

    TEST_ASSERT_EQUAL_UINT8(E_NOT_OK, ret);
}

void test_Uds_Service_ReadDataByIdentifier_invalid_request_length_should_E_NOT_OK(void)
{
    uint8_t request[] = {0x22, 0x12};
    uint8_t response[8];
    uint8_t respLen;
    Std_ReturnType ret = Uds_Service_ReadDataByIdentifier(request, 2, response, &respLen);

    TEST_ASSERT_EQUAL_UINT8(E_NOT_OK, ret);
}

void test_Uds_Service_ReadDataByIdentifier_invalid_did_should_return_E_NOT_OK(void)
{
    uint8_t request[] = {0x22, 0xAB, 0xCD};
    uint8_t response[8];
    uint8_t respLen;
    Std_ReturnType ret = Uds_Service_ReadDataByIdentifier(request, 3, response, &respLen);

    TEST_ASSERT_EQUAL_UINT8(E_NOT_OK, ret);
}

void test_Uds_Service_ReadDataByIdentifier_valid_did_should_return_E_OK(void)
{
    uint8_t request[] = {0x22, 0x12, 0x34};
    uint8_t response[8] = {0};
    uint8_t respLen = 0;

    Lin_SendData_ExpectAndReturn(response, 5, E_OK); // Positive response from Lin_SendData

    Std_ReturnType ret = Uds_Service_ReadDataByIdentifier(request, 3, response, &respLen);

    TEST_ASSERT_EQUAL_UINT8(E_OK, ret);
    TEST_ASSERT_EQUAL_UINT8(5, respLen);
    TEST_ASSERT_EQUAL_UINT8(0x62, response[0]);
    TEST_ASSERT_EQUAL_UINT8(0x12, response[1]);
    TEST_ASSERT_EQUAL_UINT8(0x34, response[2]);
    TEST_ASSERT_EQUAL_UINT8(0xDE, response[3]);
    TEST_ASSERT_EQUAL_UINT8(0xAD, response[4]);
}

void test_Uds_Service_ReadDataByIdentifier_LinSendData_fails_should_return_E_NOT_OK(void)
{
    uint8_t request[] = {0x22, 0x12, 0x34};
    uint8_t response[8] = {0};
    uint8_t respLen = 0;

    Lin_SendData_ExpectAndReturn(response, 5, E_NOT_OK); // Negative response from Lin_SendData 

    Std_ReturnType ret = Uds_Service_ReadDataByIdentifier(request, 3, response, &respLen);

    TEST_ASSERT_EQUAL_UINT8(E_NOT_OK, ret);
}
