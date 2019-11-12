#pragma once
#include <vector>


using std::vector;


class Initializer
{
	static double eval_for_4(double, double);
public:
	static void init_weights_0(vector<double>&);
	static void init_restrictions_matrix_1(vector<vector<double>> &a);
	static void init_restrictions(vector<double>& a);
	static vector<vector<double>> make_matrix4(vector<double> a);
};

