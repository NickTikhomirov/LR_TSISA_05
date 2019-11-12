#include "Initializer.h"

using std::vector;

void Initializer::init_weights_0(vector<double>& a) {
	a.resize(4);
	a[0] = 6;
	a[1] = 4;
	a[2] = 5;
	a[3] = 10;
}


void Initializer::init_restrictions_matrix_1(vector<vector<double>> &a) {
	a.resize(4);
	for (int i = 0; i < a.size(); i++)
		a[i].resize(4);
	
	//Anatoli, Alex, Vladimir, Sergey

	//educat
	a[0][0] = 4;	a[0][1] = 7;	a[0][2] = 3;	a[0][3] = 8;
	//phys
	a[1][0] = 3;	a[1][1] = 7;	a[1][2] = 8;	a[1][3] = 7;
	//face
	a[2][0] = 9;	a[2][1] = 6;	a[2][2] = 9;	a[2][3] = 6;
	//mood
	a[3][0] = 3;	a[3][1] = 8;	a[3][2] = 7;	a[3][3] = 5;
}

void Initializer::init_restrictions(vector<double>& a) {
	a.resize(3);
	a[0] = 0.5;
	a[1] = 0.2;
	a[2] = 0.4;
}


double Initializer::eval_for_4(double a, double b) {
	bool swap = (a < b);
	if (swap) std::swap(a, b);
	if ((a - b) < 3) return ((swap)?1.0/3:3);
	if ((a - b) < 5) return ((swap)?1.0/5:5);
	if ((a - b) < 7) return ((swap)?1.0/7:7);
	return ((swap)?1.0/9:9);
}

vector<vector<double>> Initializer::make_matrix4(vector<double> a) {
	vector<vector<double>> result;
	result.resize(4);
	for (int i = 0; i < 4; i++) {
		result[i].resize(4);
		for (int j = 0; j <= i; j++) {
			if (a[i] == a[j]) {
				result[i][j] = 1;
				result[j][i] = 1;
			}
			else {
				result[i][j] = eval_for_4(a[i],a[j]);
				result[j][i] = 1.0/result[i][j];
			}
		}
	}
	return result;
}