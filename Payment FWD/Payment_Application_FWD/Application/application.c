#include "application.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>



void appStart(void)
{
    ST_cardData_t card_data;
    ST_terminalData_t term_data;
    ST_accountsDB_t account;
    ST_transaction_t trans;
    float max_amount;




	getCardHolderName(&card_data);
	getCardExpiryDate(&card_data);
	getCardPAN(&card_data);

	getTransactionDate(&term_data);
	isCardExpired(&card_data , &term_data);

	//saving Card Data Into Transaction Data
	trans.cardHolderData = card_data;

	term_data.maxTransAmount = 20000.0;


	if (isCardExpired(&card_data, &term_data) == EXPIRED_CARD)
	{
		printf("DECLINED EXPIRED CARD\n ");

	}

	else
	{
		getTransactionAmount(&term_data);

		if (isBelowMaxAmount(&term_data)== EXCEED_MAX_AMOUNT)
		{
			printf("Declined Amount Exceeding Limit\n");
		}
		else
		{

			// Saving Terminal Data Into Transaction Data
			trans.terminalData = term_data;
			switch(recieveTransactionData(&trans))
			{

			case APPROVED:
				printf("Transaction Approved\n");
				break;
			case DECLINED_INSUFFECIENT_FUND:
				printf(" DECLINED\tInsufficient Fund\n");
				break;
			case DECLINED_STOLEN_CARD:
				printf(" DECLINED\tStolen Card\n");
				break;
			case FRAUD_CARD:
				printf(" DECLINED\tFraud Card\n");
				break;
			case INTERNAL_SERVER_ERROR:
				printf("Internal server error\n");
				break;
			}

		}

	}
	}






