#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;
bool isDigit( char c ){
    if(c >= '0' && c <= '9')
        return true;
    else return false;
}
int main()
{
    ifstream fin;
    ofstream fout;
    system ("sed -i '/^$/d' gre_vocab_text.txt");
    fin.open("gre_vocab_text.txt");
    fout.open("file.csv");
    fout << "TOPIC,WORD,MEANING,SENTENCE\n";
    string s;
    string s2, example, meaning, word;
    string topic = "";
    while(1){
        getline(fin, s);
        if(fin.eof())break;
        if(isDigit(s[0])){
            topic = s;
        }
        else{
            getline(fin, s2);
            word = "\"";
            meaning = "\"";
            int passedEqual = 0;
            for(int i = 0; s[i] != 0; ++i){
                if(passedEqual == 1)
                    meaning = meaning + s[i];
                if(s[i] == '=')
                {
                    word = word + "\"";
                    passedEqual = 1;
                }
                if(passedEqual == 0)
                    word = word + s[i];

            }
            if(s2[7] != ':')
            {
                meaning = meaning + " " + s2;
                getline(fin, s2);
            }
            meaning = meaning + "\"";
            int i;
            for(i = 0; s2[i] != ':'; ++i);
            example = "";
            ++i;
            for(; s2[i] != 0; ++i)
                example = example + s2[i];
            if(s2[i - 1] == '.')
                example = example;
            else
            {
                getline(fin, s2);
                example = example + " " + s2;
            }
            fout << topic << "," << word << "," << meaning << ",\"" << example << "\"" << "\n";
        }
    }

    return 0;
}
