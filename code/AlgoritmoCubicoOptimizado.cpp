#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> traspose_Matrix(vector<vector<int>> matrix){
    /*
    Parámetros:
        -matrix: Matriz a trasponer
    Describción: Retorna la matriz traspuesta, respecto a la matriz de parámetro
    */

    int col = matrix[0].size();                             //O(1)
    int row = matrix.size();                                //O(1)

    vector<vector<int>> res(col, vector<int>(row, 0));      //O(col * row)

    for (int i = 0; i < row; i++) {                         //O(row)
        for (int j = 0; j < col; j++) {                         //O(col)
            res[j][i] = matrix[i][j];                               //O(1)
        }
    }
    return res;
}

vector<vector<int>> multiply_matrix(vector<vector<int>> matrix_A, vector<vector<int>> matrix_B) {
    /*
    Parámetros:
        -matrix_A: La primera matriz a la cual multiplicar
        -matrix_B: La segunda matriz a la cual trasponer
    Descripción: Realiza la multiplicación de dos matrices, trasponiendo la segunda matriz, devolviendo la matriz resultante
    */

    int col_1 = matrix_A[0].size();                             //O(1)
	int row_1 = matrix_A.size();                                //O(1)
	int col_2 = matrix_B[0].size();                             //O(1)
	int row_2 = matrix_B.size();                                //O(1)

    if (col_1 != row_2) {                                       //O(1)
		cerr << "\nLas matrices no son compatibles para A*B\n";
		return {};
	}

    vector<vector<int>> matrix_BT = traspose_Matrix(matrix_B);  //O(col_2 * row_2)

    vector<vector<int>> res(row_1, vector<int>(col_2, 0));      //O(row_1 * col_2)

    for (int i = 0; i < row_1; ++i) {                           //O(row_1)
        for (int j = 0; j < col_2; ++j) {                           //O(col_2)
            for (int k = 0; k < col_1; ++k) {                           //O(col_1)
                res[i][j] += matrix_A[i][k] * matrix_BT[j][k];              //O(1)
            }
        }
    }

    return res;
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

    //Inserción de los datasets a la matriz   
    int f1, c1, f2, c2, elemento;

    fstream dataset1("dataset1.txt");
    dataset1 >> f1 >> c1;

    vector<vector<int>> matriz1(f1,vector<int>(c1));
    for (auto &fila: matriz1) {
        for (int &columna: fila) {
            dataset1 >> columna;
            }
        }

    dataset1.close();

    fstream dataset2("dataset2.txt");
    dataset2 >> f2 >> c2;

    vector<vector<int>> matriz2(f2,vector<int>(c2));
    for (auto &fila: matriz2) {
        for (int &columna: fila) {
            dataset2 >> columna;
            }
        }

    dataset2.close();
    
    //Llamada del algoritmo de multiplicación de matrices y la medición de tiempo de este
    auto start = chrono::high_resolution_clock::now();

    vector<vector<int>> res = multiply_matrix(matriz1,matriz2);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end -start;

    //Impresión del tiempo en ordenar la lista y escritura del resultado en otro archivo
    cout << "\nTiempo en segundos: " << duration.count() << endl;
    
    text_fileM("Res_dataset.txt",res);
    
    return 0;
}
