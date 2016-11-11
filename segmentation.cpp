#include <iostream>
#include <stdio>
#include <string>

using namespace std;

#define fr(i, a) for (i = 0; i< a; i++)

string words[] = {"share","as","a","sale","bla","other","any","sha","sh"}
int lengthOfWords = 9;
string wdict[lengthOfWords][2];
best=[];

string scanThroughString(string input, int i, string[lengthOfWords][2] prevArray){
    int count = 0;
    fr(int j, lengthOfWords){
        if (prevArray[j][0].length()>0){
            count++;
        }else
        break;
    }
    string arr[count][2];
    fr(int j, count){
        arr[j][0] = prevArray[j][0];
        arr[j][1] = prevArray[j][1];
    }
}

int main(){

}