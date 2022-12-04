#include "card.h"
#include <string.h>
#include <stdio.h>


EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{

	//*cardData->cardHolderName;

	//uint8_t CardName;
	//cardData = &CardName;

		printf("Please enter the Card Name:\n");

		gets(cardData->cardHolderName);


	if ( strlen(cardData->cardHolderName) < 20   || strlen(cardData->cardHolderName) > 24 || cardData->cardHolderName == NULL)
	{

		return WRONG_NAME;
	}
	else
	{

		return CARD_OK;
	}



}

void getCardHolderNameTest(void)
{
    ST_cardData_t cardData;
    printf("------------------------------------------------------\n");
    printf("Tester Name: Shorouk Shehab\n");
    printf("Function name: getCardHolderName\n");
    printf("Test Case 1: Less than 20 characters\n");
    printf("Input Data: Shorouk\n");
    printf("Expected Result:1 - WRONG NAME \n");
    printf("Actual result: %d\n" , getCardHolderName(&cardData));
    printf("------------------------------------------------------\n");

     printf("Tester Name: Shorouk Shehab\n");
    printf("Function name: getCardHolderName\n");
    printf("Test Case 2: More than 20 characters\n");
    printf("Input Data: Shorouk Mohsen Abdullah Shehab\n");
    printf("Expected Result:1 - WRONG NAME \n");
    printf("Actual result: %d\n" , getCardHolderName(&cardData));
     printf("------------------------------------------------------\n");

     printf("Tester Name: Shorouk Shehab\n");
    printf("Function name: getCardHolderName\n");
    printf("Test Case 3: Between 20 and 24 characters\n");
    printf("Input Data: Shorouk Mohsen Shehab\n");
    printf("Expected Result:0 -  CARD_OK \n");
    printf("Actual result: %d\n" , getCardHolderName(&cardData));
  printf("------------------------------------------------------\n");
printf("------------------------------------------------------\n");
printf("------------------------------------------------------\n");








}



EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{

		printf("Please enter the Card expiration date in the form MM/YY:");

		gets(cardData->cardExpirationDate);




	if (strlen(cardData->cardExpirationDate) == 5 && cardData->cardExpirationDate != NULL  &&  ((cardData->cardExpirationDate[0] == '0' && cardData->cardExpirationDate[1] <='9') || (cardData->cardExpirationDate[0] == '1' && cardData->cardExpirationDate[1] <='2'))  && cardData->cardExpirationDate[2] == '/' && cardData->cardExpirationDate[3] == '2' && cardData->cardExpirationDate[4] >= '2' )
	{

		return CARD_OK;
	}
	else
	{

		return WRONG_EXP_DATE;
	}


}


void getCardExpiryDateTest (void)
{

     ST_cardData_t cardData;
  printf("------------------------------------------------------\n");
    printf("Tester Name: Shorouk Shehab\n");
    printf("Function name: getCardExpiryDate\n");
    printf("Test Case 1: Less than 5 characters\n");
    printf("Input Data: 06/2\n");
    printf("Expected Result: 2 - WRONG_EXP_DATE \n");
    printf("Actual result: %d\n" , getCardExpiryDate(&cardData));
  printf("------------------------------------------------------\n");

  printf("------------------------------------------------------\n");
    printf("Tester Name: Shorouk Shehab\n");
    printf("Function name: getCardExpiryDate\n");
    printf("Test Case 2: More than 5 characters\n");
    printf("Input Data: 06/2022\n");
    printf("Expected Result:2 -  WRONG_EXP_DATE \n");
    printf("Actual result: %d\n" , getCardExpiryDate(&cardData));
  printf("------------------------------------------------------\n");
  printf("------------------------------------------------------\n");
    printf("Tester Name: Shorouk Shehab\n");
    printf("Function name: getCardExpiryDate\n");
    printf("Test Case 3: Wrong Format\n");
    printf("Input Data: 06-22\n");
    printf("Expected Result:2 -  WRONG_EXP_DATE \n");
    printf("Actual result: %d\n" , getCardExpiryDate(&cardData));
  printf("------------------------------------------------------\n");


  printf("------------------------------------------------------\n");
    printf("Tester Name: Shorouk Shehab\n");
    printf("Function name: getCardExpiryDate\n");
    printf("Test Case 4: Month more than 12\n");
    printf("Input Data: 16/25\n");
    printf("Expected Result:2 -  WRONG_EXP_DATE \n");
    printf("Actual result: %d\n" , getCardExpiryDate(&cardData));
  printf("------------------------------------------------------\n");


     printf("------------------------------------------------------\n");
    printf("Tester Name: Shorouk Shehab\n");
    printf("Function name: getCardExpiryDate\n");
    printf("Test Case 5: Wrong Format YY/MM\n");
    printf("Input Data: 27/07\n");
    printf("Expected Result:2 - WRONG_EXP_DATE \n");
    printf("Actual result: %d\n" , getCardExpiryDate(&cardData));
  printf("------------------------------------------------------\n");


   printf("------------------------------------------------------\n");
    printf("Tester Name: Shorouk Shehab\n");
    printf("Function name: getCardExpiryDate\n");
    printf("Test Case 6: Non numeric Inputs\n");
    printf("Input Data: abcde\n");
    printf("Expected Result:2 -  WRONG_EXP_DATE \n");
    printf("Actual result: %d\n" , getCardExpiryDate(&cardData));
  printf("------------------------------------------------------\n");

  printf("------------------------------------------------------\n");
    printf("Tester Name: Shorouk Shehab\n");
    printf("Function name: getCardExpiryDate\n");
    printf("Test Case 7: Right format and input\n");
    printf("Input Data: 06/28\n");
    printf("Expected Result:0 - CARD_OK \n");
    printf("Actual result: %d\n" , getCardExpiryDate(&cardData));
  printf("------------------------------------------------------\n");
    printf("------------------------------------------------------\n");
    printf("------------------------------------------------------\n");
}




//This function will ask for the card's Primary Account Number and store it in card data.
//PAN is 20 numeric characters string, 19 character max, and 16 character min.
EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{

		printf("Please enter the Card PAN number:");

		 gets(cardData->primaryAccountNumber);




	if ( strlen(cardData->primaryAccountNumber) <= 19 && strlen(cardData->primaryAccountNumber) >= 16 && cardData->primaryAccountNumber != NULL)
	{

		return CARD_OK;
	}
	else
	{

		return WRONG_PAN;
	}




}

void getCardPANTest (void)
{

     ST_cardData_t cardData;
  printf("------------------------------------------------------\n");
    printf("Tester Name: Shorouk Shehab\n");
    printf("Function name: getCardPAN\n");
    printf("Test Case 1: Less than 16 characters\n");
    printf("Input Data: 1234567890\n");
    printf("Expected Result: 3- WRONG_PAN \n");
    printf("Actual result: %d\n" , getCardPAN(&cardData));
  printf("------------------------------------------------------\n");

    printf("------------------------------------------------------\n");
    printf("Tester Name: Shorouk Shehab\n");
    printf("Function name: getCardPAN\n");
    printf("Test Case 2: More than 19 characters\n");
    printf("Input Data: 12345678901234567890\n");
    printf("Expected Result:3 -  WRONG_PAN \n");
    printf("Actual result: %d\n" , getCardPAN(&cardData));
     printf("------------------------------------------------------\n");

  printf("------------------------------------------------------\n");
    printf("Tester Name: Shorouk Shehab\n");
    printf("Function name: getCardPAN\n");
    printf("Test Case 1:Between 16 and 19 characters\n");
    printf("Input Data: 12345678901234567\n");
    printf("Expected Result: 0 - CARD_OK \n");
    printf("Actual result: %d\n" , getCardPAN(&cardData));
   printf("------------------------------------------------------\n");


}

