#include <stdio.h>
#include "Card.h"


EN_cardError_t getCardHolderName(ST_cardData_t* cardData) {
    EN_cardError_t ReturnStatus = OK;
    printf("Please enter the name of card owner \n \
, kindly notice it must be more than 20 charcters and less than 24. \n");
    gets(cardData->cardHolderName);
    if ( (cardData->cardHolderName) == NULL || strlen(cardData->cardHolderName) > 24 || strlen(cardData->cardHolderName) < 20) {
            ReturnStatus = WRONG_NAME;
        }
   
    return ReturnStatus;
}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData) {
    EN_cardError_t ReturnStatus = OK;
    printf("Please enter the Card Expiry Date in format MM/YY as M is month and Y is year \n");
    gets(cardData->cardExpirationDate);
    //   for (uint32_t counter = 0; counter < 5; counter++) {   printf("%c", TodayDate[counter]); }
    if (strlen(cardData->cardExpirationDate) != 5 || (cardData->cardExpirationDate[2]) != '/' || (cardData->cardExpirationDate) == NULL)
    {
        ReturnStatus = WRONG_EXP_DATE;
    }
    return ReturnStatus;
}

EN_cardError_t getCardPAN(ST_cardData_t* cardData) {
    EN_cardError_t ReturnStatus = OK;
    printf("Please enter the card PAN , \n kindly notice it must be more than 16 charcters and less than 19. \n ");
    gets(cardData->primaryAccountNumber);
    if (strlen(cardData->primaryAccountNumber) > 19 || strlen(cardData->primaryAccountNumber) < 16 || (cardData->primaryAccountNumber) == NULL)
    {
        ReturnStatus =   WRONG_PAN;
    }
    return ReturnStatus;
}

