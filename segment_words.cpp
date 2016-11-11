#include<bits/stdc++.h>


using namespace std;


#define fr(i,n) for(i=0;i<n;i++)
#define fra(i,a,n) for(i=a;i<n;i++)

map<string,int> mm;
int dp[100000];

const int len_ch = 12;

string ch[len_ch]={
"awkward",
"back",
"backed",
"background",
"backing",
"the",
"cat",
"in",
"the",
"hat",
"he",
"at",
// add all words present in the language here.
};

int fun(int pos,int len,string x)
{
    // return 0 if reached end of string successfully.
    if(pos==len)
        return 0;
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


int main()
{
  int i,t;
  fr(i,len_ch)
  {
     mm.insert ( pair<string,int>(ch[i],1) );
  }
  string x = "thecatinthehat";

  int len = x.length();

  fun(0,len,x);
  print_ans(0,len,x);
  cout<<"\n";
}


// #include<iostream>
// #include<stdio.h>