#include <iostream>
#include <vector>
#include "Initializer.h"
#include <iomanip>
#include <cmath>


using std::vector;
using std::cout;
using std::endl;

void normalize(vector<double> &a) {
	double summ = 0;
	for (int i = 0; i < a.size(); i++) {
		summ += a[i];
	}
	for (int i = 0; i < a.size(); i++) {
		a[i]/=summ;
	}
}



void cout_matrix(vector<vector<double>> a) {
	cout << std::fixed << std::setprecision(4) << " - |\t";
	for (int i = 0; i < 4; i++) {
		cout << i + 1 << "     |\t";
	}
	cout << "\n";
	for (int i = 0; i < 4; i++) {
		for (int j = -1; j < 4; j++) {
			if (j == -1)
				cout << " " << char('A' + i) << " |\t";
			else {
				cout << a[j][i] << "|\t";
			}
		}
		cout << "\n";
	}
}

void cout_horizontal(vector<double> a) {
	cout << " - |\t";
	for (int i = 0; i < 4; i++) {
		cout << i + 1 << "     |\t";
	}
	cout << "\n - |\t";
	for (int i = 0; i < 4; i++) {
		if (a.size()<4 && i== 0) cout << "-     ";
		else cout << a [i - (a.size()<4)];
		cout << "|\t";
	}
	cout << "\n\n";
}


//1
void normalize_restrictions_1(vector<double> &a) {
	double min = a[0];
	double max = a[0];
	for (int i = 1; i < a.size(); i++) {
		if (min > a[i]) min = a[i];
		if (max < a[i]) max = a[i];
	}
	for (int i = 0; i < a.size(); i++) 
		a[i] = (a[i] - min) / (max - min);
}
//-1

//3
double multiply(vector<double> a, vector<double> b) {
	double result = 0;	
	for (int i = 0; i < 4; i++) {
		result += a[i]*b[i];
	}
	return result;
}
//-3

//4
vector<double> cout_count_matrix4(vector<vector<double>> a,int k, bool mode) {
	vector<double> hor_summ		{0,0,0,0};
	vector<double> hor_mult {1,1,1,1};
	vector<double> ver_summ {0,0,0,0};
	double hor_mult_summ = 0;
	double lambda = 0;
	vector<double> result;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			hor_summ[i] += a[i][j];
			hor_mult[i] *= a[i][j];
		}
		hor_mult[i] = sqrt(sqrt(hor_mult[i]));
		hor_mult_summ += hor_mult[i];
	}

	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 4; i++) {
			ver_summ[j] += a[i][j];
		}
		hor_mult[j] /= hor_mult_summ;
		lambda += hor_mult[j] * ver_summ[j];
	}

	result = hor_summ;
	normalize(result);
	double index_onesound = (lambda-4)/2.7;

	cout << std::fixed << std::setprecision(4) << " "<<k+1<<" |\t";
	for (int i = 0; i < 4; i++) {
		cout << char(i + (mode?'1':'A')) << "     |\t";
	}
	cout<<" summ|\t\t norm|"<<"\n";
	for (int i = 0; i < 4; i++) {
		cout << " " << char((mode ? '1' : 'A') + i) << " |\t";
		for (int j = 0; j < 4; j++) {
			cout << a[i][j] << "|\t";
		}
		cout<<hor_summ[i]<<" |\t"<<result[i] << "\n";
	}
	cout <<"Otnoshenie sogl-ti: "<<index_onesound<< "\n\n";
	return result;
}

//-4



int main() {
	vector<double> weights;
	Initializer::init_weights_0(weights);
	vector<double> weights4 = weights;
	normalize(weights);

	//1-------------------------------------------------------------------------------------------
	cout << "NOW COUNTING WITH (1), METHOD OF REPLACEMENT WITH RESTRICTIONS\n";
	vector<vector<double>> matrix1;
	Initializer::init_restrictions_matrix_1(matrix1);
	vector<vector<double>> matrix3 = matrix1;
	cout_matrix(matrix1);

	vector<vector<vector<double>>> cube_matrix4;
	cube_matrix4.resize(4);
	for (int i = 0; i < 4; i++)
		cube_matrix4[i] = Initializer::make_matrix4(matrix1[i]);
	

	cout << "\n\n"<<"Columns 2,3,4 have been normalized\n\n";
	//let's state education (0) as the main criteria and normalize our matrix
	for (int i = 1; i < matrix1.size(); i++)
		normalize_restrictions_1(matrix1[i]);
	cout_matrix(matrix1);


	vector<double> restrictions;
	Initializer::init_restrictions(restrictions);  
	cout << "\n\nRestrictions:\n";
	cout_horizontal(restrictions);

	char final_filter_1 = 15;
	for (int i = 1; i < matrix1.size(); i++) {
		for (int j = 0; j < matrix1[i].size(); j++) {
			if (matrix1[i][j] < restrictions[i - 1]) {
				final_filter_1 &= 15^(1<<j);
			}
		}
	}


	int i_max = 0;
	double d_max = 0;
	for (int i = 0; i < 4; i++) {
		if (matrix1[0][i] > d_max && (final_filter_1&(1<<i))) {
			i_max = i;
			d_max = matrix1[0][i];
		}
	}
	if(i_max == 0) cout << "Nobody is good enough" << endl;
	cout << "The answer is " << char('A' + i_max) << endl << endl <<endl;
	
	//3--------------------------------------------------------------------------------------------------------------------
	cout << "NOW COUNTING WITH (3), METHOD OF WEIGHT AND UNITE\n";
	cout_matrix(matrix3);
	for(int i=0;i<4;i++)
		normalize(matrix3[i]);

	cout << "\n\nThe matrix was normalized:\n";
	cout_matrix(matrix3);
	cout << "\n\nOur weights:\n";
	cout_horizontal(weights);

	cout <<endl<< "Criteria uniting:"<<endl;
	vector<double> united_criteria;
	i_max = 0;
	d_max = 0;
	united_criteria.resize(4);
	for (int j = 0; j < 4; j++) {
		vector<double> horizontal;
		horizontal.resize(4);
		for (int i = 0; i < 4; i++)
			horizontal[i] = matrix3[i][j];
		united_criteria[j] = multiply(horizontal, weights);
		if (d_max < united_criteria[j]) {
			i_max = j;
			d_max = united_criteria[j];
		}
		cout << " " << char('A'+j) << "\t|" << united_criteria[j]<<endl;
	}
	cout << endl << "The result of uniting: the best option is " << char('A'+i_max) << endl << endl << endl;

	//4--------------------------------------------------------------------------------------------------------------------
	cout<< "NOW COUNTING WITH (4), METHOD OF HIERARCHY ANALYSIS\n";
	vector<vector<double>> hor_summ_x4;
	
	hor_summ_x4.resize(4);
	cout << "Our tables:\n\n";
	for (int i = 0; i < 4; i++)
		hor_summ_x4[i] = cout_count_matrix4(cube_matrix4[i],i,false);
	cout << "Criteria table:\n\n";
	weights4 = cout_count_matrix4(Initializer::make_matrix4(weights4),0,true);

	cout << endl << "Multiplying:" << endl;
	vector<double> result4;
	i_max = 0;
	d_max = 0;
	result4.resize(4);
	for (int j = 0; j < 4; j++) {
		vector<double> horizontal;
		horizontal.resize(4);
		for (int i = 0; i < 4; i++)
			horizontal[i] = hor_summ_x4[i][j];
		result4[j] = multiply(horizontal, weights4);
		if (d_max < result4 [j] ) {
			i_max = j;
			d_max = result4[j];
		}
		cout << " " << char('A' + j) << "\t|" << result4[j] << endl;
	}
	cout << endl << "The result of hierarcy analysis " << char('A' + i_max) << endl << endl << endl;
}


