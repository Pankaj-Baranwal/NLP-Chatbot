#include<iostream>  
#include<cstring>
#include<algorithm>
#include<string>
#include<cassert>
#include<iomanip>
using namespace std;

string value[] = {
    // A => Nouns
    "A fish pond boy girl ocean food table room knowledge ball apple",
    // B => Verbs
    "B eats swims ate saw put",
    // C => Prepositions
    "C of about on in with",
    // D => Determinants
    "D a an the this that",
};

string rule[] = {
    "S NP VP",
    "VP VP PP|V NP|V",
    "PP P NP",
    "NP Det N|NP PP|N",
    "N A",
    "V B",
    "P C",
    "Det D",
};

#define MAX 100
#define fr(i,a,b) for(i=a;i<b; i++)
 
string gram[MAX][MAX];  // Each row stores dpr for that production.
string dpr[MAX];        // dpr-> Each index stores one rule for a production till p.
int p;                  // p-> Max number of combination of rules for each production. 
                        // Example: For S, p = 2
int np = 11;            // np-> number of productions
 
inline string concat( string a, string b)   //concatenates unique non-terminals
{
    int i;
    string r=a;
    fr(i,0,b.length())
        if(r.find(b[i]) > r.length())
            r+=b[i];
    return (r);
}
 
inline void break_gram(string a)    //seperates right hand side of entered grammar
{
    int i;
    p=0;
    while(a.length())
    {
        i = a.find("|");
        if(i>a.length())
        {
            dpr[p++] = a;
            a="";
        }
        else
        {
            dpr[p++] = a.substr(0,i);
            a=a.substr(i+1,a.length());
        }
    }
}
 
inline string search_prod(string p) //returns a concatenated string of variables which can produce string p
{
    int j,k;
    string r="";
    fr(j,0,np)
    {
        k=1;
        while(gram[j][k] != "")
        {
            if(gram[j][k] == p)
            {
                r=concat(r,gram[j][0]);
            }
            k++;
        }
    }   
    return r;
}
 
inline string gen_comb(string a, string b)  //creates every combination of variables from a and b . For eg: BA * AB = {BA, BB, AA, BB}
{
    int i,j;
    string pri=a,re="";
    fr(i,0,a.length())
        fr(j,0,b.length())
        {
            pri="";
            pri=pri+a[i]+b[j];
            re=re+search_prod(pri);     //searches if the generated productions can be created or not
        }       
    return re;
}
 
int main()
{
    int i,pt,j,l,k;
    string a,str,r,pr,start;
    start = "S";
    fr(i,0,np)
    {
        a = rule[i];
        pt = a.find(" ");
        gram[i][0] = a.substr(0,pt);
        a = a.substr(pt+1, a.length());
        break_gram(a);
        fr(j,0,p)
        {
            gram[i][j+1]=dpr[j];
        }
    }
    string matrix[MAX][MAX],st;
    str = "fish swims in the ocean";
    fr(i,0,str.length())       //Assigns values to principal diagonal of matrix
    {
        r="";
        st = "";
        st+=str[i];
        fr(j,0,np)
        {
            k=1;
            while(gram[j][k] != "")
            {
                if(gram[j][k] == st)
                {
                    r=concat(r,gram[j][0]);
                }
                k++;
            }
        }
        matrix[i][i]=r;
    }
    int ii,kk;
    fr(k,1,str.length())       //Assigns values to upper half of the matrix
    {
        fr(j,k,str.length())
        {
            r="";
            fr(l,j-k,j)
            {
                pr = gen_comb(matrix[j-k][l],matrix[l+1][j]);
                r = concat(r,pr);
            }
            matrix[j-k][j] = r;
        }
    }
 
    fr(i,0,str.length())   //Prints the matrix
    {
        k=0;
        l=str.length()-i-1;
        fr(j,l,str.length())
        {
            cout<<setw(5)<<matrix[k++][j]<<" ";
        }
        cout<<endl;
    }
             
    int f=0;
    fr(i,0,start.length())
        if(matrix[0][str.length()-1].find(start[i]) <= matrix[0][str.length()-1].length())   //Checks if last element of first row contains a Start variable
        {
            cout<<"String can be generated\n";
            return 0;
        }
    cout<<"String cannot be generated\n";
    return 0;
}