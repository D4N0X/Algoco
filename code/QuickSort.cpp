#include <bits/stdc++.h>
using namespace std;

int partition(vector<int>& lista, int pos_0, int pos_N) {
    /*
    -Parámetros:
      - arr: vector a ordenar
      - pos_0: índice inicial de la sublista
      - pos_N: índice final de la sublista
    -Descripción: Reorganiza los elementos de la sublista de manera que los menores al pivote queden a la izquierda y los mayores a la derecha.
    */

    int pivot = lista[pos_N];                       //O(1)

    int i = pos_0 - 1;                              //O(1)

    for (int j = pos_0; j <= pos_N - 1; j++) {      //O(pos_N - pos_0)
        if (lista[j] < pivot) {                         //O(1)
            i++;
            swap(lista[i], lista[j]);
        }
    }
    swap(lista[i + 1], lista[pos_N]);               //O(1)

    return i + 1;
}

void quickSort(vector<int>& lista, int pos_0, int pos_N) {
    /*
    -Parámetros:
      - lista: Lista a ordenar
      - pos_0: Índice inicial de la sublista a ordenar
      - pos_N: Índice final de la sublista a ordenar
    -Descripción: Ordena el subarreglo utilizando la técnica de división y conquista del algoritmo QuickSort.
    */
    
    if (pos_0 < pos_N) {                                    //O(1)

        int particion = partition(lista, pos_0, pos_N);     //O(pos_N - pos_0)

        quickSort(lista, pos_0, particion - 1);             //O(log ((pos_N - pos_0)/2) ) caso promedio, O((pos_N - pos_0)/2) en el peor caso
        quickSort(lista, particion + 1, pos_N);             //O(log ((pos_N - pos_0)/2) ) caso promedio, O((pos_N - pos_0)/2) en el peor caso
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
    fstream dataset("dataset.txt");
    int tamaño, elemento;
    dataset >> tamaño;

    vector<int> lista(tamaño);
    for(auto it = lista.begin(); it != lista.end(); ++it){
        dataset >> elemento;
        *it = elemento;
    }

    dataset.close();

    //Llamada del algoritmo de orednamiento y la medición de tiempo de este
    auto start = chrono::high_resolution_clock::now();

    quickSort(lista, 0, tamaño - 1);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end -start;

    //Impresión del tiempo en ordenar la lista y escritura del resultado en otro archivo
    cout << "\nTiempo en segundos: " << duration.count() << endl;
    
    text_file("Res_dataset.txt",lista);
    
    return 0;
}