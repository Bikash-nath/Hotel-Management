#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<dos.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>

struct Hotel {
	int room_no;
	int Capacity;
	char Name[4][30];
	char Gender[4][12];
	int Age[4];
	char address[50];
	char phone[11];
	int Period;
	int Date_in[3];
	int Time_in[2];
	int Amount;
	int Payment;
	int Room_Price;
	int Food_Price;
	int laundry;
	int Gym;
} H;

void Getdata(int , int , int );		//to input customer record
void Putdata();			    //to display customer Record
void Get_Date_Time();	    //to get present date
void Put_date();			//to display Check out date
void Calc_Amount();			//to calculate Customer Bill amount

void Getdata(int r, int C, int code) {
	char Gnd, Ch, ch1;
	system("cls");
	H.room_no = r;
	H.Capacity = C;
	printf("\n Booking %d Members in Room No. %d\n", C, r);

	for (int i = 0; i < C; i++) {
		printf("\n Enter details of Guest %d", i + 1);
		while ((getchar()) != '\n');
		printf("\n Name : ");
		gets(H.Name[i]);

		while (1) {
			printf(" Gender (M/F/T): ");
			scanf("%c", &Gnd);

			if (Gnd == 'M' || Gnd == 'm') {
				strcpy(H.Gender[i], "Male");
				break;
			} else if (Gnd == 'F' || Gnd == 'f') {
				strcpy(H.Gender[i], "Female");
				break;
			}

			else if (Gnd == 'T' || Gnd == 't') {
				strcpy(H.Gender[i], "Transgender");
				break;
			} else
				printf(" Incorrect option\n");
		}
		printf(" Age: ");
		scanf("%d", &H.Age[i]);

		if (i == 0) {
			printf("\n Enter Laundry Frequency (Max. 4 days): ");
			scanf("%d", &H.laundry);
			printf("\n Do you want Fitness Center (Gym) accesibility (Y/N)");
			while ((getchar()) != '\n');
			scanf("%c", &ch1);
			if (ch1 == 'Y' || ch1 == 'y') {
				printf("\n Enter No. of days you want gym accessibility (Total Days of stay is %d): ", H.Period);
				scanf("%d", &H.Gym);
			} else
				H.Gym = 0;
			Calc_Amount();

			do {
				printf("\n Total Amount Due is %d", H.Amount);
				printf("\n Do Guest 1 want to Pay in Advance (Y/N)");
				while ((getchar()) != '\n');
				scanf("%c", &Ch);
				if (Ch == 'Y' || Ch == 'y') {
					printf("\n Enter Advance Payment: ");
					scanf("%d", &H.Payment);
				} else if (Ch == 'N' || Ch == 'n') {
					H.Payment = 0;
					printf("\n Total Payable Amount is: %d\n", H.Amount - H.Payment);
					break;
				} else {
					printf("\n Wrong Choice!\n Please Enter correct option.");
					Ch = 'A';
				}
			} while (Ch == 'A');
		}

		if (i == 0 && code == 0) {
			printf("\n Address: ");
			while ((getchar()) != '\n');
			gets(H.address);
			printf(" Phone No: ");
			gets(H.phone);
		} else {
			strcpy(H.address, "\0");
			strcpy(H.phone, "\0");
		}

	}

	if (C < 4) {
		for (int i = C; i < 4; i++) {
			strcpy(H.Name[i], "\0");
			strcpy(H.Gender[i], "\0");
			H.Age[i] = 0;
		}
	}

	Get_Date_Time();

}

void Calc_Amount() {
	int r = H.room_no;
	if (r <= 20)
		H.Room_Price = H.Period * 3000;
	else if (r > 20 && r <= 35)
		H.Room_Price = H.Period * 2000;
	else if (r > 35 && r <= 55)
		H.Room_Price = H.Period * 2700;
	else if (r > 55 && r <= 75)
		H.Room_Price = H.Period * 3600;
	else if (r > 75 && r <= 90)
		H.Room_Price = H.Period * 1000;
	else if (r > 90 && r <= 100)
		H.Room_Price = H.Period * 1800;

	H.Amount = 0;
	H.Amount += H.Room_Price;
	H.Amount += (H.Period / H.laundry) * 500;
	H.Amount += H.Gym * 1000;
	H.Food_Price = 0;
}

void Putdata() {

	system("cls");
	printf("\n  Customer Details");
	printf("\n  ****************\n");
	printf("\n Room no: ");
	printf("%d", H.room_no);
	printf("\n No. Guests in Room Booked: ");
	printf("%d", H.Capacity);

	for (int i = 0; i < H.Capacity; i++) {
		printf("\n\n Details of Guest %d", i + 1);
		printf("\n  Name: ");
		puts(H.Name[i]);
		printf("  Gender: ");
		printf(" %s", H.Gender[i]);
		printf("\n  Age:  ");
		printf("%d", H.Age[i]);

		if (strcmp(H.address, "\0") != 0) {
			printf("\n  Address: ");
			puts(H.address);
			printf("  Phone no: ");
			printf("%s", H.phone);
		}
	}
	printf("\n\n Duration(days): %d", H.Period);
	printf("\n Laundry frequency: %d", H.laundry);
	printf("\n No. of days of Gym accessibility: %d", H.Gym);
	printf("\n Food Amount Payable = %d", H.Food_Price);
	printf("\n\n Total Expense of Room is: %d", H.Amount);
	printf("\n Total Amount Payable = %d", H.Amount - H.Payment);
	printf("\n\n Check in date is : ");
	int i;

	for (i = 0; i < 3; i++) {
		printf("%d", H.Date_in[i]);
		if (i < 2)
			printf("/");
	}
	printf("\n Check in Time is : ");

	for (i = 0; i < 2; i++) {
		printf("%d", H.Time_in[i]);
		if (i < 1)
			printf(":");
	}
	Put_date();
}


void Put_date() {		//To Calculate & Display Check-out date
	int Date_out[3], i, flag = 0, N;
	int Month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	for (i = 0; i < 3; i++)
		Date_out[i] = H.Date_in[i];

	if ((H.Date_in[2] % 4 == 0) && (H.Date_in[2] % 100 != 0 || H.Date_in[3] % 400 == 0))	//to check leap year or not.
		Month[1] = 29;

	int T_Days = Month[H.Date_in[1] - 1];
	int Out_day = H.Date_in[0] + H.Period;

	if (Out_day > (T_Days + Month[H.Date_in[1]] + Month[H.Date_in[1] + 1])) {
		Date_out[0] = Out_day - (T_Days + Month[H.Date_in[1]] + Month[H.Date_in[1] + 1]);
		if (Date_out[1] + 3 > 12) {
			Date_out[1] -= 9;
			Date_out[2] += 1;
		} else
			Date_out[1] += 3;
	}


	else if (Out_day > (T_Days + Month[H.Date_in[1]])) {
		Date_out[0] = Out_day - (T_Days + Month[H.Date_in[1]]);
		if (Date_out[1] + 2 > 12) {
			Date_out[1] -= 10;
			Date_out[2] += 1;
		} else
			Date_out[1] += 2;
	} else if (Out_day > T_Days) {
		Date_out[0] = Out_day - T_Days;
		if (Date_out[1] + 1 > 12) {
			Date_out[1] -= 11;
			Date_out[2] += 1;
		} else
			Date_out[1] += 1;
	} else
		Date_out[0] = Out_day;

	printf("\n Check out date is : ");

	for (i = 0; i < 3; i++) {
		printf("%d", Date_out[i]);
		if (i < 2)
			printf("/");
	}
}



void Get_Date_Time() {     //to get present date
	SYSTEMTIME t; // Declare SYSTEMTIME struct
	GetLocalTime(&t); // Fill out the struct so that it can be used

	H.Date_in[0] = t.wDay;
	H.Date_in[1] = t.wMonth;
	H.Date_in[2] = t.wYear;

	H.Time_in[0] = t.wHour;
	H.Time_in[1] = t.wMinute;
}



void delay(int time) {
	clock_t goal = time + clock();
	while (goal > clock());
}



void Welcome_screen();	//to display Welcome screen
int login();
int  Check(int);       //to check room status
void Add();           //to book a room
int Room_opt(int , int);
void FindCombinations(int arr[], int , int , int );
void Display();       //to display the customer Record
void Room_stat();     //to display alloted rooms
int Booking_stat(int []);
void Room_Features();
void Modify_menu();
void Modify_data(int );
void Retain();
void Food_order(int );
void Laundry(int );
void Check_out();
void Exit();


int main() {
	int choice = 0, check;
	Welcome_screen();
	system("cls");
	check = login();

	if (check == 1) {
		while (choice != 7) {
			system("COLOR E1");
			system("cls");
			printf("\n\n\t\t\t\t\t       ************************\n");
			printf("\t\t\t\t\t        *THE IMPERIAL PALACE *");
			printf("\n\t\t\t\t\t       ************************\n\n\n");
			printf("\n\n\t\t\t\t\t\t *************");
			printf("\n\t\t\t\t\t\t * MAIN MENU *");
			printf("\n\t\t\t\t\t\t *************\n\n");
			printf("\n\t\t\t\t\t\t1. Book A Room\n");
			printf("\n\t\t\t\t\t\t2. Display Room Record\n");
			printf("\n\t\t\t\t\t\t3. Rooms Status\n");
			printf("\n\t\t\t\t\t\t4. Room Features\n");
			printf("\n\t\t\t\t\t\t5. Modify Room Record\n");
			printf("\n\t\t\t\t\t\t6. Check-Out\n");
			printf("\n\t\t\t\t\t\t7. Exit");
			printf("\n\n\n\t\t\t\t\t\tEnter Your Choice: ");
			scanf("%d", &choice);

			switch (choice) {
			case 1: Add();
				break;
			case 2: Display();
				break;
			case 3: Room_stat(1);
				break;
			case 4: Room_Features();
				break;
			case 5: Modify_menu();
				break;
			case 6: Check_out();
				break;
			case 7: Exit();
				break;
			default: {
				printf("\n\n\t\t\tWrong choice!!!");
				printf("\n\t\t\tPress any key to continue!!");
				getch();
			}
			}
		}
	} else
		Exit();
	return 0;
}


void Welcome_screen() {

	system("COLOR A1 ");
	char load[1][20] = {"LOADING...."};

	for (int i = 0; i < 2; i++) {
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t    ");
		for (int j = 0; load[i][j] != '\0'; j++) {
			delay(100);
			printf("%c", load[i][j]);
		}
	}

	delay(50);
	system("cls");
	printf("\n\t\t\t\t\t*");

	for (int str = 1; str < 34; str++) {
		delay(50);
		printf("*");
	}
	char prjct[30] = {"* HOTEL MANAGEMENT PROJECT *"};

	for (int i = 0; prjct[i] != '\0'; i++) {
		printf("\n\t\t\t\t\t   ");
		delay(50);
		printf("%c", prjct[i]);
	}

	printf("\n");
	delay(250);
	printf("\n\t\t\t\t\t*");

	for (int str = 1; str < 34; str++) {
		delay(50);
		printf("*");
	}
	printf("\n");

	for (int i = 0; i < 120; i++)
		printf("_");

	delay(100);
	printf("\n\n\n\n\t\t\t\t\t M");
	delay(50);
	printf("a");
	delay(50);
	printf("d");
	delay(50);
	printf("e ");
	delay(50);
	printf("b");
	delay(50);
	printf("y- ");
	delay(100);
	char name[2][30] = {"1.Bikash Ch. Nath", "2.Aniket Lodh\n\n"};

	for (int i = 0; i < 2; i++) {
		printf("\n\t\t\t\t\t       ");
		for (int j = 0; name[i][j] != '\0'; j++) {
			delay(50);
			printf("%c", name[i][j]);
		}
	}

	delay(900);
	for (int i = 0; i < 120; i++)
		printf("_");
	delay(1000);
	printf("\n\n\t\t\t Press any key to continue");
	delay(350);
	printf(".");
	delay(350);
	printf(".");
	delay(350);
	printf(".");
	delay(350);
	printf(".");
	getch();
	printf("\n\n\n\t\t\t");
	printf("Press any key to continue");
}



int login() {
	char usname[10], pword[10], code[10];
	char c = ' ';
	int a = 0, i;
	system("COLOR 5E");

	while (a < 3) {
		printf("\n\t\t\t **************************  ADMIN LOGIN PAGE  ************************** \n\n");
		delay(250);
		printf(" \n\t\t                       ENTER USERNAME:-");
		scanf("%s", &usname);
		printf(" \n\t\t                       ENTER PASSWORD:-");
		i = 0;
		while (i < 10) {
			pword[i] = getch();
			c = pword[i];
			if (c == 13)          //ASCII value of \n = 13
				break;
			else
				printf("*");
			i++;
		}

		pword[i] = '\0';
		delay(05);

		if (strcmpi(usname, "admin") == 0 && strcmp(pword, "password") == 0) {
			delay(500);
			printf("  \n\n\n\t\t\t\t WELCOME TO OUR SYSTEM !!!! LOGIN IS SUCCESSFUL");
			delay(1000);
			printf("\n\n\t\t\t\t\t Press any key to continue...");
			getch();
			return 1;

		} else {
			printf("\n\n\n\t\t    Sorry !! Login is unsuccessful");
			a++;
			printf("\n\t\t    Please try again! (Hint: password)");
			getch();
			if (a != 3)
				system("cls");
		}
		if (a == 3) {
			delay(190);
			printf("\n\n\t\t    You have entered wrong username or password 3 times.\n");
			delay(100);
			printf("\n\t\t    Press any key to exit");
			getch();
		}
	}
	return 0;

}




int Room[30][20], Room_Allot[30][20], Empty[100], length = 0, R = 0;

void Add() {
	system("COLOR 5E");
	int age[10], Total, count = 0, N, i, j, A, C = 0, choice;
	char Ans = 'N';
	do {
		system("cls");
		printf("\n NOTE: Maximum No. of Guests that can book rooms at a time is 10\n\n");
		printf("\n Enter No. of Adult guests:\n ");
		scanf("%d", &A);

		if (A <= 10) {
			printf(" Enter No. of children:\n ");
			scanf("%d", &C);
			printf(" NOTE: Free entry for children under 11 years.\n\n");
		}

		for (i = 0; i < C; i++) {
			printf(" Enter age of children %d: ", i + 1);
			scanf("%d", &age[i]);
			if (age[i] <= 11)
				count++;
		}

		if (count > 0) {
			printf("\n Do you want any extra bed for %d children below 11 years(Y/N): ", count);
			while ((getchar()) != '\n');
			scanf("%c", &Ans);
		}

		if (Ans == 'Y' || Ans == 'y')
			Total = A + C;
		else
			Total = A + C - count;

		if (Total > 10) {
			printf("\n Total no. of Guests is %d\n", Total);
			printf(" Please adjust Total No. of Beds upto 10\n Enter No. of Guests Again!");
			getch();
		}
	} while (Total > 10);

	do {
		printf("\n Duration(days) of Stay (Max. 60): ");
		scanf("%d", &H.Period);

		if (H.Period > 60)
			printf(" Stay cannot greter than 60 Days. Enter Again!\n");
	} while (H.Period < 1 || H.Period > 60);

	printf("\n\n Enter Guest Room type choice:\n");
	printf(" 1.A.C. \n 2.Non- A.C.\n -> ");
	scanf("%d", &choice);
	N = Room_opt(Total, choice);

	for (i = 0; Room_Allot[N][i] != 0; i++) {
		C = Room_Allot[N][i];
		Room_stat(0);
		if (choice == 1) {
			switch (C) {
			case 1: for (j = 0; j < length; j++) {
					if (Empty[j] <= 20) {
						Getdata(Empty[j], 1, i);
						break;
					}
				}
				break;
			case 2: for (j = 0; j < length; j++) {
					if (Empty[j] > 20 && Empty[j] <= 35) {
						Getdata(Empty[j], 2, i);
						break;
					}
				}
				break;
			case 3: for (j = 0; j < length; j++) {
					if (Empty[j] > 35 && Empty[j] <= 55) {
						Getdata(Empty[j], 3, i);
						break;
					}
				}
				break;
			case 4: for (j = 0; j < length; j++) {
					if (Empty[j] > 55 && Empty[j] <= 75) {
						Getdata(Empty[j], 4, i);
						break;
					}
				}
			}
		} else if (choice == 2) {
			switch (C) {
			case 1: for (j = 0; j < length; j++) {
					if (Empty[j] > 75 && Empty[j] <= 90) {
						Getdata(Empty[j], 1, i);
						break;
					}
				}
				break;
			case 2: for (j = 0; j < length; j++) {
					if (Empty[j] > 90 && Empty[j] <= 100) {
						Getdata(Empty[j], 2, i);
						break;
					}
				}
				break;
			}
		}
		FILE *fp = fopen("Record.txt", "a");
		fwrite(&H, sizeof(struct Hotel), 1, fp);
		printf("\n\n Room is successfully booked!!!");
		printf("\n\n Press any key to continue!!");
		getch();
		fclose(fp);
	}

}


int Room_opt(int n, int choice) {	//find all combinations
	int arr[20], R1 = 0, flag, i, j, m, N;
	int Price_list[25], Index, space;
	int s, d, t, q, k, s1, d1, t1, q1;
	R = 0;
	FindCombinations(arr, 0, n, n);

	int c = (choice == 1) ? 4 : 2;
	Room_stat(0);

	for (i = 0; i < R; i++) {
		flag = 1;
		s = 0; d = 0; t = 0; q = 0; k = 0; s1 = 0; d1 = 0; t1 = 0; q1 = 0;
		for (j = 0; Room[i][j] != 0; j++) {
			if (Room[i][j] > c)
				flag = 0;

			N = Room[i][j];
			switch (N) {
			case 1: s++;
				break;
			case 2: d++;
				break;
			case 3: t++;
				break;
			case 4: q++;
				break;
			}
		}

		for (m = 0; m < 100; m++) {
			N = Empty[m];
			if (choice == 1) {
				if (N <= 20)
					s1++;
				else if (N <= 35)
					d1++;
				else if (N <= 55)
					t1++;
				else if (N <= 75)
					q1++;
			}

			else if (choice == 2) {
				if (N > 75 && N <= 90)
					s1++;
				else if (N > 90 && N <= 100)
					d1++;
			}
		}

		if (choice == 1) {
			if (s1 < s)
				flag = 1;
			else if (d1 < d)
				flag = 1;
			else if (t1 < t)
				flag = 1;
			else if (q1 < q)
				flag = 1;
		} else {
			if (s1 < s)
				flag = 1;
			else if (d1 < d)
				flag = 1;
		}

		if (flag == 1) {
			for (j = 0; Room[i][j] != 0; j++)
				Room_Allot[R1][j] = Room[i][j];
			Room_Allot[R1][j] = 0;
			R1++;
		}
	}

	system("cls");
	printf("\n Displaying Room choices for %d Guests\n\n", n);
	printf(" Rooms option avialable:\n");

	if (choice == 1) {
		for (i = 0; i < R1; i++) {
			Price_list[i] = 0;
			k = 0; d = 0; t = 0; q = 0;
			for (j = 0; Room_Allot[i][j] != 0; j++) {
				N = Room_Allot[i][j];
				switch (N) {
				case 1: Price_list[i] += 3000;
					k++;
					break;
				case 2: Price_list[i] += 2000;
					d++;
					break;
				case 3: Price_list[i] += 2700;
					t++;
					break;
				case 4: Price_list[i] += 3600;
					q++;
					break;
				}
			}
			printf("\n %d.->  ", i + 1);
			if (k > 0)
				printf("%d King/Queen Bed,\t", k);
			if (d > 0)
				printf("%d Deluxe Double Beds,\t", d);
			if (t > 0)
				printf("%d Triple Beds,\t", t);
			if (q > 0)
				printf("%d Quadruple Beds,\t", q);

			space = 75;
			if (k > 0)
				space -= 21;
			if (d > 0)
				space -= 25;
			if (t > 0)
				space -= 18;
			if (q > 0)
				space -= 21;
			for (int p = 0; p < space; p++)
				printf(" ");;

			printf("Total Price of %d Night = %d", H.Period, H.Period * Price_list[i]);
		}
	} else {
		for (i = 0; i < R1; i++) {
			Price_list[i] = 0;
			s = 0; d = 0;
			for (j = 0; Room_Allot[i][j] != 0; j++) {
				N = Room_Allot[i][j];
				switch (N) {
				case 1: Price_list[i] += 1000;
					s++;
					break;
				case 2: Price_list[i] += 1800;
					d++;
				}
			}
			printf("\n%d.->  ", i + 1);
			if (s > 0)
				printf("%d Standard Single,\t", s);
			if (d > 0)
				printf("%d Standard Twin,\t", d);
			space = 50;
			if (s > 0)
				space -= 21;
			if (d > 0)
				space -= 25;
			for (int p = 0; p < space; p++)
				printf(" ");;

			printf("Total Price of %d Night = %d", H.Period, H.Period * Price_list[i]);
		}
	}

	printf("\n\n Enter your choice of room allotment: ");
	scanf("%d", &Index);
	return (Index - 1);
}



void FindCombinations(int arr[], int index, int num, int reducedNum) {
	if (reducedNum < 0)
		return;

	if (reducedNum == 0) {
		int i;
		for ( i = 0; i < index; i++)
			Room[R][i] = arr[i];
		Room[R][i] = 0;
		R++;
		return;
	}

	int prev = (index == 0) ? 1 : arr[index - 1];

	for (int k = prev; k <= num ; k++) {
		arr[index] = k;
		FindCombinations(arr, index + 1, num, reducedNum - k);
	}
}


void Display() {
	fflush(stdout);
	system("cls");
	FILE *fp = fopen("Record.txt", "r");
	int r, flag = 0;
	char ch;

	while (true) {
		fflush(stdout);
		system("cls");
		if (fp == NULL) {
			printf("\n No Records Found!!\nAll Rooms are Empty.");
			getch();
			return;
		}
		printf("\n Enter room no: ");
		scanf("%d", &r);

		if ((r <= 0) || (r > 100)) {
			printf("\n The entered room no does not exist.\n");
			printf("\n Please enter a valid room no \n\t Or\n Press esc to exit");
			ch = getch();
			if ((int)ch == 27)
				return;
			else
				else
					continue;
		}
		break;
	}

	while (fread(&H, sizeof(struct Hotel), 1, fp)) {
		if (H.room_no == r) {
			Putdata();
			flag = 1;
			break;
		}
	}

	if (flag == 0)
		printf("\n Sorry the Room is vacant .");

	printf("\n\n Press any key to continue!!");
	fclose(fp);
	getch();
}



void Room_stat(int code) {
	int Booked[100];
	int Count = 0, i = 0, k = 0, flag = 0, j, temp, size;

	size = Booking_stat(Booked);

	if (size == -1 && code == 1) {
		system("cls");
		printf("\n No Records Found!!\n All Rooms are Empty.");
		getch();
		return;
	}

	if (length == 0) {
		for (i = 0; i < 100; i++)
			Empty[i] = i + 1;
		length = i;
	}

	for (i = 0; i < size; i++) {
		for (j = 0; j < size - 1 - i; j++)
			if (Booked[j] > Booked[j + 1]) {
				temp = Booked[j];
				Booked[j] = Booked[j + 1];
				Booked[j + 1] = temp;
			}
	}

	for (j = 0; j < 100; j++) {
		for (i = 0; i < size; i++) {
			if ((j + 1) == Booked[i])
				flag = 1;
		}
		if (flag != 1) {
			Empty[k] = j + 1;
			k++;
		}
		flag = 0;
	}
	length = k;

	if (code == 1) {
		system("cls");
		printf("\n\t\t\t Rooms Status");
		printf("\n\t\t\t**************\n\n");

		printf("\t Total no of booked rooms are : %d\n", size);
		printf("\t Total no of empty rooms are  : %d", 100 - size);
		int Ch;
		printf("\n\n\tEnter your choice to display Room Status");
		printf("\n\t1. Display Booked Rooms");
		printf("\n\t2. Display Empty Rooms\n\t->");
		scanf("%d", &Ch);

		if (Ch == 1) {
			printf("\n\n\n \tList of Rooms booked is\n");
			for (i = 0; i < 120; i++)
				printf("_");

			int B_Display[6][20], N, k = 0, s = 0, d = 0, t = 0, q = 0, d1 = 0;

			for (i = 0; i < size; i++) {
				N = Booked[i];

				if (N <= 20)
					B_Display[0][k++] = N;
				else if (N <= 35)
					B_Display[1][d++] = N;
				else if (N <= 55)
					B_Display[2][t++] = N;
				else if (N <= 75)
					B_Display[3][q++] = N;
				if (N > 75 && N <= 90)
					B_Display[4][s++] = N;
				else if (N > 90 && N <= 100)
					B_Display[5][d1++] = N;
			}

			if (k > 0) {
				printf("\n King/Queen Bed:\t");
				for (i = 0; i < k; i++) {
					printf("    %d\t,", B_Display[0][i]);
					if ((i + 1) % 11 == 0)
						printf("\n\t\t\t");
				}
			}
			if (d > 0) {
				printf("\n\n Deluxe Double Beds:\t");
				for (i = 0; i < d; i++) {
					printf("    %d\t,", B_Display[1][i]);
					if ((i + 1) % 11 == 0)
						printf("\n\t\t\t");
				}
			}
			if (t > 0) {
				printf("\n\n Triple Beds:\t\t");
				for (i = 0; i < t; i++) {
					printf("    %d\t,", B_Display[2][i]);
					if ((i + 1) % 11 == 0)
						printf("\n\t\t\t");
				}
			}
			if (q > 0) {
				printf("\n\n Quadruple Beds:\t");
				for (i = 0; i < q; i++) {
					printf("    %d\t,", B_Display[3][i]);
					if ((i + 1) % 11 == 0)
						printf("\n\t\t\t");
				}
			}

			if (s > 0) {
				printf("\n\n Standard Single:\t");
				for (i = 0; i < s; i++) {
					printf("    %d\t,", B_Display[4][i]);
					if ((i + 1) % 11 == 0)
						printf("\n\t\t\t");
				}
			}
			if (d1 > 0) {
				printf("\n\n Standard Twin:\t\t");
				for (i = 0; i < d1; i++) {
					printf("    %d\t,", B_Display[5][i]);
					if ((i + 1) % 11 == 0)
						printf("\n\t\t\t");
				}
			}

			printf("\n");
			for (i = 0; i < 120; i++)
				printf("_");
		} else if (Ch == 2) {
			printf("\n\tList of Empty rooms are\n");
			for (i = 0; i < 120; i++)
				printf("_");
			int E_Display[6][20], N, k = 0, s = 0, d = 0, t = 0, q = 0, d1 = 0;
			for (i = 0; i < length; i++) {
				N = Empty[i];

				if (N <= 20)
					E_Display[0][k++] = N;
				else if (N <= 35)
					E_Display[1][d++] = N;
				else if (N <= 55)
					E_Display[2][t++] = N;
				else if (N <= 75)
					E_Display[3][q++] = N;
				if (N > 75 && N <= 90)
					E_Display[4][s++] = N;
				else if (N > 90 && N <= 100)
					E_Display[5][d1++] = N;
			}

			if (k > 0 || d > 0 || t > 0 || q > 0)
				printf("\n ** AC ROOMS **\n ______________");
			if (k > 0) {
				printf("\n\n King/Queen Bed:\t");
				for (i = 0; i < k; i++) {
					printf("    %d\t,", E_Display[0][i]);
					if ((i + 1) % 11 == 0)
						printf("\n\t\t\t");
				}
			}
			if (d > 0) {
				printf("\n\n Deluxe Double Beds:\t");
				for (i = 0; i < d; i++) {
					printf("    %d\t,", E_Display[1][i]);
					if ((i + 1) % 11 == 0)
						printf("\n\t\t\t");
				}
			}
			if (t > 0) {
				printf("\n\n Triple Beds:\t\t");
				for (i = 0; i < t; i++) {
					printf("    %d\t,", E_Display[2][i]);
					if ((i + 1) % 11 == 0)
						printf("\n\t\t\t");
				}
			}
			if (q > 0) {
				printf("\n\n Quadruple Beds:\t");
				for (i = 0; i < q; i++) {
					printf("    %d\t,", E_Display[3][i]);
					if ((i + 1) % 11 == 0)
						printf("\n\t\t\t");
				}
			}
			if (s > 0 || d1 > 0)
				printf("\n\n ** NON-AC ROOMS ** \n __________________");
			if (s > 0) {
				printf("\n\n Standard Single:\t");
				for (i = 0; i < s; i++) {
					printf("    %d\t,", E_Display[4][i]);
					if ((i + 1) % 11 == 0)
						printf("\n\t\t\t");
				}
			}
			if (d1 > 0) {
				printf("\n\n Standard Twin:\t\t");
				for (i = 0; i < d1; i++) {
					printf("    %d\t,", E_Display[5][i]);
					if ((i + 1) % 11 == 0)
						printf("\n\t\t\t");
				}
			}
			printf("\n");
			for (i = 0; i < 120; i++)
				printf("_");
		} else
			printf("\nWrong Choice.");
		getch();
		printf("\n\n\t\t\tPress any key to continue!!");
		getch();
	}
}

int Booking_stat(int Booked[100]) {
	FILE *fp = fopen("Record.txt", "r");
	int i = 0;
	if (fp == NULL) {
		getch();
		return -1;
	}

	while (fread(&H, sizeof(struct Hotel), 1, fp)) {
		Booked[i] = H.room_no;
		i++;
	}

	fclose(fp);
	return i;
}

void Modify_menu() {
	system("cls");
	system("COLOR 1E");
	int choice = 1, r;
	char ch;

	do {
		system("cls");
		printf("\n\n\n\t\t\t\t\t  ***********");
		printf("\n\t\t\t\t\t  MODIFY MENU");
		printf("\n\t\t\t\t\t  ***********\n\n");
		printf("\n\t\t\t\t\t 1. Food Order\n");
		printf("\n\t\t\t\t\t 2. Modify Customer Record\n");
		printf("\n\t\t\t\t\t 3. Modify Laundry Service\n");
		printf("\n\t\t\t\t\t 4. Go Back to Main Menu\n");
		printf("\n\n\n\t\t\t\t\t Enter your choice:  ");
		scanf("%d", &choice);
		if (choice < 1 || choice > 4) {
			printf("\n\n Wrong Choice!!\n Please enter a valid choice.");
			getch();
		}
	} while (choice < 1 || choice > 4);

	if (choice > 0 && choice < 4) {
		system("cls");
		printf("\n Enter room no: ");
		scanf("%d", &r);

		while ((r <= 0) || (r > 100)) {
			printf("\n The entered room no does not exist.\n");
			printf("\n Please enter a valid room no \n\t or\n Press esc to exit");
			ch = getch();
			if ((int)ch == 27)
				return;
			else {
				printf("\n Enter room no: ");
				scanf("%d", &r);
			}
		}
	}

	switch (choice) {
	case 1: Food_order(r);
		break;
	case 2: Modify_data(r);
		break;
	case 3: Laundry(r);
		break;
	case 4:
		break;
	}

}

void Food_order(int r) {
	system("cls");
	system("COLOR 1E");
	delay(100);
	system("cls");

	char Food[50][25] = {"SHAHI PANEER", "KADAI PANEER", "CHEESE KORMA", "MALAI KOFTA ", "MATAR PANEER",
	                     "PALAK PANEER", "MIX VEGITABLES", "RAJMA MAKHANI", "DAL MAKHANI", "SALAD(GREEN)", "DUM ALOO",
	                     "MUSHROOM PANEER", "MASALA DOSA", "MASALA IDLI", "DAHI VADA", "MUTTON KORMA", "MUTTON CURRY",
	                     "EGG CURRY", "BUTTER CHICKEN", "FISH CURRY", "CHICKEN CURRY", "CHILLI CHICKEN", "CHICKEN TIKKA",
	                     "SEEKH KABAB", "CHICKEN TANDOR", "PANEER TIKKA", "CHICKEN SEEKHKABAB", "CHICKEN BIRYANI", "PANEER PULAO",
	                     "VEG.PULAO", "RUMALI ROTI", "ALOO PARATHA", "PANEER PARANTHA", "PIZZA MARGHERITA", "VEG.BURGER",
	                     "CHICKEN BURGER", "PANEER BURGER", "CHEESE SANDWICH", "TEA", "COFFEE", "COLD COFFEE", "LASSI", "HOT CHOCOLATE",
	                     "SOFT DRINKS", "COLD DRINKS", "STRAWBERRY", "CHOCOLATE", "BLACK FOREST", "VANILLA", "PISTA BADAM"
	                    };

	int F_price[50] = {200, 220, 160, 130, 125, 110, 150, 160, 140, 100, 110, 180, 120, 80, 100, 250, 300, 150, 240, 200, 260, 250, 150,
	                   230, 240, 160, 260, 250, 220, 200, 40, 30, 35, 300, 200, 240, 220, 150, 20, 20, 30, 30, 50, 50, 60, 30, 40, 60, 30, 40
	                  };

	int choice, quantity, price = 0, i, count = 0;
	int flag = 0, l;

	FILE *fp = fopen("Record.txt", "r+");
	if (fp == NULL) {
		printf("\n No Records Found!!\nAll Rooms are Empty.");
		getch();
		return;
	}

	while (fread(&H, sizeof(struct Hotel), 1, fp)) {
		if (H.room_no == r) {
			flag = 1;
			break;
		}
	}
	if (flag == 0) {
		printf("\n Sorry the Room is vacant .");
		printf("\n\n Press any key to continue!!");
		getch();
		return;
	}

	char Ch;
	while (1) {
		system("cls");
		printf("\n\t\t\t\t  *********");
		printf("\n\t\t\t\t  MENU CARD");
		printf("\n\t\t\t\t  *********");

		for (int j = 0, i = 0; i < 50; i++, j++) {
			if (i == 0)
				printf("\n\n\t\t\t\t  *** VEGETARIAN ***\n");

			if (i == 15) {
				printf("\n\n\t\t\t\t *** NON-VEGETARIAN ****\n");
				j = 0;
			} else if (i == 23) {
				printf("\n\n\t\t\t\t *** BARBEQUE ***\n");
				j = 0;
			} else if (i == 27) {
				printf("\n\n\t\t\t\t *** MEAL ***\n");
				j = 0;
			} else if (i == 38) {
				printf("\n\n\t\t\t\t *** BEVERAGES ***\n");
				j = 0;
			} else if (i == 45) {
				printf("\n\n\t\t\t\t *** ICE-CREAMS ***\n");
				j = 0;
			}
			printf("%d.%s %d/-\t", i + 1, Food[i], F_price[i]);
			if ((j + 1) % 4 == 0)
				printf("\n");
		}

		count++;
		printf("\n\n Enter Item No. of Food: ");
		scanf("%d", &choice);

		if (choice < 1 || choice > 50) {
			printf("Wrong Input!\n Returning to Main Menu.");
			break;
		}

		printf("\n Enter Quantity of '%s':", Food[choice - 1]);
		scanf("%d", &quantity);
		printf(" Order %d Amount = %d", count, F_price[choice - 1]*quantity);
		price += F_price[choice - 1] * quantity;
		printf("\n\n Do you want to Order 1 more Food Item (Y/N):- ");
		while (getchar() != '\n');

		scanf("%c", &Ch);
		if (Ch == 'Y' || Ch == 'y')
			continue;

		else if (Ch == 'N' || Ch == 'n')
			break;
		else {
			printf("\n Wrong Choice!\n ");
			break;
		}
	}
	printf("\n Total Amount of %d foods: %d/-\n", count, price);
	long pos;
	fseek(fp, 0, 0);

	while (!feof(fp)) {
		pos = ftell(fp);
		fread(&H, sizeof(struct Hotel), 1, fp);
		if (H.room_no == r) {
			H.Food_Price += price;
			H.Amount += price;
			fseek(fp, pos, 0);
			printf(" Food Price of room no %d have been updated.", r);
			fwrite(&H, sizeof(struct Hotel), 1, fp);
			flag = 1;
			break;
		}
	}
	fclose(fp);
	getch();
}

void Modify_data(int r) {
	fflush(stdout);
	system("cls");
	long int pos;
	int flag = 0;
	FILE *fp = fopen("Record.txt", "r+");
	if (fp == NULL) {
		printf("\n No Records Found!!\nAll Rooms are Empty.");
		getch();
		return;
	}

	while (!feof(fp)) {
		pos = ftell(fp);
		fread(&H, sizeof(struct Hotel), 1, fp);
		if (H.room_no == r) {
			Putdata();
			Retain();
			fseek(fp, pos, 0);
			fwrite(&H, sizeof(struct Hotel), 1, fp);
			printf("\n Record of room no %d have been modified!!", H.room_no);
			flag = 1;
			break;
		}
	}

	if (flag == 0)
		printf("\n Sorry!. the Room is vacant!!\n");
	getch();
	fclose(fp);
}

void Retain() {        //to modify customer Record

	char Gnd = '.', nm[30], adrs[50] = "\0", Ph_no[11] = "\0";
	int prd, ag, n;
	printf("\n\n\n Enter Guests No. of which data is to be modified: ");
	scanf("%d", &n);

	printf("\n\n Enter New details\n");
	printf(" **********************\n");

	printf(" Name (press '0' to retain old one) :\t");
	scanf("%s", &nm);
	while ((getchar()) != '\n');

	while (1) {
		printf(" Gender [M/F/T] (press '0' to retain old one): ");
		scanf("%c", &Gnd);
		if (Gnd == 'M' || Gnd == 'm') {
			strcpy(H.Gender[n - 1], "Male");
			break;
		} else if (Gnd == 'F' || Gnd == 'f') {
			strcpy(H.Gender[n - 1], "Female");
			break;
		} else if (Gnd == 'T' || Gnd == 't') {
			strcpy(H.Gender[n - 1], "Transgender");
			break;
		} else if (Gnd == '0')
			break;
		else
			printf(" Incorrect option\n");

	}
	printf(" Age (press '0' to retain old one) :\t   ");
	scanf("%d", &ag);
	while ((getchar()) != '\n');

	if (strcmp(H.address, "\0") != 0) {
		printf(" Address (press '0' to retain old one ) :  ");
		gets(adrs);
		printf(" Phone no (press '0' to retain old one) :  ");
		scanf("%s", &Ph_no);
	}

	do {
		printf(" Duration (press '0' to retain old one) :  ");
		scanf("%d", &prd);
		if (prd > 60)
			printf(" Stay cannot greter than 60 Days. Enter Again!\n");
	} while (prd < 0 || prd > 60);

	if (strcmp(nm, "0") != 0)
		strcpy(H.Name[n - 1], nm);
	if (ag != 0)
		H.Age[n - 1] = ag;
	if (strcmp(adrs, "0") != 0)
		strcpy(H.address, adrs);
	if (strcmp(Ph_no, "0") != 0)
		strcpy(H.phone, Ph_no);
	if (prd != 0)
		H.Period = prd;
}


void Laundry(int r) {
	char Ch;
	int flag = 0, l;
	long pos;
	system("cls");
	FILE *fp = fopen("Record.txt", "r+");
	if (fp == NULL) {
		printf("\n No Records Found!!\nAll Rooms are Empty.");
		getch();
		return;
	}

	while (!feof(fp)) {
		pos = ftell(fp);
		fread(&H, sizeof(struct Hotel), 1, fp);
		if (H.room_no == r) {
			fseek(fp, pos, 0);
			do {
				printf("\n Current frequency of Laundry service is: %d", H.laundry);
				printf("\n Do you want to modify Laundry frequency(Y/N) : ");
				while ((getchar()) != '\n');
				scanf("%c", &Ch);
				if (Ch == 'Y' || Ch == 'y') {
					printf("\n Enter New Frequency: ");
					scanf("%d", &l);
					flag = 1;
				} else if (Ch == 'N' || Ch == 'n') {
					flag = 2;
					break;
				} else {
					printf("\n Wrong Choice!\n Please Enter correct option.");
					Ch = 'A';
				}
			} while (Ch == 'A');

			if (flag == 1) {
				H.Amount -= (H.Period / H.laundry) * 500;
				H.laundry = l;
				H.Amount += (H.Period / H.laundry) * 500;
				fwrite(&H, sizeof(struct Hotel), 1, fp);
				printf("\n Laundry Frequency of Room no %d have been modified.", r);
			}
			break;
		}
	}
	if (flag == 0)
		printf("\n Sorry!. the Room is vacant!!\n");
	getch();
	fclose(fp);
}

void Check_out() {
	system("cls");
	system("COLOR CF");
	int r, flag = 0, R_no = 0;;
	char ch;
	printf("\n Enter room no: ");
	scanf("%d", &r);

	while ((r <= 0) || (r > 100)) {
		printf("\n The entered room no does not exist.\n");
		printf("\n Please enter a valid room no \n\t or\n Press esc to exit");
		ch = getch();
		if ((int)ch == 27)
			return;
		else {
			printf("\n Enter room no: ");
			scanf("%d", &r);
		}
	}

	system("cls");
	FILE *fptr1 = fopen("Record.txt", "r");
	FILE *fptr2 = fopen("Temp.txt", "w");

	if (fptr1 == NULL) {
		printf("\n Sorry!! Cannot open the file");
		getch();
		return;
	}

	while (fread(&H, sizeof(struct Hotel), 1, fptr1)) {
		if (H.room_no == r) {
			Putdata();
			while ((getchar()) != '\n');
			char ch = 'a';

			while (true) {
				printf("\n\n Do you want to Check-out this Guest (y/n):  ");
				scanf("%c", &ch);
				if ((ch == 'y') || (ch == 'Y')) {
					R_no = H.room_no;
					flag = 1;
					printf("\n Price of Room Booking for %d Days is %d", H.Period, H.Room_Price);
					if (H.Food_Price > 0)
						printf("\n Price for Food ordered is %d", H.Food_Price);
					printf("\n Price for Laundry Service is %d", (H.Period / H.laundry) * 500);
					if (H.Gym > 0)
						printf("\n Price of Fitness center for %d Days is %d", H.Gym, H.Gym * 1000);

					printf("\n\n Total Expense of Room is: %d", H.Amount);
					printf("\n\n Amount Payable (Remaining: To be paid) of Room is: %d", H.Amount - H.Payment);
					break;
				} else if ((ch == 'n') || (ch == 'N')) {
					fwrite(&H, sizeof(struct Hotel), 1, fptr2);
					flag = 2;
				} else {
					printf("\n Wrong choice\n Please enter correct option\n");
					else
						continue;

				}
				break;
			}
		}

		else
			fwrite(&H, sizeof(struct Hotel), 1, fptr2);
	}

	fclose(fptr1);
	fclose(fptr2);

	if (flag == 0)
		printf("\n Sorry the room is vacant!!\n");
	else {
		if (flag == 1)
			printf("\n Data Record.txt of room no %d have been successfully deleted\n", R_no);
	}
	remove("Record.txt");
	rename("Temp.txt", "Record.txt");
	getch()	;
}


void Exit() {
	system("cls");

	for (int j = 0; j < 2; j++) {
		system("cls");
		printf("\n\n\n\n\n\n\n\n\n\t\t\t\t\tClosing Application");
		for (int i = 0; i < 4; i++) {
			delay(250);
			printf(".");
		}
		delay(50);
	}
	delay(200);
	printf("\n\n\n\n\t\t\t\t\t    THANK YOU");
	delay(500);
	printf("\n\n\t\t\t\t\t   Visit Again.\n\n\n\n\n\n");
	return;
}

void Room_Features() {
	int r = 0;
	system("cls");

	while (r < 1 || r > 100) {
		printf("\n Enter a Room No. (1-100): ");
		scanf("%d", &r);
		if (r < 1 || r > 100) {
			printf("\n Wrong Input!\n Please enter a value between 1 and 100.");
			system("cls");
		}
	}

	if (r <= 20) {
		printf("\n\n Room  Type: King/Queen ");
		printf("\n\n Number of Beds: 1 Bed");
		printf("\n Room Capacity: 1 Guest");
		printf("\n A.C./Non A.C.: A.C. Type");
		printf("\n Price per night: 3000/- (Incliding Breakfast)");
		printf("\n\n Additional Features :");
		printf("\n -> Television & MP3 dock");
		printf("\n -> Fee High speed Wi-Fi");
		printf("\n -> Remote control panels for lighting");
		printf("\n -> Refrigerator");
		printf("\n -> Geyser");
		printf("\n -> Wardrobes, iron and ironing board");
		printf("\n -> Tea/Coffee Maker");
		printf("\n -> Electric Safe");
		printf("\n -> Private Balcony");
		printf("\n -> Private bathroom");
	} else if (r > 20 && r <= 35) {
		printf("\n Room  Type: Deluxe Double ");
		printf("\n\n Number of Beds: 2 Beds");
		printf("\n Room Capacity: 2 Guest");
		printf("\n A.C./Non A.C.: A.C. Type");
		printf("\n Price per night: 2000/- (Incliding Breakfast)");
		printf("\n\n Additional Features :");
		printf("\n ->Television");
		printf("\n ->Fee Wi-Fi");
		printf("\n ->Refrigerator");
		printf("\n ->Geyser");
	} else if (r > 35 && r <= 55) {
		printf("\n Room  Type: Triple Beds ");
		printf("\n\n Number of Beds: 3 Beds");
		printf("\n Room Capacity: 3 Guest");
		printf("\n A.C./Non A.C.: A.C. Type");
		printf("\n Price per night: 2700/- (Incliding Breakfast)");
		printf("\n\n Additional Features :");
		printf("\n ->Fee Wi-Fi");
		printf("\n ->Geyser");
	} else if (r > 55 && r <= 75) {
		printf("\n Room  Type: Quadruple Beds");
		printf("\n\n Number of Beds: 4 Beds");
		printf("\n Room Capacity: 4 Guest");
		printf("\n A.C./Non A.C.: A.C. Type");
		printf("\n Price per night: 3600/- (Incliding Breakfast)");
		printf("\n Additional Features :");
		printf("\n ->Television");
		printf("\n ->Fee Wi-Fi");
		printf("\n ->Refrigerator");
		printf("\n ->Geyser");
	} else if (r > 75 && r <= 90) {
		printf("\n Room  Type: Standard Single");
		printf("\n\n Number of Beds: 1 Bed");
		printf("\n Room Capacity: 1 Guest");
		printf("\n A.C./Non A.C.: Non A.C. Type");
		printf("\n Price per night: 1000/- (Incliding Breakfast)");
	} else if (r > 90 && r <= 100) {
		printf("\n Room  Type: Standard Twin ");
		printf("\n\n Number of Beds: 2 Bed");
		printf("\n Room Capacity: 2 Guest");
		printf("\n A.C./Non A.C.: Non A.C. Type");
		printf("\n Price per night: 2800/- (Incliding Breakfast)");
	}
	getch();
}
