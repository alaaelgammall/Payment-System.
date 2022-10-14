#include <stdio.h>
#include <string.h>
#include "Card.h"
#include "Terminal.h"
#include "Server.h"
#include "App.h"

#define CODE_TRACE_ON
#ifdef CODE_TRACE_ON
#define CODE_TRACE(str) printf(str)
#define CODE_TRACE_ARG(str, ...) printf(str,__VA_ARGS__)
#else
#define CODE_TRACE(str)
#define CODE_TRACE_ARG(str) 
#endif

extern uint8_t AccountNumber = 0;

extern ST_accountsDB_t accountsDB[255];

extern ST_transaction_t transDB[255];


void PrintCard(ST_cardData_t* Card) {

	
		printf ("cardHolderName %s\n" , Card->cardHolderName );
		printf("cardExpirationDate %s\n", Card->cardExpirationDate);
		printf("primaryAccountNumber%s\n" ,Card->primaryAccountNumber);
	
}

void PrintTerminal(ST_terminalData_t* term) {

	printf ("transAmount %f\n", term->transAmount);
	printf("maxTransAmount %f\n", term->maxTransAmount);
	printf("transactionDate %s\n", term-> transactionDate);

}

EN_serverError_t isValidAccount(ST_cardData_t* cardData) {
	EN_serverError_t  ReturnnStatus = ACCOUNT_NOT_FOUND;
	for (int counter = 0; counter < (sizeof(accountsDB) / sizeof(ST_accountsDB_t)); counter++) {
		if ( ! strcmp( (cardData->primaryAccountNumber) , (accountsDB[counter].primaryAccountNumber) ) ){
			AccountNumber = counter;
			ReturnnStatus = SERVER_OK;
		}
	}
	return ReturnnStatus;
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence) {
	EN_serverError_t  ReturnnStatus = SERVER_OK;
		if ((accountRefrence->state) == BLOCKED ) {
			ReturnnStatus = BLOCKED_ACCOUNT;
		}
	return ReturnnStatus;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence) {
	EN_serverError_t ReturnnStatus = SERVER_OK;
	// printf(" %f \n", (accountRefrence->balance));
	// printf("%f \n", (termData->transAmount));
	if ( (accountRefrence->balance) < (termData->transAmount)) {
	ReturnnStatus = LOW_BALANCE;
	}
	return ReturnnStatus;
}
 
//---------------------------------------------------------------------------// 
//! \brief     This function will take all transaction data and validate its data.\
//!            It checks the account detailsand amount availability.
//!
//! \param[in]  transData : contains the needed informations that i need to validate before approving the trans
//!
//! \return     the status of trans
//!
EN_transState_t recieveTransactionData(ST_transaction_t* transData) {
	EN_transState_t ReturnStatus = APPROVED;
	// step 1 verify the card holder data 
	//printf("%s", transData->cardHolderData.primaryAccountNumber);
	//printf("%s", accountsDB[0].primaryAccountNumber);
//	CODE_TRACE("Alaa");
	if (isValidAccount(&(transData->cardHolderData)) == ACCOUNT_NOT_FOUND) {
		transData->transState = FRAUD_CARD;
		ReturnStatus= FRAUD_CARD;
	}
	else {
		 if (isBlockedAccount(&(accountsDB[AccountNumber])) == BLOCKED_ACCOUNT) {
			transData->transState = DECLINED_STOLEN_CARD;
			ReturnStatus = DECLINED_STOLEN_CARD;
		}
		 else {
			 if (isAmountAvailable((&transData->terminalData), &accountsDB[AccountNumber]) == LOW_BALANCE) {
				 transData->transState = DECLINED_INSUFFECIENT_FUND;
				 ReturnStatus = DECLINED_INSUFFECIENT_FUND;
			 }
			 else {
				 //update  balance if approved

				 transData->transState = APPROVED;
				accountsDB[AccountNumber].balance -= (transData->terminalData).transAmount;
				printf("Your new balance is : %f", accountsDB[AccountNumber].balance);
			 }

		 }
	}
	// step 2 amount and chek ammount not larger than max w avialable in balace ely f st-transc

	if (saveTransaction(transData) == SAVING_FAILED) {
		ReturnStatus = INTERNAL_SERVER_ERROR;
	}

	return ReturnStatus;
	
	// step 3 call save tran


	/* ST_transaction_t :
	ST_cardData_t cardHolderData;
	ST_terminalData_t terminalData;
	EN_transState_t transState;
	uint32_t transactionSequenceNumber; */


}

static uint8_t indexLastTrans = 0;

EN_serverError_t saveTransaction(ST_transaction_t* transData) {
	
		transData->transactionSequenceNumber++;
		transDB[indexLastTrans++] = *(transData);
		return SERVER_OK;
	
}
char* getTransStateS(EN_transState_t transState) {
	char* ReturnStatus;
	switch ( transState )
	{ 
	case APPROVED : 
		ReturnStatus = "APPROVED";
		break;
	case DECLINED_INSUFFECIENT_FUND:
		ReturnStatus = "DECLINED_INSUFFECIENT_FUND"; 
		break;
	case DECLINED_STOLEN_CARD:
		ReturnStatus = "DECLINED_STOLEN_CARD";
			break;
	case FRAUD_CARD :
		ReturnStatus = "FRAUD_CARD";
		break;
	case INTERNAL_SERVER_ERROR:
		ReturnStatus = "INTERNAL_SERVER_ERROR";
		break;
	default:
		ReturnStatus = "";
		break;
	}
}

void listSavedTransactions(void) {
	for (uint8_t counter = 0; counter < sizeof(transDB) / sizeof(ST_transaction_t); counter++) {
		char* transStateS = getTransStateS(transDB[counter].transState);
		printf("############################\nTransaction Sequence Number : %d\nTransaction Date : %s\nTransaction Amount : % f\nTransaction State : % s\nTerminal Max Amount : % f\nCardholder Name : % s\nPAN : % s\nCard Expiration Date : % s\n############################ \n",
			transDB[counter].transactionSequenceNumber, (transDB[counter].terminalData).transactionDate, \
			(transDB[counter].terminalData).transAmount, transStateS, \
			(transDB[counter].terminalData).maxTransAmount, (transDB[counter].cardHolderData).cardHolderName, \
			(transDB[counter].cardHolderData).primaryAccountNumber, (transDB[counter].cardHolderData).cardExpirationDate);
	}
	/*
			Transaction Date : ST_transaction_t->TERMINAL
			Transaction Amount : ST_transaction_t->TERMINAL
			Transaction State : ST_transaction_t
			Terminal Max Amount : ST_terminalData_t
			Cardholder Name : ST_transaction_t
			PAN: ST_cardData_t
			Card Expiration Date : ST_cardData_t

	*/
}