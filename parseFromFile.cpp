#include <stdlib.h>
#include <fstream>		//header for file-handling.
#include "senetence_parser.cpp"
// #include "segment_words.cpp"
#include <locale>
#include <sstream>

using namespace std;


string g_file_name = "sample.txt";
string dictionary_file = "sample_words.txt";

string tokens[2048];
string xml_uploads[2048][3];
int current = 0, max_words = 0;
int count_words_per_message[10];
string name1, name2;
int current_xml = 0;

void searchWordInDictionary(string word, string message_number){
	ifstream file (dictionary_file.c_str());
	int found_word = 0;
	string current_word = "";
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
				else if (!strcmp(word.c_str(), current_word.c_str()))
				{
					found_word = 1;
					xml_uploads[current_xml][0] = message_number;
					xml_uploads[current_xml][1] = current_word;
					xml_uploads[current_xml++][2] = category;
					break;
				}
				current_word = "";
			}
		}
	}
	file.close();
}

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
	int counter = 0;
	int num_of_words = 0;
	string person_name = "";
	fr(i, file_content.length()){
		if (person_name.length())
		{
			count_words_per_message[counter++] = num_of_words;
		}
		person_name = "";
		while (file_content[i] != '\n' && file_content.length()!=i ){
			// cout << file_content[i] << " a" << endl;
			string temp = "";
			if (!person_name.length())
			{
				while (file_content[i] != ':'){
					temp += file_content[i++];
				}
				person_name = temp;
				num_of_words = 0;
				if (!name1.length())
				{
					name1 = person_name;
				}else if (!name2.length())
				{
					name2 = person_name;
				}
			}else{
				while ((file_content[i] >= 'a' && file_content[i] <= 'z') || (file_content[i] >= 'A' && file_content[i] <= 'Z')){
					temp += file_content[i];
					i++;
				}
				if (temp.length())
				{
					num_of_words++;
					tokens[current++] = temp;
				}else{
					i++;
				}
			}
		}
	}
	count_words_per_message[counter++] = num_of_words;
	// at this point, we havev all the words separated in the token array.

	// fr(i, current) cout << tokens[i] << endl;
	fr (i, current){
		std::locale loc;
		int j;
		string replacement;
		fr (j, tokens[i].length())
			replacement += tolower(tokens[i][j], loc);
		int k =0;
		int total = 0;
		while (i >= total + count_words_per_message[k]){
			total += count_words_per_message[k];
			k++;
		}
		std::stringstream ss;
		ss << k;
		searchWordInDictionary(replacement, ss.str());
	}
	// saveXMLDocument("SavedData.xml");
}