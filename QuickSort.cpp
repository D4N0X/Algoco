#include <bits/stdc++.h>
using namespace std;

int partition(vector<int>& arr, int inicio, int final) {
    /*
    -Parámetros:
      - arr: vector a ordenar
      - inicio: índice inicial del subarreglo
      - final: índice final del subarreglo
    -Descripción: Reorganiza los elementos de la sublista de manera que los menores al pivote queden a la izquierda y los mayores a la derecha.
    */

    //Busca el pivote, que será el elemento de la posición final de la lista
    int pivot = arr[final];

    //Recorre la lista dejando i como el punto entre los números menores, junto al pivote y los mayores
    int i = inicio - 1;

    for (int j = inicio; j <= final - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[final]);

    //retorna el punto i para dividir en listas en quickSort()
    return i + 1;
}

void quickSort(vector<int>& lista, int inicio, int final) {
    /*
    -Parámetros:
      - lista: Lista a ordenar
      - inicio: Índice inicial de la sublista a ordenar
      - final: Índice final de la sublista a ordenar
    -Descripción: Ordena el subarreglo utilizando la técnica de división y conquista del algoritmo QuickSort.
    */
    
    //Se particionan sublistas según el criterio de partition() hasta que no se pueda
    if (inicio < final) {

        int particion = partition(lista, inicio, final);

        quickSort(lista, inicio, particion - 1);
        quickSort(lista, particion + 1, final);
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

    vector<int> v1(tamaño);
    for(auto it = v1.begin(); it != v1.end(); ++it){
        dataset >> elemento;
        *it = elemento;
    }

    dataset.close();

    //Llamada del algoritmo de orednamiento y la medición de tiempo de este
    auto start = chrono::high_resolution_clock::now();

    quickSort(v1, 0, tamaño - 1);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end -start;

    //Impresión del tiempo en ordenar la lista y escritura del resultado en otro archivo
    cout << "\nTiempo en segundos: " << duration.count() << endl;
    
    text_file("Res_dataset.txt",v1);
    
    return 0;
}
