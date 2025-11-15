/****************************************************************************************************************************************************************************************************************************/
/*! 
 *   @file   test_uds_services.c
 *
 *   @brief  This file implements Unity/CMock-based unit tests for the Uds_Service module, source file:
 *           -uds_service.c
 *
 *           Currently covering functions:
 *           - Uds_Service_ReadDataByIdentifier()
 *           - *additional UDS service functions to be added here*
 *
 *  @details  Static internal states (e.g., mockData[]) is reset to its initial state 
 *          ( {0xDE, 0xAD} ) after each test via uds_ResetStaticData() in tearDown().
 *              - Mocked functions must be initialized and verified with mock_Lin_Init(),
 *                mock_Lin_Verify(), and mock_Lin_Destroy().
 * 
 *              
 *****************************************************************************************************************************************************************************************************************************/

 #include "unity.h"
 #include "mock_lin_transport.h" // Mock lin_transport
 #include "uds_services.h"

 
                   
 
 void setUp(void) {}
 void tearDown(void){
 
    /* Call func to restore internal state of static variable (mockData[]) 
    back to its default values {0xDE, 0xAD} after each TestCase */
    uds_ResetStaticData();

    /* Clear mock functions data aftear each TestCase*/
    mock_lin_transport_Destroy();    
 }
  
 /* --------------------------------------------------------------------------------------------- TEST for: Boundary values (for each data type) ---------------------------------------------------------------------------- */
 /* ************************************************************************************************************************************************************************************************************************* */
 /* ************************************************************************************************************************************************************************************************************************* */
 /******************************************************************************************************************************** */
 /*! 
 *    @brief:        Macro to generate boundary values tests with different input values (from minimal to maximal) [unfinished]
 *                 
 *
  **********************************************************************************************************************************/
 /**********************************************************************************************************************************/
 /* Macro to generate tests for Boundary Values Check of MockData[] array with 'edge' input values:
   *min* , *min+1* , *mid* , *max-1*, *max* 
    0x00 ,  0x01   ,  0x7F ,   0xFE ,  0xFF */
 #define RUN_BOUNDARY_TEST(VAL0, VAL1)           \
 uint8_t request[]  = {0x22, 0x12, 0x34};        \
 uint8_t reqLen      = 3;                        \
 uint8_t response[8] = {0};                      \
 uint8_t respLen     = 0;                        \
                                                 \
 set_mock_data((VAL0), (VAL1));                  \
 const uint8_t* data = get_mock_data();          \
                                                 \
 uint8_t expectedResp[5] = {                     \
     0x62, request[1], request[2], (VAL0), (VAL1)\
 };                                              \
                                                 \
 Lin_SendData_ExpectAndReturn(expectedResp, 5, E_OK); \
                                                 \
 Std_ReturnType ret = Uds_Service_ReadDataByIdentifier(request, 3, response, &respLen); \
                                                 \
 TEST_ASSERT_EQUAL_UINT8_ARRAY(expectedResp, response, 5); \
 TEST_ASSERT_EQUAL_UINT8(5, respLen);            \
 TEST_ASSERT_EQUAL_UINT8(E_OK, ret);             \
 TEST_ASSERT_EQUAL_UINT8((VAL0), data[0]);       \
 TEST_ASSERT_EQUAL_UINT8((VAL1), data[1]);
/* End of macro-function to generate boundary values test cases*/


/* Call each Test for Boundary Values Check using macro RUN_BOUNDARY_TEST */
/* Test for MINIMAL input value of mockData */
void test_ReadDataByIdentifier_Boundary_Min(void)   { RUN_BOUNDARY_TEST(0x00, 0x00); }
/* Test for MINIMAL+1 VALUE of mockData */
void test_ReadDataByIdentifier_Boundary_One(void)   { RUN_BOUNDARY_TEST(0x01, 0x01); }
/* Test for MID VALUE of mockData */
void test_ReadDataByIdentifier_Boundary_Mid(void)   { RUN_BOUNDARY_TEST(0x7F, 0x7F); }
/* Test for MAXIMAL-1 VALUE of mockData */
void test_ReadDataByIdentifier_Boundary_Max1(void)  { RUN_BOUNDARY_TEST(0xFE, 0xFE); }
/* Test for MAXIMAL VALUE of mockData */
void test_ReadDataByIdentifier_Boundary_Max(void)   { RUN_BOUNDARY_TEST(0xFF, 0xFF); }
/**********************************************************************************************************************************/


/* already tested with macro-like function - left for example of easier way to test */
/******************************************************************************************************************************** */
 /*! 
 *    @brief:        This test checks if tested function corectlLy fill response for minimal input value of mockData[].
 *
 *                 
 * 
 *   Parameter input values:
 *     - request  : {0x22, 0x12, 0x34}   (expected value)    [uint8_t range: 0–255]
 *     - reqLen   : 0x03                 (expected value)    [uint8_t range: 0–255]
 *     - response : 0x00                 (min value)         [uint8_t range: 0–255]
 *     - respLen  : 0x00                 (min value)         [uint8_t range: 0–255]
 *
 *   Static/global values:
 *     - mockData[] = {0x00, 0x00}       (min, min)           [uint8_t range: 0–255]
 *
  **********************************************************************************************************************************/
 void test_Uds_Service_ReadDataByIdentifier_boundary_check_MinimalValues_of_mockData(void)
 {
     /* Set Parameter input values */        
     uint8_t request[] = {0x22, 0x12, 0x34};
     uint8_t response[8] = {0};
     uint8_t respLen = 0;
 
 
     /* Function to set static variable mockData[] */
     set_mock_data(0x00, 0x00);
 
     /* Function to get static variable mockData[] */
     const uint8_t* data = get_mock_data();
 

     /* Check parameter input values and set return value of mock function Lin_SendData() */        
     Lin_SendData_ExpectAndReturn(response, 5, E_OK); // Positive response from Lin_SendData
 
    /* Store return value of tested function */ 
     Std_ReturnType ret = Uds_Service_ReadDataByIdentifier(request, 3, response, &respLen);


     /* Check output values of static variable "mockData[]" */
     TEST_ASSERT_EQUAL_UINT8(0x00, data[0]);
     TEST_ASSERT_EQUAL_UINT8(0x00, data[1]);     
 
    
     /* Check output value of parameter "respLen" */   
     TEST_ASSERT_EQUAL_UINT8(5, respLen);
    
     /* Check output values of parameter "response" */        
     TEST_ASSERT_EQUAL_UINT8(0x62, response[0]);
     TEST_ASSERT_EQUAL_UINT8(0x12, response[1]);
     TEST_ASSERT_EQUAL_UINT8(0x34, response[2]);
     TEST_ASSERT_EQUAL_UINT8(0x00, response[3]);
     TEST_ASSERT_EQUAL_UINT8(0x00, response[4]);

     /* Check return of tested function */
     TEST_ASSERT_EQUAL_UINT8(E_OK, ret);
 }
 /* --------------------------------------------------------------------------------------------- End of TEST for: Boundary values (for each data type)  -------------------------------------------------------------------- */
 /* ************************************************************************************************************************************************************************************************************************* */
 /* ************************************************************************************************************************************************************************************************************************* */





/* ---------------------------------------------------------------------------------------------- TEST for: NULL pointer checks --------------------------------------------------------------------------------------------- */
 /* ************************************************************************************************************************************************************************************************************************* */
 /* ************************************************************************************************************************************************************************************************************************* */
 
 /******************************************************************************************************************************** */
 /*! 
 *    @brief:        This test checks if tested function returns E_NOT_OK for invalid pointer to request (NULL).
 *                   Parameters are set as follows:
 *
 *                   
 *   
 *
 *   Parameter input values:
 *     - request  : {NULL}   (invalid pointer)   [uint8_t range: 0–255]
 *     - reqLen   : 0x00     (min value)         [uint8_t range: 0–255]
 *     - response : 0x00     (min value )        [uint8_t range: 0–255]
 *     - respLen  : 0x00     (min value)         [uint8_t range: 0–255]
 *
 *   Static/global values:
 *     - mockData[] = {0xDE, 0xAD}               [uint8_t range: 0–255]
 *
  **********************************************************************************************************************************/
 void test_Uds_Service_ReadDataByIdentifier_request_is_null_should_return_E_NOT_OK(void)
 {
    /* Set Parameter input values */    
     uint8_t* request = NULL;    /* Invalid pointer to request */
     uint8_t reqLen = 0;
     uint8_t response[8] = {0x00};
     uint8_t respLen = 0x00;
 
    /* Store return value of tested function */
     Std_ReturnType ret = Uds_Service_ReadDataByIdentifier(request, reqLen, response, &respLen);
 
     /* Check return of tested function */
     TEST_ASSERT_EQUAL_UINT8(E_NOT_OK, ret);
 }
 
 /******************************************************************************************************************************** */
 /*! 
 *    @brief:        This test checks if tested function returns E_NOT_OK for invalid pointer to response (NULL).
 *                   
 *   
 *
 *   Parameter input values:
 *     - request  : {0x00}   (min value)         [uint8_t range: 0–255]
 *     - reqLen   : 0x00     (min value)         [uint8_t range: 0–255]
 *     - response : NULL     (invalid pointer)   [uint8_t range: 0–255]
 *     - respLen  : 0x00     (min value)         [uint8_t range: 0–255]
 *
 *   Static/global values:
 *     - mockData[] = {0xDE, 0xAD}               [uint8_t range: 0–255]
 *
  **********************************************************************************************************************************/
 void test_Uds_Service_ReadDataByIdentifier_response_is_null_should_return_E_NOT_OK(void)
 {
    /* Set Parameter input values */    
     uint8_t request[] = {0x00, 0x00, 0x00};
     uint8_t reqLen = 0;
     uint8_t* response = NULL;   /* Invalid pointer to response  */
     uint8_t respLen = 0x00;
 
    /* Store return value of tested function */
     Std_ReturnType ret = Uds_Service_ReadDataByIdentifier(request, reqLen, response, &respLen);
 
     /* Check return of tested function */
     TEST_ASSERT_EQUAL_UINT8(E_NOT_OK, ret);
 }
 
 /******************************************************************************************************************************** */
 /*! 
 *    @brief:        This test checks if tested function returns E_NOT_OK for invalid pointer to respLen (NULL).
 *         
 *
 *                    
 *   Parameter input values:
 *     - request  : {0x00}   (min value)         [uint8_t range: 0–255]
 *     - reqLen   : 0x00     (min value)         [uint8_t range: 0–255]
 *     - response : 0x00     (min value)         [uint8_t range: 0–255] 
 *     - respLen  : NULL     (invalid pointer)   [uint8_t range: 0–255]
 *
 *   Static/global values:
 *     - mockData[] = {0xDE, 0xAD}               [uint8_t range: 0–255]
 *
  **********************************************************************************************************************************/
 void test_Uds_Service_ReadDataByIdentifier_respLen_is_null_should_return_E_NOT_OK(void)
 {
    /* Set Parameter input values */    
     uint8_t request[] = {0x00, 0x00, 0x00};
     uint8_t reqLen = 0;
     uint8_t response[8] = {0x00};
     uint8_t* respLen = NULL;     /* Invalid pointer to response length */
 
    /* Store return value of tested function */
     Std_ReturnType ret = Uds_Service_ReadDataByIdentifier(request, reqLen, response, respLen);
 
     /* Check return of tested function */
     TEST_ASSERT_EQUAL_UINT8(E_NOT_OK, ret);
 }
 /* --------------------------------------------------------------------------------------------- End of TEST for: NULL pointer checks -------------------------------------------------------------------------------------- */
 /* ************************************************************************************************************************************************************************************************************************* */
 
 
 
 
 
 /* --------------------------------------------------------------------------------------------- TEST for: invalid request/did/LinSendData() ------------------------------------------------------------------------------- */
 /* ************************************************************************************************************************************************************************************************************************* */
 /* ************************************************************************************************************************************************************************************************************************* */
 
 /******************************************************************************************************************************** */
 /*! 
*   @brief:        This test checks if tested function returns E_NOT_OK for request length different than 3.
 *              
 * 
 *
 *   Parameter input values:
 *     - request  : {0x22, 0x12}   (min value)                         [uint8_t range: 0–255]
 *     - reqLen   : 0x02           (different than expected value)     [uint8_t range: 0–255]
 *     - response : 0x00           (min value)                         [uint8_t range: 0–255]
 *     - respLen  : 0x00           (min value)                         [uint8_t range: 0–255]
 *
 *   Static/global values:
 *     - mockData[] = {0xDE, 0xAD}                                      [uint8_t range: 0–255]
 *
  **********************************************************************************************************************************/
 void test_Uds_Service_ReadDataByIdentifier_request_length_different_than_3_should_return_E_NOT_OK(void)
 {
     /* Set Parameter input values */    
     uint8_t request[] = {0x22, 0x12};   
     uint8_t reqLen = 2;                 /* Invalid request length (EXPECTED: 3) */
     uint8_t response[8] = {0x00};
     uint8_t respLen = 0x00;
 
     /* Store return value of tested function */
     Std_ReturnType ret = Uds_Service_ReadDataByIdentifier(request, reqLen, response, &respLen);
 
     /* Check return of tested function */
     TEST_ASSERT_EQUAL_UINT8(E_NOT_OK, ret);
 }
 
 /******************************************************************************************************************************** */
 /*! 
 *    @brief:        This test checks if tested function returns E_NOT_OK for invalid DID.
 *    
 *                    
 *
 *   Parameter input values:
 *     - request  : {0x22, 0xAB, 0xCD}   (min value)         [uint8_t range: 0–255]
 *     - reqLen   : 0x03                 (expected value)    [uint8_t range: 0–255]
 *     - response : 0x00                 (min value)         [uint8_t range: 0–255]
 *     - respLen  : 0x00                 (min value)         [uint8_t range: 0–255]
 *
 *   Static/global values:
 *     - mockData[] = {0xDE, 0xAD}                           [uint8_t range: 0–255]
 *
  **********************************************************************************************************************************/
 void test_Uds_Service_ReadDataByIdentifier_did_different_than_0x123_should_return_E_NOT_OK(void)
 {
     /* Set Parameter input values */    
     uint8_t request[] = {0x22, 0xAB, 0xCD};
     uint8_t reqLen = 3;
     uint8_t response[8] = {0};
     uint8_t respLen = 0;

     /* Store return value of tested function */
     Std_ReturnType ret = Uds_Service_ReadDataByIdentifier(request, reqLen, response, &respLen);
 
     /* Check return of tested function */
     TEST_ASSERT_EQUAL_UINT8(E_NOT_OK, ret);
 }
 
 /******************************************************************************************************************************** */
 /*! 
 *    @brief:        This test checks if tested function returns E_NOT_OK if return from mocked function LinSendData().
 *                   is different than E_OK.                   
 *    
 *                    
 *
 *   Parameter input values:
 *     - request  : {0x22, 0x12, 0x34}   (min value)         [uint8_t range: 0–255]
 *     - reqLen   : 0x03                 (expected value)    [uint8_t range: 0–255]
 *     - response : 0x00                 (min value)         [uint8_t range: 0–255]
 *     - respLen  : 0x00                 (min value)         [uint8_t range: 0–255]
 *
 *   Static/global values:
 *     - mockData[] = {0xDE, 0xAD}                           [uint8_t range: 0–255]
 *
  **********************************************************************************************************************************/
 void test_Uds_Service_ReadDataByIdentifier_return_from_LinSendData_different_than_E_OK_should_return_E_NOT_OK(void) 
 {
     /* Set Parameter input values */
     uint8_t request[] = {0x22, 0x12, 0x34};
     uint8_t reqLen = 3;
     uint8_t response[8] = {0};
     uint8_t respLen = 0;
 
     /* Check parameter input values and set return value of mock function Lin_SendData() */
     Lin_SendData_ExpectAndReturn(response, 5, E_NOT_OK); // Negative response from Lin_SendData()
 
     /* Store return value of tested function */
     Std_ReturnType ret = Uds_Service_ReadDataByIdentifier(request, reqLen, response, &respLen);
 
     /* Check return of tested function */
     TEST_ASSERT_EQUAL_UINT8(E_NOT_OK, ret);
 }  
 /* --------------------------------------------------------------------------------------------- End of TEST for: invalid request/did/LinSendData -------------------------------------------------------------------------- */
 /* ************************************************************************************************************************************************************************************************************************* */
 /* ************************************************************************************************************************************************************************************************************************* */
 
 
 
 
 
 /* --------------------------------------------------------------------------------------------- TEST for: happy path ------------------------------------------------------------------------------------------------------ */
 /* ************************************************************************************************************************************************************************************************************************* */
 /* ************************************************************************************************************************************************************************************************************************* */
 
/******************************************************************************************************************************** */
 /*! 
 *    @brief:        This test checks if tested function returns E_OK for expected DID, request and request length. 
 *                 
 *
 * 
 *   Parameter input values:
 *     - request  : {0x22, 0x12, 0x34}   (expected value)    [uint8_t range: 0–255]
 *     - reqLen   : 0x03                 (expected value)    [uint8_t range: 0–255]
 *     - response : 0x00                 (min value)         [uint8_t range: 0–255]
 *     - respLen  : 0x00                 (min value)         [uint8_t range: 0–255]
 *
 *   Static/global values:
 *     - mockData[] = {0xDE, 0xAD}                           [uint8_t range: 0–255]
 *
  **********************************************************************************************************************************/
 void test_Uds_Service_ReadDataByIdentifier_valid_did_should_return_E_OK(void)
 {
     /* Set Parameter input values */
     uint8_t request[] = {0x22, 0x12, 0x34};
     uint8_t reqLen = 3;
     uint8_t response[8] = {0};
     uint8_t respLen = 0;
 
     /* Check parameter input values and set return value of mock function Lin_SendData() */  
     Lin_SendData_ExpectAndReturn(response, 5, E_OK); // Positive response from Lin_SendData
 
     /* Store return value of tested function */
     Std_ReturnType ret = Uds_Service_ReadDataByIdentifier(request, reqLen, response, &respLen);
 

     /* Check output value of parameter "respLen" */
     TEST_ASSERT_EQUAL_UINT8(5, respLen);

     /* Check output values of parameter "response" */ 
     TEST_ASSERT_EQUAL_UINT8(0x62, response[0]);
     TEST_ASSERT_EQUAL_UINT8(0x12, response[1]);
     TEST_ASSERT_EQUAL_UINT8(0x34, response[2]);
     TEST_ASSERT_EQUAL_UINT8(0xDE, response[3]);
     TEST_ASSERT_EQUAL_UINT8(0xAD, response[4]);

     /* Check return of tested function */
     TEST_ASSERT_EQUAL_UINT8(E_OK, ret);
 }
 /* --------------------------------------------------------------------------------------------- End of TEST for: happy path() --------------------------------------------------------------------------------------------- */
 /* ************************************************************************************************************************************************************************************************************************* */
 /* ************************************************************************************************************************************************************************************************************************* */
 
 
 
  
 
 
 
 
 
 

 
 
 /* End of file */















