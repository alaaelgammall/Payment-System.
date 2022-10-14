#include <stdio.h>
#include "Card.h"
#include "Terminal.h"
#include "Server.h"
#include "App.h"

void appStart(void) {

	ST_cardData_t Card;
	EN_cardError_t ErrorState;
	EN_terminalError_t ErrorTerminal;
	ST_terminalData_t CardTerminal;
	EN_serverError_t ServerError;
	EN_transState_t TransState;
	EN_accountState_t AccountState;
	ST_transaction_t transData;
	transData.transactionSequenceNumber = 0;

	ErrorState = getCardHolderName(&Card);

	while (ErrorState == WRONG_NAME) {

		ErrorState = getCardHolderName(&Card);
	}

	ErrorState = getCardExpiryDate(&Card);

	while (ErrorState == WRONG_EXP_DATE) {

		ErrorState = getCardExpiryDate(&Card);
	}

	ErrorState = getCardPAN(&Card);

	while (ErrorState == WRONG_PAN) {

		ErrorState = getCardPAN(&Card);
	}


	ErrorTerminal = getTransactionDate(&CardTerminal);

	//printf("%d", ErrorTerminal);

	while (ErrorTerminal == WRONG_DATE) {
	ErrorTerminal = getTransactionDate(&CardTerminal);}


	ErrorTerminal = isCardExpired(Card, CardTerminal);


	if (ErrorTerminal == EXPIRED_CARD) {
			printf("\nEXPIRED_CARD\n");
			return;
		} 

	ErrorTerminal = setMaxAmount(&CardTerminal);
	while (ErrorTerminal == INVALID_MAX_AMOUNT) {
		ErrorTerminal = setMaxAmount(&CardTerminal);
	}


	ErrorTerminal = getTransactionAmount(&CardTerminal);
	while (ErrorTerminal == INVALID_AMOUNT) {
		ErrorTerminal = getTransactionAmount(&CardTerminal);
	}



	ErrorTerminal = isBelowMaxAmount(&CardTerminal);

	if (ErrorTerminal == EXCEED_MAX_AMOUNT)
	{
		printf("\DECLINED EXCEED_MAX_AMOUNT\n");
		return;
	}


	// PrintCard(&Card);
	// PrintTerminal(&CardTerminal);

	transData.cardHolderData = Card;

	transData.terminalData = CardTerminal;


   // PrintCard(&transData.cardHolderData);
   //PrintTerminal(&transData.terminalData);
   //printf("%s", transData.cardHolderData.primaryAccountNumber);

	TransState = recieveTransactionData(&transData);

	// printf("TranS %d", TransState);

	//  saves any type of transaction,
	// APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, FRAUD_CARD, INTERNAL_SERVER_ERROR.

	if (TransState == APPROVED) {
		printf("\nAPPROVED\n");
	}
	else if (TransState == DECLINED_INSUFFECIENT_FUND) {
		printf("\nDECLINED_INSUFFECIENT_FUND\n");

	}
	else if (TransState == DECLINED_STOLEN_CARD) {
		printf("\nDECLINED STOLEN CARD\n");

	}
	else if (TransState == FRAUD_CARD) {
		printf("\nFRAUD_CARD\n");
	}
	else if (TransState == INTERNAL_SERVER_ERROR) {
		printf("\nINTERNAL_SERVER_ERROR\n");
	}
	printf("\nSAVING TRANSACTION\n");

	listSavedTransactions();

	//printf("al");
}