#include <bits/stdc++.h>
using namespace std;

void merge(vector<int>& lista, int inicio, int medio, int final) {
    /*
    -Parámetros: 
      -lista: Lista a ordenar
      -inicio: Índice inicial de la sublista izquierda
      -medio: Índice medio, final de la sublista izquierda
      -final: Índice final de la sublista derecha
    -Descripción: Combina dos sublistas en una sola sublista ordenada.
    */
    
    //Creación de una copia de las sublistas derecha e izquierda
    int n1 = medio - inicio + 1;
    int n2 = final - medio;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++) {L[i] = lista[inicio + i];}
    for (int j = 0; j < n2; j++) {R[j] = lista[medio + 1 + j];}

    //Fusión de las sublistas en base a comparación del menor
    int i = 0, j = 0;
    int k = inicio;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            lista[k] = L[i];
            i++;
        } else {
            lista[k] = R[j];
            j++;
        }
        k++;
    }

    //Si faltan elementos, se agregan a la sublista fusionada
    while (i < n1) {
        lista[k] = L[i];
        i++; k++;
    }
    while (j < n2) {
        lista[k] = R[j];
        j++; k++;
    }
}



void mergeSort(vector<int>& lista, int inicio, int final) {
    /*
    -Parámetros:
        -lista: Lista a ordenar 
        -inicio: Índice inicial de la sublista
        -final: Índice final de la sublista
    -Descripción: Realiza la división de la lista en sublistas para trabajarlas con merge()
    */

    //Revisión para devolver la sublista del menor tamaño posible
    if (inicio >= final)
        return;

    //División recursiva de sublistas para luego ordenadas por el merge
    int medio = inicio + (final - inicio) / 2;

    mergeSort(lista, inicio, medio);
    mergeSort(lista, medio + 1, final);

    merge(lista, inicio, medio, final);
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

    mergeSort(v1, 0, tamaño - 1);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end -start;

    //Impresión del tiempo en ordenar la lista y escritura del resultado en otro archivo
    cout << "\nTiempo en segundos: " << duration.count() << endl;
    
    text_file("Res_dataset.txt",v1);
    
    return 0;
}
