#include <bits/stdc++.h>
using namespace std;
#define endl "\n"

vector<int> RNG(unsigned int n){
    /*
    (R)andom (N)umber (G)enerator
    -Parámetros: unsigned int n
    -Descripción: Crea un vector de n enteros aleatorios en un rango de [0,n]
    */
    vector<int> Ntest(n);
    for (int &random : Ntest) {random = rand() % (n+1);}
    return Ntest;
}

vector<int> ONG(unsigned int n){
    /*
    (O)rdered (N)umber (G)enerator
    -Parámetros: unsigned int n
    -Descripción: Crea un vector de n enteros ordenados de menor a mayor en un rango de [0,n]
    */
    vector<int> Ntest(n);
    int i = 0;
    auto it = Ntest.begin();
    for (; it != Ntest.end() ; ++it) {*it = ++i;}
    return Ntest;
}

vector<int> RONG(unsigned int n){
    /*
    (R)everse (O)rdered (N)umber (G)enerator
    -Parámetros: unsigned int n
    -Descripción: Crea un vector de n enteros ordenados de mayor a menor en un rango de [0,n]
    */
    vector<int> Ntest(n);
    int i = 0;
    auto rit = Ntest.rbegin();
    for (; rit != Ntest.rend() ; ++rit) {*rit = ++i;}
    return Ntest;
}

vector<vector<int>> RMG(unsigned int n, unsigned int m){
    /*
    (R)andom (M)atrix (G)enerator
    -Parámetros: unsigned int n
    -Descripción: Crea un vector de vectores (o matriz) de n*m enteros aleatorios en un rango de [0,100]
    */
    vector<vector<int>> Mtest(n,vector<int>(m));
    for (auto &fila: Mtest) {
        for (int &columna: fila) {
            columna = rand() % (101);
            }
        }
    return Mtest;
}

vector<vector<int>> IMG(unsigned int n){
    /*
    (I)dentity (M)atrix (G)enerator
    -Parámetros: unsigned int n
    -Descripción: Crea una matriz indentidad de n*n elementos
    */
    vector<vector<int>> Mtest(n,vector<int>(n));
    for (int i = 0; i < n; i++) {Mtest[i][i] = 1;}
    return Mtest;
}

void text_file(const string &filename, const vector<int> &lista) {
    /*
    -Parámetros: 
        -filename: Nombre del archivo
        -lista: Lista con los elementos a guardar
    -Decripción: Guarda en un archivo el tamaño y los elementos de un vector
    */
    ofstream outfile(filename);

    if (!outfile) {cerr << "No se pudo abrir el archivo para escribir: " << filename << endl;return;}

    outfile << lista.size() << endl;
    for (const int &num : lista) {outfile << num << endl;}

    outfile.close();
}


void text_fileM(const string &filename, const vector<vector<int>> &matriz) {
    /*
    -Parámetros: 
        -filename: Nombre del archivo
        -matriz: Matriz con los elementos a guardar
    -Descripción: Guarda en un archivo el tamaño y los elementos de un vector
    */

    ofstream outfile(filename);

    if (!outfile) {cerr << "No se pudo abrir el archivo para escribir: " << filename << endl; return;}

    int is = matriz.size();
    int js = matriz[0].size();
    outfile << is << " " << js << endl;

    for (const auto &fila : matriz) {
        for (const auto &columna : fila) {
            outfile << columna << " ";
        }
        outfile << endl;
    }

    outfile.close();
}



int main(){
    srand(time(0));
    cout << "___DATASET GENERATOR____" << endl;
    cout << "Lista (L) o Matriz (M): ";
    char Type;
    cin >> Type;
    int N, M;
    if (toupper(Type == 'L')) {
        cout << "Escriba el tamaño de la lista: ";
        cin >> N;
        cout << "Creando datasets....." << endl;
        vector<int> v1 = RNG(N);
        text_file("A.txt",v1);
        vector<int> v2 = ONG(N);
        text_file("B.txt",v2);
        vector<int> v3 = RONG(N);
        text_file("C.txt",v3);
        cout << "Datasets generados :)" << endl;
    } else if (toupper(Type) == 'M'){        
        cout << "Escriba la cantidad de filas y columnas: ";
        cin >> N;
        cout << "Creando datasets....." << endl;
        vector<vector<int>> m1 = RMG(N,N);
        text_fileM("E1e5.txt",m1);
        vector<vector<int>> m2 = RMG(N,N);
        text_fileM("E2e5.txt",m2);
        vector<vector<int>> m3 = IMG(N);
        text_fileM("Fe5.txt",m3);
        cout << "Datasets generados :)" << endl;
    }
}
