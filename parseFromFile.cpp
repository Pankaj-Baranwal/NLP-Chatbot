#include <stdlib.h>
#include <fstream>		//header for file-handling.
#include "senetence_parser.cpp"
// #include "segment_words.cpp"
#include <locale>

using namespace std;


string g_file_name = "sample.txt";
string dictionary_file = "sample_words.txt";

string tokens[2048];
string xml_uploads[2048][3];
int current = 0, max_words = 0;
int count_words_per_message[10];
string name1, name2;
int current_xml = 0;

void searchWordInDictionary(string word, string root_tag, string message_number){
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
				cout << " " << word << "  " << current_word << endl;
				if (current_word[0]=='*')
				{
					category = current_word;
				}
				else if (!strcmp(word.c_str(), current_word.c_str()))
				{
					found_word = 1;
					xml_uploads[current_xml++] = {message_number, current_word, category}
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
	fr(i, file_content.length()){
		if (person_name.length())
		{
			count_words_per_message[counter++] = num_of_words;
		}
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
	// at this point, we havev all the words separated in the token array.

	// fr(i, current) cout << tokens[i] << endl;
	fr (i, current){
		std::locale loc;
		int j;
		string replacement;
		fr (j, tokens[i].length())
			replacement += tolower(tokens[i][j],loc);
		int k =0;
		while (i < count_words_per_message[k]){
			k++;
		}
		searchWordInDictionary(replacement, --k);
	}
	saveXMLDocument("SavedData.xml");
}