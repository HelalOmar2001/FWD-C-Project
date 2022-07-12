#include"card.h"


EN_cardError_t getCardHolderName(ST_cardData_t* cardData) {
	printf("Enter The Card Holder Name: ");
	scanf("%s",cardData->cardHolderName);
	printf("\n");
	if (strlen(cardData->cardHolderName) >= 20 && strlen(cardData->cardHolderName) <= 24) {
		for (uint8_t i = 0; i < strlen(cardData->cardHolderName); i++) {
			if (cardData->cardHolderName[i] >= '0' && cardData->cardHolderName[i]<='9')
				return WRONG_NAME;
		}
		return OK;
	}
	return WRONG_NAME;
}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData){
	printf("Enter The Card Expiration Date: ");
	scanf("%s", cardData->cardExpirationDate);
	printf("\n");
	if (strlen(cardData->cardExpirationDate) == 5 && cardData->cardExpirationDate[2]=='/') {
		uint8_t* expiryDate =  cardData->cardExpirationDate ;
		if ((expiryDate[0] == '1' && expiryDate[1] >= '0' && expiryDate[1] <= '2') || (expiryDate[0] == '0' && expiryDate[1] >= '0' && expiryDate[1] <= '9')) {
			if (expiryDate[3] >= '0' && expiryDate[3] <= '9' && expiryDate[4] >= '0' && expiryDate[4] <= '9')
				return OK;
		}
	}
	return WRONG_EXP_DATE;
}


EN_cardError_t getCardPAN(ST_cardData_t* cardData) {
	printf("Enter The Card PAN: ");
	scanf("%s", cardData->primaryAccountNumber);
	printf("\n");
	if (strlen(cardData->primaryAccountNumber) >= 16 && strlen(cardData->primaryAccountNumber) <= 19) {
		for (uint8_t i = 0; i < strlen(cardData->primaryAccountNumber); i++) {
			if (cardData->primaryAccountNumber[i] < '0' || cardData->primaryAccountNumber[i]>'9')
				return WRONG_PAN;
		}
		return OK;
	}
	return WRONG_PAN;
}