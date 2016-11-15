#include <stdlib.h>
#include <fstream>		//header for file-handling.
#include "senetence_parser.cpp"
// #include "segment_words.cpp"
#include <locale>
#include <sstream>

using namespace std;

// File to take converation input from
string g_file_name = "sample.txt";
// File which contains the dictionary
string dictionary_file = "sample_words.txt";

// All the words which have been processed from the conversation
string tokens[2048];
// Actual content which will be uploaded to the XML.
string xml_uploads[2048][3];

// stores last index of token which has been filled.
int current = 0;

int count_words_per_message[10];

// Name of the people conversing
string name1, name2;

// stores last index of xml content which has been filled.
int current_xml = 0;


void update_xml(string message_number, string current_word, string category){
	xml_uploads[current_xml][0] = message_number;
	xml_uploads[current_xml][1] = current_word;
	xml_uploads[current_xml++][2] = category;
}

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
					update_xml(message_number, current_word, category);
					break;
				}
				current_word = "";
			}
		}
	}
	file.close();
}

void uploadToXML(){
	int i;
	string count = "";
	fr(i, current_xml){
		if (count != xml_uploads[i][0]){
			count = xml_uploads[i][0];
			int j;
			std::istringstream ss(count);
			ss >> j;
			cout << j << endl;
			if (j%2==0)
			{
				string attributes[][2]={{"name", name1}};
				XMLElement * pElement = createChild("Person", attributes, 1);
				XMLElement * pElement1 = createChild("Message", attributes, 0, pElement);
				while (count == xml_uploads[i][0]){
					attributes[0][0] = "category";
					attributes[0][1] = xml_uploads[i][2];
					addDatatoXMLElement(pElement1, "Word", xml_uploads[i][1], attributes, 1);
					i++;
				}
				i--;
			}else{
				string attributes[][2]={{"name", name2}};
				XMLElement * pElement = createChild("Person", attributes, 1);
				XMLElement * pElement1 = createChild("Message", attributes, 0, pElement);
				while (count == xml_uploads[i][0]){
					attributes[0][0] = "category";
					attributes[0][1] = xml_uploads[i][2];
					addDatatoXMLElement(pElement1, "Word", xml_uploads[i][1], attributes, 1);
					i++;
				}
				i--;
			}
		}
	}
	saveXMLDocument("SavedData.xml");
}

string getFileContent(){
	ifstream file (g_file_name.c_str());
	string file_content;
	if (file.is_open()){
		char x;
		while ((x = file.get()) != EOF){
			file_content += x;
		}
	}
	file.close();
	return file_content;
}

int main(){
	createXMLDocument();
	string file_content = getFileContent();
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

	fr(i, current_xml){
		cout << xml_uploads[i][0] << "  ";
		cout << xml_uploads[i][1] << "  ";
		cout << xml_uploads[i][2] << "  ";
		cout << endl;
	}
	uploadToXML();
	// saveXMLDocument("SavedData.xml");
}