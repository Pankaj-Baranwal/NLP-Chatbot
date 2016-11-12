#include <iostream>
#include <stdlib.h>
#include <string.h>		//header for string functionality.
#include <fstream>		//header for file-handling.
#include "senetence_parser.cpp"
// #include "segment_words.cpp"

using namespace std;

#define fr(i, a) for (i = 0; i<a; i++)

string g_file_name = "sample.txt";
string dictionary_file = "sample_words.txt"

string tokens[2048];
string words_in_dictionary[2048];
int current = 0, max_words = 0;

int main(){
	createXMLDocument();
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
					tokens[current++] = temp;
				}else{
					i++;
				}
			}
		}
	}
	// at this point, we havev all the words separated in the token array.

	// fr(i, current) cout << tokens[i] << endl;
	fr (i, current){
		searchWordInDictionary(tokens[i]);
	}
	saveXMLDocument("SavedData.xml");
}

void parseAllWordsInDictinary(string fileName){
	ifstream file (fileName.c_str());
	string file_content;
	if (file.is_open()){
		char x;
		while ((x = file.get()) != EOF){
			if (x == '\n')
			{
				max_words++;
			}
			file_content += x;
		}
	}
	// cout << file_content;
	file.close();
	int i;
}

void searchWordInDictionary(string word){
	ifstream file (dictionary_file.c_str());
	int found_word = 0;
	string current_word;
	string category;
	if (file.is_open())
	{
		char x;
		while ((x = file.get()) != EOF){
			if (x != '\n')
			{
				current_word += x;
			}else{
				if (current_word[0]=='*')
				{
					category = current_word;	
				}
				else if (strcmp(word, current_word))
				{
					found_word = 1;
					string attributes[][2] = {{"category", category}};
					int size = sizeof attributes/ sizeof attributes[0];
					addDataToXMLDocument("word", current_word, attributes, size);
					break;
				}
				current_word = "";
			}
		}
		if (!found_word)
		{
			
		}
	}
}