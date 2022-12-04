#include "terminal.h"


EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{

		printf("Please enter the Transaction Date in FORMAT DD/MM/YYYY:");

		gets(termData->transactionDate);



		//Console.WriteLine(dateTime.ToString("dd/MM/yyyy"));

	if (strlen(termData->transactionDate) == 10   && strlen(termData->transactionDate) != NULL && termData->transactionDate[0] <='3' && termData->transactionDate[1] <= '9' && termData->transactionDate[2] == '/' && ((termData->transactionDate[3] == '0' && termData->transactionDate[4] <= '9') || (termData->transactionDate[3] =='1' &&termData->transactionDate[4] <= '2')) && termData->transactionDate[5] == '/' && termData->transactionDate[6] == '2' && termData->transactionDate[7] == '0' && termData->transactionDate[8] == '2' && termData->transactionDate[9] >=2)
	{

		return TERMINAL_OK;
	}
	else
	{

		return WRONG_DATE;
	}

}

void getTransactionDateTest(void)
{
    ST_terminalData_t termdata;
    printf("------------------------------------------------------\n");
    printf("Tester Name: Shorouk Shehab\n");
    printf("Function name: getTransactionDate\n");
    printf("Test Case 1: Less than 10 characters\n");
    printf("Input Data: 06/22\n");
    printf("Expected Result:1 -  WRONG_DATE \n");
    printf("Actual result: %d\n" , getTransactionDate(&termdata));
    printf("------------------------------------------------------\n");

    printf("------------------------------------------------------\n");
    printf("Tester Name: Shorouk Shehab\n");
    printf("Function name: getTransactionDate\n");
    printf("Test Case 2: Wrong format\n");
    printf("Input Data: 06-12-2022\n");
    printf("Expected Result:1 - WRONG_DATE \n");
    printf("Actual result: %d\n" , getTransactionDate(&termdata));
    printf("------------------------------------------------------\n");

        printf("------------------------------------------------------\n");
    printf("Tester Name: Shorouk Shehab\n");
    printf("Function name: getTransactionDate\n");
    printf("Test Case 3: Wrong format\n");
    printf("Input Data: 29/16/2022\n");
    printf("Expected Result:1 -  WRONG_DATE \n");
    printf("Actual result: %d\n" , getTransactionDate(&termdata));
     printf("------------------------------------------------------\n");

         printf("------------------------------------------------------\n");
    printf("Tester Name: Shorouk Shehab\n");
    printf("Function name: getTransactionDate\n");
    printf("Test Case 4: Right format\n");
    printf("Input Data: 06/05/2023\n");
    printf("Expected Result:0 - TERMINAL_OK \n");
    printf("Actual result: %d\n" , getTransactionDate(&termdata));
    printf("------------------------------------------------------\n");


}




EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData)
{

	uint8_t card_Exp_Month;
	card_Exp_Month = (cardData->cardExpirationDate[0] ) * 10 + (cardData->cardExpirationDate[1]);
	uint8_t card_Exp_Year;
	card_Exp_Year = (cardData->cardExpirationDate[3] ) * 10 + (cardData->cardExpirationDate[4] );
	uint8_t current_Month;
	current_Month = (termData->transactionDate[3]) * 10 + (termData->transactionDate[4] );
	uint8_t current_Year;
	current_Year = (termData->transactionDate[8] ) * 10 + (termData->transactionDate[9]);


	if ((card_Exp_Month < current_Year && card_Exp_Year == current_Year)|| card_Exp_Year < current_Year)
	{
        return EXPIRED_CARD;
	}

	else
	{
		return TERMINAL_OK;
	}


}

void isCardExpriedTest(void)
{
    ST_cardData_t cardData1 = {"SHOROUK MOHSEN ABDULLAH","123456789012345567","07/20"};
	ST_cardData_t cardData2 = {"SHOROUK MOHSEN ABDULLAH","123456789012345688","11/27"};
	ST_terminalData_t termData;
	getTransactionDate(&termData);
    //ST_terminalData_t termdata;
    printf("%s\n\n", termData.transactionDate);
    printf("------------------------------------------------------\n");
    printf("Tester Name: Shorouk Shehab\n");
    printf("Function name: isCardExpriedTest\n");
    printf("Test Case 1:2 - Expired Card\n");
    printf("Input Data: 07/20\n");
    printf("Expected Result:2 - EXPIRED CARD \n");
    printf("Actual result: %d\n" , isCardExpired(&cardData1 , &termData));
      printf("------------------------------------------------------\n");

      printf("------------------------------------------------------\n");
    printf("Tester Name: Shorouk Shehab\n");
    printf("Function name: isCardExpriedTest\n");
    printf("Test Case 2:NOT Expired Card\n");
    printf("Input Data: 11/27\n");
    printf("Expected Result:0 - TERMINAL OK \n");
    printf("Actual result: %d\n" , isCardExpired(&cardData2 , &termData));
        printf("------------------------------------------------------\n");
}



EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{

	printf("Please put your desired Transaction amount :) ");
	scanf("%f",&termData->transAmount);

	if (termData->transAmount > 0)
	{
        return TERMINAL_OK;
	}
	else
	{
	    return INVALID_AMOUNT;

	}


}

void getTransactionAmountTest(void)
{
    ST_terminalData_t term_Data;
    printf("------------------------------------------------------\n");
    printf("Tester Name: Shorouk Shehab\n");
    printf("Function name:getTransactionAmount \n");
    printf("Test Case 1: The transaction Amount equals zero\n");
    printf("Input Data: 0\n");
    printf("Expected Result: 4 - INVALID AMOUNT \n");
    printf("Actual result: %d\n" , getTransactionAmount (&term_Data));
    printf("------------------------------------------------------\n");

    printf("------------------------------------------------------\n");
    printf("Tester Name: Shorouk Shehab\n");
    printf("Function name:getTransactionAmount \n");
    printf("Test Case 1: The transaction Amount more than zero\n");
    printf("Input Data: 10000\n");
    printf("Expected Result: 0 - TERMINAL OK \n");
    printf("Actual result: %d\n" , getTransactionAmount (&term_Data));
       printf("------------------------------------------------------\n");


}



EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{

	if (termData->transAmount > termData->maxTransAmount)
	{
		return EXCEED_MAX_AMOUNT;
	}
	else
	{
		return TERMINAL_OK;
	}

}

void isBelowMaxAmountTest(void)
{

ST_terminalData_t term_Data;
term_Data.maxTransAmount = 10000;
    printf("------------------------------------------------------\n");
    printf("Tester Name: Shorouk Shehab\n");
    printf("Function name:isBelowMaxAmount \n");
    printf("Test Case 1: The transaction Amount is more than the max amount\n");
    printf("Input Data: 200000\n");
    term_Data.transAmount = 200000;
    printf("Expected Result: 5 - EXCEED_MAX_AMOUNT \n");
    printf("Actual result: %d\n" , isBelowMaxAmount(&term_Data));
    printf("------------------------------------------------------\n");

    printf("------------------------------------------------------\n");
    printf("Tester Name: Shorouk Shehab\n");
    printf("Function name:isBelowMaxAmount \n");
    printf("Test Case 2: The transaction Amount is less than the max amount\n");
    printf("Input Data: 1000\n");
    term_Data.transAmount = 1000;
    printf("Expected Result: 0 - TERMINAL_OK \n");
    printf("Actual result: %d\n" , isBelowMaxAmount(&term_Data));
    printf("------------------------------------------------------\n");




}

EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float maxAmount)
{

	printf("Enter the maximum transaction amount: \n");
    maxAmount = termData->maxTransAmount;
	scanf("%f",&maxAmount);

  //  maxAmount = 10000;
	if (maxAmount <= 0)
	{
		return INVALID_MAX_AMOUNT;
	}
	else
	{
		return TERMINAL_OK;
	}

}

void setMaxAmountTest(void)
{
    ST_terminalData_t term_Data;
    float max = 0;

    printf("------------------------------------------------------\n");
    printf("Tester Name: Shorouk Shehab\n");
    printf("Function name:setMaxAmount \n");
    printf("Test Case 1: The MAX amount equals zero\n");
    printf("Input Data: 0\n");
    printf("Expected Result: 6 - INVALID MAX AMOUNT \n");
    printf("Actual result: %d\n" , setMaxAmount (&term_Data , max));
    printf("------------------------------------------------------\n");

    printf("------------------------------------------------------\n");
    printf("Tester Name: Shorouk Shehab\n");
    printf("Function name:setMaxAmount \n");
    printf("Test Case 1: The MAX Amount more than zero\n");
    printf("Input Data: 10000\n");
    printf("Expected Result: 0 - TERMINAL OK \n");
    printf("Actual result: %d\n" ,setMaxAmount (&term_Data, max));
    printf("------------------------------------------------------\n");

}
