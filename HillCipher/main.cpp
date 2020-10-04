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

void printMatrix(int matrix[2][2]){
    cout<<"\n";
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }
}

void getKeyMatrix(int matrix[2][2]){
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            cin>>matrix[i][j];
        }
    }
}

int modularInverse(int det){
    for(int i = 0; i < 26; i++){
        if((det*i)%26 == 1){
            return i;
        }
    }
}

int determinant(int arr[2][2]){
    return (arr[0][0] * arr[1][1]) - (arr[0][1] * arr[1][0]);
}

string prepareString(string str){
    string aux = removeSpaces(str);
    if(aux.length()%2!=0){
        aux.push_back('x');
    }
    return aux;
}

void stringToASCII(string text, int messageVector[][1]){
    for (int i = 0; i < 2; i++)
        messageVector[i][0] = (text[i]) % 65;
}

void multiplyMatrix(int cipherMatrix[2][1], int keyMatrix[2][2], int messageVector[2][1]){

    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 1; j++){
            cipherMatrix[i][j] = 0;
            for (int k = 0; k < 2; k++){
                cipherMatrix[i][j] += keyMatrix[k][i] * messageVector[k][j];
            }
            cipherMatrix[i][j] = cipherMatrix[i][j] % 26;
        }
    }
}

void adjMatrix(int key[2][2], int adj[2][2]){
    int cofactor[2][2];
    cofactor[0][0] = key[1][1]; cofactor[0][1] = -key[1][0]; cofactor[1][0] = -key[0][1]; cofactor[1][1] = key[0][0];
    adj[0][0] = cofactor[0][0]; adj[0][1] = cofactor[1][0]; adj[1][0] = cofactor[0][1]; adj[1][1] = cofactor[1][1];
}

void invMatrix(int key[2][2], int inv[2][2]){
    int adj[2][2];
    adjMatrix(key, adj);
    for(int i = 0; i < 2; i++){
        for(int j = 0; j< 2; j++){
            inv[i][j] = ((modularInverse(determinant(key))*adj[i][j]) % 26 + 26) % 26;
        }
    }
}

string HillCipher(string text, int key[2][2]){
    string cipherText, evenString = prepareString(text);
    int messageVector[2][1];
    int cipherMatrix[2][1];

    for(int i = 0; i < evenString.length(); i=i+2){
        stringToASCII(evenString.substr(i, 2), messageVector);
        multiplyMatrix(cipherMatrix, key, messageVector);

        for (int j = 0; j < 2; j++){
            cipherText += cipherMatrix[j][0] + 65;
        }
    }
    return cipherText;
}

string HillDecipher(string cipherText, int key[2][2]){
    string text;
    int messageVector[2][1];
    int matrix[2][1];
    int inv[2][2];
    invMatrix(key, inv);

    for(int i = 0; i < cipherText.length(); i=i+2){
        stringToASCII(cipherText.substr(i, 2), messageVector);
        multiplyMatrix(matrix, inv, messageVector);

        for (int j = 0; j < 2; j++){
            text += matrix[j][0] + 65;
        }
    }
    return text;
}

int main(){
    string text, message;
    int keyMatrix[2][2];
    bool option;
    cout<<"\nWELCOME\n"<<endl;
    cout<<"- Cipher(1)"<<endl;
    cout<<"- Decipher(0)"<<endl;
    cout<<"Enter an option: ";
    cin>>option;
    message = option?"cipher":"decipher";
    cout<<"\nEnter the key matrix(2x2):"<<endl;
    getKeyMatrix(keyMatrix);
    cin.ignore();
    cout<<"\nEnter text to "<<message<<": ";
    getline(cin, text); //Capital letter
    if(option){
        cout<<"Cipher text: "<<HillCipher(text, keyMatrix)<<endl;
    } else{
        cout<<"Decipher text: "<<HillDecipher(text, keyMatrix)<<endl;
    }
    return 0;
}
