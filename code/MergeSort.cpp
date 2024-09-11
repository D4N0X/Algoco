#include <bits/stdc++.h>
using namespace std;

void merge(vector<int>& lista, int pos_0, int S, int pos_N) {
    /*
    -Parámetros: 
      -lista: Lista a ordenar
      -pos_0: Índice inicial de la sublista izquierda
      -S: Índice medio, final de la sublista izquierda
      -pos_N: Índice final de la sublista derecha
    -Descripción: Combina dos sublistas en una sola sublista ordenada.
    */
    

    int N1 = S - pos_0 + 1;             //O(1)
    int N2 = pos_N - S;                 //O(1)

    vector<int> L(N1), R(N2);           //O(N1) + O(N2)

    for (int i = 0; i < N1; i++) {      //O(N1)
        L[i] = lista[pos_0 + i];            //O(1)
        }

    for (int j = 0; j < N2; j++) {      //O(N2)
        R[j] = lista[S + 1 + j];            //O(1)
        }

    int i = 0, j = 0;                   //O(1)
    int k = pos_0;                      //O(1)

    while (i < N1 && j < N2) {          //O(N1 + N2)
        if (L[i] <= R[j]) {                 //O(1)
            lista[k] = L[i];                
            i++;
        } else {
            lista[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < N1) {                    //O(N1)
        lista[k] = L[i];                    //O(1)
        i++; 
        k++;
    }
    while (j < N2) {                    //O(N1)
        lista[k] = R[j];                    //O(1)
        j++; 
        k++;
    }
}



void mergeSort(vector<int>& lista, int pos_0, int pos_N) {
    /*
    -Parámetros:
        -lista: Lista a ordenar 
        -pos_0: Índice inicial de la sublista
        -pos_N: Índice pos_N de la sublista
    -Descripción: Realiza la división de la lista en sublistas para trabajarlas con merge()
    */

    if (pos_0 >= pos_N) {return;}           //O(1)

    int S = pos_0 + (pos_N - pos_0) / 2;    //O(1)

    mergeSort(lista, pos_0, S);             //O(log (pos_N - pos_0))
    mergeSort(lista, S + 1, pos_N);         //O(log (pos_N - pos_0))

    merge(lista, pos_0, S, pos_N);          //O(pos_N - pos_0)
}

/* LO QUE SIGUE ES CREADO PARA EL TESTEO DE LOS DATASETS */

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



int main() {
    /*
    Descripción: crea una lista en base a un dataset entregado 
        por el archivo para luego ser ordenado y ser guardado en otro archivo.
        Se mide el tiempo que toma en ordenarse y se imprime por pantalla
    */

    //Inserción del dataset a la lista
    fstream dataset("dataset.txt");
    int tamaño, elemento;
    dataset >> tamaño;

    vector<int> lista(tamaño);
    for(auto it = lista.begin(); it != lista.end(); ++it){
        dataset >> elemento;
        *it = elemento;
    }

    dataset.close();

    //Llamada del algoritmo de ordenamiento y la medición de tiempo de este
    auto start = chrono::high_resolution_clock::now();

    mergeSort(lista, 0, tamaño - 1);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end -start;

    //Impresión del tiempo en ordenar la lista y escritura del resultado en otro archivo
    cout << "\nTiempo en segundos: " << duration.count() << endl;
    
    text_file("Res_dataset.txt",lista);
    
    return 0;
}
