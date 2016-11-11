#include <iostream>
// #include <regex>
#include <string>
#include "tinyxml2.h"
#include "tinyxml2.cpp"

using namespace std;
using namespace tinyxml2;

#define fr(i,n) for(i=0;i<n;i++)

#ifndef XMLCheckResult
	#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("Error: %i\n", a_eResult); return a_eResult; }
#endif

int gPass = 0;
int gFail = 0;
XMLDocument xmlDoc;


int main(){
	// string s = "Hello, my name is Pankaj. I am a good boy.";
	// final String regex = "(?:\\s?)((?:(?:[\\\"\\'].*?(?:[\\.?!][\\\"\\'](?:\\s[a-z].*?[\\.?!])?|[\\\"\\'].*?[\\.?!]))|(?:[^.?!\\\"]{2,1000}[\\.?!]?)))";
}

void createXMLDocument(){
	XMLNode * pRoot = xmlDoc.NewElement("Root");
	xmlDoc.InsertFirstChild(pRoot);
}

void addDataToXMLDocument(string elementName, string text, string [][] attrib_key){
	XMLElement * pElement = xmlDoc.NewElement(elementName);
	fr(i, attrib_key[0].length){
		pElement->SetAttribute(attrib_key[i][0], attrib_key[i][1]);
		pElement.SetText(text);
	}
	pRoot->InsertEndChild(pElement);
}

void saveXMLDocument(string name){
	XMLError eResult = xmlDoc.SaveFile(name);
	XMLCheckResult(eResult);
}

void readXMLDocument(string name){
	XMLError eResult = xmlDoc.LoadFile("SavedData.xml");
	XMLCheckResult(eResult);
}

void readDataFromXML(){
	XMLNode * pRoot = xmlDoc.FirstChild();
	if (pRoot == nullptr) return XML_ERROR_FILE_READ_ERROR;
	XMLElement * pListElement = pElement->FirstChildElement("word");
	std::vector<int> vecList;
	while (pListElement != nullptr){
		string iOutListValue;
		XMLError eResult = pListElement->QueryIntText(&iOutListValue);
		XMLCheckResult(eResult);

		vecList.push_back(iOutListValue);
		pListElement = pListElement->NextSiblingElement("word");
	}
}