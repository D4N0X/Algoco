#include <bits/stdc++.h>
using namespace std;


void selectionSort(vector<int>& list_A) {
    /*
    -Parámetros:
      -list_A: Lista a ordenar
    -Descripción: Ordena la sleccionando el menor valor y colocandolo en la posición correspondiente
    */

    int N = list_A.size();                      //O(1)

    for (int i = 0; i < N - 1; ++i) {           //O(N)
        int index = i;
        for (int j = i + 1; j < N; ++j) {           //O(N-i)
            if (list_A[j] < list_A[index]) {            //O(1)
                index = j;
            }
        }

        if (index != i) {                       //O(1)
            swap(list_A[index], list_A[i]);         //0(1)
        }
    }
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
    fstream dataset("Be6.txt");
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

    selectionSort(lista);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end -start;

    //Impresión del tiempo en ordenar la lista y escritura del resultado en otro archivo
    cout << "\nTiempo en segundos: " << duration.count() << endl;
    
    text_file("Res_dataset.txt",lista);

    return 0;
}