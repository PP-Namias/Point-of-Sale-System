#include<iostream>
#include<conio.h>
#include<fstream>
#include<iomanip>
using namespace std;

class mall
{
	int pno;
	char name[50];
	float price, dis;

public:
	void getdata()
	{
		char ch;
		system("color e4");

		cout << "\n\tEnter the details of the product...";
		cout << "\n\tProduct No: ";
		cin >> pno;
		cin.get(ch);
		cout << "\n\tProduct Name: ";
		cin >> name;
		cout << "\n\tProduct Price: ";
		cin >> price;
		cout << "\n\tProduct Discount(%): ";
		cin >> dis;
	}

	void showdata()
	{
		cout << setw(4) << pno << setw(20) << name << setw(8) << price << setw(10) << dis << "%" << "\n\t";
	}

	int retpno()
	{
		return pno;
	}

	float retprice()
	{
		return price;
	}

	char* retname()
	{
		return name;
	}

	int retdis()
	{
		return dis;
	}
};

fstream f;
mall m;

void menu()
{
	cout << "\n\t";
	system("color e4");
	cout << setw(4) << "P No" << setw(20) << "Product Name" << setw(8) << "Price" << setw(10) << "Discount";
	cout << "\n\t--------------------------------------------\n\t";
}

void enter()
{
	system("cls");
	system("color e4");

	f.open("mall.txt", ios::out | ios::app);
	m.getdata();
	f.write((char*)&m, sizeof(mall));
	f.close();

	cout << "\n\n\tProduct has been created...!!! ";
	_getch();
}

void display()
{
	system("color e4");
	cout << "\n\n\t\tDISPLAYING ALL RECORDS !!!\n\n";

	f.open("mall.txt", ios::in);
	menu();

	while (f.peek() != EOF)
	{
		f.read((char*)&m, sizeof(mall));
		m.showdata();
	}
	f.close();
	_getch();
}

void search()
{
	int no, flag = 0;
	system("cls");
	system("color e4");

	cout << "\n\n\tEnter the Product No. of the Product to be searched: ";
	cin >> no;

	f.open("mall.txt", ios::in);
	menu();

	while (f.read((char*)&m, sizeof(mall)))
	{
		if (m.retpno() == no)
		{
			m.showdata();
			flag = 1;
		}
	}
	f.close();

	if (flag == 0)
		cout << "\n\n\tRecord does not exist...!!!";
	_getch();
}

void update()
{
	int no, found = 0;
	system("cls");
	system("color e4");

	cout << "\n\n\tTo Update...Enter The Product No: ";
	cin >> no;

	f.open("mall.txt", ios::in | ios::out);
	menu();

	while (f.read((char*)&m, sizeof(mall)) && found == 0)
	{
		if (m.retpno() == no)
		{
			m.showdata();
			m.getdata();

			int pos = -1 * sizeof(m);
			f.seekp(pos, ios::cur);
			f.write((char*)&m, sizeof(mall));

			cout << "\n\n\t Record has been Updated...!!!";
			found = 1;
		}
	}
	f.close();

	if (found == 0)
		cout << "\n\n\tRecord Not Found ";
	_getch();
}

void erase()
{
	int no;
	system("cls");
	system("color e4");

	cout << "\n\n\n\tTo Delete...Enter The product No: ";
	cin >> no;

	f.open("mall.txt", ios::in | ios::out);
	fstream ft;
	ft.open("temp.txt", ios::out);
	f.seekg(0, ios::beg);

	while (f.read((char*)&m, sizeof(mall)))
	{
		if (m.retpno() != no)
		{
			ft.write((char*)&m, sizeof(mall));
		}
	}
	ft.close();
	f.close();

	remove("mall.txt");
	rename("temp.txt", "mall.txt");
	cout << "\n\n\tRecord  has been Deleted...!!!";
	display();
	_getch();
}

void place_order()
{
	int  order[30], quan[30], i = 0;
	float amt, damt, total = 0;
	char ch = 'Y';

	system("cls");
	system("color e4");
	display();

	cout << "\n\n\t============================";
	cout << "\n\t      PLACE YOUR ORDER";
	cout << "\n\t============================\n";

	do
	{
		cout << "\n\n\tEnter The Product No: ";
		cin >> order[i];
		cout << "\tQuantity: ";
		cin >> quan[i];

		i++;
		cout << "\n\tDo you want to order another product ?(y/n): ";
		cin >> ch;
	} while (ch == 'y' || ch == 'Y');

	cout << "\n\n\tThank You...!!!";
	_getch();

	system("cls");
	system("color 70");

	cout << "\n\n\t\t************************BILL************************\n\n\t\t";
	cout << setw(4) << "P No" << setw(20) << "Product Name" << setw(10) << "Quantity" << setw(8) << "Price" << setw(8) << "Amount" << setw(10) << "Discount" << endl;
	cout << "\t\t------------------------------------------------------------\n\t\t";

	for (int x = 0; x <= i; x++)
	{
		f.open("mall.txt", ios::in);
		f.read((char*)&m, sizeof(mall));

		while (f)
		{
			if (m.retpno() != order[x])
			{
				amt = 0;
				damt = 0;
			}
			else
			{
				amt = m.retprice() * quan[x];
				damt = amt - (amt * m.retdis() / 100);

				cout << setw(4) << order[x] << setw(20) << m.retname() << setw(10) << quan[x] << setw(8) << m.retprice() << setw(8) << amt << setw(10) << damt << "\n\t\t";
				total += damt;
			}
			f.read((char*)&m, sizeof(mall));
		}
		f.close();
	}

	cout << "\n\t\t--------------------------------------------------------------";
	cout << "\n\t\tThank You...Visit Once Again...............TOTAL = " << "Pesos." << total;
	cout << "\n\t\t--------------------------------------------------------------";
	_getch();
}

void intro()
{
	system("color b4");
	cout << "\n\n\n\n\n\n\n\n\n\t\t\t\tPoint of Sale System\n\t\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	cout << "\n\n\t\t\t\tMade By: @PP_Namias\n\t\t\t\t-------------------------";
	_getch();
}

void welcome()
{
	system("cls");
	system("color a4");
	cout << "\n\n\n\n\n\n\n\n\n\n\t\t\t\tWelcome to KASHYAP'S  WORLD";
	_getch();
}

int main()
{
	system("cls");
	intro();
	welcome();
	char ch;

	do
	{
		system("cls");
		system("color e4");
		cout << "\n\n\t1.Create Products";
		cout << "\n\n\t2.Display Products";
		cout << "\n\n\t3.Search Products ";
		cout << "\n\n\t4.Modify Products";
		cout << "\n\n\t5.Delete Products";
		cout << "\n\n\t6.Place an Order";
		cout << "\n\n\t7.EXIT";
		cout << "\n\n\tEnter Your Choice: ";
		ch = _getch();

		switch (ch)
		{
		case '1': enter(); break;
		case '2': system("cls"); display(); break;
		case '3': search(); break;
		case '4': update(); break;
		case '5': erase(); break;
		case '6': place_order(); break;
		case '7': exit(0);
		default: cout << "\a";
		}
	} while (ch != '7');

	_getch();
}
