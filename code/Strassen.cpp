#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> add_matrix(vector<vector<int> > matrix_A, vector<vector<int> > matrix_B) {
	/*
    Parámetros:
        -matrix_A: La primera matriz de la suma
        -matrix_B: La segunda matriz de la suma
    Descripción: Realiza la suma de dos matrices, devolviendo la matriz resultante
    */

    int row_1 = matrix_A.size();							//O(1)
    int col_1 = matrix_A[0].size();							//O(1)
	int row_2 = matrix_B.size();							//O(1)
	int col_2 = matrix_B[0].size();							//O(1)

    if (col_1 != col_2 && row_1 != row_2) {					//O(1)
		cerr << "\nLas matrices no son compatibles para A*B\n";
		return {};
	}

    vector<vector<int>> res(row_1, vector<int>(col_2, 0));	//O(row_1 * col_2)

	for (auto i = 0; i < row_1; i++){						//O(row_1)
		for (auto j = 0; j < col_1; j++){						//O(col_1)
			res[i][j] = matrix_A[i][j] + matrix_B[i][j];			//O(1)
		}
	}
	return res;
}

vector<vector<int>> subtract_matrix(vector<vector<int> > matrix_A, vector<vector<int> > matrix_B) {
	/*
    Parámetros:
        -matrix_A: La primera matriz de la resta
        -matrix_B: La segunda matriz de la resta
    Descripción: Realiza la resta de dos matrices, devolviendo la matriz resultante
    */

    int row_1 = matrix_A.size();							//O(1)
    int col_1 = matrix_A[0].size();							//O(1)
	int row_2 = matrix_B.size();							//O(1)
	int col_2 = matrix_B[0].size();							//O(1)

    if (col_1 != col_2 && row_1 != row_2) {					//O(1)
		cerr << "\nLas matrices no son compatibles para A*B\n";
		return {};
	}

    vector<vector<int>> res(row_1, vector<int>(col_2, 0));	//O(row_1 * col_2)

	for (auto i = 0; i < row_1; i++){						//O(row_1)
		for (auto j = 0; j < col_1; j++){						//O(col_1)
			res[i][j] = matrix_A[i][j] - matrix_B[i][j];			//O(1)
		}
	}
	return res;
}

vector<vector<int>> multiply_matrix(vector<vector<int>> matrix_A, vector<vector<int>> matrix_B) {
    /*
    Parámetros:
        -matrix_A: La primera matriz a la cual multiplicar
        -matrix_B: La segunda matriz a la cual multiplicar
    Descripción: Realiza la multiplicación de dos matrices, devolviendo la matriz resultante
    */

	int row_1 = matrix_A.size();							//O(1)
    int col_1 = matrix_A[0].size();							//O(1)
	int row_2 = matrix_B.size();							//O(1)
	int col_2 = matrix_B[0].size();							//O(1)

    if (col_1 != row_2) {									//O(1)
		cerr << "\nLas matrices no son compatibles para A*B\n";
		return {};
	}

    vector<vector<int>> res(row_1, vector<int>(col_2, 0));	//O(row_1 * col_2)

    for (int i = 0; i < row_1; ++i) {						//O(row_1)
        for (int j = 0; j < col_2; ++j) {						//O(col_2)
            for (int k = 0; k < col_1; ++k) {						//O(col_1)
                res[i][j] += matrix_A[i][k] * matrix_B[k][j];			//O(1)
            }
        }
    }
    return res;
}

vector<vector<int>> strassen(vector<vector<int>> matrix_A,vector<vector<int>> matrix_B, int N){

	if(N == 1) {
		return multiply_matrix(matrix_A,matrix_B);			//O(1)
	}

	vector<vector<int>> res(N,vector<int>(N));				//O(N)

	int S = N/2;											//O(1)

	//O((N/2)²) c/u
	vector<vector<int>> a00(S,vector<int>(S));
	vector<vector<int>> a01(S,vector<int>(S));
	vector<vector<int>> a10(S,vector<int>(S));
	vector<vector<int>> a11(S,vector<int>(S));

	vector<vector<int>> b00(S,vector<int>(S));
	vector<vector<int>> b01(S,vector<int>(S));
	vector<vector<int>> b10(S,vector<int>(S));
	vector<vector<int>> b11(S,vector<int>(S));

	for(int i = 0; i < S; ++i){								//O(N/2)
		for(int j = 0; j < S; ++j){								//O(N/2)
			a00[i][j] = matrix_A[i][j];								//O(1)
			a01[i][j] = matrix_A[i][j + S];
			a10[i][j] = matrix_A[i + S][j];
			a11[i][j] = matrix_A[i + S][j + S];

			b00[i][j] = matrix_B[i][j];
			b01[i][j] = matrix_B[i][j + S];
			b10[i][j] = matrix_B[i + S][j];
			b11[i][j] = matrix_B[i + S][j + S];
		}
	}

	//Operaciones suma y resta -- O((N/2)²) c/u
	vector<vector<int>> S0 = subtract_matrix(b01, b11);
	vector<vector<int>> S1 = add_matrix(a00, a01);
	vector<vector<int>> S2 = add_matrix(a10, a11);
	vector<vector<int>> S3 = subtract_matrix(b10, b00);
	vector<vector<int>> S4 = add_matrix(a00, a11);
	vector<vector<int>> S5 = add_matrix(b00, b11);
	vector<vector<int>> S6 = subtract_matrix(a01, a11);
	vector<vector<int>> S7 = add_matrix(b10, b11);
	vector<vector<int>> S8 = subtract_matrix(a00, a10);
	vector<vector<int>> S9 = add_matrix(b00, b01);

	//Llamada recursiva de strassen para las multiplicaciones -- //O((N/2)^log(7)) c/u
	vector<vector<int>> P1 = strassen(a00, S0, S);
	vector<vector<int>> P2 = strassen(S1, b11, S);
	vector<vector<int>> P3 = strassen(S2, b00, S);
	vector<vector<int>> P4 = strassen(a11, S3, S);
	vector<vector<int>> P5 = strassen(S4, S5, S);
	vector<vector<int>> P6 = strassen(S6, S7, S);
	vector<vector<int>> P7 = strassen(S8, S9, S);

	//Subcuadrantes -- O((N/2)²) c/u 
	vector<vector<int>> r00 = subtract_matrix(add_matrix(add_matrix(P5, P4), P6), P2);
	vector<vector<int>> r01 = add_matrix(P1, P2);
	vector<vector<int>> r10 = add_matrix(P3, P4);
	vector<vector<int>> r11 = subtract_matrix(subtract_matrix(add_matrix(P5, P1), P3), P7);	

	for (unsigned int i = 0; i < S; i++) {					//O(N/2)
		for (unsigned int j = 0; j < S; j++) {					//O(N/2)
			res[i][j] = r00[i][j];									//O(1)
			res[i][j + S] = r01[i][j];
			res[S + i][j] = r10[i][j];
			res[S + i][S + j] = r11[i][j];
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
