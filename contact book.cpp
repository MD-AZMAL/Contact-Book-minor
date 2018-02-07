#include<iostream>
#include<fstream>
#include<conio.h>
#include<process.h>
#include<stdio.h>
#include<string.h>

using namespace std;

class Contact{
	char phn[11];
	char fn[26];
	char ln[26];
	char email[26];
	public:
		void enter();
		void display();
		char *ret_req(int);
		void modf(int,char [],char []);
};

void Contact::enter(){
	cout<<"Enter first name: ";cin>>fn;
	cout<<"Enter last name: ";cin>>ln;
	cout<<"Enter email: ";cin>>email;
	cout<<"Enter phone number: ";cin>>phn;
}

void Contact::display(){
	cout<<"First name: "<<fn<<endl;
	cout<<"Last name: "<<ln<<endl;
	cout<<"E-mail: "<<email<<endl;
	cout<<"Phone number: "<<phn<<endl;
}

char *Contact::ret_req(int n){
	switch(n){
	case 1: return fn;
			break;
	case 2: return phn;
			break;
	case 3: return email;
			break;
	}
}

void Contact::modf(int ch,char ch1[],char ch2[]){
	switch(ch){
		case 1: strcpy(fn,ch1);
			    strcpy(ln,ch2);
			    break;
		case 2: strcpy(phn,ch1);
				break;
		case 3: strcpy(email,ch1);
	}
}



void Add();
void Delete();
int Search_base();
void Disp_res();
void Edit();
void View_All();

int main(){
	
	char go = 'y';
	int choice=0;
	while(go == 'y'){
		system("CLS");
		cout<<"CONTACT BOOK MENU"<<endl<<endl;
		cout<<"1.Add\n2.Edit\n3.Search\n4.Delete\n5.View All\n6.Delete All\n7.Exit\n\nEnter choice: ";
		cin>>choice;
		system("CLS");
		switch(choice){
			case 1:
				   cout<<"ADD TO CONTACT LIST"<<endl<<endl;
				   Add();
				   break;
			case 2:
				   cout<<"EDIT A CONTACT"<<endl<<endl;
				   Edit();
				   break;
			case 3:
				   cout<<"SEARCH CONTACT LIST"<<endl<<endl;
				   Disp_res();
				   break;
			case 4:
				   cout<<"DELETE A CONTACT"<<endl<<endl;
				  Delete();
				   break;
			case 5:
				   cout<<"VIEW ALL CONTACTS"<<endl<<endl;
				   View_All();
				   break;
			case 6:
				   remove("contact.bin");
				   cout<<"Successfully removed"<<endl;
				   break;
			case 7:
				   exit(0);
				   break;
			default:
				   cout<<"Invalid Input"<<endl<<endl;
	}
		cout<<"Do you want to continue (y/n): ";
		cin>>go;
	}
	return 0;
}

int Search_base(){
	int choice=-1,loc = 0;
	Contact C;
	char ch[26];
	while(choice > 3 || choice < 0){
	cout<<"Search by\n1.Name(first name)\n2.Number\n3.E-mail\nEnter choice: ";
	cin>>choice;
	if(choice > 3 || choice <0)
		cout<<"Invalid input";
	}
	switch(choice){
		case 1: cout<<"Enter the name (first name only): ";
				break;
		case 2: cout<<"Enter the number: ";
				break;
		case 3: cout<<"Enter e-mail: ";
				break;
	}
	cin>>ch;
	
	fstream obj("contact.bin",ios::binary|ios::in);
	while(obj){
		obj.read((char *)&C,sizeof(C));
		if(obj && strcmpi(C.ret_req(choice),ch)!=0){
			loc++;
		}
		else if(strcmpi(C.ret_req(choice),ch)==0){
			return loc;
		}
	}
	obj.close();
	return -1;
}

void Disp_res(){
	int loc = Search_base();
	if(loc == -1)
		cout<<"No contacts found"<<endl;
	else{
		fstream obj("contact.bin",ios::binary|ios::in);
		Contact C;
		obj.seekg(loc*sizeof(C),ios::beg);
		obj.read((char *)&C,sizeof(C));
		C.display();
		cout<<"\n----------------------------\n";
		obj.close();
	}
}

void Delete(){
	int loc = Search_base();
	if(loc == -1)
		cout<<"No contacts found"<<endl;
	else{
		int i;
		Contact C;
		fstream iobj("contact.bin",ios::binary|ios::in);
		fstream obj("tmp.bin",ios::binary|ios::out|ios::app);
		for(i = 0 ; i < loc ; i++){
			iobj.read((char *)&C,sizeof(C));
			obj.write((char *)&C,sizeof(C));
		}
		iobj.seekp((loc+1)*sizeof(C),ios::beg);
		while(iobj){
			iobj.read((char *)&C,sizeof(C));
			if(iobj)
				obj.write((char *)&C,sizeof(C));
		}
		obj.close();
		iobj.close();
		remove("contact.bin");
		rename("tmp.bin","contact.bin");
        cout<<"Successfully deleted"<<endl;
	}
}

void Edit(){
	int ch;
	char inp1[26],inp2[26];
	int loc = Search_base();
	if(loc==-1)
		cout<<"No contacts found"<<endl;
	else{
		cout<<"Match found\n1.Edit name\n2.Edit number\n3.Edit mail\n4.Edit all\nEnter choice: ";
		cin>>ch;
		switch(ch){
			case 1: cout<<"Enter the first name: ";
				    cin>>inp1;
				    cout<<"Enter last name: ";
				    cin>>inp2;
				    break;
			case 2: cout<<"Enter the number: ";
					cin>>inp1;
					break;
			case 3: cout<<"Enter the e-mail: ";
			        cin>>inp1;
			        break;
			default: cout<<"Invalid choice\npress any key.......";
			         getch();
		}
		Contact C;
		fstream iobj("contact.bin",ios::binary|ios::in);
		fstream obj("tmp.bin",ios::binary|ios::out|ios::app);
		for(int i=0 ; i < loc; i++){
			iobj.read((char *)&C,sizeof(C));
			obj.write((char *)&C,sizeof(C));	
		}
		iobj.read((char *)&C,sizeof(C));
		C.modf(ch,inp1,inp2);
		obj.write((char *)&C,sizeof(C));
		while(iobj){
			iobj.read((char *)&C,sizeof(C));
			if(iobj)
				obj.write((char *)&C,sizeof(C));
		}
		obj.close();
		iobj.close();
		remove("contact.bin");
		rename("tmp.bin","contact.bin");
        cout<<"Successfully edited"<<endl;
	}
}

void View_All(){
	int i=1;
	fstream obj("contact.bin",ios::binary|ios::in);
	Contact C;
	while(obj){
		obj.read((char *)&C,sizeof(C));
		if(obj){
			i=0;
			C.display();
		cout<<"\n----------------------------\n";
		}
	}
	obj.close();
	if(i)
		cout<<"No contacts found\n";
}

void Add(){
	Contact C;
	C.enter();
	fstream obj("contact.bin",ios::binary|ios::out|ios::app);
	obj.write((char *)&C,sizeof(C));
	cout<<"Successfully added"<<endl;
}






