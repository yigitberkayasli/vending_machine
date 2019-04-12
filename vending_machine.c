#include <stdlib.h>
#include <stdio.h>
#define LF 10 /* ASCII code for LINE FEED character */

void DisplayErrorMessage(int insufficientStock, int invalidSelection, int insufficientMoney, int insufficientCoins, int wrongPincode)
{
	printf("Error! ");
	if (insufficientStock) printf("You selected an item that machine doesnt have!");
	if (invalidSelection) printf("Invalid selection!");
	if (insufficientMoney) printf("Insufficient amount of money! Take your money back!");
	if (insufficientCoins) printf("Machine doesnt have enough coins to make return change! Take your money back!");
	if (wrongPincode) printf("Wrong Pincode!");
	printf("\n");
	system("pause");
	printf("\n");
}

void Maintenance(int numOfStocks[9], int numOfCoins[5], double netIncome)
{
	while (1)
	{
		char ch;
		int counter = 1;
		int reset_loop = 0;
		printf("Enter pincode: ");
		scanf(" %c", &ch);
		while (ch != LF)
		{
			if (counter == 1)
			{
				if (ch != '1') reset_loop = 1;
			}
			if (counter == 2)
			{
				if (ch != '2') reset_loop = 1;
			}
			if (counter == 3)
			{
				if (ch != '3') reset_loop = 1;
			}
			if (counter == 4)
			{
				if (ch != '4') reset_loop = 1;
			}
			counter++;
			scanf("%c", &ch);
		}
		if (counter != 5) reset_loop = 1;
		if (reset_loop)
		{
			DisplayErrorMessage(0, 0, 0, 0, 1);
			continue;
		}
		break;
	}
	
	system("cls");
	printf("DAILY REPORT\n");
	printf("\nNumber of items left:\n");
	printf("1.Water: %d\n", numOfStocks[0]);
	printf("2.Coke: %d\n", numOfStocks[1]);
	printf("3.Diet Coke: %d\n", numOfStocks[2]);
	printf("4.Iced Tea: %d\n", numOfStocks[3]);
	printf("5.Swiss Chocolate: %d\n", numOfStocks[4]);
	printf("6.Candy: %d\n", numOfStocks[5]);
	printf("7.Chips: %d\n", numOfStocks[6]);
	printf("8.Bubble Gum: %d\n", numOfStocks[7]);
	printf("9.Turkish Delight: %d\n", numOfStocks[8]);
	
	printf("\nNumber of coins left:\n");
	printf("1 TL: %d left\n", numOfCoins[0]);
	printf("0.5 TL: %d left\n", numOfCoins[1]);
	printf("0.25 TL: %d left\n", numOfCoins[2]);
	printf("0.10 TL: %d left\n", numOfCoins[3]);
	printf("0.05 TL: %d left\n", numOfCoins[4]);
	
	printf("\nNet income: %.2lf TL\n", netIncome);
	
	int i;
	for (i = 0; i < 9; i++)
		numOfStocks[i] = 10;
	for (i = 0; i < 5; i++)
		numOfCoins[i] = 10;
	
	printf("All items in the vending machine are restocked\n\n");
	
	system("pause");
	
}

int CalculateReqCoins(double value, int numOfCoinsReq[5])
{	
	if (numOfCoinsReq[0] == 0 && numOfCoinsReq[1] == 0 && numOfCoinsReq[2] == 0 && numOfCoinsReq[3] == 0 && numOfCoinsReq[4] == 0)
	{
		numOfCoinsReq[0] = value / 1.0;
		value -= numOfCoinsReq[0] * 1.0;
		numOfCoinsReq[1] = value / 0.5;
		value -= numOfCoinsReq[1] * 0.5;
		numOfCoinsReq[2] = value / 0.25;
		value -= numOfCoinsReq[2] * 0.25;
		numOfCoinsReq[3] = value / 0.10;
		value -= numOfCoinsReq[3] * 0.10;
		numOfCoinsReq[4] = value / 0.05;
		value -= numOfCoinsReq[4] * 0.05;
	}
	else if (numOfCoinsReq[1] == 0 && numOfCoinsReq[2] == 0 && numOfCoinsReq[3] == 0 && numOfCoinsReq[4] == 0)
	{
		numOfCoinsReq[1] = value / 0.5;
		value -= numOfCoinsReq[1] * 0.5;
		numOfCoinsReq[2] = value / 0.25;
		value -= numOfCoinsReq[2] * 0.25;
		numOfCoinsReq[3] = value / 0.10;
		value -= numOfCoinsReq[3] * 0.10;
		numOfCoinsReq[4] = value / 0.05;
		value -= numOfCoinsReq[4] * 0.05;
	}
	else if (numOfCoinsReq[2] == 0 && numOfCoinsReq[3] == 0 && numOfCoinsReq[4] == 0)
	{
		numOfCoinsReq[2] = value / 0.25;
		value -= numOfCoinsReq[2] * 0.25;
		numOfCoinsReq[3] = value / 0.10;
		value -= numOfCoinsReq[3] * 0.10;
		numOfCoinsReq[4] = value / 0.05;
		value -= numOfCoinsReq[4] * 0.05;
	}
	else if (numOfCoinsReq[3] == 0 && numOfCoinsReq[4] == 0)
	{
		numOfCoinsReq[3] = value / 0.10;
		value -= numOfCoinsReq[3] * 0.10;
		numOfCoinsReq[4] = value / 0.05;
		value -= numOfCoinsReq[4] * 0.05;
	}
	else if (numOfCoinsReq[4] == 0)
	{
		numOfCoinsReq[4] = value / 0.05;
		value -= numOfCoinsReq[4] * 0.05;
	}	

	if (value > 0.001) return 1;
	else return 0;

}

int ReturnChange(double *deposit, int numOfCoins[5])
{	
	int numOfCoinsReq[5] = {0, 0, 0, 0, 0};
	int insufficientCoins[4] = {0, 0, 0, 0};
	int errorCode = CalculateReqCoins(*deposit, numOfCoinsReq);	
	if (errorCode) return errorCode;
	
	double change = *deposit;
	
	if (numOfCoins[0] < numOfCoinsReq[0])
	{
		insufficientCoins[0] = 1;
		*deposit -= numOfCoins[0] * 1.0;
		numOfCoinsReq[0] = numOfCoins[0];
		if (numOfCoinsReq[0] == 0) numOfCoinsReq[0] = -1;
		numOfCoinsReq[1] = 0; numOfCoinsReq[2] = 0; numOfCoinsReq[3] = 0; numOfCoinsReq[4] = 0;
		errorCode = CalculateReqCoins(*deposit, numOfCoinsReq);
		if (errorCode) return errorCode;
	}
	if (numOfCoins[1] < numOfCoinsReq[1])
	{
		insufficientCoins[1] = 1;
		*deposit -= numOfCoins[1] * 0.5;
		numOfCoinsReq[1] = numOfCoins[1];
		if (numOfCoinsReq[1] == 0) numOfCoinsReq[1] = -1;
		numOfCoinsReq[2] = 0; numOfCoinsReq[3] = 0; numOfCoinsReq[4] = 0;
		errorCode = CalculateReqCoins(*deposit, numOfCoinsReq);
		if (errorCode) return errorCode;
	}
	if (numOfCoins[2] < numOfCoinsReq[2])
	{
		insufficientCoins[2] = 1;
		*deposit -= numOfCoins[2] * 0.25;
		numOfCoinsReq[2] = numOfCoins[2];
		if (numOfCoinsReq[2] == 0) numOfCoinsReq[2] = -1;
		numOfCoinsReq[3] = 0; numOfCoinsReq[4] = 0;
		errorCode = CalculateReqCoins(*deposit, numOfCoinsReq);
		if (errorCode) return errorCode;
	}
	if (numOfCoins[3] < numOfCoinsReq[3])
	{
		insufficientCoins[3] = 1;
		*deposit -= numOfCoins[3] * 0.10;
		numOfCoinsReq[3] = numOfCoins[3];
		if (numOfCoinsReq[3] == 0) numOfCoinsReq[3] = -1;
		numOfCoinsReq[4] = 0;
		errorCode = CalculateReqCoins(*deposit, numOfCoinsReq);
		if (errorCode) return errorCode;
	}
	if (numOfCoins[4] < numOfCoinsReq[4])
	{
		return 1;
	}
	
	printf("Get your item! ");
	if (insufficientCoins[0] || insufficientCoins[1] || insufficientCoins[2] || insufficientCoins[3])
	{
		printf("Machine doesnt have enough");
		if (insufficientCoins[0]) printf(" 1 TLs");
		if (insufficientCoins[1]) printf(" 0.5 TLs");
		if (insufficientCoins[2]) printf(" 0.25 TLs");
		if (insufficientCoins[3]) printf(" 0.10 TLs");
		printf("!\n");
		if (insufficientCoins[0])
		{
			printf("%d 0.5 TLs ", numOfCoinsReq[1]);
			if (insufficientCoins[1])
			{
				printf("%d 0.25 TLs ", numOfCoinsReq[2]);
				if (insufficientCoins[2])
				{
					printf("%d 0.10 TLs ", numOfCoinsReq[3]);
					if (insufficientCoins[3]) printf("%d 0.05 TLs ", numOfCoinsReq[4]);
				}
			}
		}
		else if (insufficientCoins[1])
		{
			printf("%d 0.25 TLs ", numOfCoinsReq[2]);
			if (insufficientCoins[2])
			{
				printf("%d 0.10 TLs ", numOfCoinsReq[3]);
				if (insufficientCoins[3]) printf("%d 0.05 TLs ", numOfCoinsReq[4]);
			}
		}
		else if (insufficientCoins[2])
		{
			printf("%d 0.10 TLs ", numOfCoinsReq[3]);
			if (insufficientCoins[3]) printf("%d 0.05 TLs ", numOfCoinsReq[4]);
		} else if (insufficientCoins[3]) printf("%d 0.05 TLs ", numOfCoinsReq[4]);
		else printf("%d 0.10 TLs ", numOfCoinsReq[3]);
		printf("are used!\n");
	}
	
	printf("Change: %.2lf TL\n", change);
	numOfCoins[0] -= numOfCoinsReq[0]; numOfCoins[1] -= numOfCoinsReq[1]; numOfCoins[2] -= numOfCoinsReq[2]; numOfCoins[3] -= numOfCoinsReq[3]; numOfCoins[4] -= numOfCoinsReq[4];
	
	return 0;
}

int MakeSelection(double *deposit, int *selection, int numOfStocks[9], double *income)
{
	while (1)
	{
		printf("Enter the deposit: ");
		scanf("%lf", deposit);
	
		if (*deposit < -0.9999 && *deposit > -1.0001)
			return 1;
		else if (*deposit < 0.01)
		{
			DisplayErrorMessage(0, 1, 0, 0, 0);
			continue;
		}
	
		double value;
		while (1)
		{
			printf("What do you want? ");
			scanf("%d", selection);
			
			if (*selection == 1) value = 1.00;
			else if (*selection == 2) value = 1.20;
			else if (*selection == 3) value = 1.20;
			else if (*selection == 4) value = 1.00;
			else if (*selection == 5) value = 1.50;
			else if (*selection == 6) value = 0.95;
			else if (*selection == 7) value = 2.50;
			else if (*selection == 8) value = 1.50;
			else if (*selection == 9) value = 2.00;
			else 
			{
				DisplayErrorMessage(0, 1, 0, 0, 0);
				continue;
			}
		
			if (!(numOfStocks[*selection - 1]))
			{
				DisplayErrorMessage(1, 0, 0, 0, 0);
				continue;
			}
		
			break;
		}
	
		*income = value;
		*deposit -= value;
	
		break;
	}
	
	return 0;
}

void ShowMenu(int numOfStocks[9])
{
	system("cls");
	
	printf("1.Water            ");
	if (numOfStocks[0]) printf("1.00 TL\n");
	else printf("not available\n");
	printf("2.Coke             ");
	if (numOfStocks[1]) printf("1.20 TL\n");
	else printf("not available\n");
	printf("3.Diet Coke        ");
	if (numOfStocks[2]) printf("1.20 TL\n");
	else printf("not available\n");
	printf("4.Iced Tea         ");
	if (numOfStocks[3]) printf("1.00 TL\n");
	else printf("not available\n");
	printf("5.Swiss Chocolate  ");
	if (numOfStocks[4]) printf("1.50 TL\n");
	else printf("not available\n");
	printf("6.Candy            ");
	if (numOfStocks[5]) printf("0.95 TL\n");
	else printf("not available\n");
	printf("7.Chips            ");
	if (numOfStocks[6]) printf("2.50 TL\n");
	else printf("not available\n");
	printf("8.Bubble Gum       ");
	if (numOfStocks[7]) printf("1.50 TL\n");
	else printf("not available\n");
	printf("9.Turkish Delight  ");
	if (numOfStocks[8]) printf("2.00 TL\n");
	else printf("not available\n");
	
	printf("\n");
	
}

int main()
{
	int numOfStocks[9] = {10, 10, 10, 10, 10, 10, 10, 10, 10};
	int numOfCoins[5] = {10, 10, 10, 10, 10};
	double income = 0.0;
	
	while (1)
	{	
		ShowMenu(numOfStocks);
	
		double deposit, temp_income;
		int selection;
	
		int goToMaintance = MakeSelection(&deposit, &selection, numOfStocks, &temp_income);
		if (goToMaintance)
		{
			Maintenance(numOfStocks, numOfCoins, income);
			continue;
		}
		
		if (deposit < 0.0)
		{
			DisplayErrorMessage(0, 0, 1, 0, 0);
			continue;
		}
		
		int errorCode =	ReturnChange(&deposit, numOfCoins);
	
		if (errorCode) DisplayErrorMessage(0, 0, 0, 1, 0);
		else
		{
			numOfStocks[selection - 1] -= 1;
			income += temp_income;
			system("pause");
		}
	}
	
	return 0;
}
