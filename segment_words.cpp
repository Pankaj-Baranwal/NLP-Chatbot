#include<bits/stdc++.h>


using namespace std;

// since for loop is used very frequently, I have defined a shorter version of them.
#define fr(i,n) for(i=0;i<n;i++)
#define fra(i,a,n) for(i=a;i<n;i++)

// no need to use map, they just one line searching code. Hence used.
// Array can be employed too.
map<string,int> mm;
// stores the finally chosen characters.
int dp[100000];
// Just to print all the words.
string main_sentence="";

int fun(int pos,int len,string x)
{
    // return 0 if reached end of string successfully.
    if(pos==len){
      return 0;
    }
    // mini stores max length of int and is only used to check if program didn't get drunk anywhere.
    // i stores start position of coming word.
    int mini = INT_MAX, i;

    string temp="";
    // ans stores position of end of coming word.
    int ans;
    fra(i,pos,len)
    {
        temp += x[i];
        // if mm contains temp
        if(mm.find(temp)!=mm.end())
        {
          main_sentence += temp + " ";
            // iterate over left over substring
            int get = fun(i+1,len,x);
            // get will satisfy below mentioned condition if 
            if(get<=mini)
            {
                mini = get;
                ans=i;
            }
        }
    }

    if(mini==INT_MAX)
    {
        dp[pos]=len-1;
        // return number of characters left to parse.
        return len-pos;
    }
    dp[pos]=ans;
    // always return 0 if successfuly found a word.
    return mini;
}

void print_ans(int pos,int len,string x)
{
    if(pos==len)
        return ;
   int i;
   // dp[pos] stores the end index of each word.
    fra(i, pos, dp[pos]+1)
    {
       cout<<x[i];
    }
    cout<<" ";
    print_ans(dp[pos]+1,len,x);
}

string ans(int pos,int len,string x)
{
    if(pos==len)
        return "";
   int i;
   string w = "";
   // dp[pos] stores the end index of each word.
    fra(i, pos, dp[pos]+1)
    {
       w += x[i];
    }
    w += " ";
    return w + ans(dp[pos]+1, len, x);
}

string segmentIntoWords(string word){
  string dictionary_file = "sample_words.txt";
  ifstream fin (dictionary_file.c_str());
  string temp="";
  while( fin >> temp ){
    mm.insert ( pair<string,int>(temp,1) );
  }

  int len = word.length();

  fun(0,len,word);
  return ans(0,len,word);
}