// #include <iostream>
// #include <stdio>

// int main(){

// }

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <locale>
#include <sstream>

using namespace std;

int display(){
	cout << "Displaying" << endl;
}

void test0(){
	int a = 1;
	std::stringstream ss;
	ss << a;
	string s = ss.str();
	cout << s << endl;
}

void test1(){
	string a = "Pankaj";
	cout << a[0] << endl;
	if (a[0] >= 'A' && a[0]<='Z')
	{
		cout << "TRUE";
	}else cout << "FALSE";
}

int main(){
	// string current = "pankaj";
	// string m;
	// char a[] = {'p', 'a', 'n', 'k', 'i', 'j'};
	// for (int i = 0; i<6; i++){
	// 	m+= a[i];
	// }
	// cout << m << " " << current << endl;
	// if(strcmp(current.c_str(), m.c_str())){
	// 	cout << "MATCHED";
	// }
	test1();
}