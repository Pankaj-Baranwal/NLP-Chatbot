#include <stdlib.h>
#include <fstream>		//header for file-handling.
#include "senetence_parser.cpp"
#include "segment_words.cpp"
#include <locale>
#include <sstream>
#include <cstring>

using namespace std;

// File to take conversation input from
string g_file_name = "sample.txt";
// File which contains the dictionary
string dictionary_file = "sample_words.txt";

bool searchWordInDictionary(string word){
	ifstream fin (dictionary_file.c_str());
	string temp="";
	while( fin >> temp ){
		if(strcmp(temp.c_str(),word.c_str())==0)
		{
			fin.close();
			return true;
		}
	}
	fin.close();
	return false;
}

string getCategory(string word){
	ifstream fin (dictionary_file.c_str());
	string current_cat="",temp="";
	while( fin >> temp ){
		
		if( temp[0] =='*'){
			current_cat = temp.substr(1,temp.length());
		}
		if(strcmp(temp.c_str(),word.c_str())==0)
		{
			fin.close();
			return current_cat;
		}
	}
	fin.close();
}

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
		transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
		//cout<<temp<<endl;
		if(temp[temp.length()-1]==':') {
			person_name = temp.substr(0,temp.length()-1);
			string attributes[][2]={{"name", person_name}};

			pElement = createChild("Person", attributes, 1);
			pElement1 = createChild("Message", attributes, 0, pElement);					
		} else  {
			if( !searchWordInDictionary(temp) ){
				string splitted_word = segmentIntoWords(temp);
				splitted_word = splitted_word.substr(0,splitted_word.length()-1);
				if( splitted_word.length() > temp.length() ){
					istringstream iss(splitted_word);
					while( iss >> tmp ){
						if(searchWordInDictionary(tmp)){
							//store tmp in xml for current person
							string attributes[][2]={{"category", getCategory(tmp).c_str()}};
							addDatatoXMLElement(pElement1, "Word", tmp , attributes, 1);
			
						}
					}
				} else {
					if( can_be_proper_noun ) {
						string attributes[][2]={{"category", "noun"}};
						temp = trim(temp);
						addDatatoXMLElement(pElement1, "Word", temp , attributes, 1);
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