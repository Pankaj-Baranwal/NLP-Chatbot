// #include <iostream>
// #include <stdio>

// int main(){

// }

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <locale>

using namespace std;

int display(){
	cout << "Displaying" << endl;
}
int main(){
	string current = "pankaj";
	string m;
	char a[] = {'p', 'a', 'n', 'k', 'i', 'j'};
	for (int i = 0; i<6; i++){
		m+= a[i];
	}
	cout << m << " " << current << endl;
	if(strcmp(current.c_str(), m.c_str())){
		cout << "MATCHED";
	}
}