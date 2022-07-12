#include "app.h"

void appStart(void) {
	while (1) {
		while (getCardHolderName(&x.cardHolderData)==WRONG_NAME) {
			printf("Please Enter The Name In Correct Format\n");
		}
		while (getCardExpiryDate(&x.cardHolderData) == WRONG_EXP_DATE) {
			printf("Please Enter The Expiration Date In Correct Format\n");
		}
		while (getCardPAN(&x.cardHolderData) == WRONG_PAN) {
			printf("Please Enter The Card Pan In Correct Format\n");
		}
		getTransactionDate(&x.terminalData);
		if (isCardExpired(x.cardHolderData, x.terminalData) == EXPIRED_CARD) {
			printf("Declined Expeired Card\n Press Any Button To Restart"); getch(); system("cls"); continue;
		}
		while (getTransactionAmount(&x.terminalData) == INVALID_AMOUNT) {
			printf("Please Enter The Valid Amount Of Transation\n");
		}
		while (setMaxAmount(&x.terminalData) == INVALID_MAX_AMOUNT) {
			printf("Please Enter The Valid Max Amount Of Transation\n");
		}
		if (isBelowMaxAmount(&x.terminalData) == EXCEED_MAX_AMOUNT) {
			printf("Eceeded Max Amount\n");
			printf("Press Any Button To Restart"); getch(); system("cls"); continue;
		}
		EN_transState_t z = recieveTransactionData(&x);
		if (z == INTERNAL_SERVER_ERROR) {
			printf("the transaction isn't saved\n");
		}
		else if (z == APPROVED) {
			printf("the Transaction is saved and approved\n");
		}
		else if (z == DECLINED_INSUFFECIENT_FUND) {
			printf("Declined Insuffecient Funds\n Press Any Button To Restart"); getch(); system("cls"); continue;
		}
		else if(z== DECLINED_STOLEN_CARD) {
			printf("Declined Invalid Account\n Press Any Button To Restart"); getch(); system("cls"); continue;
		}
		printf("Press Any Button To Restart"); getch(); system("cls");
	}
}