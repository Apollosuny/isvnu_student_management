#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

struct Dob {
	int day;
	int month;
	int year;
};
typedef struct Dob Dob;

struct Student {
	char id[10];
	char name[50];
	char gender[10];
	Dob dob;
	char address[50];
	char email[50];
	long int phone; 
	char classs[10];
	float mark[3];
	float average;
	char academic[15];
};

typedef struct Student Student;

int login();
void printLine(int x);
int checkId(char id[]);
void menu();
void sortMenu();
void searchMenu();
void add();
void display();
void updateStudentById();
void deleteStudentById();
int checkName(char x[], char y[]);
void searchStudentByName();
void searchStudentByClass();
void searchStudentByAddress();
void separateName(char fullName[], char firstName[]);
void sortStudentByName();
void sortStudentByAverage();

COORD coord;
void gotoxy(int x, int y){
    coord.X = x; coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int main() {
	// system("color B0");
	// int d = login();
	// if (d == 0) 
	// 	return 0;
	// else {
	// 	system("cls");
	// 	gotoxy(20,8);printf("WELCOME TO THE PROGRAM");
	// 	menu();
	// }
	menu();
	return 0;
}

void printLine(int x) {
	for (int i = 0; i < x; i++) {
		if (i == 0 || i == x - 1) 
			printf("+");
		else 
			printf("-");
	}
}

int checkId(char id[]) {
	FILE *fp;
	Student s;
	fp = fopen("Database.txt", "rb+");
	if (fp == NULL) {
		printf("\nNo data in DB!");
		exit(1);
	} else {
		while (fread(&s, sizeof(s), 1, fp) == 1) {
			if (strcmp(id, s.id) == 0) {
				fclose(fp);
				return 1;
			}
		}
	}
	fclose(fp);
	return 0;
}

int login(){
	char c;
	int count = 3;
	while(count > 0){
		char userName[9];
		char password[9];
		int num = 0;
		gotoxy(5,5);printf("Sign in");
		gotoxy(5,6);printf("User name: "); fflush(stdin); gets(userName);
		gotoxy(5,7);printf("Password: "); 
		do{
			if(kbhit()){
				c = getch();
				if(c != 13){
					password[num] = c;
					num++;
					printf("*");
				}else
					break;
			}
		}while(1);
		if(strcmp(userName, "group1") == 0 && strcmp(password, "group1") == 0)
			return 1;
		else{
			gotoxy(5, 10);printf("Incorrect user name or password!");
			count--;
			getch();   
			system("cls"); 
		}
	}
	return 0;
}

void menu() {
	int choice;
	gotoxy(10,10);printf("+========================================+");
	gotoxy(10,11);printf("|| 		   GROUP 1		  ||");
	gotoxy(10,12);printf("||	   Student Record System 	  ||");
	gotoxy(10,13);printf("||		   Menu 		  ||");
	gotoxy(10,14);printf("+========================================+");
	gotoxy(10,15);printf("||1. Add Student		  	  ||");
	gotoxy(10,16);printf("||2. Update Student		  	  ||");
	gotoxy(10,17);printf("||3. Delete Student		  	  ||");
	gotoxy(10,18);printf("||4. List Student		  	  ||");
	gotoxy(10,19);printf("||5. Search           	  	  ||");
	gotoxy(10,20);printf("||6. Sort			  	  ||");
	gotoxy(10,21);printf("||0. Exit			  	  ||");
	gotoxy(10,22);printf("+========================================+");
	gotoxy(10,23);printf("||Your choice: ");
	gotoxy(50,23);printf("||");
	gotoxy(10,24);printf("+========================================+");
	gotoxy(26,23);scanf("%d", &choice);
		
	switch (choice) {
		case 1: 
			add();
			break;
		case 2:
			// updateStudentById();
			break;
		case 3: 
			// deleteStudentById();
			break;
		case 4: 
			display();
			break;
		case 5: 
			// searchMenu();
			break;
		case 6:
			// sortMenu();
			break;
		case 0:
			exit(0);
			break;
		default: 
			system("cls");
			gotoxy(10, 8);printf("Enter 0 to 6 only! Please input again!");
			menu();
	}
}

void sortMenu() {
	system("cls");
	int choice;
	gotoxy(5,5);printLine(25);
	gotoxy(5,6);printf("|       Sort Menu       |");
	gotoxy(5,7);printLine(25);
	gotoxy(5,8);printf("|1. Sort by Name"); gotoxy(29,8);printf("|");
	gotoxy(5,9);printf("|2. Sort by Average"); gotoxy(29,9);printf("|");
	gotoxy(5,10);printf("|0. Exit"); gotoxy(29,10);printf("|");
	gotoxy(5,11);printLine(25);
	gotoxy(5,12);printf("|Your choice: "); gotoxy(29,12);printf("|"); gotoxy(5,13);printLine(25); gotoxy(20, 12);scanf("%d", &choice);
	switch(choice) {
		case 1: 
			sortStudentByName();
			break;
		case 2:
			sortStudentByAverage();
			break;
		case 0:
			system("cls");
			menu();
			break;
		default: 
			system("cls");
			gotoxy(5, 14);printf("Enter 0 to 2 only! Please input again!");
			sortMenu();
			break;
	}
}

void searchMenu() {
	system("cls");
	int choice;
	gotoxy(5,5);printLine(25);
	gotoxy(5,6);printf("|      Search Menu      |");
	gotoxy(5,7);printLine(25);
	gotoxy(5,8);printf("|1. Search by Name"); gotoxy(29,8);printf("|");
	gotoxy(5,9);printf("|2. Search by Class"); gotoxy(29,9);printf("|");
	gotoxy(5,10);printf("|3. Search by Address"); gotoxy(29,10);printf("|");
	gotoxy(5,11);printf("|0. Exit"); gotoxy(29,11);printf("|");
	gotoxy(5,12);printLine(25);
	gotoxy(5,13);printf("|Your choice: "); gotoxy(29,13);printf("|"); gotoxy(5,14);printLine(25); gotoxy(20, 13);scanf("%d", &choice);
	switch(choice) {
		case 1: 
			searchStudentByName();
			break;
		case 2:
			searchStudentByClass();
			break;
		case 3:
			searchStudentByAddress();
			break;
		case 0:
			system("cls");
			menu();
			break;
		default: 
			system("cls");
			gotoxy(5, 14);printf("Enter 0 to 3 only! Please input again!");
			searchMenu();
			break;
	}
}

void Standardized(char *a) { //trung --> Trung
	int i; 
	if (a[strlen(a) - 1] == '\n')
		a[strlen(a) - 1] = '\0';
	if (a[0] <= 122 && a[0] >= 95)
		a[0] -= 32;
	for (i = 1; i < strlen(a); i++) {
		if (a[i] == 32 && a[i + 1] >= 95 && a[i + 1] <= 122)
			a[i + 1] -= 32;
		else if (a[i] <= 90 && a[i] >= 65 && a[i - 1] != 32)
			a[i] += 32;	
	}
}

float calculateAverage(Student s) {
	float total = 0;
	s.average = 0;
	for (int i = 0; i < 3; i++) {
		total += s.mark[i];
	}
	return s.average = total / 3.0;
}

int isChar(char c) {
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) 
		return 1;
	return 0;
}

int isDigit(char c) {
	if (c >= '0' && c <= '9') 
		return 1;
	return 0;
}

int checkEmail(char email[]) {
	if (!isChar(email[0])) {
		return 0;
	}
	
	int At = -1, Dot = -1;
	int length = strlen(email);
	
	
	for (int i = 0; i < length; i++) {
		if (email[i] == '@') 
			At = i;
		else if (email[i] == '.') 
			Dot = i;
	}
	
	if (At == -1 || Dot == -1) 
		return 0;
	
	if (At > Dot) 
		return 0;
		
	if (Dot >= (length - 1)) 
		return 0;
	return 1;
}

int countDigit(long int phone) {
	int count = 0;
	while (phone != 0) {
		phone = phone/10;
		count++;
	}
	return count + 1;
}

int checkDOB(int day, int month, int year) {
	if (year >= 1900 && year <= 9999) {
		if (month >= 1 && month <= 12) {
			if ((day >= 1 && day <= 31) && (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12))
				return 1;
			else if ((day >= 1 && day <= 30) && (month == 4 || month == 6 || month == 9 || month == 11))
				return 1;
			else if ((day >= 1 && day <= 28) && (month == 2))
				return 1;
			else if (day == 29 && month == 2 && (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)))
				return 1;
		}
	}
	return 0;
}

const char * rankedAcademic(float x) {
	if (x >= 9)
		return "Excellent";
	else if (x >= 8) 
		return "Good";
	else if (x >= 6.5)
		return "Fair";
	else 
		return "Poor";
}

void add() {
	system("cls");
	FILE *fp;
	Student s;
	fp = fopen("Database.txt", "a+");
	char another = 'y'; 
	while (another == 'y' || another == 'Y') {
		gotoxy(25,1);printf("Add student: ");
		gotoxy(5,2);printLine(52);
		gotoxy(5,3);printf("|Field			|Information		|");
		gotoxy(5,4);printLine(52);
		fflush(stdin);
		do {
			gotoxy(5,5);printf("|Enter id: ");  gotoxy(32,5);printf("|"); gotoxy(56,5);printf("|"); gotoxy(33,5);gets(s.id);
			if (checkId(s.id) == 1) {
				gotoxy(60,5);printf("Duplicate id! Input again!"); 
			}
			else {
				gotoxy(60,5);printf("Valid id                   "); 
			} 
		} while (checkId(s.id) == 1);
		gotoxy(5,6);printf("|Enter name: "); gotoxy(32,6);printf("|"); gotoxy(56,6);printf("|"); gotoxy(33,6);gets(s.name); Standardized(s.name); 
		gotoxy(5,7);printf("|Enter gender: "); gotoxy(32,7);printf("|"); gotoxy(56,7);printf("|"); gotoxy(33,7);gets(s.gender); Standardized(s.gender); // male //Male
		do {
			gotoxy(5,8);printf("|Enter dob: "); gotoxy(32,8);printf("|"); gotoxy(56,8);printf("|"); gotoxy(33,8);scanf("%d%d%d", &s.dob.day, &s.dob.month, &s.dob.year); fflush(stdin);
			if (checkDOB(s.dob.day, s.dob.month, s.dob.year) == 0) {
				gotoxy(60,8);printf("Invalid Date of birth! Input again!"); 
			} else {
				gotoxy(60,8);printf("Valid Date of birth!                 ");
			}
		} while (checkDOB(s.dob.day, s.dob.month, s.dob.year) == 0);
		gotoxy(5,9);printf("|Enter address: "); gotoxy(32,9);printf("|"); gotoxy(56,9);printf("|"); gotoxy(33,9);gets(s.address); Standardized(s.address);
		do {
			gotoxy(5,10);printf("|Enter email: "); gotoxy(32,10);printf("|"); gotoxy(56,10);printf("|"); gotoxy(33,10);gets(s.email);
			if (checkEmail(s.email) == 0) {
				gotoxy(60,10);printf("Invalid email! Input again!"); 
			} else {
				gotoxy(60,10);printf("Valid email!                 ");
			}
		} while (checkEmail(s.email) != 1);
		do {
			gotoxy(5,11);printf("|Enter phone: "); gotoxy(32,11);printf("|"); gotoxy(56,11);printf("|"); gotoxy(33,11);scanf("%ld", &s.phone); fflush(stdin);
			if (countDigit(s.phone) != 10) {
				gotoxy(60,11);printf("Invalid phone number! Input again!"); 
			} else {
				gotoxy(60,11);printf("Valid phone number                  "); 
			}
		} while (countDigit(s.phone) != 10);
		gotoxy(5,12);printf("|Enter class: "); gotoxy(32,12);printf("|"); gotoxy(56,12);printf("|"); gotoxy(33,12);gets(s.classs); strupr(s.classs); //MIS2021
		for (int i = 0, j = 13; i < 3; i++) {
			do {
				gotoxy(5,j+i); printf("|Enter subject %d: ", i + 1); gotoxy(32,j+i);printf("|"); gotoxy(56,j+i);printf("|"); gotoxy(33,j+i);scanf("%f", &s.mark[i]);
				if (s.mark[i] >= 0 && s.mark[i] <= 10) {
					gotoxy(60,j+i);printf("Valid mark!                ");
				} else {
					gotoxy(60,j+i);printf("Invalid mark! Input again");
				}
			} while (s.mark[i] < 0 || s.mark[i] > 10);
		}
		s.average = calculateAverage(s);
		strcpy(s.academic, rankedAcademic(s.average)); 
		gotoxy(5,16);printLine(52);
		fwrite(&s, sizeof(s), 1, fp);
	
		fflush(stdin);
		gotoxy(5,18);printf("Record saved");
		gotoxy(5,19);printf("Add another student? (Y/N)? ");
		fflush(stdin);
		another = getchar();
		system("cls");
	}
	fclose(fp);
	if (another == 'n' || another == 'N')  {
		system("cls");
		menu();
	}
}

void display() {
	system("cls");
	Student s;
	FILE *fp;
	int i = 10, j = 1;
	fp = fopen("Database.txt", "rb");
	if (fp == NULL) {
		printf("\nFile opening error");
		exit(1);
	}
	gotoxy(5,5);printLine(192);
	gotoxy(5,6);printf("|"); gotoxy(92,6);printf("LIST OF STUDENTS"); gotoxy(196,6);printf("|");
	gotoxy(5,7);printLine(192);
	gotoxy(5,8);printf("|%-5s|%-10s|%-20s|%-10s|%-22s|%-15s|%-20s|%-15s|%-10s|%10s|%10s|%10s|%10s|%10s|",
			"No","ID", "Name", "Gender", "Date of birth", "Address", "Email", "Phone", "Class", "Subject 1", "Subject 2", "Subject 3", "Average", "Academic");
	gotoxy(5,9);printLine(192);
	while(fread(&s, sizeof(s), 1, fp) == 1) {
		gotoxy(5,i);printf("|%-5d|%-10s|%-20s|%-10s|%-2d - %-2d - %-12d|%-15s|%-20s|(+84)%-10ld|%-10s|%10.1f|%10.1f|%10.1f|%10.1f|%10s|",
				j, s.id, s.name, s.gender, s.dob.day, s.dob.month, s.dob.year, s.address, s.email, s.phone, s.classs, s.mark[0], s.mark[1], s.mark[2], s.average, s.academic);
		j++;     
		i++;
	} 
	gotoxy(5,i);printLine(192);
	
	fclose(fp);
	gotoxy(5,i + 2);printf("Enter any key to back to menu!");
	getch();
	system("cls");
	menu();
}

void updateStudentById() {
	FILE *fp;
	int choice = 'y';
	Student s;
	char id[10];
	fp = fopen("Database.txt", "rb+");
	if (fp == NULL) {
		printf("\nNo Data in DB!");
		exit(1);
	} else {
		system("cls");
		while (choice == 'y' || choice == 'Y') {
			int flag = 0;
			gotoxy(5,3);printf("Modify student");
			fflush(stdin);
			gotoxy(5,5);printf("Enter the student's id to modify: ");
			gotoxy(40,5);gets(id);
			fseek(fp, SEEK_SET, 0);
			while (fread(&s, sizeof(s), 1, fp) == 1) {
				if (strcmp(id, s.id) == 0) {
					fflush(stdin);
					gotoxy(5,7);printf("Student found!");
					gotoxy(5,8);printLine(186);
					gotoxy(5,9);printf("|%-10s|%-20s|%-10s|%-22s|%-15s|%-20s|%-15s|%-10s|%10s|%10s|%10s|%10s|%10s|",
							"ID", "Name", "Gender", "Date of birth", "Address", "Email", "Phone", "Class", "Subject 1", "Subject 2", "Subject 3", "Average", "Academic");
					gotoxy(5,10);printLine(186);
					gotoxy(5,11);printf("|%-10s|%-20s|%-10s|%-2d - %-2d - %-12d|%-15s|%-20s|(+84)%-10ld|%-10s|%10.1f|%10.1f|%10.1f|%10.1f|%10s|",
								s.id, s.name, s.gender, s.dob.day, s.dob.month, s.dob.year, s.address, s.email, s.phone, s.classs, s.mark[0], s.mark[1], s.mark[2], s.average, s.academic);
					gotoxy(5,12);printLine(186);
					do {
						gotoxy(5,13);printLine(35);
						gotoxy(5,14);printf("|Choose what you want to update   |");
						gotoxy(5,15);printLine(35);
						gotoxy(5, 16);printf("|1.Name"); gotoxy(39,16);printf("|"); 
						gotoxy(5, 17);printf("|2.Gender"); gotoxy(39,17);printf("|"); 
						gotoxy(5, 18);printf("|3.Date of birth"); gotoxy(39,18);printf("|"); 
						gotoxy(5, 19);printf("|4.Address"); gotoxy(39,19);printf("|"); 
						gotoxy(5, 20);printf("|5.Email"); gotoxy(39,20);printf("|"); 
						gotoxy(5, 21);printf("|6.Phone"); gotoxy(39,21);printf("|"); 
						gotoxy(5, 22);printf("|7.Class"); gotoxy(39,22);printf("|"); 
						gotoxy(5, 23);printf("|8.Mark of subject 1"); gotoxy(39,23);printf("|"); 
						gotoxy(5, 24);printf("|9.Mark of subject 2"); gotoxy(39,24);printf("|"); 
						gotoxy(5, 25);printf("|10.Mark of subject 3"); gotoxy(39,25);printf("|"); 
						gotoxy(5, 26);printf("|11.Update all"); gotoxy(39,26);printf("|"); 
						gotoxy(5, 27);printf("|0.Exit"); gotoxy(39,27);printf("|"); 
						gotoxy(5,28);printLine(35);
						gotoxy(5,29);printf("|Your choice:"); gotoxy(39,29);printf("|"); gotoxy(5,30);printLine(35); gotoxy(20,29);scanf("%d", &choice);
						switch(choice) {
							case 1: 
								gotoxy(60,13);printf("Modify %s's name", s.id);
								fflush(stdin);
								gotoxy(60,14);printf("Enter name: "); gotoxy(74,14);gets(s.name); Standardized(s.name); gotoxy(60,15);printf("Name is modified"); 
								fseek(fp, -(long)sizeof(s), SEEK_CUR); 
								fwrite(&s, sizeof(s), 1, fp);
								flag = 1; 
								break;
							case 2:
								gotoxy(60,17);printf("Modify %s's gender", s.id);
								fflush(stdin);
								gotoxy(60,18);printf("Enter gender: "); gotoxy(75,18);gets(s.gender); Standardized(s.gender); gotoxy(60,19);printf("Gender is modified");
								fseek(fp, -(long)sizeof(s), SEEK_CUR);
								fwrite(&s, sizeof(s), 1, fp);
								flag = 1;
								break;
							case 3: 
								gotoxy(60,21);printf("Modify %s's date of birth", s.id);
								do {
									gotoxy(60,22);printf("Enter dob: "); 
									gotoxy(73,22);scanf("%d%d%d", &s.dob.day, &s.dob.month, &s.dob.year); 
									if (checkDOB(s.dob.day, s.dob.month, s.dob.year) == 0) {
										gotoxy(95,22);printf("|Invalid Date of birth! Input again!"); 
									} else {
										gotoxy(95,22);printf("|Valid Date of birth!                 ");
										gotoxy(60,23);printf("DOB is modified");
									}
								} while (checkDOB(s.dob.day, s.dob.month, s.dob.year) == 0);
								fseek(fp, -(long)sizeof(s), SEEK_CUR);
								fwrite(&s, sizeof(s), 1, fp);
								flag = 1;
								break;
							case 4:
								gotoxy(60,25);printf("Modify %s's address", s.id);
								fflush(stdin);
								gotoxy(60,26);printf("Enter address: "); gotoxy(76,26);gets(s.address); Standardized(s.address); gotoxy(60,27);printf("Address is modified");
								fseek(fp, -(long)sizeof(s), SEEK_CUR);
								fwrite(&s, sizeof(s), 1, fp);
								flag = 1;
								break;
							case 5: 
								gotoxy(60,29);printf("Modify %s's email", s.id);
								fflush(stdin);
								do {
									gotoxy(60,30);printf("Enter email: "); gotoxy(73,30);gets(s.email); 
									if (checkEmail(s.email) == 0) {
										gotoxy(95,30);printf("|Invalid email! Input again!"); 
									} else {
										gotoxy(95,30);printf("|Valid email!                 ");
										gotoxy(60,31);printf("Email is modified");
									}
								} while (checkEmail(s.email) != 1);
								fseek(fp, -(long)sizeof(s), SEEK_CUR);
								fwrite(&s, sizeof(s), 1, fp);
								flag = 1;
								break;
							case 6:
								gotoxy(60,33);printf("Modify %s's phone", s.id);
								do {
									gotoxy(60,34);printf("Enter phone: "); 
									gotoxy(75,34);scanf("%ld", &s.phone); 
									if (countDigit(s.phone) != 10) {
										gotoxy(95,34);printf("|Invalid phone number! Input again!"); 
									} else {
										gotoxy(95,34);printf("|Valid phone number                  "); 
										gotoxy(60,35);printf("Phone is modified");
									}
								} while (countDigit(s.phone) != 10);
								fseek(fp, -(long)sizeof(s), SEEK_CUR);
								fwrite(&s, sizeof(s), 1, fp);
								flag = 1;
								break;
							case 7:
								gotoxy(60,37);printf("Modify %s's class", s.id);
								fflush(stdin);
								gotoxy(60,38);printf("Enter class: "); gotoxy(75,38);gets(s.classs); strupr(s.classs); gotoxy(60,39);printf("Class is modified");
								fseek(fp, -(long)sizeof(s), SEEK_CUR);
								fwrite(&s, sizeof(s), 1, fp);
								flag = 1;
								break;
							case 8: 
								gotoxy(60,41);printf("Modify %s's subject 1", s.id);
								do {
									gotoxy(60,42);printf("Enter subject 1: "); gotoxy(78,42);scanf("%f", &s.mark[0]); 
									if (s.mark[0] >= 0 && s.mark[0] <= 10) {
										gotoxy(85,42);printf("|Valid mark!                ");
										gotoxy(60,43);printf("Subject 1 is modified");
									} else {
										gotoxy(85,42);printf("|Invalid mark! Input again");
									}
								} while (s.mark[0] < 0 || s.mark[0] > 10);
								fseek(fp, -(long)sizeof(s), SEEK_CUR);
								s.average = calculateAverage(s);
								strcpy(s.academic, rankedAcademic(s.average));
								fwrite(&s, sizeof(s), 1, fp);
								flag = 1;
								break;
							case 9:
								gotoxy(60,45);printf("Modify %s's subject 2", s.id);
								do {
									gotoxy(60,46);printf("Enter subject 2: "); gotoxy(78,46);scanf("%f", &s.mark[1]); 
									if (s.mark[1] >= 0 && s.mark[1] <= 10) {
										gotoxy(85,46);printf("|Valid mark!                ");
										gotoxy(60,47);printf("Subject 2 is modified");
									} else {
										gotoxy(85,46);printf("|Invalid mark! Input again");
									}
								} while (s.mark[1] < 0 || s.mark[1] > 10);
								fseek(fp, -(long)sizeof(s), SEEK_CUR);
								s.average = calculateAverage(s);
								strcpy(s.academic, rankedAcademic(s.average));
								fwrite(&s, sizeof(s), 1, fp);
								flag = 1;
								break;
							case 10: 
								gotoxy(60,49);printf("Modify %s's subject 3", s.id);
								do {
									gotoxy(60,50);printf("Enter subject 3: "); gotoxy(78,50);scanf("%f", &s.mark[2]); 
									if (s.mark[2] >= 0 && s.mark[2] <= 10) {
										gotoxy(85,50);printf("|Valid mark!                ");
										gotoxy(60,51);printf("Subject 3 is modified");
									} else {
										gotoxy(85,50);printf("|Invalid mark! Input again");
									}
								} while (s.mark[2] < 0 || s.mark[2] > 10);
								fseek(fp, -(long)sizeof(s), SEEK_CUR);
								s.average = calculateAverage(s);
								strcpy(s.academic, rankedAcademic(s.average));
								fwrite(&s, sizeof(s), 1, fp);
								flag = 1;
								break;
							case 11:
								gotoxy(140,13);printf("Modify all field");
								fflush(stdin);
								gotoxy(140,14);printf("Enter name: "); gotoxy(155,14);gets(s.name); Standardized(s.name);
								gotoxy(140,15);printf("Enter gender: "); gotoxy(156,15);gets(s.gender); Standardized(s.gender);
								do {
									gotoxy(140,16);printf("Enter dob: "); gotoxy(152,16);scanf("%d%d%d", &s.dob.day, &s.dob.month, &s.dob.year); fflush(stdin);
									if (checkDOB(s.dob.day, s.dob.month, s.dob.year) == 0) {
										gotoxy(175,16);printf("|Invalid Date of birth! Input again!"); 
									} else {
										gotoxy(175,16);printf("|Valid Date of birth!                 ");
									}
								} while (checkDOB(s.dob.day, s.dob.month, s.dob.year) == 0);
								gotoxy(140,17);printf("Enter address: "); gotoxy(156,17);gets(s.address); Standardized(s.address);
								do {
									gotoxy(140,18);printf("Enter email: "); gotoxy(155,18);gets(s.email);
									if (checkEmail(s.email) == 0) {
										gotoxy(175,18);printf("|Invalid email! Input again!"); 
									} else {
										gotoxy(175,18);printf("|Valid email!                 ");
									}
								} while (checkEmail(s.email) != 1);
								
								do {
									gotoxy(140,19);printf("Enter phone: "); gotoxy(155,19);scanf("%ld", &s.phone);fflush(stdin);
									if (countDigit(s.phone) != 10) {
										gotoxy(175,19);printf("|Invalid phone number! Input again!"); 
									} else {
										gotoxy(175,19);printf("|Valid phone number                  "); 
									}
								} while (countDigit(s.phone) != 10);
								gotoxy(140,20);printf("Enter class: "); gotoxy(155,20);gets(s.classs); strupr(s.classs);
								for (int i = 0, j = 21; i < 3; i++) {
									do {
										gotoxy(140,j + i);printf("Enter subject %d: ", i + 1); gotoxy(158,j + i);scanf("%f", &s.mark[i]);
										if (s.mark[i] >= 0 && s.mark[i] <= 10) {
											gotoxy(175,j+i);printf("|Valid mark!                ");
										} else {
											gotoxy(175,j+i);printf("|Invalid mark! Input again");
										}
									} while (s.mark[i] < 0 || s.mark[i] > 10);
								}
								gotoxy(140,25);printf("Modify successfully!");
								fseek(fp, -(long)sizeof(s), SEEK_CUR);
								s.average = calculateAverage(s);
								strcpy(s.academic, rankedAcademic(s.average));
								fwrite(&s, sizeof(s), 1, fp);
								flag = 1;
								break;
							case 0:
								flag = 1;
								break;
							default:
								gotoxy(5,32);printf("Please input from 1 to 11 to update!");
								break;
						}
					} while (choice != 0);
					break;
				}
				fflush(stdin);
			}
			if (flag == 1) {
				gotoxy(5,35);printf("Do you want to modify another student? (Y/N)?");
				fflush(stdin);
				choice = getchar();
				system("cls");
			} else {
				gotoxy(5,7);printf("No record Found in database");
				gotoxy(5,8);printf("Do you want to modify another student? (Y/N)?");
				fflush(stdin);
				choice = getchar();
				system("cls");
			}
		}
	}
	fclose(fp);
	if (choice == 'n' || choice == 'N') {
		system("cls");
		menu();
	}
}

void deleteStudentById() {
	Student s;
	FILE *fp, *temp;
	int flag = 0;
	char id[10];
	fp = fopen("Database.txt", "rb");
	if (fp == NULL) {
		gotoxy(5,5);printf("No Data in DB");
		gotoxy(5,6);printf("Press any key...");
		getch();
		system("cls");
		menu();
	} 
	temp = fopen("temp.txt", "wb+");
	if (temp == NULL) {
		gotoxy(5,5);printf("Opening database error");
		gotoxy(5,6);printf("Press any key...");
		getch(); //conio.h
		system("cls"); //stdlib.h
		menu();
	} 
	system("cls");
	gotoxy(6,6);printf("Enter the student's id: "); 
	fflush(stdin);
	gotoxy(30,6);gets(id);
	while (fread(&s, sizeof(s), 1, fp) == 1) {
		if (strcmp(id, s.id) != 0) 
			fwrite(&s, sizeof(s), 1, temp);
		if (strcmp(id, s.id) == 0) 
			flag = 1;
	}
	fclose(fp);
	fclose(temp);
	if (flag != 1) {
		gotoxy(8,8);printf("Cannot delete!");
		remove("temp.txt"); //stdio.h
		gotoxy(8,9);printf("Press any key...");
		getchar();
		system("cls");
		menu();
	} else {
		remove("Database.txt");
		rename("temp.txt", "Database.txt");
		gotoxy(8,8);printf("Deleted Successfully");
		gotoxy(8,9);printf("Press any key...");
		getchar();
		system("cls");
		menu();
	}
}

int search(char name_input[], char name_db[]) {
	int i, j, check;
	int name_input_length = strlen(name_input);
	int name_db_length = strlen(name_db);
	for (i = 0; i < name_db_length - name_input_length + 1; i++) 
	{
		check = 0;
		for (j = 0; j < name_input_length; j++)
			if ((name_input[j] != name_db[i + j]) && (name_input[j] + 32 != name_db[i + j]) && (name_input[j] != name_db[i + j] + 32))
			{
				check = 1;
				break;
			}
		if (check == 0)
			return 0;
	}
	return 1;
}

void searchStudentByName() {
	Student s;
	FILE *fp;
	char name[50];
	char choice = 'y';
	fp = fopen("Database.txt", "rb");
	if (fp == NULL) {
		printf("\nERROR");
		exit(1);
	}
	while (choice == 'y' || choice == 'Y') {
		system("cls");
		int count = 0, i = 10, j = 1;
		int isFound = 0;
		gotoxy(5,5);printf("Enter the name of the person want to search: ");
		fflush(stdin);
		gotoxy(52,5);gets(name);
		gotoxy(8,7);printLine(192);
		gotoxy(8,8);printf("|%-5s|%-10s|%-20s|%-10s|%-22s|%-15s|%-20s|%-15s|%-10s|%10s|%10s|%10s|%10s|%10s|",
				"No", "ID", "Name", "Gender", "Date of birth", "Address", "Email", "Phone", "Class", "Subject 1", "Subject 2", "Subject 3", "Average", "Academic");
		gotoxy(8,9);printLine(192);
		fseek(fp, SEEK_SET, 0); 
		while(fread(&s, sizeof(s), 1, fp) == 1) {
			if (search(name, s.name) == 0) {
				gotoxy(8,i);printf("|%-5d|%-10s|%-20s|%-10s|%-2d - %-2d - %-12d|%-15s|%-20s|(+84)%-10ld|%-10s|%10.1f|%10.1f|%10.1f|%10.1f|%10s|",
						j, s.id, s.name, s.gender, s.dob.day, s.dob.month, s.dob.year, s.address, s.email, s.phone, s.classs, s.mark[0], s.mark[1], s.mark[2], s.average, s.academic);
				isFound = 1;
				j++;
				i++;
				count++;
			}
		}
		if (isFound == 0) {
			gotoxy(8, i + 1);printf("Sorry, no record FOUND in the database");
			gotoxy(8, i + 2); printf("Do you want to search other names? (Y/N)?");
			fflush(stdin);
			choice = getchar();
		} else {
			printf("\n");
			gotoxy(8,i);printLine(192);
			gotoxy(8, i + 2);printf("FOUND %d record(s) in the database", count);
			gotoxy(8, i + 3); printf("Do you want to search other names? (Y/N)?");
			fflush(stdin);
			choice = getchar();
		}
	}
	fclose(fp);
	if (choice == 'n' || choice == 'N') {
		system("cls");
		searchMenu();
	}
}

void searchStudentByClass() {
	Student s;
	FILE *fp;
	char classs[10];
	char choice = 'y';
	fp = fopen("Database.txt", "rb");
	if (fp == NULL) {
		printf("\nERROR");
		exit(1);
	}
	while (choice == 'y' || choice == 'Y') {
		system("cls");
		int count = 0, i = 10, j = 1;
		int isFound = 0;
		gotoxy(5,5);printf("Enter the class to search: ");
		fflush(stdin);
		gotoxy(33,5);gets(classs);
		gotoxy(8,7);printLine(192);
		gotoxy(8,8);printf("|%-5s|%-10s|%-20s|%-10s|%-22s|%-15s|%-20s|%-15s|%-10s|%10s|%10s|%10s|%10s|%10s|",
				"No", "ID", "Name", "Gender", "Date of birth", "Address", "Email", "Phone", "Class", "Subject 1", "Subject 2", "Subject 3", "Average", "Academic");
		gotoxy(8,9);printLine(192);
		fseek(fp, SEEK_SET, 0); 
		while(fread(&s, sizeof(s), 1, fp) == 1) {
			if (search(classs, s.classs) == 0) {
				gotoxy(8,i);printf("|%-5d|%-10s|%-20s|%-10s|%-2d - %-2d - %-12d|%-15s|%-20s|(+84)%-10ld|%-10s|%10.1f|%10.1f|%10.1f|%10.1f|%10s|",
						j, s.id, s.name, s.gender, s.dob.day, s.dob.month, s.dob.year, s.address, s.email, s.phone, s.classs, s.mark[0], s.mark[1], s.mark[2], s.average, s.academic);
				isFound = 1;
				j++;
				i++;
				count++;
			}
		}
		if (isFound == 0) {
			gotoxy(8, i + 1);printf("Sorry, no record FOUND in the database");
			gotoxy(8, i + 2); printf("Do you want to search other names? (Y/N)?");
			fflush(stdin);
			choice = getchar();
		} else {
			printf("\n");
			gotoxy(8,i);printLine(192);
			gotoxy(8, i + 2);printf("FOUND %d record(s) in the database", count);
			gotoxy(8, i + 3); printf("Do you want to search other names? (Y/N)?");
			fflush(stdin);
			choice = getchar();
		}
	}
	fclose(fp);
	if (choice == 'n' || choice == 'N') {
		system("cls");
		searchMenu();
	}
}

void searchStudentByAddress() {
	Student s;
	FILE *fp;
	char address[50];
	char choice = 'y';
	fp = fopen("Database.txt", "rb");
	if (fp == NULL) {
		printf("\nERROR");
		exit(1);
	}
	while (choice == 'y' || choice == 'Y') {
		system("cls");
		int count = 0, i = 10, j = 1;
		int isFound = 0;
		gotoxy(5,5);printf("Enter the address to search: ");
		fflush(stdin);
		gotoxy(34,5);gets(address);
		gotoxy(8,7);printLine(192);
		gotoxy(8,8);printf("|%-5s|%-10s|%-20s|%-10s|%-22s|%-15s|%-20s|%-15s|%-10s|%10s|%10s|%10s|%10s|%10s|",
				"No", "ID", "Name", "Gender", "Date of birth", "Address", "Email", "Phone", "Class", "Subject 1", "Subject 2", "Subject 3", "Average", "Academic");
		gotoxy(8,9);printLine(192);
		fseek(fp, SEEK_SET, 0);
		while(fread(&s, sizeof(s), 1, fp) == 1) {
			if (search(address, s.address) == 0) {
				gotoxy(8,i);printf("|%-5d|%-10s|%-20s|%-10s|%-2d - %-2d - %-12d|%-15s|%-20s|(+84)%-10ld|%-10s|%10.1f|%10.1f|%10.1f|%10.1f|%10s|",
						j, s.id, s.name, s.gender, s.dob.day, s.dob.month, s.dob.year, s.address, s.email, s.phone, s.classs, s.mark[0], s.mark[1], s.mark[2], s.average, s.academic);
				isFound = 1;
				j++;
				i++;
				count++;
			}
		}
		if (isFound == 0) {
			gotoxy(8, i + 1);printf("Sorry, no record FOUND in the database");
			gotoxy(8, i + 2); printf("Do you want to search other names? (Y/N)?");
			fflush(stdin);
			choice = getchar();
		} else {
			printf("\n");
			gotoxy(8,i);printLine(192);
			gotoxy(8, i + 2);printf("FOUND %d record(s) in the database", count);
			gotoxy(8, i + 3); printf("Do you want to search other names? (Y/N)?");
			fflush(stdin);
			choice = getchar();
		}
	}
	fclose(fp);
	if (choice == 'n' || choice == 'N') {
		system("cls");
		searchMenu();
	}
}

void separateName(char fullName[], char firstName[]) {
	char lastName[20];
	int i, j, n;
	n = strlen(fullName);
	for (i = n - 1; i > 0; i--)
		if (fullName[i] == ' ')
	    	break;
	for (j = 0; j < i; j++) {
		lastName[j] = fullName[j];
	    lastName[i] = '\0';
	}
	for (j = i + 1; j < n; j++)
	    firstName[j - i - 1] = fullName[j];
	firstName[n - i - 1] = '\0';
}

void sortStudentByName() {
	Student *s, s1;
	FILE *fp;
	int i, j = 1;
	char firstName1[20], firstName2[20];
	fp = fopen("Database.txt", "rb");
	fseek(fp, 0, SEEK_END);
	int n = ftell(fp) / sizeof(Student);
	s = (Student*)calloc(n, sizeof(Student));
	
	rewind(fp);
	if (fp == NULL) {
		printf("\nERROR");
	} else {
		for (int i = 0; i < n; i++) {
			fread(&s[i], sizeof(Student), 1, fp);
		}
		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				separateName(s[i].name, firstName1);
				separateName(s[j].name, firstName2);
				if (strcmp(firstName1, firstName2) > 0) {
					s1 = s[i];
					s[i] = s[j];
					s[j] = s1;
				}
			}
		}
		system("cls");
		gotoxy(5,5);printLine(192);
		gotoxy(5,6);printf("|"); gotoxy(90, 6); printf("LIST OF STUDENTS AFTER SORTING"); gotoxy(196,6);printf("|");
		gotoxy(5,7);printLine(192);
		gotoxy(5,8);printf("|%-5s|%-10s|%-20s|%-10s|%-22s|%-15s|%-20s|%-15s|%-10s|%10s|%10s|%10s|%10s|%10s|",
				"No", "ID", "Name", "Gender", "Date of birth", "Address", "Email", "Phone", "Class", "Subject 1", "Subject 2", "Subject 3", "Average", "Academic");
		gotoxy(5,9);printLine(192);
		for (i = 0; i < n; i++) {
			gotoxy(5, i + 10);printf("|%-5d|%-10s|%-20s|%-10s|%-2d - %-2d - %-12d|%-15s|%-20s|(+84)%-10ld|%-10s|%10.1f|%10.1f|%10.1f|%10.1f|%10s|",
				j, s[i].id, s[i].name, s[i].gender, s[i].dob.day, s[i].dob.month, s[i].dob.year, s[i].address, s[i].email, s[i].phone, s[i].classs, s[i].mark[0], s[i].mark[1], s[i].mark[2], s[i].average, s[i].academic);
			j++;
		}
		gotoxy(5, i + 10);printLine(192);
		
	} 
	free(s);
	fclose(fp);
	gotoxy(5, i + 12);printf("Press any key...");
	getch();
	system("cls");
	sortMenu();
}

void sortStudentByAverage() {
	Student *s, s1;
	FILE *fp;
	int i, j = 1;
	fp = fopen("Database.txt", "rb");
	fseek(fp, 0, SEEK_END);
	int n = ftell(fp) / sizeof(Student);
	s = (Student*)calloc(n, sizeof(Student));
	
	rewind(fp);
	if (fp == NULL) {
		printf("\nERROR");
	} else {
		for (int i = 0; i < n; i++) {
			fread(&s[i], sizeof(Student), 1, fp);
		}
		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				if (s[i].average > s[j].average) {
					s1 = s[i];
					s[i] = s[j];
					s[j] = s1;
				}
			}
		}
		system("cls");
		gotoxy(5,5);printLine(192);
		gotoxy(5,6);printf("|"); gotoxy(90, 6); printf("LIST OF STUDENTS AFTER SORTING"); gotoxy(196,6);printf("|");
		gotoxy(5,7);printLine(192);
		gotoxy(5,8);printf("|%-5s|%-10s|%-20s|%-10s|%-22s|%-15s|%-20s|%-15s|%-10s|%10s|%10s|%10s|%10s|%10s|",
				"No", "ID", "Name", "Gender", "Date of birth", "Address", "Email", "Phone", "Class", "Subject 1", "Subject 2", "Subject 3", "Average", "Academic");
		gotoxy(5,9);printLine(192);
		for (i = 0; i < n; i++) {
			gotoxy(5, i + 10);printf("|%-5d|%-10s|%-20s|%-10s|%-2d - %-2d - %-12d|%-15s|%-20s|(+84)%-10ld|%-10s|%10.1f|%10.1f|%10.1f|%10.1f|%10s|",
				j, s[i].id, s[i].name, s[i].gender, s[i].dob.day, s[i].dob.month, s[i].dob.year, s[i].address, s[i].email, s[i].phone, s[i].classs, s[i].mark[0], s[i].mark[1], s[i].mark[2], s[i].average, s[i].academic);
			j++;
		}
		gotoxy(5, i + 10);printLine(192);
		
	} 
	free(s);
	fclose(fp);
	gotoxy(5, i + 12);printf("Press any key...");
	getch();
	system("cls");
	sortMenu();
}







