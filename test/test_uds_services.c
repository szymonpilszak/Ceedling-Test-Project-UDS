/****************************************************************************************************************************************************************************************************************************/
/*! 
    @file   test_uds_services.c

    @brief  This file contains unit tests of :
            source file: uds_service.c

            Including functions:
            - Uds_Service_ReadDataByIdentifier()
            - *more functions to add in future*
 *****************************************************************************************************************************************************************************************************************************/


 #include "unity.h"
 #include "mock_lin_transport.h" // Mock lin_transport
 #include "uds_services.h"
 
 void setUp(void) {}
 void tearDown(void) {}
  
 
 
 
 
 
 /* --------------------------------------------------------------------------------------------- TEST for: NULL pointer checks --------------------------------------------------------------------------------------------- */
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
 *   Parameter values:
 *     - request  : {NULL}   (invalid value)     [uint8_t range: 0–255]
 *     - reqLen   : 0x00     (min value)         [uint8_t range: 0–255]
 *     - response : 0x00     (invalid pointer)   [uint8_t range: 0–255]
 *     - respLen  : 0x00     (min value)         [uint8_t range: 0–255]
 *
 *   Static/global values:
 *     - mockData[] = {0xDE, 0xAD}               [uint8_t range: 0–255]
 *
  **********************************************************************************************************************************/
 void test_Uds_Service_ReadDataByIdentifier_request_is_null_should_return_E_NOT_OK(void)
 {
        /* Set parameter values */    
     uint8_t* request = NULL;    /* Invalid request */
     uint8_t reqLen = 0;
     uint8_t response[8] = {0x00};
     uint8_t respLen = 0x00;
 
 
     Std_ReturnType ret = Uds_Service_ReadDataByIdentifier(request, reqLen, response, &respLen);
 
     TEST_ASSERT_EQUAL_UINT8(E_NOT_OK, ret);
 }
 
 /******************************************************************************************************************************** */
 /*! 
 *    @brief:        This test checks if tested function returns E_NOT_OK for invalid pointer to response (NULL).
 *                   
 *   
 *
 *   Parameter values:
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
        /* Set parameter values */    
     uint8_t request[] = {0x00, 0x00, 0x00};
     uint8_t reqLen = 0;
     uint8_t* response = NULL;   /* Invalid response  */
     uint8_t respLen = 0x00;
 
 
     Std_ReturnType ret = Uds_Service_ReadDataByIdentifier(request, reqLen, response, &respLen);
 
     TEST_ASSERT_EQUAL_UINT8(E_NOT_OK, ret);
 }
 
 /******************************************************************************************************************************** */
 /*! 
 *    @brief:        This test checks if tested function returns E_NOT_OK for invalid pointer to respLen (NULL).
 *                   Parameters are set as follows:     
 *
 *                   
 *   
 *
 *   Parameter values:
 *     - request  : {0x00}   (min value)         [uint8_t range: 0–255]
 *     - reqLen   : 0x00     (min value)         [uint8_t range: 0–255]
 *     - response : 0x00     (invalid pointer)   [uint8_t range: 0–255] 
 *     - respLen  : NULL     (min value)         [uint8_t range: 0–255]
 *
 *   Static/global values:
 *     - mockData[] = {0xDE, 0xAD}               [uint8_t range: 0–255]
 *
  **********************************************************************************************************************************/
 void test_Uds_Service_ReadDataByIdentifier_respLen_is_null_should_return_E_NOT_OK(void)
 {
        /* Set parameter values */    
     uint8_t request[] = {0x00, 0x00, 0x00};
     uint8_t reqLen = 0;
     uint8_t response[8] = {0x00};
     uint8_t* respLen = NULL;     /* Invalid response length */
 
     Std_ReturnType ret = Uds_Service_ReadDataByIdentifier(request, reqLen, response, respLen);
 
     TEST_ASSERT_EQUAL_UINT8(E_NOT_OK, ret);
 }
 /* --------------------------------------------------------------------------------------------- End of TEST for: NULL pointer checks -------------------------------------------------------------------------------------- */
 /* ************************************************************************************************************************************************************************************************************************* */
 
 
 
 
 
 
 /* --------------------------------------------------------------------------------------------- TEST for: invalid request/did/LinSendData() ------------------------------------------------------------------------------- */
 /* ************************************************************************************************************************************************************************************************************************* */
 /* ************************************************************************************************************************************************************************************************************************* */
 
 /******************************************************************************************************************************** */
 /*! 
     @brief:        This test checks if tested function returns E_NOT_OK for request length different than 3.
                    Parameters are set as follows:     
 
 *
 *                   
 *   
 *
 *   Parameter values:
 *     - request  : {0x22, 0x12}   (min value)         [uint8_t range: 0–255]
 *     - reqLen   : 0x02                               [uint8_t range: 0–255]
 *     - response : 0x00           (min value)         [uint8_t range: 0–255]
 *     - respLen  : NULL           (min value)         [uint8_t range: 0–255]
 *
 *   Static/global values:
 *     - mockData[] = {0xDE, 0xAD}               [uint8_t range: 0–255]
 *
  **********************************************************************************************************************************/
 void test_Uds_Service_ReadDataByIdentifier_request_length_different_than_3_should_return_E_NOT_OK(void)
 {
        /* Set parameter values */    
     uint8_t request[] = {0x22, 0x12};   
     uint8_t reqLen = 2;                 /* Invalid request length (EXPECTED: 3) */
     uint8_t response[8] = {0x00};
     uint8_t respLen = 0x00;
 
     Std_ReturnType ret = Uds_Service_ReadDataByIdentifier(request, reqLen, response, &respLen);
 
     TEST_ASSERT_EQUAL_UINT8(E_NOT_OK, ret);
 }
 
 /******************************************************************************************************************************** */
 /*! 
     @brief:        This test checks if tested function returns E_NOT_OK for invalid DID.
                    Parameters are set as follows:     
 
     @param[inout]  request :   Pointer to service request 
                    Set to  :   {0x22, 0x12}    
                    Range   :   uint8_t (0-255)     
 
     @param[in]     reqLen  :   Request length
                    Set to  :   3 (as expected)   
                    Range   :   uint8_t (0-255)          
 
     @param[inout]  response:   Pointer to service response
                    Set to  :   *min* (0)    
                    Range   :   uint8_t (0-255)       
                    
     @param[inout]  respLen :   Pointer to response length
                    Set to  :   *min* (0)    
                    Range   :   uint8_t (0-255)        
     
 
  **********************************************************************************************************************************/
 void test_Uds_Service_ReadDataByIdentifier_did_different_than_0x123_should_return_E_NOT_OK(void)
 {
        /* Set parameter values */    
     uint8_t request[] = {0x22, 0xAB, 0xCD};
     uint8_t reqLen = 3;
     uint8_t response[8] = {0};
     uint8_t respLen = 0;
     Std_ReturnType ret = Uds_Service_ReadDataByIdentifier(request, reqLen, response, &respLen);
 
     TEST_ASSERT_EQUAL_UINT8(E_NOT_OK, ret);
 }
 
 /******************************************************************************************************************************** */
 /*! 
     @brief:        This test checks if tested function returns E_NOT_OK if return from mocked function LinSendData().
                    is different than E_OK.
                    Parameters are set as follows:                    
 
     @param[inout]  request :   Pointer to service request 
                    Set to  :   {0x22, 0x12, 0x34}    
                    Range   :   uint8_t (0-255)     
 
     @param[in]     reqLen  :   Request length
                    Set to  :   3 (as expected)   
                    Range   :   uint8_t (0-255)          
 
     @param[inout]  response:   Pointer to service response
                    Set to  :   *min* (0)    
                    Range   :   uint8_t (0-255)       
                    
     @param[inout]  respLen :   Pointer to response length
                    Set to  :   *min* (0)    
                    Range   :   uint8_t (0-255)        
     
 
  **********************************************************************************************************************************/
 void test_Uds_Service_ReadDataByIdentifier_return_from_LinSendData_different_than_E_OK_should_return_E_NOT_OK(void) 
 {
        /* Set parameter values */
     uint8_t request[] = {0x22, 0x12, 0x34};
     uint8_t reqLen = 3;
     uint8_t response[8] = {0};
     uint8_t respLen = 0;
 
 
     Lin_SendData_ExpectAndReturn(response, 5, E_NOT_OK); // Negative response from Lin_SendData()
 
     Std_ReturnType ret = Uds_Service_ReadDataByIdentifier(request, reqLen, response, &respLen);
 
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
     @brief:        This test checks if tested function returns E_OK for expected request, request length, and DiD.
                    Parameters are set as follows:     
 
     @param[inout]  request :   Pointer to service request 
                    Set to  :   {0x22, 0x12, 0x34}    
                    Range   :   uint8_t (0-255)     
 
     @param[in]     reqLen  :   Request length
                    Set to  :   3 (as expected)   
                    Range   :   uint8_t (0-255)          
 
     @param[inout]  response:   Pointer to service response
                    Set to  :   *min* (0)    
                    Range   :   uint8_t (0-255)       
                    
     @param[inout]  respLen :   Pointer to response length
                    Set to  :   *min* (0)    
                    Range   :   uint8_t (0-255)        
     
 
  **********************************************************************************************************************************/
 void test_Uds_Service_ReadDataByIdentifier_valid_did_should_return_E_OK(void)
 {
        /* Set parameter values */
     uint8_t request[] = {0x22, 0x12, 0x34};
     uint8_t reqLen = 3;
     uint8_t response[8] = {0};
     uint8_t respLen = 0;

 
 
        /* Set return and parameter values of mock function Lin_SendData() */
     Lin_SendData_ExpectAndReturn(response, 5, E_OK); // Positive response from Lin_SendData
 
     Std_ReturnType ret = Uds_Service_ReadDataByIdentifier(request, reqLen, response, &respLen);
 

        /* Check output values of parameter "response" */ 
     TEST_ASSERT_EQUAL_UINT8(E_OK, ret);
     TEST_ASSERT_EQUAL_UINT8(5, respLen);
     TEST_ASSERT_EQUAL_UINT8(0x62, response[0]);
     TEST_ASSERT_EQUAL_UINT8(0x12, response[1]);
     TEST_ASSERT_EQUAL_UINT8(0x34, response[2]);
     TEST_ASSERT_EQUAL_UINT8(0xDE, response[3]);
     TEST_ASSERT_EQUAL_UINT8(0xAD, response[4]);
 }
 /* --------------------------------------------------------------------------------------------- End of TEST for: happy path() --------------------------------------------------------------------------------------------- */
 /* ************************************************************************************************************************************************************************************************************************* */
 /* ************************************************************************************************************************************************************************************************************************* */
 
 
 
 
 
 
 /* --------------------------------------------------------------------------------------------- TEST for: Boundary values (for each data type) ---------------------------------------------------------------------------- */
 /* ************************************************************************************************************************************************************************************************************************* */
 /* ************************************************************************************************************************************************************************************************************************* */
 
 

 void test_Uds_Service_ReadDataByIdentifier_check_of_minimal_boundary_values_of_mockData(void)
 {
        /* Set parameter values */        
     uint8_t request[] = {0x22, 0x12, 0x34};
     uint8_t response[8] = {0};
     uint8_t respLen = 0;
 
 
         /* Function to set static variable mockData[] */
     set_mock_data(0x00, 0x00);
 
         /* Function to get static variable mockData[] */
     const uint8_t* data = get_mock_data();
 

        /* Set return and parameter values of mock function Lin_SendData() */        
     Lin_SendData_ExpectAndReturn(response, 5, E_OK); // Positive response from Lin_SendData
 
     Std_ReturnType ret = Uds_Service_ReadDataByIdentifier(request, 3, response, &respLen);

            /* Check output values of static variable "mockData[]" */
    TEST_ASSERT_EQUAL_UINT8(0x00, data[0]);
    TEST_ASSERT_EQUAL_UINT8(0x00, data[1]);     
 
             /* Check output values of parameter "response" */    
     TEST_ASSERT_EQUAL_UINT8(E_OK, ret);
     TEST_ASSERT_EQUAL_UINT8(5, respLen);
     TEST_ASSERT_EQUAL_UINT8(0x62, response[0]);
     TEST_ASSERT_EQUAL_UINT8(0x12, response[1]);
     TEST_ASSERT_EQUAL_UINT8(0x34, response[2]);
     TEST_ASSERT_EQUAL_UINT8(0x00, response[3]);
     TEST_ASSERT_EQUAL_UINT8(0x00, response[4]);
 }
 /* --------------------------------------------------------------------------------------------- End of TEST for: Boundary values (for each data type)  -------------------------------------------------------------------- */
 /* ************************************************************************************************************************************************************************************************************************* */
 /* ************************************************************************************************************************************************************************************************************************* */
 
 
 

 
 
 /* End of file */