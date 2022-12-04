#include "server.h"




ST_accountsDB_t accountsDB[255] = { {2000.0, RUNNING, "8989374615436851"},
								   {100000.0, BLOCKED, "5807007076043875"},
									{300000.0, RUNNING, "1234567890123456"} ,
									{30000.0, BLOCKED, "1234567890123457"},
									{10000.0, RUNNING, "12345678901234500"},
									{300000.0, BLOCKED, "1234567890123458"},
									{200.0, RUNNING, "1234567890123459"},
									{8800000.5, BLOCKED, "1234567890123450"},
									{900000.0, RUNNING, "1234567890123451"},
									{300000.0, BLOCKED, "1234567890123452"} };


ST_transaction_t Transaction_Data[255] = { 0 };

uint8_t User_Account;
uint8_t sequence_no = 0;

EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{


	if (isValidAccount(&transData->cardHolderData, &accountsDB) == ACCOUNT_NOT_FOUND)
	{
		transData->transState = FRAUD_CARD;
		printf("FRAUD CARD\n");
		return FRAUD_CARD;
	}

	else if (isAmountAvailable(&transData->terminalData.transAmount , &accountsDB[User_Account]) == LOW_BALANCE)
	{
		transData->transState = DECLINED_INSUFFECIENT_FUND;
		//printf(" DECLINED INSUFFECIENT FUND\n");
			return DECLINED_INSUFFECIENT_FUND;
	}

	else if (isBlockedAccount(&accountsDB[User_Account]) == BLOCKED_ACCOUNT)
	{
		transData->transState == DECLINED_STOLEN_CARD;
		//printf("DECLINED STOLEN CARD\n");
		return DECLINED_STOLEN_CARD;

	}

	else if (saveTransaction(&transData) == SAVING_FAILED)
	{
		transData->transState = INTERNAL_SERVER_ERROR;
		//printf("INTERNAL SERVER ERROR\n");
		return INTERNAL_SERVER_ERROR;

	}

	else
	{
		accountsDB[User_Account].balance -= transData->terminalData.transAmount;
		printf("The new Balance is: %f \n", accountsDB[User_Account].balance);
		transData->transState = APPROVED;
		//print("APPROVED");
		return APPROVED;
	}
}




void recieveTransactionDataTest(void)
{
    ST_transaction_t transData;

     printf("------------------------------------------------------\n");
    printf("Tester Name: Shorouk Shehab\n");
    printf("Function name: recieveTransactionData\n");
    printf("Test Case 1:Fraud card (WRONG PAN)\n");

  transData = (ST_transaction_t){ .cardHolderData = "Shorouk Mohsen Shehab ","12345678909876542","10/26",.terminalData = {150,1500,"30/9/2022"} };

    printf("Expected Result:3 - FRAUD CARD\n");
    printf("Actual result: %d\n" , recieveTransactionData(&transData));
    printf("------------------------------------------------------\n");


     printf("------------------------------------------------------\n");
    printf("Tester Name: Shorouk Shehab\n");
    printf("Function name: recieveTransactionData\n");
    printf("Test Case 1:STOLEN CARD\n");

  transData = (ST_transaction_t){ .cardHolderData = "Shorouk Mohsen Shehab ","5807007076043875","10/26",.terminalData = {150,1500,"30/9/2022"} };

    printf("Expected Result:2 - DECLINED_STOLEN_CARD\n");
    printf("Actual result: %d\n" , recieveTransactionData(&transData));
    printf("------------------------------------------------------\n");


    printf("------------------------------------------------------\n");
    printf("Tester Name: Shorouk Shehab\n");
    printf("Function name: recieveTransactionData\n");
    printf("Test Case 1:INSUFFICIENT FUND\n");

  transData = (ST_transaction_t){ .cardHolderData = "Shorouk Mohsen Shehab ","1234567890123459","10/26",.terminalData = {900,1500,"30/9/2022"} };

    printf("Expected Result:1 -INSUFFICIENT FUND\n");
    printf("Actual result: %d\n" , recieveTransactionData(&transData));
    printf("------------------------------------------------------\n");


    printf("------------------------------------------------------\n");
    printf("Tester Name: Shorouk Shehab\n");
    printf("Function name: recieveTransactionData\n");
    printf("Test Case 1:APPROVED\n");

 transData = (ST_transaction_t){ .cardHolderData = "Shorouk Mohsen Shehab ","1234567890123459","10/26",.terminalData = {100,1500,"30/9/2022"} };

    printf("Expected Result:0 - APPROVED\n");
    printf("Actual result: %d\n" , recieveTransactionData(&transData));
    printf("------------------------------------------------------\n");










}


EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence)
{
    accountRefrence = &accountsDB[User_Account];

	int flag=0;

	for (int i =0 ; i < 255; i++)
	{

			if (strcmp(cardData->primaryAccountNumber,accountsDB[i].primaryAccountNumber ) == 0)
			{
			     flag = 1;

                User_Account = i;



				return SERVER_OK;

			}
			else
                flag =0;



	}

if (flag == 0)
	{

		return ACCOUNT_NOT_FOUND;
	}




}




void isValidAccountTest(void)
{
      ST_cardData_t cardData;
      ST_accountsDB_t acc;

    printf("------------------------------------------------------\n");
    printf("Tester Name: Shorouk Shehab\n");
    printf("Function name: isValidAccount\n");
    printf("Test Case 1:WRONG PAN\n");

    cardData = (ST_cardData_t){.cardHolderName="Shorouk Mohsen Shehab ",.primaryAccountNumber="1236541265474145",.cardExpirationDate="10/26"};
    printf("Input Data: cardData.primaryAccountNumber = 45123456789012345\n");
    printf("Expected Result:3 - ACCOUNT_NOT_FOUND \n");
    printf("Actual result: %d\n" , isValidAccount(&cardData , &acc));
    printf("------------------------------------------------------\n");


    printf("Tester Name: Shorouk Shehab\n");
    printf("Function name: isValidAccount\n");
    printf("Test Case 2: RIGHT PAN\n");
     cardData = (ST_cardData_t){.cardHolderName="Shorouk Mohsen Shehab ",.primaryAccountNumber="1234567890123452",.cardExpirationDate="10/26"};


    printf("Input Data:  cardData.primaryAccountNumber = 1234567890123456\n");
    printf("Expected Result:0 - SERVER_OK \n");
    printf("Actual result: %d\n" , isValidAccount(&cardData , &acc));
     printf("------------------------------------------------------\n");
    printf("------------------------------------------------------\n");
        printf("------------------------------------------------------\n");
            printf("------------------------------------------------------\n");




}











EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence)
{
	if (termData->transAmount > accountRefrence->balance)
	{
		return LOW_BALANCE;

	}
	else
	{
		return SERVER_OK;
	}

}

void isAmountAvailableTest(void)
{
     ST_accountsDB_t* accountRefrence;
    ST_terminalData_t termData;

    printf("------------------------------------------------------\n");
    printf("Tester Name: Shorouk Shehab\n");
    printf("Function name: isAmountAvailable\n");
    printf("Test Case 1:Low account Balance\n");
    termData = (ST_terminalData_t){ .transAmount = 500000,.maxTransAmount = 300000,.transactionDate = "30/09/2022" };
    accountRefrence = &accountsDB[1];
    printf("Input Data: accountsDB[1]\n");
    printf("Expected Result: 4 - LOW_BALANCE \n");
    printf("Actual result: %d\n" ,isAmountAvailable( &termData , accountRefrence));
    printf("------------------------------------------------------\n");

     printf("------------------------------------------------------\n");
    printf("Tester Name: Shorouk Shehab\n");
    printf("Function name: isAmountAvailable\n");
    printf("Test Case 1:Sufficent account Balance\n");
    termData = (ST_terminalData_t){ .transAmount = 1000,.maxTransAmount = 1500,.transactionDate = "30/09/2022" };
    accountRefrence = &accountsDB[2];
    printf("Input Data: accountsDB[2]\n");
    printf("Expected Result: 0 - SERVER OK\n");
    printf("Actual result: %d\n" ,isAmountAvailable( &termData , accountRefrence));
    printf("------------------------------------------------------\n");
    printf("------------------------------------------------------\n");
        printf("------------------------------------------------------\n");
            printf("------------------------------------------------------\n");

}


EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
	if (&Transaction_Data[sequence_no] == NULL)
	{
		printf("ERROR\n");
		return SAVING_FAILED;

	}


	else
	{
		transData->transactionSequenceNumber = sequence_no ;
		Transaction_Data[sequence_no].cardHolderData = transData->cardHolderData;
		Transaction_Data[sequence_no].terminalData = transData->terminalData;
		Transaction_Data[sequence_no].transactionSequenceNumber = transData->transactionSequenceNumber;
		Transaction_Data[sequence_no].transState = transData->transState;
		sequence_no++;
		return  SERVER_OK;


	}



}


void saveTransactionTest(void)
{

   ST_transaction_t transData;


      printf("------------------------------------------------------\n");
    printf("Tester Name: Shorouk Shehab\n");
    printf("Function name: saveTransaction\n");
    printf("Test Case 1:APPROVED\n");

    transData = (ST_transaction_t) { .cardHolderData = {.cardHolderName = "Shorouk Mohsen Shehab",.cardExpirationDate = "10/27",.primaryAccountNumber = "1234567890123456"}
	 ,.terminalData = {.maxTransAmount = 1500,.transactionDate = "21/8/2022",.transAmount = 350}
	 ,.transState = APPROVED
	};



    printf("Input Data: DATA\n");
    printf("Expected Result: 0 - SERVER_OK \n");
    printf("Actual result: %d\n" ,saveTransaction(&transData));
      printf("------------------------------------------------------\n");

       printf("------------------------------------------------------\n");
    printf("Tester Name: Shorouk Shehab\n");
    printf("Function name: saveTransaction\n");
    printf("Test Case 2:DECLINED_INSUFFECIENT_FUND\n");

     transData = (ST_transaction_t) { .cardHolderData = {.cardHolderName = "Shorouk Mohsen Shehab",.cardExpirationDate = "10/27",.primaryAccountNumber = "1234567890123456"}
	 ,.terminalData = {.maxTransAmount = 1500,.transactionDate = "21/8/2022",.transAmount = 350}
	 ,.transState = DECLINED_INSUFFECIENT_FUND
	};



    printf("Input Data: DATA\n");
    printf("Expected Result: 0 - SERVER_OK \n");
    printf("Actual result: %d\n" ,saveTransaction(&transData));
       printf("------------------------------------------------------\n");

    printf("------------------------------------------------------\n");
    printf("Tester Name: Shorouk Shehab\n");
    printf("Function name: saveTransaction\n");
    printf("Test Case 3:DECLINED_STOLEN_CARD\n");

     transData = (ST_transaction_t)
	{ .cardHolderData = {.cardHolderName = "Shorouk Mohsen Shehab",.cardExpirationDate = "10/27",.primaryAccountNumber = "1234567890123450"}
	 ,.terminalData = {.maxTransAmount = 1500,.transactionDate = "21/8/2022",.transAmount = 350}
	 ,.transState = DECLINED_STOLEN_CARD
	};



    printf("Input Data: DATA\n");
    printf("Expected Result: 0 - SERVER_OK \n");
    printf("Actual result: %d\n" ,saveTransaction(&transData));
    printf("------------------------------------------------------\n");
    printf("------------------------------------------------------\n");
        printf("------------------------------------------------------\n");
            printf("------------------------------------------------------\n");


}



EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence)
{
	if (accountRefrence->state == RUNNING)
	{
		return SERVER_OK;
	}
	else
	{
		return BLOCKED_ACCOUNT;
	}

}


void isBlockedAccountTest(void)
{
   ST_accountsDB_t* accountRefrence = NULL;


     printf("------------------------------------------------------\n");
    printf("Tester Name: Shorouk Shehab\n");
    printf("Function name: isBlockedAccount\n");
    printf("Test Case 1:BLOCKED ACCOUNT\n");
    accountRefrence = &accountsDB[1];
    printf("Input Data: accountsDB[2]\n");
    printf("Expected Result: 5 - BLOCKED_ACCOUNT \n");
    printf("Actual result: %d\n" ,isBlockedAccount( accountRefrence));
    printf("------------------------------------------------------\n");
    printf("------------------------------------------------------\n");
    printf("Tester Name: Shorouk Shehab\n");
    printf("Function name: isBlockedAccount\n");
    printf("Test Case 1:RUNNING ACCOUNT\n");
     accountRefrence = &accountsDB[2];
    printf("Input Data: accountsDB[3]\n");
    printf("Expected Result: 0 - SERVER_OK \n");
    printf("Actual result: %d\n" ,isBlockedAccount( accountRefrence));
       printf("------------------------------------------------------\n");
    printf("------------------------------------------------------\n");
        printf("------------------------------------------------------\n");
            printf("------------------------------------------------------\n");

}





void listSavedTransactions(void)
{

    for (int i = 0; i < 255; i++)
		{

	printf("##################################\n");
	printf("Transaction Sequence Number: %d\n", Transaction_Data[i].transactionSequenceNumber);
	printf("Transaction Date: %s\n", Transaction_Data[i].terminalData.transactionDate);
	printf("Transaction Amount: %f\n", Transaction_Data[i].terminalData.transAmount);
	printf("Transaction State: %s \n", Transaction_Data[i].transState);
	printf("Transaction MAX Amount: %d \n", Transaction_Data[i].terminalData.maxTransAmount);
	printf("CardHolder Name: %s\n", Transaction_Data[i].cardHolderData.cardHolderName);
	printf("PAN: %s\n", Transaction_Data[i].cardHolderData.primaryAccountNumber);
	printf("Card Expiration Date:%s \n ", Transaction_Data[i].cardHolderData.cardExpirationDate);
	printf("##################################\n");

		}
}



/*void listSavedTransactionsTest(void)
{

      ST_transaction_t transData;


      printf("###########################################\n");
    printf("Tester Name: Shorouk Shehab\n");
    printf("Function name: listSavedTransactions\n");
    printf("Test Case 1:BLOCKED ACCOUNT\n");
    transData = (ST_transaction_t)
	{ .cardHolderData = {.cardHolderName = "Shorouk Mohsen Shehab",.cardExpirationDate = "10/27",.primaryAccountNumber = "1234567890123456"}
	 ,.terminalData = {.maxTransAmount = 1500,.transactionDate = "21/8/2022",.transAmount = 350}
	 ,.transState = DECLINED_STOLEN_CARD
	};
    printf("Input Data: accountsDB[2]\n");
    printf("Expected Result: 5 - BLOCKED_ACCOUNT \n");
    printf("Actual result: %d\n" ,listSavedTransactions());
    printf("###########################################\n");

}*/
