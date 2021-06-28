#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<conio.h>
#include<iomanip>
using namespace std;
int main()
{
	FILE *fp,*ft;
	char another,choice;
	struct student
	{
		char first_name[50],last_name[50];
		char course[50];
		int section;
	};
	struct student e;
	char xfirst_name[50],xlast_name[50];
	long int recsize;
	fp=fopen("users.txt","rb+");
	if(fp==NULL)
	{
		fp=fopen("users.txt","wb+");
		if(fp==NULL)
		{
			puts("Cannot open file");
			return 0;
		}
	}
	recsize=sizeof(e);
	while(1)
	{
		system("cls");
		cout<<"\nSTUDENT DATABASE MANAGEMENT SYSTEM\n";
		cout<<"\n1.ADD RECORDS";
		cout<<"\n2.LIST RECORDS";
		cout<<"\n3.MODIFY RECORDS";
		cout<<"\n4.DELETE RECORDS";
		cout<<"\n5.EXIT";
		cout<<"\n\nSelect your choice:";
		fflush(stdin);
		choice=getche();
		switch(choice)
		{
			case '1':
				fseek(fp,0,SEEK_END);
				another='Y';
				while(another=='Y'||another=='y')
				{
					system("cls");
					cout<<"\nEnter first name:";
					cin>>e.first_name;
					cout<<"\nEnter last name:";
					cin>>e.last_name;
					cout<<"\nEnter course:";
					cin>>e.course;
					cout<<"\nEnter the section:";
					cin>>e.section;
					fwrite(&e,recsize,1,fp);
					cout<<"\nAdd another record(Y/N):";
					fflush(stdin);
					another=getchar();
				}
				break;
			case '2':
				system("cls");
				rewind(fp);
				cout<<"***View the records in the database***\n";
				while(fread(&e,recsize,1,fp)==1)
				{
					cout<<"\n"<<e.first_name<<setw(10)<<e.last_name;
					cout<<"\n"<<e.course<<setw(8)<<e.section;
				}
				cout<<"\n";
				system("pause");
				break;
			case '3':
				system("cls");
				another='Y';
				while(another=='Y'||another=='y')
				{
					cout<<"\nEnter the last name of the student:";
					cin>>xlast_name;
					rewind(fp);
					while(fread(&e,recsize,1,fp)==1)
					{
						if(strcmp(e.last_name,xlast_name)==0)
						{
							cout<<"\nEnter new first name:";
							cin>>e.first_name;
							cout<<"\nEnter new last name:";
							cin>>e.last_name;
							cout<<"\nEnter new course:";
							cin>>e.course;
							cout<<"\nEnter new section:";
							cin>>e.section;
							fseek(fp,recsize,SEEK_CUR);
							fwrite(&e,recsize,1,fp);
							break;
						}
						else
						cout<<"\nRecord not found!";
					}
					cout<<"\nModify another record(Y/N):";
					fflush(stdin);
					another=getchar();
				}
				break;
			case '4':
				system("cls");
				another='Y';
				while(another=='Y'||another=='y')
				{
					cout<<"\nEnter the last name of the student to delete:";
					cin>>xlast_name;
					ft=fopen("temp.dat","wb");
					rewind(fp);
					while(fread(&e,recsize,1,fp)==1)
						if(strcmp(e.last_name,xlast_name)!=0)
						{
							fwrite(&e,recsize,1,ft);
						}
					fclose(fp);
					fclose(ft);
					remove("users.txt");
					rename("temp.dat","users.txt");
					fp=fopen("users.txt","rb+");
					cout<<"\nDelete another record(Y/N):";
					fflush(stdin);
					another=getchar();
				}
				break;
			case '5':
				fclose(fp);
				cout<<"\nTHANK YOU\n";
				exit(0);
				break;
		}
	}
	system("pause");
	return 0;
}
