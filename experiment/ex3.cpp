#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
using namespace std;
int count = 0;  //从 0 开始计数
int n;  //正整数
int factors[100];  //存因子
int matrixs[100][100] = {0};  //初始化为 0 


//计算正整数 n 的因子
void factor(){
	cout << "The factors of " << n << " are: " << endl;
	for(int i = 1; i <= n/2; ++i){  //到 n/2 结束就行
		if(n % i == 0){
			factors[count++] = i;
			cout << i << ",";
		}
	}
	factors[count] = n;  //n 自己也是因子
	cout << n << endl;
}


//盖住关系
void cover(){
	//关系矩阵初始化
	for(int i = 0; i <= count; ++i){
		for(int j = 0; j <= count; ++j){
			if(factors[j] % factors[i] == 0){  //如果满足整除关系，就设为 1
				matrixs[i][j] = 1;
			}
		}
	}
	//开始判断
	for(int i = 0; i <= count; ++i){
		for(int j = 0; j <= count; ++j){
			for(int k = 0; k <= count; ++k){
				matrixs[k][k] = 0;  //先去掉自反性
				if(matrixs[i][j] && matrixs[j][k]){
					matrixs[i][k] = 0;  //再去掉传递性
				}
			}
		}
	}
	cout << "The cover is: {";
	for(int i = 0; i <= count; ++i){
		for(int j = 0; j <= count; ++j){
			if(matrixs[i][j]){  //除去前面去掉的，其他就满足盖住关系了
				cout << " <" << factors[i] << "," << factors[j] << ">";
			}
		}
	}
	cout << " }" << endl;
}

//求最大公约数
int gcd(int x, int y){
	int m;
	//辗转相除法
	while(m != 0){
		m = x % y;
		x = y;
		y = m;
	}
	return x;
}

//判断有补格
void complemented_lattice(){
	bool flag;
	int Gcd, Lcm;
	for(int i = 1; i < count; i++)
	{
		flag = false;
		for(int j = 1; j < count; j++)
		{
			if(i == j)
				continue;
			Gcd = gcd(factors[i], factors[j]);  //最大公约数，即最大下界
            Lcm = factors[i] / Gcd * factors[j];  //最小公倍数，即最小上界
			if(Gcd == factors[0] && Lcm == factors[count])  //最大下界为 1，最小上界为 n
			{
				flag = true;
				break;
			}
			if(!flag)
			{
				cout << "This is not complemented lattice!" << endl;
				return;
			}
		}
	}
	cout << "This is complemented lattice!" << endl;
	return;
}


int main(){
	cout << "Please input a positive integer: ";
	cin >> n;
	cout << endl;
	factor();
	cout << endl;
	cover();
	cout << endl;
	complemented_lattice();
	cout << endl;
	return 0;
}