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
		cout << "1.创建进程" << endl;
		cout << "2.分配资源" << endl;
		cout << "3.查看情况" << endl;
		cout << "4.退出" << endl;
		cout << "\n" << "请输入你的选择:";
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