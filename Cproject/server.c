#include"server.h"

ST_accountsDB_t validAccounts[255] = { {200000,"1234567891234567890"},{25,"1234567891234567891"} };
ST_transaction_t serverTransaction[255] = { [0] .transactionSequenceNumber = 1 , [1].transactionSequenceNumber=5, [2].transactionSequenceNumber=2};
uint16_t transactionNumbers = 3;

EN_transState_t recieveTransactionData(ST_transaction_t* transData) {
	if (isValidAccount(&transData->cardHolderData) == tOK) {
		if (saveTransaction(transData) == SAVING_FAILED) {
			return transData->transState = INTERNAL_SERVER_ERROR;
		}
		else if (isAmountAvailable(transData) == tOK) {
			for (int j = 0; j < 255; j++) {
				if (strcmp(validAccounts[j].primaryAccountNumber , transData->cardHolderData.primaryAccountNumber)==0) {
					validAccounts[j].balance -= transData->terminalData.transAmount; break;
				}
			}
			return serverTransaction[transactionNumbers == 0 ? 0 : transactionNumbers - 1].transState = transData->transState = APPROVED;
		}
		else return serverTransaction[transactionNumbers == 0 ? 0 : transactionNumbers - 1].transState = transData->transState = DECLINED_INSUFFECIENT_FUND;
	}
	return transData->transState = DECLINED_STOLEN_CARD;
}


EN_serverError_t isValidAccount(ST_cardData_t* cardData) {
	for (int i = 0; i < 255; i++)
	{
		if (strcmp(cardData->primaryAccountNumber , validAccounts[i].primaryAccountNumber)==0) {
			return tOK;
		}
	}
	return DECLINED_STOLEN_CARD;
}


EN_serverError_t isAmountAvailable(ST_transaction_t* transData) {
	for (int i = 0; i < 255; i++) {
		if (strcmp(validAccounts[i].primaryAccountNumber , transData->cardHolderData.primaryAccountNumber)==0) {
			if (validAccounts[i].balance < transData->terminalData.transAmount) {
				return LOW_BALANCE;
			}
			else return tOK;
		}
	}
}


EN_serverError_t saveTransaction(ST_transaction_t* transData) {
	if (transactionNumbers == 255)return SAVING_FAILED;
	serverTransaction[transactionNumbers++] = *transData;
	return tOK;
}


EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t* transData) {
	for (int i = 0; i < transactionNumbers; i++)
	{
		if (serverTransaction[i].transactionSequenceNumber == transactionSequenceNumber) {
			transData = &serverTransaction[i];
			return tOK;
		}
	}
	return TRANSACTION_NOT_FOUND;
}