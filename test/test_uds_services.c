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

/* ********************************************************************************************* TEST for: NULL pointer checks ********************************************************************************************* */
/* ************************************************************************************************************************************************************************************************************************* */
/* ************************************************************************************************************************************************************************************************************************* */

/******************************************************************************************************************************** */
/*! 
    @brief:        This test checks if function returns E_NOT_OK for invalid pointer to request (NULL).

    @param[inout]  request :   Pointer to service request 
                   Set to  :   NULL (invalid)    
                   Range   :   uint8_t (0-255)     

    @param[in]     reqLen  :   Request length
                   Set to  :   *min* (0)    
                   Range   :   uint8_t (0-255)          

    @param[inout]  response:   Pointer to service response
                   Set to  :   *min* (0)    
                   Range   :   uint8_t (0-255)       
                   
    @param[inout]  respLen :   Pointer to response length
                   Set to  :   *min* (0)    
                   Range   :   uint8_t (0-255)    


 **********************************************************************************************************************************/
void test_Uds_Service_ReadDataByIdentifier_request_is_null_should_return_E_NOT_OK(void)
{
    uint8_t* request = NULL;    /* Invalid request */
    uint8_t reqLen = 0;
    uint8_t response[8] = {0x00};
    uint8_t respLen = 0x00;

    Std_ReturnType ret = Uds_Service_ReadDataByIdentifier(request, reqLen, response, &respLen);

    TEST_ASSERT_EQUAL_UINT8(E_NOT_OK, ret);
}

/******************************************************************************************************************************** */
/*! 
    @brief:        This test checks if function returns E_NOT_OK for invalid pointer to response (NULL).

    @param[inout]  request :   Pointer to service request 
                   Set to  :   *min* (0)    
                   Range   :   uint8_t (0-255)     

    @param[in]     reqLen  :   Request length
                   Set to  :   *min* (0)    
                   Range   :   uint8_t (0-255)          

    @param[inout]  response:   Pointer to service response
                   Set to  :   NULL (invalid)    
                   Range   :   uint8_t (0-255)       
                   
    @param[inout]  respLen :   Pointer to response length
                   Set to  :   *min* (0)    
                   Range   :   uint8_t (0-255)        

 **********************************************************************************************************************************/
void test_Uds_Service_ReadDataByIdentifier_response_is_null_should_return_E_NOT_OK(void)
{
    uint8_t request[] = {0x00, 0x00, 0x00};
    uint8_t reqLen = 0;
    uint8_t* response = NULL;   /* Invalid response  */
    uint8_t respLen = 0x00;


    Std_ReturnType ret = Uds_Service_ReadDataByIdentifier(request, reqLen, response, &respLen);

    TEST_ASSERT_EQUAL_UINT8(E_NOT_OK, ret);
}

/******************************************************************************************************************************** */
/*! 
    @brief:              This test checks if function returns E_NOT_OK for invalid pointer to respLen(NULL)

    @param[inout]  request :   Pointer to service request 
                   Set to  :   *min* (0)    
                   Range   :   uint8_t (0-255)     

    @param[in]     reqLen  :   Request length
                   Set to  :   *min* (0)    
                   Range   :   uint8_t (0-255)          

    @param[inout]  response:   Pointer to service response
                   Set to  :   *min* (0)    
                   Range   :   uint8_t (0-255)       
                   
    @param[inout]  respLen :   Pointer to response length
                   Set to  :   NULL (invalid)    
                   Range   :   uint8_t (0-255)     

 **********************************************************************************************************************************/
void test_Uds_Service_ReadDataByIdentifier_respLen_is_null_should_return_E_NOT_OK(void)
{
    uint8_t request[] = {0x00, 0x00, 0x00};
    uint8_t reqLen = 0;
    uint8_t response[8] = {0x00};
    uint8_t* respLen = NULL;     /* Invalid response length */

    Std_ReturnType ret = Uds_Service_ReadDataByIdentifier(request, reqLen, response, respLen);

    TEST_ASSERT_EQUAL_UINT8(E_NOT_OK, ret);
}
/* ********************************************************************************************* End of TEST for: NULL pointer checks ************************************************************************************** */
/* ************************************************************************************************************************************************************************************************************************* */





/* ********************************************************************************************* TEST for: invalid request/did/LinSendData() ******************************************************************************* */
/* ************************************************************************************************************************************************************************************************************************* */
/* ************************************************************************************************************************************************************************************************************************* */

/******************************************************************************************************************************** */
/*! 
    @brief:        This test checks if function returns E_NOT_OK for invalid request length

    @param[inout]  request :   Pointer to service request 
                   Set to  :   {0x22, 0x12}    
                   Range   :   uint8_t (0-255)     

    @param[in]     reqLen  :   Request length
                   Set to  :   2   
                   Range   :   uint8_t (0-255)          

    @param[inout]  response:   Pointer to service response
                   Set to  :   *min* (0)    
                   Range   :   uint8_t (0-255)       
                   
    @param[inout]  respLen :   Pointer to response length
                   Set to  :   *min* (0)    
                   Range   :   uint8_t (0-255)        
    

 **********************************************************************************************************************************/
void test_Uds_Service_ReadDataByIdentifier_invalid_request_length_should_E_NOT_OK(void)
{
    uint8_t request[] = {0x22, 0x12};   
    uint8_t reqLen = 2;                 /* Invalid request length (EXPECTED: 3) */
    uint8_t response[8] = {0x00};
    uint8_t respLen = 0x00;

    Std_ReturnType ret = Uds_Service_ReadDataByIdentifier(request, reqLen, response, &respLen);

    TEST_ASSERT_EQUAL_UINT8(E_NOT_OK, ret);
}

/******************************************************************************************************************************** */
/*! 
    @brief:        This test checks if function returns E_NOT_OK for invalid DID.

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
void test_Uds_Service_ReadDataByIdentifier_invalid_did_should_return_E_NOT_OK(void)
{
    uint8_t request[] = {0x22, 0xAB, 0xCD};
    uint8_t reqLen = 3;
    uint8_t response[8] = {0};
    uint8_t respLen = 0;
    Std_ReturnType ret = Uds_Service_ReadDataByIdentifier(request, reqLen, response, &respLen);

    TEST_ASSERT_EQUAL_UINT8(E_NOT_OK, ret);
}


/******************************************************************************************************************************** */
/*! 
    @brief:        This test checks if function returns E_NOT_OK if return from mocked function LinSendData()
                   is different than E_OK.

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
void test_Uds_Service_ReadDataByIdentifier_LinSendData_fails_should_return_E_NOT_OK(void)
{
    uint8_t request[] = {0x22, 0x12, 0x34};
    uint8_t reqLen = 3;
    uint8_t response[8] = {0};
    uint8_t respLen = 0;


    Lin_SendData_ExpectAndReturn(response, 5, E_NOT_OK); // Negative response from Lin_SendData()

    Std_ReturnType ret = Uds_Service_ReadDataByIdentifier(request, reqLen, response, &respLen);

    TEST_ASSERT_EQUAL_UINT8(E_NOT_OK, ret);
}
/* ********************************************************************************************* End of TEST for: invalid request/did/LinSendData ************************************************************************** */
/* ************************************************************************************************************************************************************************************************************************* */
/* ************************************************************************************************************************************************************************************************************************* */




/* ********************************************************************************************* TEST for: happy path ****************************************************************************************************** */
/* ************************************************************************************************************************************************************************************************************************* */
/* ************************************************************************************************************************************************************************************************************************* */

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
/* ********************************************************************************************* End of TEST for: happy path() ********************************************************************************************* */
/* ************************************************************************************************************************************************************************************************************************* */
/* ************************************************************************************************************************************************************************************************************************* */





/* ********************************************************************************************* TEST for: Boundary values (for each data type) **************************************************************************** */
/* ************************************************************************************************************************************************************************************************************************* */
/* ************************************************************************************************************************************************************************************************************************* */

/******************************************************************************************************************************** */
/*! 
    @brief:              This test checks if function return positive reposne to valid DID 

    @param  request :    xx
    @param  response:    x
    @param  respLen :    x

 **********************************************************************************************************************************/


/* ********************************************************************************************* End of TEST for: Boundary values (for each data type)  ********************************************************************************************* */
/* ************************************************************************************************************************************************************************************************************************* */
/* ************************************************************************************************************************************************************************************************************************* */



/* End of TEST for: Boundary values  */


/* End of file */