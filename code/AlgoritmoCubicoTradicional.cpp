#include <bits/stdc++.h>
using namespace std;


vector<vector<int>> mulMat(vector<vector<int>> mat1, vector<vector<int>> mat2, int N, int M) {

    vector<vector<int>> rslt(N, vector<int>(N, 0));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < M; k++) {
                rslt[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }

    return rslt;
}


/* LO QUE SIGUE ES CREADO PARA EL TESTEO DE LOS DATASETS */

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



int main() {
    /*
    Descripción: crea una matriz en base a un dataset entregado 
        por el archivo para luego ser ordenado y ser guardado en otro archivo.
        Se mide el tiempo que toma en ordenarse y se imprime por pantalla
    */

    //Inserción del dataset a la lista    
    int f1, c1, f2, c2, elemento;

    fstream dataset1("Fe6.txt");
    dataset1 >> f1 >> c1;

    vector<vector<int>> matriz1(f1,vector<int>(c1));
    for (auto &fila: matriz1) {
        for (int &columna: fila) {
            dataset1 >> columna;
            }
        }

    dataset1.close();

    fstream dataset2("Fe6.txt");
    dataset2 >> f1 >> c1;

    vector<vector<int>> matriz2(f1,vector<int>(c1));
    for (auto &fila: matriz2) {
        for (int &columna: fila) {
            dataset2 >> columna;
            }
        }

    dataset2.close();
    
    //Llamada del algoritmo de orednamiento y la medición de tiempo de este
    auto start = chrono::high_resolution_clock::now();

    vector<vector<int>> res = mulMat(matriz1,matriz2,f1,c1);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end -start;

    //Impresión del tiempo en ordenar la lista y escritura del resultado en otro archivo
    cout << "\nTiempo en segundos: " << duration.count() << endl;
    
    text_fileM("Res_dataset.txt",res);
    
    return 0;
}
