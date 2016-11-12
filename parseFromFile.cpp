#include <iostream>
#include <stdlib.h>
#include <string.h>		//header for string functionality.
#include <fstream>		//header for file-handling.

using namespace std;

#define fr(i, a) for (i = 0; i<a; i++)

string g_file_name = "sample.txt";

string tokens[2048];
int current = 0;

int main(){
	ifstream file (g_file_name.c_str());
	string file_content;
	if (file.is_open()){
		char x;
		while ((x = file.get()) != EOF){
			file_content += x;
		}
	}
	// cout << file_content;
	file.close();
	int i;
	fr(i, file_content.length()){
		string person_name = "";
		while (file_content[i] != '\n' && file_content.length()!=i ){
			// cout << file_content[i] << " a" << endl;
			string temp = "";
			if (!person_name.length())
			{
				while (file_content[i] != ':'){
					temp += file_content[i++];
				}
				person_name = temp;
			}else{
				while ((file_content[i] >= 'a' && file_content[i] <= 'z') || (file_content[i] >= 'A' && file_content[i] <= 'Z')){
					temp += file_content[i];
					i++;
				}
				if (temp.length())
				{
					tokens[current] = temp;
				}else{
					i++;
				}
			}
		}
	}

	fr(i, current){
		cout << tokens[i] << endl;
	}
}

