#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#define PERSONAL_ALLOWANCE 4000.0
#define RATE_HEALTH_INSURANCE 0.01
#define RATE_PENSION 0.05
#define RATE_DEPENDANT 1600
struct employee
{
	char code[21];
	char name[51];
	float income, allowance, pension, healthInsurance, dependants, charity, deduction, taxable, tax, netIncome;
};
void get_code(int i, struct employee a[], int *exit, int count);
void get_name(int i, struct employee a[]);
float get_income();
float pension_calculating(float income);
float health_insurance_calculating(float income);
float dependant_allowance_calculating(float income);
float charity_input(float income);
float deduction_calculating(float pension, float healthInsurance, float dependant, float charity);
float taxable_income_calculating(float income, float deduction);
float tax_calculating(float income, float taxable);
float net_income_calculating(float income, float tax);
void displayMenu();
void display(int k, struct employee a[]);
void swapStruct(struct employee b[],int i,int k);
void bubbleSort(struct employee a[], int j);
void structDel(struct employee a[],int j, int del);
main()
{
	float income, deduction, taxable, tax, netIncome, pension, healthInsurance, dependant, charity;
	char startAgain;
	float option;
	int i=0;
	int j, optionInt, k,l, searchCheck, incrCheck, decrCheck, del;
	char search[20];
	int exit;
	int count=0;
	int load=0;
	struct employee a[100];
	struct employee b[100];
	char fileName[51];
	char delCode[21];
	FILE * f;
	FILE * w;
	FILE * sortCheck;
		
	start:
	enter_option:
	printf("----------------------------------------------------\n");
	printf("Choose one of the following options: \n");
	printf("1. Enter name of a file to store data\n");
	printf("2. Enter a list of employees\n");
	printf("3. Display tax information\n");
	printf("4. Search an employee by code\n");
	printf("5. Sort in increasing order by code\n");
	printf("6. Sort directly on file by bubble sort\n");
	printf("7. Check if data on the file is sorted or not\n");
	printf("8. Delete an employee by code\n");
	printf("0. Exit\n");
	scanf("%f", &option);
	
	//Enter the number again if the input is a float not an integer
	optionInt=option;
	if(option-optionInt!=0)
	{
		printf("Invalid input. Try again. \n");
		fflush(stdin);
		goto enter_option;
	}
	//Enter the number again if the input is not 0->8
	if(option!=0 && option!=1 && option!=2 && option!=3 && option!=4 && option!=5 && option!=6 && option!=7 && option!=8)
	{
		printf("Invalid input. Try again. \n");
		fflush(stdin);
		goto enter_option;
	}
	
	switch(optionInt)
	{
		case 0: 
			fclose(f);
			return 0;
			break;
		case 1:
			{
				j=0;
				system("cls");
				
				fflush(stdin);
				printf("Enter the name of the file: ");
				scanf("%100[^\n]", &fileName);
				
				f = fopen(fileName, "a+");
				load++;
				while(1)
				{
				//load data
				
				fscanf(f, "%100[^\n]%*c", &b[j].code);
				fscanf(f, "%100[^\n]%*c", &b[j].name);
				fscanf(f, "%f%*c", &b[j].income);
				fscanf(f, "%f%*c", &b[j].allowance);
				fscanf(f, "%f%*c", &b[j].pension);
				fscanf(f, "%f%*c", &b[j].healthInsurance);
				fscanf(f, "%f%*c", &b[j].dependants);
				fscanf(f, "%f%*c", &b[j].charity);
				fscanf(f, "%f%*c", &b[j].deduction);
				fscanf(f, "%f%*c", &b[j].taxable);
				fscanf(f, "%f%*c", &b[j].tax);
				fscanf(f, "%f%*c", &b[j].netIncome);
				if(feof(f))
				{
					system("cls");
					printf("%s loaded\n", fileName);
					printf("Number of employees: %d\n\n", j);
					system("pause");
					system("cls");
					break;
				}
				
				j++;
				}

				break;
			}
		case 2:			
		
			//Calculations
			system("cls");
			while(1)
			{
				exit=0;
				count++;
				
			if(load==0)
			{
				printf("\nFile not loaded.\n\n");
				system("pause");
				system("cls");
				break;
			}
				enter_code:
				get_code(j,b, &exit, count);
				if(exit==1)
				{
					break;
				}
				
				get_name(j,b);
				
				b[j].income=get_income();
				
				b[j].allowance=PERSONAL_ALLOWANCE;
				
				b[j].pension = pension_calculating(b[j].income);
				
				b[j].healthInsurance=health_insurance_calculating(b[j].income);
				
				b[j].dependants=dependant_allowance_calculating(b[j].income);
				
				b[j].charity=charity_input(b[j].income);
				printf("\n");
				
				b[j].deduction=deduction_calculating(b[j].pension,b[j].healthInsurance,b[j].dependants,b[j].charity);
				
				b[j].taxable=taxable_income_calculating(b[j].income,b[j].deduction);
				
				
				b[j].tax=tax_calculating(b[j].income, b[j].taxable);
				
				b[j].netIncome = net_income_calculating(b[j].income, b[j].tax);
					
				
				fprintf(f, "%s\n", b[j].code);
				fprintf(f, "%s\n", b[j].name);
				fprintf(f, "%f\n", b[j].income);
				fprintf(f, "%f\n", b[j].allowance);
				fprintf(f, "%f\n", b[j].pension);
				fprintf(f, "%f\n", b[j].healthInsurance);
				fprintf(f, "%f\n", b[j].dependants);
				fprintf(f, "%f\n", b[j].charity);
				fprintf(f, "%f\n", b[j].deduction);
				fprintf(f, "%f\n", b[j].taxable);
				fprintf(f, "%f\n", b[j].tax);
				fprintf(f, "%f\n", b[j].netIncome);
					
				j++;
				fclose(f);
				f = fopen(fileName, "a+");

			}
			system("pause");
			system("cls");
			break;
			
		case 3:
		
		system("cls");
		
			if(load==0)
			{
				printf("\nFile not loaded.\n\n");
				system("pause");
				system("cls");
				break;
			}
			
			displayMenu();
			for(k=0;k<j;k++)
			{
				
				display(k,b);
			}
			system("pause");
			system("cls");
			break;
			
		case 4:
			{
				
			if(load==0)
			{
				printf("\nFile not loaded.\n\n");
				system("pause");
				system("cls");
				break;
			}
			
			system("cls");
			printf("Enter code to be searched: ");
			fflush(stdin);
			scanf("%100[^\n]", &search);
			searchCheck=0;
			for(l=0;l<j;l++)
			{
				if(strcmp(search,b[l].code)==0)
				{
					displayMenu();
					display(l, b);
					searchCheck++;
					break;
				}
			}
			if(searchCheck==0)
			{
				printf("Not found.\n\n");
			}
			
			}
			system("pause");
			system("cls");
			break;
		case 5:
			{
				system("cls");
				if(load==0)
				{
				printf("\nFile not loaded.\n\n");
				system("pause");
				system("cls");
				break;
				}
				
				for(i=0;i<j;i++)
				{
					for(k=i+1;k<j;k++)
					{
						if(strcmp(b[i].code,b[k].code)>0)
						{
							swapStruct(b,i,k);
						}
					}
				}
				printf("Sorting Completed!\n");
				displayMenu();
				for(k=0;k<j;k++)
				{
				
				display(k,b);
				}
				system("pause");
				system("cls");
			break;
			}
		case 6:
		{
			system("cls");
			if(load==0)
				{
				printf("\nFile not loaded.\n\n");
				system("pause");
				system("cls");
				break;
				}
			bubbleSort(b,j);
			w=fopen(fileName, "w");
			for(i=0;i<j;i++)
			{
			fprintf(w, "%s\n", b[i].code);
			fprintf(w, "%s\n", b[i].name);
			fprintf(w, "%f\n", b[i].income);
			fprintf(w, "%f\n", b[i].allowance);
			fprintf(w, "%f\n", b[i].pension);
			fprintf(w, "%f\n", b[i].healthInsurance);
			fprintf(w, "%f\n", b[i].dependants);
			fprintf(w, "%f\n", b[i].charity);
			fprintf(w, "%f\n", b[i].deduction);
			fprintf(w, "%f\n", b[i].taxable);
			fprintf(w, "%f\n", b[i].tax);
			fprintf(w, "%f\n", b[i].netIncome);
			}
			fclose(w);
			system("pause");
			system("cls");
			break;
		}
		case 7:
		{
			system("cls");
			if(load==0)
				{
				printf("\nFile not loaded.\n\n");
				system("pause");
				system("cls");
				break;
				}
			incrCheck=0;
			decrCheck=0;
			sortCheck = fopen(fileName, "r");
			//load data
			for(i=0;i<j;i++)
			{
				fscanf(sortCheck, "%100[^\n]%*c", &a[i].code);
				fscanf(sortCheck, "%100[^\n]%*c", &a[i].name);
				fscanf(sortCheck, "%f%*c", &a[i].income);
				fscanf(sortCheck, "%f%*c", &a[i].allowance);
				fscanf(sortCheck, "%f%*c", &a[i].pension);
				fscanf(sortCheck, "%f%*c", &a[i].healthInsurance);
				fscanf(sortCheck, "%f%*c", &a[i].dependants);
				fscanf(sortCheck, "%f%*c", &a[i].charity);
				fscanf(sortCheck, "%f%*c", &a[i].deduction);
				fscanf(sortCheck, "%f%*c", &a[i].taxable);
				fscanf(sortCheck, "%f%*c", &a[i].tax);
				fscanf(sortCheck, "%f%*c", &a[i].netIncome);
			}
			
			for(i=0;i<j;i++)
			{
				
				for(k=i+1;k<j;k++)
				{
				
					if(strcmp(a[i].code,a[k].code)>0)
					{
						incrCheck++;
					}
					
					if(strcmp(a[i].code,a[k].code)<0)
					{
						decrCheck++;
					}	
				}
			}
			if(incrCheck==0)
			{
				printf("The file is sorted in increasing order!\n");
			}
			else if(decrCheck==0)
			{
				printf("The file is sorted in decreasing order!\n");
			}
			else printf("The file is not sorted!\n");
			fclose(sortCheck);
			system("pause");
			system("cls");
			break;
		}
		case 8:
		{
			system("cls");
			fflush(stdin);
			printf("Enter the code of the data you want to delete: ");
			scanf("%21[^\n]",&delCode);
			
			for(i=0;i<j;i++)
			{

				if(strcmp(b[i].code,delCode)==0)
				{
					del=i;
					break;
				}	
			}
			
			structDel(b,j,del);
			j--;
			
			w=fopen(fileName, "w");
			for(i=0;i<j;i++)
			{
			fprintf(w, "%s\n", b[i].code);
			fprintf(w, "%s\n", b[i].name);
			fprintf(w, "%f\n", b[i].income);
			fprintf(w, "%f\n", b[i].allowance);
			fprintf(w, "%f\n", b[i].pension);
			fprintf(w, "%f\n", b[i].healthInsurance);
			fprintf(w, "%f\n", b[i].dependants);
			fprintf(w, "%f\n", b[i].charity);
			fprintf(w, "%f\n", b[i].deduction);
			fprintf(w, "%f\n", b[i].taxable);
			fprintf(w, "%f\n", b[i].tax);
			fprintf(w, "%f\n", b[i].netIncome);
			}
			fclose(w);
			
			displayMenu();
			for(k=0;k<j;k++)
			{
				
				display(k,b);
			}
			system("pause");
			system("cls");
		}
	}

	goto start;
}

void get_code(int i, struct employee a[], int *exit, int count)
{

	char code[20];
	char zero[]="0";
	int j;
	enter:
	fflush(stdin);
	printf("Enter code (0 to stop): ");
	scanf("%100[^\n]", &code);

	if(strcmp(code,zero)==0)
	{
		*exit=1;
		return;
	}
	int check=0;
		for(j=0;j<count;j++)
		{
			if(strcmp(code, a[j].code)==0)
			check++;
			if(check!=0)
			{
			printf("Entered code has been used, please enter another code\n");
			goto enter;
			}		
		}
	strcpy(a[i].code,code);
	return;
	
}

void get_name(int i, struct employee a[])
{
	fflush(stdin);
	printf("Enter name: ");
	scanf("%100[^\n]", a[i].name);
	return;
}

float get_income()
{
	float income;
	enter_income:
	fflush(stdin);
	printf("Income for the current month (in thousand VND): ");
	scanf("%f", &income);
	if(income<=0)
	{
		printf("Invalid input, try again.\n");
		goto enter_income;
	}
	return income;
	
}

float pension_calculating(float income)
{
	char option;
	float pension;
	enter_pension:
	printf("Pension contributions (%.0f%%) y/n? ", RATE_PENSION*100);
	scanf(" %c", &option);
	
	if(option!='y' && option!='n')
	{
		printf("Invalid Input. Try again.\n");
		goto enter_pension;
	}
	
	if(option=='y')
	{
		pension=income*RATE_PENSION;
	}
	
	if(option=='n')
	{
		pension=0;
	}
	return pension;
}
	
float health_insurance_calculating(float income)
{
	char option;
	float healthInsurance;
	enter_healthInsurance:
	printf("Health insurance (%.0f%%) y/n? ", RATE_HEALTH_INSURANCE*100);
	scanf(" %c", &option);
	
	if(option!='y' && option!='n')
	{
		printf("Invalid Input. Try again.\n");
		fflush(stdin);
		goto enter_healthInsurance;
	}
	
	if(option=='y')
	{
		healthInsurance=income*RATE_HEALTH_INSURANCE;
	}
	
	if(option=='n')
	{
		healthInsurance=0;
	}
}	

float dependant_allowance_calculating(float income)
{
	float dependant;
	float dependantAmt;
	int dependantAmtInt;
	enter_dependant:
	printf("Number of dependants < 18 years old: ");
	scanf("%f", &dependantAmt);
	
	dependantAmtInt=dependantAmt;
	
	if(dependantAmt<0)
	{
		printf("Invalid input. Try again. \n");
		fflush(stdin);
		goto enter_dependant;
	}
	
	if(dependantAmt-dependantAmtInt!=0)
	{
		printf("Invalid input. Try again. \n");
		fflush(stdin);
		goto enter_dependant;
	}
	
	dependant= RATE_DEPENDANT*dependantAmtInt;
	return dependant;
	
}

float charity_input(float income)
{
	float charity;
	enter_charity:
	printf("Gift of charity: ");
	scanf("%f", &charity);
	
	if(charity>income)
	{
		printf("Invalid input. Try again. \n");
		fflush(stdin);
		goto enter_charity;
	}
	
	if(charity<0)
	{
		printf("Invalid input. Try again. \n");
		fflush(stdin);
		goto enter_charity;
	}
	
	return charity;
	
}

float deduction_calculating(float pension, float healthInsurance, float dependant, float charity)
{
	float deduction;
	deduction=PERSONAL_ALLOWANCE+pension+healthInsurance+dependant+charity;
	return deduction;
}

float taxable_income_calculating(float income, float deduction)
{
	float taxable;
	taxable=income-deduction;
		if(taxable<0)
		taxable=0;
	return taxable;
}

float tax_calculating(float income, float taxable)
{
	float tax;
	if(taxable<=5000) tax=0.05*taxable;
	else if(taxable>5000&&taxable<=10000) tax=0.05*5000+0.1*(taxable-5000);
	else if(taxable>10000&&taxable<=20000) tax=0.05*5000+0.1*5000+0.15*(taxable-10000);
	else if(taxable>20000&&taxable<=30000) tax=0.05*5000+0.1*5000+0.15*10000+0.2*(taxable-20000);
	else if(taxable>30000&&taxable<=50000) tax=0.05*5000+0.1*5000+0.15*10000+0.2*10000+0.25*(taxable-30000);
	else if(taxable>30000&&taxable<=50000) tax=0.05*5000+0.1*5000+0.15*10000+0.2*10000+0.25*20000+0.3*(taxable-50000);
	else tax=0.05*5000+0.1*5000+0.15*10000+0.2*10000+0.25*20000+0.3*30000+0.35*(taxable-80000);
	return tax;
}

float net_income_calculating(float income, float tax)
{
	float netIncome;
	netIncome=income-tax;
	return netIncome;
}


void displayMenu()
{
		printf (" \n%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s","Code","Name","Income","Allow","Pens","Ins","Depend","Charity","Taxable","Tax","Net");
   	    printf ("\n---------------------------------------------------------------------------------------------------------------------");
   	    printf ("\n");
}
void display(int k, struct employee a[])
{

	
		printf ("%-10s%-10s%-10.0lf%-10.0lf%-10.0lf%-10.0lf%-10.0lf%-10.0lf%-10.0lf%-10.0lf%-10.0lf\n", a[k].code,a[k].name,a[k].income,a[k].allowance,a[k].pension,a[k].healthInsurance,a[k].dependants,a[k].charity,a[k].taxable,a[k].tax,a[k].netIncome);
}

void printOptions()

{
	return;
}
	
void swapStruct(struct employee b[],int i,int k)
{
	char tempS[51];
	float tempF;
	strcpy(tempS,b[i].code);
	strcpy(b[i].code,b[k].code);
	strcpy(b[k].code,tempS);
	
	strcpy(tempS,b[i].name);
	strcpy(b[i].name,b[k].name);
	strcpy(b[k].name,tempS);
	
	tempF=b[i].income;
	b[i].income=b[k].income;
	b[k].income=tempF;
	
	tempF=b[i].allowance;
	b[i].allowance=b[k].allowance;
	b[k].allowance=tempF;
	
	tempF=b[i].pension;
	b[i].pension=b[k].pension;
	b[k].pension=tempF;
	
	tempF=b[i].healthInsurance;
	b[i].healthInsurance=b[k].healthInsurance;
	b[k].healthInsurance=tempF;
	
	tempF=b[i].charity;
	b[i].charity=b[k].charity;
	b[k].charity=tempF;
	
	tempF=b[i].dependants;
	b[i].dependants=b[k].dependants;
	b[k].dependants=tempF;

	tempF=b[i].taxable;
	b[i].taxable=b[k].taxable;
	b[k].taxable=tempF;
	
	tempF=b[i].tax;
	b[i].tax=b[k].tax;
	b[k].tax=tempF;
	
	tempF=b[i].netIncome;
	b[i].netIncome=b[k].netIncome;
	b[k].netIncome=tempF;
}	


void bubbleSort(struct employee a[], int j)
{
	int i, k, choiceINT;
	float choice;
	enter_choice:
	printf("0. Cancel\n");
	printf("1. Increasing\n");
	printf("2. Decreasing\n");
	scanf("%f",&choice);
	
	choiceINT=choice;
	if(choice-choiceINT!=0)
	{
		printf("Invalid input. Try again. \n");
		fflush(stdin);
		goto enter_choice;
	}
	//Enter the number again if the input is not 0->2
	if(choice!=0 && choice!=1 && choice!=2)
	{
		printf("Invalid input. Try again. \n");
		fflush(stdin);
		goto enter_choice;
	}
	
	switch(choiceINT)
	{
	case 0:
		return;
		break;
		
	case 1:
	{
    for (i = 0; i < j-1; i++)     
       for (k = 0; k < j-i-1; k++)
           if (strcmp(a[k].code,a[k+1].code)>0)
              swapStruct(a,k,k+1);
    printf("File is sorted in increasing order\n");
	break; 
	}
	
	case 2:
	{
    for (i = 0; i < j-1; i++)     
       for (k = 0; k < j-i-1; k++)
           if (strcmp(a[k].code,a[k+1].code)<0)
              swapStruct(a,k,k+1); 
	}
	displayMenu();
			for(i=0;i<j;i++)
			{
				
				display(i,a);
			}
		printf("File is sorted in decreasing order\n");
	break;
	}
}

void structDel(struct employee a[],int j, int del)
{
	int i;
	for(i=del;i<j;i++)
	{
		strcpy(a[i].code,a[i+1].code);
		strcpy(a[i].name,a[i+1].name);
		a[i].income=a[i+1].income;
		a[i].allowance=a[i+1].allowance;
		a[i].pension=a[i+1].pension;
		a[i].healthInsurance=a[i+1].healthInsurance;
		a[i].charity=a[i+1].charity;
		a[i].dependants=a[i+1].dependants;
		a[i].taxable=a[i+1].taxable;
		a[i].tax=a[i+1].tax;
		a[i].netIncome=a[i+1].netIncome;
	}
}

