#include <iostream>		 
#include <fstream> 		
#include <cstring>		
#include <cstdio> 		
#include<iomanip> 		
#include <stdlib.h> 	
using namespace std;

int count = 0, tries = 0;
float total;

class OrderManagement{
	string title, author;
	int quantity;
	public:
		void OrderManagementFunc() {
			getInfo();
			handleFile();
			cout<<"\tOrder placed successfully..."<<endl<<endl;
			return;
		}
		
		void getInfo() {
			cout<<"\n\tName of Book: ";
			cin>>title;
			cout<<"\tAuthor of Book: ";
			cin>>author;
			cout<<"\tQuantity: ";
			cin>>quantity;
		}
		
		void handleFile() {
			fstream file;
			file.open("order.txt", ios::app);
			file<<title<<" "<<author<<" "<<quantity<<"\n";
			file.close();	
		}
		
		void displayOrders() {
			fstream file;
			file.open("order.txt", ios::in);
			if(file.peek()==EOF){
				cout<<"\tNo orders from customers !!!"<<endl<<endl;
			}
			while (file>>title>>author>>quantity) {
				cout<<title<<" "<<author<<" "<<quantity<<"\n\n";
			}
			file.close();
		}
		friend class Admin;
};

class Admin {
	string title, author, validatedTitle, validatedAuthor;
	float price;
	int quantity, id;
	
	public:
		void getInfo(){
			cout<<"\tName of the book: ";
			cin>>title;
			validatedTitle = validateTitle(title);
			cout<<"\tAuthor of the book: ";
			cin>>author;
			validatedAuthor = validateAuthor(author);
			cout<<"\tPrice of the book: ";
			cin>>price;
			cout<<"\tID of the book: ";
			cin>>id;
			cout<<"\tQuantity of the book: ";
			cin>>quantity;
		}
		
		void addBook(){
			fstream file;
			file.open("books.txt", ios::app);
			getInfo();
			file<<id<<" "<<validatedTitle<<" "<<validatedAuthor<<" "<<price<<" "<<quantity<<"\n";
			cout<<"\tBook Added Successfully..."<<endl<<endl;
			file.close();
		}
		
		string validateTitle(string str) {
			int minS =  7, maxS = 14;
			if (str.length() < minS || str.length() > maxS) {
				cout<<"\tBook Name must be [7-14] characters!!!"<<endl<<endl;
				cout<<"\tName of the book: ";
				cin>>str;
				return validateTitle(str);
			} else {
				return str;
			}
		}
		
		string validateAuthor(string str) {
			int minS =  8, maxS = 14;
			if (str.length() < minS || str.length() > maxS) {
				cout<<"\tAuthor Name must be [8-14] characters!!!"<<endl<<endl;
				cout<<"\tAuthor of the book: ";
				cin>>str;
				return validateAuthor(str);
			} else {
				return str;
			}
		}
		
		void displayBooks() {
			fstream file;
			file.open("books.txt", ios::in);
			cout<<"\n\n\t__________________________________________________________________\n";
			cout<<"\t|ID\t|Title\t\t|Author\t\t|Price\t\t|In Stock|\n";
			cout<<"\t|_______|_______________|_______________|_______________|________|\n";
			if(!file.is_open() || file.peek()==EOF){
				cout<<"\tThe file contains no records !!!"<<endl<<endl;
				file.close();
				return;
			}
			while(file>>id>>title>>author>>price>>quantity){
				cout<<"\t|"<<id<<"\t|"<<title<<"\t|"<<author<<"\t|"<< fixed << setprecision(2)<<price<<"\t|"<<quantity<<"\t |"<<endl;
				cout<<"\t|_______|_______________|_______________|_______________|________|\n";
			}
			file.close();
		}
		
		void deleteBook(){
			int ID;
			bool found = false;
			fstream file;
			fstream FILE;
			file.open("books.txt", ios::in);
			FILE.open("temp.txt", ios::out);
			cout<<"\tID of the book you want to delete: ";
			cin>>ID;
			while(file>>id>>title>>author>>price>>quantity){
				if (ID == id) {
					found = true;
				}
				else{
					FILE<<id<<" "<<title<<" "<<author<<" "<<price<<" "<<quantity<<"\n";
				}
			}
			file.close();
			FILE.close();
			remove("books.txt");
			rename("temp.txt", "books.txt");
			if (found) {
				cout<<"\tThe item was deleted successfully!!!"<<endl<<endl;
			}
			else{
				cout<<"\tItem not found!!!"<<endl<<endl;
			}	
		}
		
		void adminInterface(OrderManagement& obj1) {
			char username[] = "admin";
			char password[] = "admin";
			char inputUsername[10], inputPassword[10];
			cout<<"\n\t\tAdmin Panel Interface"<<endl;
        	cout<<"\tEnter Username: ";
        	cin>>inputUsername;
			cout<<"\tEnter Password: ";
			cin>>inputPassword;
			system("CLS");
			if((strcmp(username, inputUsername) == 0 && strcmp(password, inputPassword) == 0)) {
				while(1) {
					int choice;
					cout<<"_______________________________________________"<<endl<<endl;
					cout<<"\t\tAdmin Interface"<<endl<<endl;
					cout<<"\t1. Add Book"<<endl;
					cout<<"\t2. Display Books"<<endl;
					cout<<"\t3. Delete Book"<<endl;
					cout<<"\t4. Display Orders"<<endl;
					cout<<"\t5. Return to Main Menu"<<endl<<endl;
					cout<<"_______________________________________________\n";
					cout<<"\n\tEnter your choice: ";
					cin>>choice;
					switch (choice) {
						case 1:
							system("CLS");	
							addBook();
							break;
						case 2:
							system("CLS");
							displayBooks();
							break;
						case 3:
							system("CLS");
							deleteBook();
							break;
						case 4:
							system("CLS");
							obj1.displayOrders();
							break;
						case 5:
							return;
						default:
							cout<<"\tInvalid choice. Please try again."<<endl<<endl;
							break;
					}
				}	
			} else {
				system("CLS");
				cout<<"\tInvalid Username or Password..."<<endl<<endl;
				++tries;
				if(tries>2){
					cout<<"\tMamimum Limit Reached..."<<endl<<endl;
					return;
				}
				adminInterface(obj1);
			}
		}
};

class BuyingInterface : public Admin {
	string title, author;
	float price;
	int quantity, id;
	public:		
		void buyBook(){
			char bill[] = "bill.txt";
			bool found = false;
	        int ID;
			cout<<"\n\tID of Book: ";
			cin>>ID;
			fstream file;
			file.open("books.txt", ios::in);
			fstream FILE;
			FILE.open("temp.txt", ios::out);
			fstream File;
			File.open("bill.txt", ios::app);
			system("CLS");
			while(file>>id>>title>>author>>price>>quantity){
				if(ID == id){
					found = true;
					if(quantity == 0){
						cout<<"\n\tBook Unavailable"<<endl<<endl;
					} else{
						--quantity;
						total = total + price;
						File<<title<<" "<<author<<" "<<price<<" "<<id<<"\n";
					}
				}
				FILE<<id<<" "<<title<<" "<<author<<" "<<price<<" "<<quantity<<"\n";
			}
			if (!found){
				cout<<"\tBook with entered ID doesn't exist..."<<endl<<endl;
			}
			file.close();
			FILE.close();
			File.close();
			char original[] = "books.txt";
			char temp[] = "temp.txt";
			remove(original);
			rename(temp, original);
			++count;
		}
		void Stop() {
			system("CLS");
			char bill[] = "bill.txt";
			fstream File;
			File.open("bill.txt", ios::in);
			if (!File.is_open() || total == 0){
				cout<<"\tZero Books Selected...\n"<<endl;
				return;
			}
			cout<<"\n\n\t_________________________________________________________\n";
			cout<<"\t|\t\t\tBILL\t\t\t\t|\n";
			cout<<"\t|_______________________________________________________|\n";

			cout<<"\t|ID\t|Title\t\t|Author\t\t|Price\t\t|\n";
			cout<<"\t|_______|_______________|_______________|_______________|\n";
			while (File>>title>>author>>price>>id){
				cout<<"\t|"<<id<<"\t|"<<title<<"\t|"<<author<<"\t|"<< fixed << setprecision(2)<<price<<"\t|"<<endl;
				cout<<"\t|_______|_______________|_______________|_______________|\n";
			}
			cout<<"\t|Total\t\t\t\t\t|Rs."<<total<<"\t|"<<endl;
			cout<<"\t|_______________________________________|_______________|\n";
			cout<<"\n\tThankyou for Purchasing..."<<endl<<endl<<endl;
			File.close();
			remove(bill);
			total = 0;
		}
};

void BuyingFunc() {
	system("CLS");
	Admin obj;
	BuyingInterface obj1;
	char decision[10];
	while (1) {
		obj.displayBooks();
		obj1.buyBook();
		obj.displayBooks();
		if (count > 0) {
			cout<<"\t|Total\t\t\t\t\t|Rs."<<total<<"\t\t |"<<endl;
			cout<<"\t|_______________________________________|________________________|\n";
		}
		cout<<"\n\tContinue Purchasing ? (y/n): ";
		cin>>decision;
		if (strcmp(decision, "y") == 0) {
			obj.displayBooks();
			BuyingFunc();
			} else if (strcmp(decision, "n") == 0) {
				obj1.Stop();
				return;
			}
		return;
	}
}

int main() {
	OrderManagement obj;
	Admin obj1;
	while(1) {
		int choice;
		cout<<"_______________________________________________\n";
		cout<<"\n\t\tBOOKSHOP INTERFACE SYSTEM"<<endl<<endl;
		cout<<"\t1. Buy Book"<<endl;
		cout<<"\t2. Order Book"<<endl;
		cout<<"\t3. Admin Panel"<<endl;
		cout<<"\t4. Exit Program"<<endl;
		cout<<"_______________________________________________\n";
		cout<<"\n\tEnter Your Choice: ";
		cin>>choice;
		cout<<"_______________________________________________\n";
		switch (choice) {
			case 1:
				BuyingFunc();
				break;
			case 2:
				obj.OrderManagementFunc();
				break;
			case 3:
				obj1.adminInterface(obj);
				break;
		}
	}
}
