#include <stdio.h>
#include "Card.h"
#include "Terminal.h"
#include "Server.h"
#include "App.h" 


// TODO the databases should be protected by semaphore
ST_accountsDB_t accountsDB[255] = {
		{2000.0, RUNNING,  "8989374615436851"} ,  {100000.0, BLOCKED,"5807007076043875"} ,
		{20030.0, RUNNING, "2697057586256566"} , {109000.0, BLOCKED,"0672577074517618306"} ,
		{9808.0, RUNNING,  "4977794668070395610"} ,  {1019320.0,BLOCKED,"41114616345778682"} ,
		{20030.0, RUNNING, "380712061045635700"} , {14200.0, BLOCKED, "8503465564247080912"} ,
		{2670.0, RUNNING,  "998866559829660433"} ,  {1230.0, BLOCKED,  "82677167672895627"} ,
};

ST_transaction_t transDB[255] = { 0 };

int main() {
	appStart();

}