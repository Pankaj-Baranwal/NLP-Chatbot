#include <stdlib.h>
#include <fstream>		//header for file-handling.
#include "XMLHelper.cpp"
#include "segment_words.cpp"
#include <locale>
#include <sstream>
#include <cstring>

using namespace std;

// File to take conversation input from
string g_file_name = "sample.txt";
// File which contains the dictionary
string dictionary_file = "sample_words.txt";


/*
	Function name: searchWordInDictionary
	Arguments: 1 string argument=> String to be searched in dictionary
	Work: returns true if word found in dictionary
*/
bool searchWordInDictionary(string word){
	ifstream fin (dictionary_file.c_str());
	string temp="";
	while( fin >> temp ){
		if(!strcmp(temp.c_str(),word.c_str()))
		{
			fin.close();
			return true;
		}
	}
	fin.close();
	return false;
}

/*
	Function name: getCategory
	Arguments: 1 string argument=> Word which needs to be categorized
	Work: Returns the pos of the word from dictionary
*/
string getCategory(string word){
	ifstream fin (dictionary_file.c_str());
	string current_cat="",temp="";
	while( fin >> temp){
		// All pos categories have * before their name.
		if( temp[0] =='*'){
			current_cat = temp.substr(1,temp.length());
		}else if(!strcmp(temp.c_str(),word.c_str()))
		{
			fin.close();
			return current_cat;
		}
	}
	fin.close();
}

/*
	Function name: trim
	Arguments: 1 string argument=> String to be trimmed
	Work: Remove extra symbols used with a word
*/
string trim(string word){
	string temp="";
	for(int i=0;i<word.length();i++) {
		if( (word[i]>='A' && word[i]<='Z') || (word[i]>='a' && word[i]<='z') ||(word[i]>='0' && word[i]<='9') ) {
			temp+=word[i];
		}
	}
	return temp;
}

int main(){
	createXMLDocument();
	
	ifstream file (g_file_name.c_str());
	string person_name = "";
	
	XMLElement * pElement;
	XMLElement * pElement1;
	string temp="",tmp="";

	bool can_be_proper_noun;
	while(file >> temp) {
		if(isupper(temp[0]))
			can_be_proper_noun=true;
		else
			can_be_proper_noun=false;

		// convert all characters to lower case
		transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
		
		// Save initial identity of people conversing
		if(temp[temp.length()-1]==':') {
			person_name = temp.substr(0,temp.length()-1);
			string attributes[][2]={{"name", person_name}};

			pElement = createChild("Person", attributes, 1);
			// pElement is parent of pElement1
			pElement1 = createChild("Message", attributes, 0, pElement);
		} else  {
			temp = trim(temp);
			if( !searchWordInDictionary(temp) ){
				if( can_be_proper_noun ) {
					string attributes[][2]={{"category", "proper_noun"}};
					addDatatoXMLElement(pElement1, "Word", temp , attributes, 1);
				}else {
					// Word neither in dictionary nor proper noun
					string splitted_word = segmentIntoWords(temp);
					// Remove extra whitespace at the end
					splitted_word = splitted_word.substr(0,splitted_word.length()-1);

					if( splitted_word.length() > temp.length() ){
						// parse all words in the string
						istringstream iss(splitted_word);
						while( iss >> tmp ){
							if(searchWordInDictionary(tmp)){
								//store tmp in xml for current person
								string attributes[][2]={{"category", getCategory(tmp).c_str()}};
								addDatatoXMLElement(pElement1, "Word", tmp , attributes, 1);
			
							}
						}
					}
				}
			} else {
				//store temp in xml for current person
				string attributes[][2]={{"category", getCategory(temp).c_str()}};
				addDatatoXMLElement(pElement1, "Word", temp , attributes, 1);
			}
		}
	}
	saveXMLDocument("SavedData.xml");
	cout<<"Data saved to SavedData.xml\n";
}