//(P^Q) V (非P^R)
//主合取范式: (非PVQV非R) ^ (非PVQVR) ^ (PV非QVR) ^ (PVQVR)
//主析取范式: (P^Q^R) V (P^Q^非R) V (非P^Q^R) V (非P^非Q^R)
#include <iostream>
#include <cmath>
using namespace std;
int a[1000], b[1000], c[1000];  //P^Q  非P^R  A
int x[1000], y[1000], z[1000];  //P Q R
int n;


//输出真值表
void Output_truth_table(){
	cout << endl << "The truth table is:" << endl;
	cout << 'P' << '\t' << 'Q' << '\t' << 'R' << '\t';
	cout << "P^Q" << '\t' << "非P^R" << '\t' << "(P^Q) V (非P^R)" << endl;
	for(int i = 0; i < pow(2, n); ++i){
		//输出 P Q R 的真值
		if(i < pow(2, n-1)){
			x[i] = 1;
			cout << 'T' << '\t';
		}
		if(i >= pow(2, n-1)){
			x[i] = 0;
			cout << 'F' << '\t';
		}
		if(i % 4 < 2){
			y[i] = 1;
			cout << 'T' << '\t';
		}
		if(i % 4 >= 2){
			y[i] = 0;
			cout << 'F' << '\t';
		}
		if(i % 2 == 0){
			z[i] = 1;
			cout << 'T' << '\t';
		}
		if(i % 2 == 1){
			z[i] = 0;
			cout << 'F' << '\t';
		}
		//输出(P^Q)  (非P^R)  (P^Q) V (非P^R) 的真值
		if(a[i] == 1) cout << 'T' << '\t';
		else if(a[i] == 0) cout << 'F' << '\t';
		if(b[i] == 1) cout << 'T' << '\t';
		else if(b[i] == 0) cout << 'F' << '\t';
		if(c[i] == 1) cout << 'T' << endl;
		else if(c[i] == 0) cout << 'F' << endl;
	}
}


//主合取范式
void Master_conjunction(){
	cout << endl << "Master_conjunction is: ";
	int count = 0;
	for(int i = 0; i < pow(2, n); ++i){
		if(c[i] == 0){  //如果公式真值为假，则输出相应的真值相反的 P Q R
			if(x[i] == 1 && y[i] == 1 && z[i] == 1){
				cout << "(非PV非QV非R)";
				count++;
			}
			else if(x[i] == 1 && y[i] == 1 && z[i] == 0){
				cout << "(非PV非QVR)";
				count++;
			}
			else if(x[i] == 1 && y[i] == 0 && z[i] == 1){
				cout << "(非PVQV非R)";
				count++;
			}
			else if(x[i] == 1 && y[i] == 0 && z[i] == 0){
				cout << "(非PVQVR)";
				count++;
			}
			else if(x[i] == 0 && y[i] == 1 && z[i] == 1){
				cout << "(PV非QV非R)";
				count++;
			}
			else if(x[i] == 0 && y[i] == 1 && z[i] == 0){
				cout << "(PV非QVR)";
				count++;
			}
			else if(x[i] == 0 && y[i] == 0 && z[i] == 1){
				cout << "(PVQV非R)";
				count++;
			}
			else if(x[i] == 0 && y[i] == 0 && z[i] == 0){
				cout << "(PVQVR)";
				count++;
			}
			if(count != pow(2, n-1)) cout << " ^ ";
		}
	}
	cout << endl;
}


//主析取范式
void Master_disjunction(){
	cout << endl << "Master_disjunction is: ";
	int count = 0;
	for(int i = 0; i < pow(2, n); ++i){
		if(c[i] == 1){  //如果公式真值为真，则输出相应真值的 P Q R
			if(x[i] == 1 && y[i] == 1 && z[i] == 1){
				cout << "(P^Q^R)";
				count++;
			}
			else if(x[i] == 1 && y[i] == 1 && z[i] == 0){
				cout << "(P^Q^非R)";
				count++;
			}
			else if(x[i] == 1 && y[i] == 0 && z[i] == 1){
				cout << "(P^非Q^R)";
				count++;
			}
			else if(x[i] == 1 && y[i] == 0 && z[i] == 0){
				cout << "(P^非Q^非R)";
				count++;
			}
			else if(x[i] == 0 && y[i] == 1 && z[i] == 1){
				cout << "(非P^Q^R)";
				count++;
			}
			else if(x[i] == 0 && y[i] == 1 && z[i] == 0){
				cout << "(非P^Q^非R)";
				count++;
			}
			else if(x[i] == 0 && y[i] == 0 && z[i] == 1){
				cout << "(非P^非Q^R)";
				count++;
			}
			else if(x[i] == 0 && y[i] == 0 && z[i] == 0){
				cout << "(非P^非Q^非R)";
				count++;
			}
			if(count != pow(2, n-1)) cout << " V ";
		}
	}
	cout << endl;
}


int main(){
	cout << "Please input the number of variable:";
	cin >> n;
	cout << endl << "The formula is:(P^Q) V (非P^R)" << endl;
	int m1 = 0;
	int m2 = 0;
	int m3 = 0;
	//三重循环
	for(int i = 0; i < 2; ++i){
		for(int j = 0; j < 2; ++j){
			for(int k = 0; k < 2; ++k){
				if(i == 0 && j == 0){
					a[m1++] = 1;  //P为真，Q为真：P^Q 为真
				}
				if(j == 1 || i == 1){
					a[m1++] = 0;  //P为真，Q为假 或 P为假：P^Q 为假
				}
				if(i == 0 || k == 1){
					b[m2++] = 0;  //P为真 或 P为假，R为假：(非P^R)为假
				}
				if(i == 1 && k == 0){
					b[m2++] = 1;  //P为假 且 R为真：(非P^R)为真
				}
			}
		}
	}
	for(int m3 = 0; m3 < pow(2, n); ++m3){
		if(a[m3] == 0 && b[m3] == 0){  //P^Q 为假 且 (非P^R)为假
			c[m3] = 0;
		}
		else c[m3] = 1;
	}
	Output_truth_table();
	Master_conjunction();
	Master_disjunction();
	return 0;
}