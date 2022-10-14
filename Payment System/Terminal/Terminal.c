#include <stdio.h>
#include <string.h>
#include "Card.h"
#include "Terminal.h"



EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) {
	printf("Please enter today's Date in format DD/MM/YYYY as D is day, M is month and Y is year \n");
    EN_terminalError_t ReturnState = WRONG_DATE;
    char Buffer[11] = {0};
  //  printf("%s", Buffer);
#pragma warning(suppress : 4996)
    scanf("%s" , Buffer);
 //   printf("%s", Buffer);
   // termData->transactionDate
   if (Buffer != NULL ) {
       //  printf("bB1");
        if (strlen(Buffer) == 10) {
          //  printf("bB2");
            if ((Buffer[2] == '/' ) && (Buffer[5] == '/')) {
              //  printf("bB3");
#pragma warning(suppress : 4996)
                strcpy (termData->transactionDate , Buffer) ;
              //  printf("bB4");
                ReturnState = Ok;
            }
       }
    }
    return ReturnState; 
 /*  if (strlen(termData->transactionDate) != 10 || (termData->transactionDate[2]) != '/' || (termData->transactionDate[5]) != '/' || (termData->transactionDate) == NULL)
    {
        return WRONG_DATE;
    }
    else
    {
        return Ok;
    } */
}
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData) {
    EN_terminalError_t ReturnStatus = Ok ;

    uint8_t TempCurrentArray[5];

    for (uint8_t counter = 0; counter < 2; counter++) {
        TempCurrentArray[counter] = (termData.transactionDate[counter + 3]);
    }

 /*  for (uint8_t counter = 0; counter < 2; counter++) {
        printf("%c", TempCurrentArray[counter]);
    } */ 

    for (uint8_t counter = 3; counter < 5; counter++) {
        TempCurrentArray[counter] = (termData.transactionDate[counter + 5]);
    }

    /*
    for (uint8_t counter = 3; counter < 5; counter++) {
        printf("%c", TempCurrentArray[counter]);
    }*/

    uint8_t TempExpDate[6];

    for (uint8_t counter = 0; counter < 5; counter++) {
        TempExpDate[counter] = (cardData.cardExpirationDate[counter]);
    }
/*
    for (uint8_t counter = 0; counter < 5; counter++) {
        printf("%c", TempExpDate[counter]);
    }
*/
    uint8_t Monthcurrent[3];
    Monthcurrent[0] = TempCurrentArray[0];
    Monthcurrent[1] = TempCurrentArray[1];

    Monthcurrent[2] = '\0';

 //   printf("%s \n", Monthcurrent);
/*  for (uint8_t counter = 0; counter < 2; counter++) {
        printf("%c", Monthcurrent[counter]);
    }
*/
    uint8_t Yearcurrent[3];
    Yearcurrent[0] = TempCurrentArray[3];
    Yearcurrent[1] = TempCurrentArray[4];
    Yearcurrent[2] = '\0';
  //  printf("%s \n", Yearcurrent);
 /* for (uint8_t counter = 0; counter < 2; counter++) {
        printf("%c", Yearcurrent[counter]);
    } 
 */
    uint8_t Monthexp[3];
    Monthexp[0] = TempExpDate[0];
    Monthexp[1] = TempExpDate[1];
    Monthexp[2] = '\0';

 //   printf("%s \n", Monthexp);
 /*  for (uint8_t counter = 0; counter < 2; counter++) {
        printf("%c", Monthexp[counter]);
    }
 */   
    uint8_t Yearexp[3];
    Yearexp[0] = TempExpDate[3];
    Yearexp[1] = TempExpDate[4];
    Yearexp[2] =  '\0' ;
  /*for (uint8_t counter = 0; counter < 2; counter++) {
        printf("%c", Yearexp[counter]);
    }
*/
//    printf("%s \n", Yearexp);
    int result = strcmp(Yearexp , Yearcurrent ); 
 //  printf("%d \n", result);

    int resultcomp = strcmp(Monthexp, Monthcurrent);
  //  printf("%d \n", resultcomp);

    if (result < 0) {
     //   printf("a");
        ReturnStatus = EXPIRED_CARD;
    }
    else if (result > 0) {
     //   printf("aa");
        ReturnStatus = Ok;
    }
    else if (result == 0) {
      //  printf("po");
        if (resultcomp<0) {
         //   printf("c");
            ReturnStatus = EXPIRED_CARD;
        }
        else if (resultcomp > 0) {
         //   printf("d");
            ReturnStatus = Ok;
        }
        else if (resultcomp == 0) {
        //    printf("k");
            ReturnStatus = Ok; ;
        }
    }
    return ReturnStatus;
}

EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData) {}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData) {
    EN_terminalError_t ReturnStatus = Ok;
    printf("please enter the transaction amount.");
#pragma warning(suppress : 4996)
    scanf("%f", &termData->transAmount);
    if ((termData->transAmount) == 0 || (termData->transAmount) < 0)
    {
        ReturnStatus = INVALID_AMOUNT;
    }
    return ReturnStatus;
}

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData) {
    EN_terminalError_t ReturnStatus = Ok;
    printf("please enter the maximum amount.");
#pragma warning(suppress : 4996)
    scanf("%f", &termData->maxTransAmount);
    if ((termData->maxTransAmount) == 0 || (termData->maxTransAmount) < 0)
    {
        ReturnStatus= INVALID_MAX_AMOUNT;
    }

    return ReturnStatus;
}

EN_terminalError_t isBelowMaxAmount (ST_terminalData_t* termData) {
    EN_terminalError_t ReturnStatus = Ok;
    if ((termData->transAmount) > (termData->maxTransAmount))   {
   //  printf("BelowERROR2");
        ReturnStatus = EXCEED_MAX_AMOUNT;
    }
   
    return ReturnStatus;
}


