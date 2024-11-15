#include <bits/stdc++.h>
using namespace std;

void text_fileM(const string &filename, const vector<vector<char>> &matriz) {
    /*
    -Parámetros: 
        -filename: Nombre del archivo
        -matriz: Matriz con los elementos a guardar
    -Descripción: Guarda en un archivo el tamaño y los elementos de un vector
    */

    ofstream outfile(filename);

    if (!outfile) {
        cerr << "No se pudo abrir el archivo para escribir: " << filename << endl;
        return;
    }
    outfile << matriz.size()/2 << endl;

    bool sdl = false;

    for (const auto &fila : matriz) {
        for (const auto &columna : fila) {
            if(columna != '0') outfile << columna;
        }
        outfile << endl;
        if(sdl) outfile  << endl;
        sdl = !sdl;
    }

    outfile.close();
}

int main() {
    srand(time(0));

    cout << "___DATASET GENERATOR____" << endl;
    cout << endl;

    cout << "Elija su cantidad de casos (Exponente de potencia de 10): ";

    int N,M,V;
    cin >> N;
    int size = 2*(pow(10,N));

    vector<vector<char>> str(size,vector<char>(8));

    cout << "Elija que tipos de strings quiere:" << endl;
    cout << "1.Código genético(A,C,G,T)" << endl;
    cin >> M;

    cout << "Puede haber palabras vacías?" << endl;
    cout << "1.SI 0.NO" << endl;
    cin >> V;

    switch(M){
        case 1:
            for(int i = 0; i < size; ++i){

                if(V == 1 && rand()%10 == 0){
                    for(int j = 0; j < 8; ++j){str[i][j] = '0';}
                } else {
                    for(int j = 0; j < 8; ++j){
                        if(j != 0 && rand()%8 == 0) str[i][j] = '0';
                        else {
                            switch(rand()%4){
                                case 0:
                                    str[i][j] = 'C';
                                    break;
                                case 1:
                                    str[i][j] = 'G';
                                    break;
                                case 2:
                                    str[i][j] = 'T';
                                    break;
                                case 3:
                                    str[i][j] = 'A';
                                    break;
                            }
                        }
                    }
                }
            }
            break;   
    }

    
    

    

    text_fileM("dataset2.txt",str);

    return 0;
}