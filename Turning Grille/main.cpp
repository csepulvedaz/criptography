#include <bits/stdc++.h>

using namespace std;

int** initInt(int n){
    int** matrix = new int*[n];
    for (int i = 0; i < n; ++i)
        matrix[i] = new int[n];
    return matrix;
}

char** initChar(int n){
    char** matrix = new char*[n];
    for (int i = 0; i < n; ++i)
        matrix[i] = new char[n];
    return matrix;
}

string removeSpaces(string text){
    string aux;
    for(unsigned i = 0; i < text.length(); i++){
        if(text[i]!=' '){
            aux.push_back(text[i]);
        }
    }
    return aux;
}

string m_to_string(char** matrix, int n){
    string aux;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++){
            aux.push_back(matrix[i][j]);
        }aux.push_back(' ');
    }
    return aux;
}

char** s_to_matrix(string text, int n){
    char** aux = initChar(n);
    int k = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++){
            aux[i][j] = text[k];
            k++;
        }
    }
    return aux;
}

void reverseColumns(int** matrix, int n){
    for (int i = 0; i < n; i++)
        for (int j = 0, k = n - 1; j < k; j++, k--)
            swap(
                matrix[j][i], matrix[k][i]);
}

void reverseRows(int** matrix, int n){
    for (int i = 0; i < n; i++)
        for (int j = 0, k = n - 1; j < k; j++, k--)
            swap(
                matrix[i][j], matrix[i][k]);
}

void transpose(int** matrix, int n){
    for (int i = 0; i < n; i++)
        for (int j = i; j < n; j++)
            swap(matrix[i][j], matrix[j][i]);
}

void printIntMatrix(int** arr, int n){
    cout<<'\n';
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << arr[i][j] << " ";
        cout << '\n';
    }
}

void printCharMatrix(char** arr, int n){
    cout<<'\n';
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << arr[i][j] << " ";
        cout << '\n';
    }
}

void rotate_matrix(int** matrix, bool dir, int n, int k){
    transpose(matrix, n);
    if((n % 2 != 0) && k != 0){ //in odd-sized matrix the center is used only once
        matrix[(n-1)/2][(n-1)/2] = 0;
    }
    if(dir){
        reverseRows(matrix, n);
    } else {
        reverseColumns(matrix, n);
    }
}

void create_grid(int** grid, vector<pair <int, int>> pos, int n){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if(count(pos.begin(), pos.end(), make_pair(i, j))){
                grid[i][j] = 1;
            } else{
                grid[i][j] = 0;
            }
        }
    }
}

void turning_cipher(int** grid, char** res, string &text, int n, unsigned k, bool dir){
    if(k == text.size()){
        return ;
    } else {
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                if(k == text.size()){
                    return ;
                }
                if(grid[i][j] == 1){
                    res[i][j] = text[k];
                    k++;
                }
            }
        }
        rotate_matrix(grid, dir, n, k);
        turning_cipher(grid, res, text, n, k, dir);
    }
}

void turning_decipher(int** grid, char** enc, int n, int round, bool dir){
    if(round == 4){
        return ;
    } else {
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                if(grid[i][j] == 1){
                    cout<<enc[i][j];
                }
            }
        }
        round++;
        rotate_matrix(grid, dir, n, 0);
        turning_decipher(grid, enc, n, round, dir);
    }
}


int main(){
    string text, message;
    int m_size, n_holes, x, y;
    bool rot_direction, cipher;
    vector<pair <int, int>> positions;
    cout<<"Enter square matrix size: ";
    cin>>m_size;
    cout<<"Enter the direction of matrix rotation(1 or 0): ";
    cin>>rot_direction;
    cout<<"Enter mode (cipher(1) or decipher(0)): ";
    cin>>cipher;
    message = cipher?"cipher":"decipher";
    cout<<"Enter the number of holes: ";
    cin>>n_holes;
    cout<<"\nEnter the position of the holes(row, col)"<<endl;
    for(int i = 1; i <= n_holes; i++){
        cout<<"Hole "<<i<<": ";
        cin>>x>>y;
        positions.push_back(make_pair(x, y));
    }
    cin.ignore();
    cout<<"\nEnter text to "<<message<<": ";
    getline(cin, text);
    string aux = removeSpaces(text);

    int** grid = initInt(m_size);
    create_grid(grid, positions, m_size);

    if(cipher){
        char** res = initChar(m_size);
        turning_cipher(grid, res, aux, m_size, 0, rot_direction);
        printCharMatrix(res, m_size);
        cout<<"Cipher text: "<<m_to_string(res, m_size)<<endl;
    } else{
        char** enc = s_to_matrix(aux, m_size);
        cout<<"Decipher text: ";
        turning_decipher(grid, enc, m_size, 0, rot_direction);
        cout<<endl;
    }
    return 0;
}
