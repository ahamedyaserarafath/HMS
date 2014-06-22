#include<stdio.h>
void append();
void view();
void search();
void modify();
void delete();
struct patient
	{
		char name[20];
		char diag[12];
		char gender[5];
		int no;
		int age;
	};

void main()
	{	
		int a;
		int ch;
		do
		{
			system("clear");
			printf("\n*****HOSPITAL MANAGMENT SYSTEM*****\n\n");
			printf("1.Append patient Record:\n2.List patient Record:\n3.Modify patient Record:\n");
			printf("4.Delete patient Record:\n5.Search patient Record:\nEnter Choice:\n");
			scanf("%d",&a);
			switch(a)
			{
				case 1:
					append();
					break;
				case 2:
					view();
					break;
				case 3:
					modify();
					break;
				case 4:
					delete();
					break;
				case 5:
					search();
					break;
				default :
					printf("Invalid Choice!");
				}
			printf("\n More Actions ? (1.Yes/2.No) :");
			scanf("%d", &ch);
			}while(ch==1);
	}
//APPENDING PATIENT DETAILS TO FILE
void append()
{ 
	int i,n;
	struct patient e;
	FILE *fp;
	fp=fopen("patient.dat", "a");
	if(fp==NULL)
	{
		printf("File Creation Failed!");
	}
	printf("Enter the nos. of patients : ");
	scanf("%d", &n);
		for(i=0;i<n;i++)
			{
				printf("Enter the patient id  Number : ");
				scanf("%d", &e.no);
				printf("Enter the patient Name : ");
				scanf("%s",e.name);
				printf("Enter diagnosis :");
				scanf("%s",e.diag);
				printf("Enter Gender :");
				scanf("%s",e.gender);
				printf("Enter Age :");
				scanf("%d",&e.age);
				printf("\n\n");
				fwrite((char *)&e, sizeof(e), 1, fp);
			}
	fclose(fp);
}
//VIEWING PATIENT DETAILS

void view()
{ 
	int nofrec=0;
	struct patient e;
	FILE *fp;
	fp=fopen("patient.dat", "r");
	if(fp==NULL)
		printf("\n\tFile doesn’t exist!! try again");
	else
	{
		while((fread((char *)&e, sizeof(e), 1, fp))==1)
		{ 
			nofrec++;
			printf("\npatient Number : %d ", e.no);
			printf("\npatient Name : %s",e.name);
			printf("\npatient diagnosis : %s",e.diag);
			printf("\npatient gender : %s",e.gender);
			printf("\npatient age : %d",e.age);
			printf("\n\n");
		}
	printf("Total number of records present are : %d", nofrec);
	fclose(fp);
	}
}

//MODIFY THE PATIENT DETAIL

void modify()
{
	int recno, nofrec=0;
	int ch;
	struct patient e;
	FILE *fp;
	fp=fopen("patient.dat", "rb+");
	if(fp==NULL)
                printf("\n\tFile doesn’t exist!! try again");
	else
	{
		view();	
		printf("\nEnter the patient id Number to modify : ");
		scanf("%d", &recno);
		while((fread((char *)&e, sizeof(e), 1, fp))==1)
		{
			nofrec++;
			if(e.no==recno)
			{
				printf("\npatient Number : %d", e.no);
				printf("\npatient Name : %s",e.name);
				printf("\npatient diagnosis : %s",e.diag);
				printf("\npatient gender : %s",e.gender);
				printf("\npatient age : %d",e.age);
				printf("\n");
				printf("Do you want to modify this record : ? (1.Y/2.N)");
				scanf("%d", &ch);
				fseek(fp, ((nofrec-1)*sizeof(e)),0);
				if(ch==1)
				{
					printf("Enter the patient id No : ");
					scanf("%d",&e.no);
					printf("Enter the patient Name : ");
					scanf("%s",e.name);
					printf("Enter diagnosis :");
					scanf("%s",e.diag);
					printf("Enter Gender :");
					scanf("%s",e.gender);
					printf("Enter Age :");
					scanf("%d",&e.age);

					fwrite((char *)&e, sizeof(e), 1, fp);
					printf("Record Modified");
				}
				else
					printf("No modifications were made");
				fclose(fp);
			}	
		}
	}
}
//DELETE THE RECORD
void delete()
{
	int recno;
	int ch;
	struct patient e;
	FILE *fp, *ft;
	fp=fopen("patient.dat", "rb");
	ft=fopen("Temp.dat", "wb");
	if(fp==NULL)
                printf("\n\tFile doesn’t exist!! try again");
	else
	{	
		view();
		printf("\nEnter the patient id Number to delete : ");
		scanf("%d", &recno);
		while((fread((char *)&e, sizeof(e), 1, fp))==1)
		{
			if(e.no==recno)
			{
				printf("\npatient Number : %d", e.no);
				printf("\npatient Name : %s",e.name);
				printf("\npatient diagnosis : %s",e.diag);
				printf("\npatient gender : %s",e.gender);
				printf("\npatient age : %d",e.age);
				printf("\n");
				printf("Do you want to delete this record : ? (1.Y/2.N)");
				scanf("%d", &ch);
			}
		}
		if(ch==1)
		{
			rewind(fp);
			while((fread((char *)&e, sizeof(e), 1, fp))==1)
			{
				if(recno!=e.no)
				{
					fwrite((char *)&e, sizeof(e), 1, ft);
				}
			}
				printf("\nrecord deleted\n");	
		}
		else
			printf("No Record was deleted");
		fclose(fp);
		fclose(ft);
		remove("patient.dat");
		rename("Temp.dat", "patient.dat");
	}
}

////SEARCH THE PATIENT RECORD
void search()
{
	int s,recno;
	char sname[20];
	struct patient e;
	FILE *fp;
	fp=fopen("patient.dat", "rb");
	if(fp==NULL)
                printf("\n\tFile doesn’t exist!! try again");
	else
	{
		printf("\n1.Search by Name\n2.Search by patient No.\n Enter choice : ");
		scanf("%d", &s);
		switch(s)
		{
			case 1:
				printf("Enter the patient Name to Search : ");
				scanf("%s",sname);
				while((fread((char *)&e, sizeof(e), 1, fp))==1)
				{
					if(strcmp(sname,e.name)==0)
					{
						printf("\npatient Number : %d", e.no);
						printf("\npatient Name : %s",e.name);
						printf("\npatient diagnosis : %s",e.diag);
						printf("\npatient gender : %s",e.gender);
						printf("\npatient age : %d",e.age);
						printf("\n");
					}
				}
				break;
			case 2:
				printf("Enter the patient Number to Search : ");
				scanf("%d", &recno);
				while((fread((char *)&e, sizeof(e), 1, fp))==1)
				{
					if(e.no==recno)
					{
						printf("\npatient Number : %d", e.no);
						printf("\npatient Name : %s",e.name);
						printf("\npatient diagnosis : %s",e.diag);
						printf("\npatient gender : %s",e.gender);
						printf("\npatient age : %d",e.age);
						printf("\n");
					}
				}
				break;
		}
	}
} //end of the program
		
