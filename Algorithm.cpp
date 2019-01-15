
#include <iostream>
#include "Algorithm.h"
using std::cout;
using std::cin;
using std::endl;

bool Banker::set_size()
{
	cout << "�����������Դ����(����#��������): ";
	int t;
	while (cin >> t)
	{
		total_space.push_back(t);
		surplus_space.push_back(t);
	}
	cin.clear();
	cin.get();
	return true;
}
bool Banker::create_process()
{
	cout << "������ý��̵ĸ�����Դ������(����#��������): ";
	int t;
	Process t_pro;
	while (cin >> t)
	{
		t_pro.require.push_back(t);
		t_pro.acquire.push_back(0);
	}
	cin.clear();
	cin.get();
	if (t_pro.require.size() != total_space.size())
	{
		cout << "��������ʧ��!��Դ�������͹���/����!";
		system("pause");
		return false;
	}
	size_t i;
	for (i = 0; i < total_space.size(); i++)
	{
		if (t_pro.require[i] > total_space[i])
		{
			cout << "��������ʧ��!��Դ���䳬���������!";
			system("pause");
			return false;
		}
	}
	process.push_back(t_pro);
	return true;
}
bool Banker::apply()
{
	cout << "������Ҫ����Ľ��̺�(��1��ʼ): ";
	int id;
	cin >> id;
	if (id > process.size())
	{
		cout << "����ʧ��!û�иý���!";
		system("pause");
		return false;
	}
	vector<int> t_resources;
	cout << "������Ҫ����Ĵ�С(����#��������): ";
	int t;
	while (cin >> t)
	{
		t_resources.push_back(t);
	}
	cin.clear();
	cin.get();
	if (t_resources.size() != process[id-1].require.size())
	{
		cout << "������Դʧ��!��Դ�������͹���/����!";
		system("pause");
		return false;
	}
	return safely(id, t_resources);
}
bool Banker::safely(int id,vector<int> & const t_resources)
{
	size_t i;
	for (i = 0; i < process[id - 1].require.size(); i++)
	{
		if (t_resources[i] > process[id - 1].require[i])
		{
			cout << "������Դʧ��!��Դ���䳬���������ʣ����Ҫ����!";
			system("pause");
			return false;
		}
	}
	for (i = 0; i < surplus_space.size(); i++)
	{
		if (t_resources[i] > surplus_space[i])
		{
			cout << "������Դʧ��!ʣ����������!";
			system("pause");
			return false;
		}
	}
	vector<Process> t_process = process;
	vector<int> t_surplus_space = surplus_space;
	for (i = 0; i < t_surplus_space.size(); i++)
	{
		t_surplus_space[i] -= t_resources[i];
		t_process[id - 1].require[i] -= t_resources[i];
		t_process[id - 1].acquire[i] += t_resources[i];
	}
	vector<bool> state(t_process.size(), false);
	vector<int> t_safely_array;
	bool state1;
	size_t j;
	while (1)
	{
		state1 = false;
		for (i = 0; i < t_process.size(); i++)
		{
			if (state[i] == false)
			{
				for (j = 0; j < t_surplus_space.size(); j++)
				{
					if (t_process[i].require[j] > t_surplus_space[j])
						break;
				}
				if (j == t_surplus_space.size())
				{
					state[i] = true;
					state1 = true;
					t_safely_array.push_back(i + 1);
					for (j = 0; j < t_surplus_space.size(); j++)
						t_surplus_space[j] += t_process[i].acquire[j];
				}
			}
		}
		if (state1 == false)
			break;
	}
	for (i = 0; i < state.size(); i++)
	{
		if (state[i] != 1)
			break;
	}
	if (i == state.size())
	{
		safely_array = t_safely_array;
		for (i = 0; i < surplus_space.size(); i++)
		{
			surplus_space[i] -= t_resources[i];
			process[id - 1].require[i] -= t_resources[i];
			process[id - 1].acquire[i] += t_resources[i];
		}
		cout << "����ɹ�!";
		system("pause");
		return true;
	}
	else
	{
		cout << "�޷����ɰ�ȫ����!����ʧ��!";
		system("pause");
		return false;
	}
}
void Banker::show()
{
	cout << "��Դ�ܴ�СΪ: ";
	size_t i;
	size_t j;
	for (i = 0; i < total_space.size(); i++)
	{
		cout << total_space[i] << " ";
	}
	cout << "ʣ������ԴΪ: ";
	for (i = 0; i < surplus_space.size(); i++)
	{
		cout << surplus_space[i] << " ";
	}
	cout << "\n";
	for (i = 0; i < process.size(); i++)
	{
		cout << "����" << i << " : " << endl;
		cout << "�ѻ�ȡ��Դ: ";
		for (j = 0; j < process[i].acquire.size(); j++)
		{
			cout << process[i].acquire[j] << " ";
		}
		cout << "\n";
		cout << "����Ҫ��Դ: ";
		for (j = 0; j < process[i].require.size(); j++)
		{
			cout << process[i].require[j] << " ";
		}
		cout << "\n";
	}
	cout << "��ȫ����Ϊ: ";
	for (i = 0; i < safely_array.size(); i++)
		cout << safely_array[i] << " ";
	cout << "\n";
	system("pause");
}
