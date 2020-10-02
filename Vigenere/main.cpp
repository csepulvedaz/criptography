#include <bits/stdc++.h>

using namespace std;

string removeSpaces(string text){
    string aux;
    for(unsigned i = 0; i < text.length(); i++){
        if(text[i]!=' '){
            aux.push_back(text[i]);
        }
    }
    return aux;
}

string createKeywordString(string text, string keyword){
    string aux;
    for(unsigned i = 0; i < text.length(); i++){
        aux.push_back(keyword[i%keyword.length()]);
    }
    return aux;
}

string cipherText(string text, string keyword){
    string res;
    for(unsigned i = 0; i < text.size(); i++){
        char x = (text[i] + keyword[i]) %26;
        x += 'A';
        res.push_back(x);
    }
    return res;
}

string decipherText(string cipherText, string keyword) {
    string res;

    for (unsigned i = 0 ; i < cipherText.size(); i++){
        char x = (cipherText[i] - keyword[i] + 26) %26;
        x += 'A';
        res.push_back(x);
    }
    return res;
}

string createStringBlocks(string text, int blockSize){
    string block, res = "";
    block = removeSpaces(text);
    for(unsigned i = 0; i < block.length(); i += blockSize) {
        res += block.substr(i, blockSize);
        if(i!=block.length()-1){
            res+=" ";
        }
    }
    return res;
}

int main(){
    string keyword, text, blocks, message;
    int t;
    bool option;
    cout<<"\nWELCOME\n"<<endl;
    cout<<"- Cipher(1)"<<endl;
    cout<<"- Decipher(0)"<<endl;
    cout<<"Enter an option: ";
    cin>>option;
    message = option?"encrypt":"decrypt";
    cout<<"\nEnter t: ";
    cin>>t;
    cin.ignore();
    cout<<"\nEnter the keyword: ";
    getline(cin, keyword); //Capital letter
    cout<<"\nEnter text to "<<message<<": ";
    getline(cin, text); //Capital letter
    cout<<"Keyword:       "<<createStringBlocks(createKeywordString(removeSpaces(text), keyword), t)<<endl;
    cout<<"Text:          "<<createStringBlocks(text, t)<<endl;
    if(option){
        cout<<"Cipher text:   "<<createStringBlocks(cipherText(removeSpaces(text), createKeywordString(removeSpaces(text), keyword)), t)<<endl;
    } else {
        cout<<"Decipher text: "<<createStringBlocks(decipherText(removeSpaces(text), createKeywordString(removeSpaces(text), keyword)), t)<<endl;
    }
    return 0;
}
