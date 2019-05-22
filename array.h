#pragma once
#include "../../project_1/project_1/class_1.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct City
{
	string name = "";
	int index = 0;
	int CoastFromCity = 0;
	City(string name1, int CoastFromCity1, int index1) : name(name1), CoastFromCity(CoastFromCity1), index(index1) {};
	City() {};
	
};

class Dijkstra
{
public:
	bool check;
	int coast;
	string Dname;
	List<City> *elem;
	Dijkstra(string str) : Dname(str), check(false), coast(0), elem(new List<City>()){};
};

class Alg
{
	std::vector<Dijkstra> arr;
public:
	void input();
	int find_path(string, string);
	~Alg()
	{
		for (int i = 0; i < arr.size(); ++i)
			arr[i].elem->clear();
	}
};

void Alg::input()
{
	fstream file;
	file.open("data.txt", ios_base::in);
	if (file.is_open())
	{
		while (!file.eof())
		{
			bool flaq = false;
			string city1, city2, coast1, coast2;
			int index1, index2, num1, num2;
			std::getline(file, city1, ';');
			for (int i = 0; i < arr.size() && !flaq; ++i)
			{
				if (arr[i].Dname == city1)
				{
					flaq = true;
					index1 = i;
				}
			}
			if (!flaq)
			{
				index1 = arr.size();
				arr.push_back(Dijkstra(city1));
			}
			flaq = false;
			std::getline(file, city2, ';');
			for (int i = 0; i < arr.size() && !flaq; ++i)
			{
				if (arr[i].Dname == city2)
				{
					flaq = true;
					index2 = i;
				}
			}
			if (!flaq)
			{
				index2 = arr.size();
				arr.push_back(Dijkstra(city2));
			}
			std::getline(file, coast1, ';');
			if (coast1 != "N/A")
			{
				num1 = std::stoi(coast1);
				arr[index1].elem->push_back(City(city2, num1, index2));
			}
			std::getline(file, coast2, '\n');
			if (coast2 != "N/A")
			{
				num2 = std::stoi(coast2);
				arr[index2].elem->push_back(City(city1, num2, index1));
			}
		}
	}
	else
		std::cout << "error" << endl;
}

int Alg::find_path(string dep, string arrive)
{
	if (dep != arrive)
	{
		int number_of_dep = 0,
			number_of_arrive = 0;
		int mincoast = 0;
		int tmpindex = 0;
		std::vector<int> indexx;
		bool flaq = false;
		for (int i = 0; i < arr.size(); ++i)
		{
			if (arr[i].Dname == dep)
			{
				number_of_dep = i;
				arr[i].check = true;
				indexx.push_back(i);
			}
			if (arr[i].Dname == arrive)
				number_of_arrive = i;
		}
		while (!flaq)
		{
			mincoast = std::numeric_limits<int>::max();
			for (int i = 0; i < arr.size(); ++i)
			{
				if (arr[i].check)
				{
					int k = arr[i].elem->get_size();
					for (int j = 1; j <= k; ++j)
					{
						bool flaq1 = false;
						for (int m = 0; m < indexx.size(); ++m)
						{
							if (arr[i].elem->at(j).index == indexx[m])
								flaq1 = true;
						}
						if (!flaq1)
						{
							if(arr[arr[i].elem->at(j).index].coast == 0)
								arr[arr[i].elem->at(j).index].coast = arr[i].coast + arr[i].elem->at(j).CoastFromCity;
							else if (arr[i].coast + arr[i].elem->at(j).CoastFromCity < arr[arr[i].elem->at(j).index].coast)
								arr[arr[i].elem->at(j).index].coast = arr[i].coast + arr[i].elem->at(j).CoastFromCity;

							if (arr[arr[i].elem->at(j).index].coast < mincoast)
							{
								mincoast = arr[arr[i].elem->at(j).index].coast;
								tmpindex = arr[i].elem->at(j).index;
							}
						}
					}
				}
			}
			arr[tmpindex].check = true;
			indexx.push_back(tmpindex);
			if (tmpindex == number_of_arrive)
				flaq = true;
		}
		cout <<"You need " << arr[number_of_arrive].coast << " to go from " << dep << " to " << arrive << "\n";
		return arr[number_of_arrive].coast;
	}
	else
	{
		std::cout << "error. d=a\n";
		return -1;
	}
}
