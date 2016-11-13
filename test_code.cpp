// #include <iostream>
// #include <stdio>

// int main(){

// }

#include <iostream>
#include <stdlib.h>
#include <string>
#include <locale>
#include <sstream>

using namespace std;

int display(){
	cout << "Displaying" << endl;
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
	int a = 1;
	std::stringstream ss;
	ss << a;
	string s = ss.str();
	cout << s << endl;
}