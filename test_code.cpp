// #include <iostream>
// #include <stdio>

// int main(){

// }

#include <iostream>
#include <stdlib.h>

using namespace std;

int main(){
	string arr[][2] = {{"a", "b"}, {"d", "e"}, {"d", "e"}};;
	int one = (sizeof arr / sizeof arr[0]);
	int two = (sizeof arr[0] / sizeof arr[0][0]);
	cout << one << "  " << two;
}