//集合 A = {1,2,3,4}
//关系矩阵为：
//1 0 1 0
//0 1 0 0
//1 0 1 1
//0 0 1 1
//满足：自反性、对称性
//集合 A 的闭包：
//1 0 1 1
//0 1 0 0
//1 0 1 1
//1 0 1 1
#include <iostream>
using namespace std;

#define MAX 1000
bool flag_ref, flag_irr, flag_sym, flag_dis, flag_tra;  //判断自反性、反自反性、对称性、反对称性、传递性的 flag
int matrix[MAX][MAX];
int n;


//自反性
void Reflexive(){
	flag_ref = true;
	for(int i = 0; i < n; ++i){
		if(matrix[i][i] != 1){  //只要有一个对角线元素为 0：即不满足
			flag_ref = false;
			break;
		}
	}
}


//反自反性
void Irreflexive(){
	flag_irr = true;
	for(int i = 0; i < n; ++i){
		if(matrix[i][i] == 1){  //只要有一个对角线元素为 1：即不满足
			flag_irr = false;
			break;
		}
	}
}


//对称性
void Symmetrical(){
	flag_sym = true;
	for(int i = 0 ; i < n; ++i){
		for(int j = 0; j < n; ++j){
			if(matrix[i][j] != matrix[j][i]){  //只要有一对对称元素不相等：即不满足对称性
				flag_sym = false;
				break;
			}
		}
	}
}


//反对称性
void Dissymmetrical(){
	flag_dis = true;
	for(int i = 0 ; i < n; ++i){
		for(int j = 0; j < n; ++j){
			if(matrix[i][j] == matrix[j][i]){  //只要有一对对称元素相等：即不满足反对称性
				flag_dis = false;
				break;
			}
		}
	}
}


//传递性
void Transitive(){
	flag_tra = true;
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			for(int k = 0; k < n; ++k){
				if(matrix[i][j] && matrix[j][k] && !matrix[i][k]){  //前两个为 1，第三个为 0
					flag_tra = false;
					break;
				}
			}
		}
	}
}


//求闭包
void Closure(){
	for(int i = 0; i < n; ++i){  //列
		for(int j = 0; j < n; ++j){  //行
			if(matrix[j][i] == 1){
				for(int k = 0 ; k < n; ++k){
					if(matrix[j][k] == 0 && matrix[i][k] == 0){
						matrix[j][k] = 0;
					}
					else if(matrix[j][k] == 0 && matrix[i][k] == 1){
						matrix[j][k] = 1;
					}
					else if(matrix[j][k] == 1 && matrix[i][k] == 0){
						matrix[j][k] = 1;
					}
					else if(matrix[j][k] == 1 && matrix[i][k] == 1){
						matrix[j][k] = 1;
					}
				}
			}
		}
	}
}


int main(){
	int a[MAX];
	cout << "Please input the n of the set:" << endl;
	cin >> n;
	cout << "Please input the elements of the set:" << endl;
	for(int i = 0; i < n; ++i){
		cin >> a[i];
	}
	cout << "The set A = {";
	for(int i = 0; i < n-1; ++i){
		cout << a[i] << ",";
	}
	cout << a[n-1] << "}" << endl;
	cout << "Please input the Relation matrix:" << endl;
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			cin >> matrix[i][j];
		}
	}
	cout << endl;
	Reflexive();
	Irreflexive();
	Symmetrical();
	Dissymmetrical();
	Transitive();
	cout << "The set A has some characters:" << endl; 
	if(flag_ref == true){
		cout << "自反性" << endl;
	}
	if(flag_irr == true){
		cout << "反自反性" << endl;
	}
	if(flag_sym == true){
		cout << "对称性" << endl;
	}
	if(flag_dis == true){
		cout << "反对称性" << endl;
	}
	if(flag_tra == true){
		cout << "传递性" << endl;
	}
	cout << endl;
	cout << "Output the Closure of the set A:" << endl;
	Closure();
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}