#include <iostream>
#include "banker.h"

using std::cout;
using std::cin;
using std::endl;

int main()
{
	Banker banker;
	banker.set_size();
	int chiose;
	while (1)
	{
		system("cls");
		cout << "1.��������" << endl;
		cout << "2.������Դ" << endl;
		cout << "3.�鿴���" << endl;
		cout << "4.�˳�" << endl;
		cout << "\n" << "���������ѡ��:";
		cin >> chiose;
		switch (chiose)
		{
		case 1: 
		{	system("cls");
			banker.create_process();
		}
			break;
		case 2:
		{
			system("cls");
			banker.apply();
		}
			break;
		case 3:
		{
			system("cls");
			banker.show();
		}
			break;
		case 4:exit(0);
			break;
		default:
			break;
		}
	}
}