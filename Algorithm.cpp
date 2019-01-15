
#include <iostream>
#include "Algorithm.h"
using std::cout;
using std::cin;
using std::endl;

bool Banker::set_size()
{
	cout << "请输入各类资源总数(输入#结束输入): ";
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
	cout << "请输入该进程的各类资源需求量(输入#结束输入): ";
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
		cout << "创建进程失败!资源分配类型过多/过少!";
		system("pause");
		return false;
	}
	size_t i;
	for (i = 0; i < total_space.size(); i++)
	{
		if (t_pro.require[i] > total_space[i])
		{
			cout << "创建进程失败!资源分配超过最大容量!";
			system("pause");
			return false;
		}
	}
	process.push_back(t_pro);
	return true;
}
bool Banker::apply()
{
	cout << "请输入要申请的进程号(从1开始): ";
	int id;
	cin >> id;
	if (id > process.size())
	{
		cout << "申请失败!没有该进程!";
		system("pause");
		return false;
	}
	vector<int> t_resources;
	cout << "请输入要分配的大小(输入#结束输入): ";
	int t;
	while (cin >> t)
	{
		t_resources.push_back(t);
	}
	cin.clear();
	cin.get();
	if (t_resources.size() != process[id-1].require.size())
	{
		cout << "分配资源失败!资源分配类型过多/过少!";
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
			cout << "分配资源失败!资源分配超过所宣告的剩余需要容量!";
			system("pause");
			return false;
		}
	}
	for (i = 0; i < surplus_space.size(); i++)
	{
		if (t_resources[i] > surplus_space[i])
		{
			cout << "分配资源失败!剩余容量不够!";
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
		cout << "分配成功!";
		system("pause");
		return true;
	}
	else
	{
		cout << "无法构成安全序列!分配失败!";
		system("pause");
		return false;
	}
}
void Banker::show()
{
	cout << "资源总大小为: ";
	size_t i;
	size_t j;
	for (i = 0; i < total_space.size(); i++)
	{
		cout << total_space[i] << " ";
	}
	cout << "剩余总资源为: ";
	for (i = 0; i < surplus_space.size(); i++)
	{
		cout << surplus_space[i] << " ";
	}
	cout << "\n";
	for (i = 0; i < process.size(); i++)
	{
		cout << "进程" << i << " : " << endl;
		cout << "已获取资源: ";
		for (j = 0; j < process[i].acquire.size(); j++)
		{
			cout << process[i].acquire[j] << " ";
		}
		cout << "\n";
		cout << "还需要资源: ";
		for (j = 0; j < process[i].require.size(); j++)
		{
			cout << process[i].require[j] << " ";
		}
		cout << "\n";
	}
	cout << "安全序列为: ";
	for (i = 0; i < safely_array.size(); i++)
		cout << safely_array[i] << " ";
	cout << "\n";
	system("pause");
}
