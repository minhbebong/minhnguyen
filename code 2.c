#include<stdio.h>
#include<string.h>

#define RATE_PENSION  0.05
#define RATE_INSURANCE  0.01
//m cot col
//n hang row
void Input(char a[][100], int col, int row)
{
   int i,j;
   for(i = 0; i < col; i++)
      for(j = 0; j < row; j++)
      {
         printf("A[%d][%d] = ", i, j);
         scanf("%s", &a[i][j]);
      }
}
 
void Output(char a[][100], int col, int row)
{
   int i,j;
   for( i = 0; i < col; i++)
   {
    for(j = 0; j < row; j++)
	printf("%10c\t", a[i][j]);
	printf("\n");
   }
}
struct Employees //dinh nghia kieu du lieu(struct) ten la SinhVien
{
	int Code;
	char Name[101] ;
	double income,total,taxable,tax,net,depend,pens,ins,charity,allow;
};
main()
{
	int col=11,row=3,selec,de,A,B,Code,o,p=11;
	double income,total,taxable,tax,net,depend,pens,ins,charity,allow=4000,X,Y=0;
	char a[100][100],Name[100],m=37,k1[2],k2[2],k3[2]="y",k4[2]="n",k5[2];
	while(1)
	{
		printf("Choose one of the following options:");
		printf("\n1. Enter a list of employees");
		printf("\n2. Display tax information");
		printf("\n3. Search an employee by code");
		printf("\n0. Exit\n");
		
		printf("Your selection (0 -> 3): ",selec);scanf("%d",&selec);
		
		
		if(selec==1)
		{	
			printf("Enter personal information:\n");
			while(1)
			{
					printf("Enter code (0 to stop):");
					scanf("%d",&Code);
					if(Code==0) break;
					fflush(stdin);
					printf("Enter name: ");scanf("%100[^\n]",&Name);
					while(1)
					{
						printf("Income for the current month (in thousand VND): ");
				    	scanf("%lf", &income);
				    	if(income<=0) printf("\nInvalid input,Try again."); 
				    	else if(income>0) break;
					}
					pens =  income * RATE_PENSION;
					ins =  income * RATE_INSURANCE;
				    
					fflush(stdin);
				    printf("Pension contributions (5%c) y/n ? ",m);scanf("%c",&k1[0]);
				    if(strcmp(k1,k3)==0) A=1;
					else if(strcmp(k1,k4)==0) A=0;
						
					
					fflush(stdin);
					printf("Health insurance (1%c) y/n ? ",m);scanf("%c",&k2[0]);
				    if(strcmp(k2,k3)==0) B=1;
					else if(strcmp(k2,k4)==0) B=0;
				
					while(1)
					{
						fflush(stdin);
						printf("Number of dependants < 18 years old:");scanf("%d",&de);
						if(de<0) printf("\nInvalid input,Try again.");
						else if (de>=0) break;
					} 
					while(1)//check va nhap charity
					{
						fflush(stdin);
						printf("Gift of charity:");scanf("%lf",&charity);
						if(charity>income) printf("Invalid input,Try again.");
						else if(charity<income) break;
					}
					
					depend = 1600.0*de;
				    if(A==1 && B==1) total = allow+pens+ins+charity+depend;
				    else if(A==0 && B==0) total = allow+charity+depend;
				    else if(A==1 && B==0) total = allow+pens+charity+depend;
				    else if (A==0 && B==1) total = allow+ins+charity+depend;
					//tinh thue
					taxable = income - total;
					X=taxable;
					   
					if(X<=5000)	Y=Y+(X*0.05);
					else
					{
						if(X<=10000 && X>5000) Y= 250 + ((X-5000)*0.1);
						else
							if(X<=20000&& X>10000) Y= 750 +((X-10000)*0.15);
							else
								if(X<=30000&&X>20000) Y= 2250+((X-20000)*0.2);
								else
									if(X<=50000&&X>30000) Y=4250+((X-30000)*0.25);
									else
										if(X<=80000&&X>50000) Y=9250+((X-50000)*0.3);
										else
											Y=18250+((X-80000)*0.35);
					}
					tax=Y;
					net=income-tax;	
				
					
		}}
		else if(selec==2)
		{
			printf("Code	Name	income  allow	pens	ins	depend	  charity	taxable   tax	 net\n");
			printf("--------------------------------------------------------------------------------------------------------------------------");
			Output(a,col,row);	
		}
		else if(selec==3)
		{
			
		}
		else if(selec==0) return 0;
	
		

}
}
