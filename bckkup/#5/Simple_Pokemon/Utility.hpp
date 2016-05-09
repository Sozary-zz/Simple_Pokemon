#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
struct Position
{
	int x;
	int y;
};

struct Node
{
	Position coord;
	double cout;
	double heuristique;
	Node* parent;
	
	bool operator<(Node& a)
	{
		return heuristique < a.heuristique;
	}
};

std::vector<std::string> split(std::string , char );
int distanceE(int , int , int , int );

