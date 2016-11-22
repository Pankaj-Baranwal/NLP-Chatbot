#include<iostream>
#include<string>
#include<cstring>
#include<algorithm>
#include<iomanip>

using namespace std;

// Please add a whitespace at the end of each string.
string value[] = {
    // A => Nouns
    "a fish pond boy girl ocean food table room knowledge ball apple she fork ",
    // B => Verbs
    "b eats swims ate saw put ",
    // C => Prepositions
    "c of about on in with ",
    // D => Determinants
    "d a an the this that ",
};

int length_of_value = 4;


// VP = 1, PP = 2, NP = 3, N = 4, V = 5, P = 6, Det = 7
string rule[] = {
    "S 31",
    "1 12|53|b",
    "2 63|6",
    "3 74|4|a",
    "4 a",
    "5 b",
    "6 c",
    "7 d",
};

#define MAX 100
#define fr(i,a,b) for(i=a;i<b; i++)
 
string gram[MAX][MAX];  // Each row stores dpr for that production.
string dpr[MAX];        // dpr-> Each index stores one rule for a production till p.
int p;                  // p-> Max number of combination of rules for each production. 
                        // Example: For S, p = 2
int np = 8;            // np-> number of productions

string replaceWordsWithSymbols(string sentence) // Replace the words in the input sentence with production-readable symbols
{
    string return_string = "";
    string word;
    int i;
    while (sentence.find(" ") < sentence.length())
    {
        word = " " + sentence.substr(0, sentence.find(" ")+1);
        sentence = sentence.substr(sentence.find(" ")+1, sentence.length());
        fr(i, 0, length_of_value)
        {
            if (value[i].find(word) < value[i].length())
            {
                return_string += value[i][0];
                break;
            }
        }
    }
    word = " " + sentence + " ";
    fr(i, 0, length_of_value)
    {
        if (value[i].find(word) < value[i].length())
        {
            return_string += value[i][0];
            break;
        }
    }
    return return_string;
}

string concat(string a, string b)   //concatenates unique non-terminals
{
    int i;
    string r=a;
    fr(i,0,b.length())
        if(r.find(b[i]) > r.length())
            r+=b[i];
    return (r);
}
 
void break_gram(string a)    // Breaks OR separated rules for each production
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
 
string search_prod(string p) // returns a concatenated string of variables which can produce string p
{
    // cout << "p = " << p << endl;
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
 
string gen_comb(string a, string b)  //creates every combination of variables from a and b . For eg: BA * AB = {BA, BB, AA, BB}
{
    // cout << "a = "<< a << "b = " << b << endl;
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

// VP = 1, PP = 2, NP = 3, N = 4, V = 5, P = 6, Det = 7
string convert(string m){
    int i;
    string return_string = "";
    fr (i, 0, m.length())
    {
        if (m[i]=='1'){
            return_string += "VP";
        }else if (m[i]=='2'){
            return_string += "PP";
        }else if (m[i]=='3'){
            return_string += "NP";
        }else if (m[i]=='4'){
            return_string += "N";
        }else if (m[i]=='5'){
            return_string += "V";
        }else if (m[i]=='6'){
            return_string += "P";
        }else if (m[i]=='7'){
            return_string += "Det";
        }else if (m[i]=='S'){
            return_string += "S";
        }else return_string += "";
    }
    return return_string;
}
 
int main()
{
    int i, j, k, l;
    int pt;         // Find first location of whitespace in production
    string a,r,pr;
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
    string matrix[MAX][MAX],st; // MATRIX stores the table containing the parse tree.
    string str = "she eats a fish with a fork";
    cout << str << endl;
    string original = str;
    str = replaceWordsWithSymbols(str);
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
            string h = convert(matrix[k++][j]);
            cout<<setw(5)<<h<<" ";
        }
        cout<<endl;
    }

    while (original.find(" ")<original.length())
    {
        cout << setw(5) << original.substr(0, original.find(" "))<<" ";
        original = original.substr(original.find(" ")+1, original.length());
    }
    cout << setw(5) << original << endl;
             
    int f=0;
    cout << endl;
    if(matrix[0][str.length()-1].find('S') <= matrix[0][str.length()-1].length())   //Checks if last element of first row contains 'S'
    {
        cout<<"THIS IS A VALID SENTENCE\n";
        return 0;
    }
    cout<<"THIS IS NOT A VALID SENTENCE\n";
    return 0;
}