#ifndef BANKER_H
#define BANKER_H

#include <vector>
using std::vector;

class Banker
{
private:
	struct Process
	{
		vector<int> require;
		vector<int> acquire;
	};
	vector<int> total_space;
	vector<Process> process;
	vector<int> surplus_space;
	vector<int> safely_array;
	bool safely(int, vector<int> & const);
public:
	Banker(){};
	bool set_size();
	bool create_process();
	bool apply();
	void show();
};

#endif