#include <bits/stdc++.h>

using namespace std;

const char alphabet[]  = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

void showGrid(char** matrix){
    cout<<"\n"<<endl;
    for(int i=0;i<5;i++){
       for(int j=0;j<5;j++){
           cout<<matrix[i][j]<<" ";
       }
       cout<<endl;
    }
}

int mod(int a, int b){
	return (a % b + b) % b;
}

bool isCharRepeated(string key, char letter){
    return key.find(letter) != string::npos;
}

vector<int> letterPosition(char** matrix, char letter){
    vector<int> position;
    for(int i = 0; i < 5; i++){
        for(int j=0;j<5;j++){
            if(matrix[i][j]==letter){
                position.push_back(i);
                position.push_back(j);
                break;
            }
        }
    }
    return position;
}

string removeSpaces(string text){
    string aux;
    for(int i = 0; i < text.length(); i++){
        if(text[i]!=' '){
            aux.push_back(text[i]);
        }
    }
    return aux;
}

string prepareString(string str){
    string aux;
    for(int i = 0; i < str.length(); i=i+2){
        aux.push_back(str[i]);
        if(str[i]==str[i+1]){
            aux.push_back('x');
        }
        if(i!=str.length()-1){
            aux.push_back(str[i+1]);
        }
    }
    if(aux.length()%2!=0){
        aux.push_back('x');
    }
    return aux;
}

string createStringBlocks(string plainText){
    string block, res;
    block = prepareString(removeSpaces(plainText));
    for(int i = 0; i < block.length(); i++){
        res.push_back(block[i]);
        if(i%2!=0){
            res.push_back(' ');
        }
    }
    return res;
}

string concatWithoutRepeat(string word, string concatWord){
    string aux = word;
    for(int i = 0; i < concatWord.length(); i++){
        if(!isCharRepeated(aux, concatWord[i])){
            aux.push_back(concatWord[i]);
        }
    }
    return aux;
}

string createString(string keyword){
    string aux;
    aux = concatWithoutRepeat(aux, removeSpaces(keyword));
    aux = concatWithoutRepeat(aux, alphabet);
    return aux;
}

char** createMatrix(string key){
    int k = 0;
    char** auxMatrix = new char*[5];
    for(int i = 0; i < 5; ++i){
        auxMatrix[i] = new char[5];
    }

    string values = createString(key);
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            auxMatrix[i][j] = values[k];
            k++;
        }
    }
    return auxMatrix;
}

string sameColumn(char** matrix, vector<int> posFirst, vector<int> posSecond, bool option){
    string res;
    int adition = option ? 1 : -1;
    vector<int> first = posFirst, second = posSecond;
    first[0] = mod(first[0] + adition, 5);
    second[0] = mod(second[0] + adition, 5);

    res.push_back(matrix[first[0]][first[1]]);
    res.push_back(matrix[second[0]][second[1]]);
    return res;
}

string sameRow(char** matrix, vector<int> posFirst, vector<int> posSecond, bool option){
    string res;
    int adition = option ? 1 : -1;
    vector<int> first = posFirst, second = posSecond;
    first[1] = mod(first[1] + adition, 5);
    second[1] = mod(second[1] + adition, 5);

    res.push_back(matrix[first[0]][first[1]]);
    res.push_back(matrix[second[0]][second[1]]);
    return res;
}

string differentRowAndColumn(char** matrix, vector<int> posFirst, vector<int> posSecond){
    string res;
    vector<int> first = posFirst, second = posSecond;
    first[1] = posSecond[1];
    second[1] = posFirst[1];

    res.push_back(matrix[first[0]][first[1]]);
    res.push_back(matrix[second[0]][second[1]]);
    return res;
}

string cipher(char** matrix, string blocks, bool option){
    string cipherText;
    string readyBlocks = removeSpaces(blocks);
    for(int i = 0; i < readyBlocks.size(); i=i+2){
        vector<int> posA, posB;
        posA = letterPosition(matrix, readyBlocks[i]);
        posB = letterPosition(matrix, readyBlocks[i+1]);
        if(posA[0]==posB[0]){
            cipherText = cipherText + sameRow(matrix, posA, posB, option) + " ";
        }else if(posA[1]==posB[1]){
            cipherText = cipherText + sameColumn(matrix, posA, posB, option) + " ";
        }else{
            cipherText = cipherText + differentRowAndColumn(matrix, posA, posB) + " ";
        }
    }
    return cipherText;
}

int main(){
    string keyword, plainText, blocks, message, messageTwo;
    bool option;
    cout<<"\nWELCOME\n"<<endl;
    cout<<"- Cipher(1)"<<endl;
    cout<<"- Decipher(0)"<<endl;
    cout<<"Enter an option: ";
    cin>>option;
    cin.ignore();
    message = option?"encrypt":"decrypt";
    messageTwo = option?"Cipher":"Decipher";
    cout<<"\nEnter the keyword:"<<endl;
    getline(cin, keyword);
    char** matrix = createMatrix(keyword);
    showGrid(matrix);
    cout<<"\nEnter text to "<<message<<":"<<endl;
    getline(cin, plainText);
    blocks = createStringBlocks(plainText);
    if(option){
        cout<<"\nPlain text blocks:"<<endl;
        cout<<blocks<<endl;
    }
    cout<<"\n"<<messageTwo<<" text:"<<endl;
    cout<<cipher(matrix, blocks, option)<<endl;
}
