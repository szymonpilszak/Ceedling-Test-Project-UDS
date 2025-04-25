#include "unity.h"
#include "uds_services.h"

void test_ReadDataByIdentifier_valid_did_should_return_ok(void) {
    uint8_t request[] = {0x22, 0x12, 0x34};
    uint8_t response[8];
    uint8_t respLen;

    Std_ReturnType ret = Uds_Service_ReadDataByIdentifier(request, 3, response, &respLen);

    TEST_ASSERT_EQUAL_UINT8(E_OK, ret);
    TEST_ASSERT_EQUAL_UINT8(5, respLen);
    TEST_ASSERT_EQUAL_UINT8(0x62, response[0]);
    TEST_ASSERT_EQUAL_UINT8(0x12, response[1]);
    TEST_ASSERT_EQUAL_UINT8(0x34, response[2]);
    TEST_ASSERT_EQUAL_UINT8(0xDE, response[3]);
    TEST_ASSERT_EQUAL_UINT8(0xAD, response[4]);
}


#include "unity.h"
#include "uds_services.h"

// Test: msgLen < 3 (too short) → E_NOT_OK
void test_ReadDataByIdentifier_request_too_short_should_return_error(void) {
    uint8_t request[] = {0x22, 0x12}; // only 2 bytes
    uint8_t response[8];
    uint8_t respLen = 0xFF;

    Std_ReturnType ret = Uds_Service_ReadDataByIdentifier(request, 2, response, &respLen);

    TEST_ASSERT_EQUAL_UINT8(E_NOT_OK, ret);
    TEST_ASSERT_EQUAL_UINT8(0xFF, respLen); // shouldn't be changed
}

// Test: msgLen = 255 (max uint8_t)
void test_ReadDataByIdentifier_request_max_length_should_return_error(void) {
    uint8_t request[255] = {0};
    request[0] = 0x22;
    request[1] = 0x12;
    request[2] = 0x34;
    uint8_t response[16] = {0};
    uint8_t respLen = 0;

    Std_ReturnType ret = Uds_Service_ReadDataByIdentifier(request, 255, response, &respLen);

    TEST_ASSERT_EQUAL_UINT8(E_NOT_OK, ret);
    TEST_ASSERT_EQUAL_UINT8(0, respLen);
}

// Test: max uint8_t DID (0xFFFF), not handled
void test_ReadDataByIdentifier_did_max_uint16_should_return_error(void) {
    uint8_t request[] = {0x22, 0xFF, 0xFF}; // 0xFFFF
    uint8_t response[8] = {0};
    uint8_t respLen = 0;

    Std_ReturnType ret = Uds_Service_ReadDataByIdentifier(request, 3, response, &respLen);

    TEST_ASSERT_EQUAL_UINT8(E_NOT_OK, ret);
    TEST_ASSERT_EQUAL_UINT8(0, respLen);
}

// Test: handled DID, with edge response buffer
void test_ReadDataByIdentifier_valid_but_edge_buffer(void) {
    uint8_t request[] = {0x22, 0x12, 0x34};
    uint8_t response[5]; // exactly the size needed
    uint8_t respLen = 0;

    Std_ReturnType ret = Uds_Service_ReadDataByIdentifier(request, 3, response, &respLen);

    TEST_ASSERT_EQUAL_UINT8(E_OK, ret);
    TEST_ASSERT_EQUAL_UINT8(5, respLen);
}