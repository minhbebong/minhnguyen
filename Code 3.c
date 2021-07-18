#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<stdbool.h>
#define Rate_Health 0.01
#define Rate_Pension 0.05
struct Tax{
	char ten[100];
	int in,a,de,c,taxable,tax,net,pens,ins,g;
	char p[2],h[2],income[100],depend[100],gift[100],code[100];
	int allow;
};

bool ktra(char *s){
	int i,count = 0;
	for (i=0;i<strlen(s);i++){
		if (s[i] < '0' || s[i] > '9'){
			return false;
		}
	}
	return true;
}

int convert(char *s){
	char *ptr;
	int kqua;
	kqua = strtod(s,&ptr);
	return kqua;
}
//Ham Nhap Code
void Code(char *s){
	while (1){
		fflush(stdin);
		printf("Enter code (0 to stop): ");
		gets(s);
		if (!ktra(s)){
			printf("Invalid input, try again.\n");
		}else{
			break;
		}
	}
}
//Ham Nhap Income
void Income(char *s){
	while (1){
		fflush(stdin);
		printf("Income for the current month (in thousand VND): ");
		gets(s);
		if (!ktra(s)){
			printf("Invalid input, try again.\n");
		}else{
			break;
		}
	}
}
//Ham nhap Depend
void Depend(char *s){
	while (1){
		fflush(stdin);
		printf("Number of dependants < 18 years old: ");
		gets(s);
		if (!ktra(s)){
			printf("Invalid input, try again.\n");
		}else{
			break;
		}
	}
}
//Ham nhap Gift
void Gift(char *s){
	while (1){
		fflush(stdin);
		printf("Gift of charity: ");
		gets(s);
		if (!ktra(s)){
			printf("Invalid input, try again.\n");
		}else{
			break;
		}
	}
}
//Ham Nhap Pension
void Pension(char *s){
    while(1){
    	fflush(stdin);
        printf("Pension contributions (5%%) y/n? ");
        scanf("%s",s);
        if (strlen(s) > 1 || (tolower(s[0]) != 'y') &&tolower(s[0]) != 'n'){
            printf("Invalid input, try again.\n");
        }else{
        	break;
		}
    }
}
//Ham Nhap Health
void Health(char *s){
    while(1){
    	fflush(stdin);
        printf("Health insurance (1%%) y/n? ");
        scanf("%s",s);
        if (strlen(s) > 1 || (tolower(s[0]) != 'y') &&tolower(s[0]) != 'n'){
            printf("Invalid input, try again.\n");
        }else{
        	break;
		}
    }
}
//Ham tinh tax
int taxableIncome(int a){
	int tax;
    if (a<=5000){
        tax = a * 0.05;
    }else if(5000<a && a<=10000){
        tax = 250 + (a-5000)*0.1;
    }else if(10000<a && a<=20000){
        tax = 750 + (a-10000)*0.15;
    }else if(20000<a && a<=30000){
        tax = 2250 + (a-20000)*0.2;
    }else if(30000<a && a<=50000){
        tax = 4250 + (a-30000)*0.25;
    }else if(50000<a && a<=80000){
        tax = 9250 + (a-50000)*0.3;
    }else{
        tax = 18250 + (a - 80000)*0.35;
    }
    return tax;
}
//Ham nhap vao
void nhap(struct Tax *t,int *sl){
	int i;
	while (1){
		printf("\nEnter personal information:\n");
		Code(t->code);
		t->c = convert(t->code);
		*sl = *sl +1;
		if (t->c == 0){
			printf("\n");
			system("pause");
			printf("\n");
			break;
		}
		printf("Enter name: "); scanf("%[^\n]s",t->ten);
		Income(t->income);
		t->in = convert(t->income);
		Pension(t->p);
		Health(t->h);
		Depend(t->depend);
		t->de = convert(t->depend);
		do{
			Gift(t->gift);
			t->g = convert(t->gift);
			if (t->g >= t->in){
				printf("Gift greater than Income, try again\n");
			}else{
				break;
			}
		}while(t->g > t->in);
		if (tolower(t->p[0])=='y'){
       	 	t->pens = t->in*Rate_Pension;
   		}else{
           	t->pens = 0;
		}
   	    if (tolower(t->h[0])=='y'){
	       	t->ins = t->in*Rate_Health;
    	}else{
          	t->ins = 0;
		}
		t->taxable = t->in - 4000 - t->pens - t->ins - t->de*1600 - t->g;
		t->tax = taxableIncome(t->taxable);
		t->net = t->in - t->tax;
		t->allow = 4000;
		t++;
	}
}
//Ham in thu tu
void inTT (struct Tax *t,int sl){
	int i;
	for (i=0;i<sl;i++){
		printf("%-10.3d %-10s %-10d %-10d %-10d %-10d %-10d %-10d %-10d %-10d %-10d\n",
		(t+i)->c,(t+i)->ten,(t+i)->in,(t+i)->allow,(t+i)->pens,(t+i)->ins,(t+i)->de*1600,(t+i)->g,(t+i)->taxable,(t+i)->tax,(t+i)->net);
	}
}
//Ham hien thi cot
void hienThiCot(){	
	printf("%-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s\n",
	"Code","name","income","allow","pens","ins","depend","charity","taxable","tax","net");
	printf("--------------------------------------------------------------------------------------------------------------------\n");
}
//Ham nhap lua chon
void nhapChoice(char *s){
	while (1){
		fflush(stdin);
		printf("\nYour selection <0 -> 8>: ");
		gets(s);
		if (!ktra(s)){
			printf("Invalid input, try again.\n");
		}else{
			break;
		}
	}
}
//Ham ghi file
void ghiFile(char file[100],struct Tax *t,int sl){
	int i;
	FILE *f;
	f = fopen(file,"w+");
	fprintf(f,"%-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s\n",
	"Code","name","income","allow","pens","ins","depend","charity","taxable","tax","net");
	fprintf(f,"--------------------------------------------------------------------------------------------------------------------\n");
	for (i=0;i<sl;i++){
		fprintf(f,"%-10.3d %-10s %-10d %-10d %-10d %-10d %-10d %-10d %-10d %-10d %-10d\n",
		(t+i)->c,(t+i)->ten,(t+i)->in,4000,(t+i)->pens,(t+i)->ins,(t+i)->de*1600,(t+i)->g,(t+i)->taxable,(t+i)->tax,(t+i)->net);
	}
	fclose(f);
}
// Ham doc file
void docFile(struct Tax *t,int *sl){
	FILE *f = fopen("tax.dat","r");
	int i=0;
	if (f){
		while(1){
			fscanf(f,"%10d %10[^\n] %10d %10d %10d %10d %10d %10d %10d %10d %10d",
			&(t+i)->c,(t+i)->ten,&(t+i)->in,&(t+i)->allow,&(t+i)->pens,&(t+i)->ins,&(t+i)->de,&(t+i)->g,&(t+i)->taxable,&(t+i)->tax,&(t+i)->net);
			if (feof(f)){
				break;
			}
			i++;
		}
		
	}
	fclose(f);
	*sl = i;
}
//Ham tim kiem
void search(struct Tax *t,int sl){
	int mark = 0;
	char timCode[100];
	Code(timCode);
	int scode = convert(timCode);
	int i;
	for (i=0;i<sl;i++){
		if (t->c == scode){
			printf("Found at position: %d\n",i);
			hienThiCot();
			printf("%-10.3d %-10s %-10d %-10d %-10d %-10d %-10d %-10d %-10d %-10d %-10d\n",
			t->c,t->ten,t->in,4000,t->pens,t->ins,t->de*1600,t->g,t->taxable,t->tax,t->net);
			mark = 1;
		} t++;
		
	}
	if (mark == 0){
		printf("Code can't be found!\n");
	}
}
//Ham sap xep
void sapXep(struct Tax *t,int sl){
	int i,j;
	struct Tax temp;
	for (i=0;i<sl-1;i++){
		for (j=i+1;j<sl;j++){
			if ((t+i)->c > (t+j)->c){
				temp = t[i];
				t[i] = t[j];
				t[j] = temp;
			}
		}
	}
}
//Ham kiem tra sap xep
bool ktraSapXep(struct Tax *t,int sl){
	int i,j;
	for (i=0;i<sl-1;i++){
		for (j=i+1;j<sl;j++){
			if ((t+i)->c > (t+j)->c){
				return false;
			}
		}
	}
	return true;
}
//Ham xoa code
void nhapDelCode(char *s){
	while (1){
		fflush(stdin);
		printf("Enter code u want to delete: ");
		gets(s);
		if (!ktra(s)){
			printf("Invalid input, try again.\n");
		}else{
			break;
		}
	}
}
//Ham xoa
void del(struct Tax *t,int *sl,int xoa){
	int i,vt,mark=0;
	for (i=0;i<*sl;i++){
		if ((t+i)->c == xoa){
			vt = i;
			mark = 1;
		}
	}
	*sl = *sl - 1;
	for (i=vt;i<*sl;i++){
		t[i] = t[i+1];
	}
	if (mark == 0){
		printf("Code cannot be found!\n");
	}
}
main(){
	FILE *f;
	char choice[9]; 
	int luaChon;
	struct Tax s[100];
	char file[100];
	int sl=-1,i;
	char xoa[100];
	int delcode;
	do{
		printf("Choose one of the following options:");
		printf("\n1. Enter a name of a file to store data");
		printf("\n2. Enter a list of employees");
		printf("\n3. Display tax information");
		printf("\n4. Search an employee by code");
		printf("\n5. Sort in increasing order by code");
		printf("\n6. Sort directly on file by bubble sort");
		printf("\n7. Check if data on file is stored or not");
		printf("\n8. Delete an employee by code");
		printf("\n0. Exit");
		nhapChoice(choice);
		luaChon = convert(choice);
		switch (luaChon){
			case 1:
				printf("Enter a name of a file to store data: ");
				scanf("%s",file);
				f = fopen(file,"w");
				fclose(f);
				break;
			case 2:
				nhap(s,&sl);
				ghiFile(file,s,sl);
				break;
			case 3:
				docFile(s,&sl);
				ghiFile(file,s,sl);
				hienThiCot();
				inTT(s,sl);
				break;
			case 4:
				search(s,sl);
				break;	
			case 5:
				sapXep(s,sl);
				ghiFile(file,s,sl);
				hienThiCot();
				inTT(s,sl);
				break;
			case 6:
				printf("Khong lam!\n");
				break;
			case 7:
				if (ktraSapXep(s,sl)){
					printf("Danh sach da duoc sap xep");
				}else{
					printf("Danh sach chua duoc sap xep");
				}
				break;
			case 8:
				nhapDelCode(xoa);
				delcode = convert(xoa);
				del(s,&sl,delcode);
				hienThiCot();
				inTT(s,sl);
				break;
		}
	}while(luaChon);
}
