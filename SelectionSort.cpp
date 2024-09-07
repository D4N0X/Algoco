#include <bits/stdc++.h>
using namespace std;


void selectionSort(int lista[], int tamaño) {
    /*
    -Parámetros:
      - lista: Lista a ordenar
      - tamaño: tamaño de la lista
    -Descripción: Ordena la sleccionando el menor valor y colocandolo en la posición correspondiente
    */

   //Itera sobre la lista tomando la posición como referencia
    for (int i = 0; i < tamaño - 1; i++) {
        int indice = i;

        //Itera sobre la lista nuevamente buscando el menor elemento en el rango entre el indice y el final
        for (int j = i + 1; j < tamaño; j++) {
            if (lista[j] < lista[indice]) { 
                indice = j;
            }
        }

        //En caso de encontrar un número menor al de la posición del indice se hace un intercambio
        if (indice != i) {swap(lista[indice], lista[i]);}
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

    int lista[tamaño];
    for(int i= 0; i < tamaño; ++i){
        dataset >> elemento;
        lista[i] = elemento;
    }

    dataset.close();

    //Llamada del algoritmo de orednamiento y la medición de tiempo de este
    auto start = chrono::high_resolution_clock::now();

    selectionSort(lista,tamaño);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end -start;

    //Impresión del tiempo en ordenar la lista y escritura del resultado en otro archivo
    cout << "\nTiempo en segundos: " << duration.count() << endl;
    
    vector<int> v (lista,lista + sizeof(lista)/sizeof(int));
    text_file("Res_dataset.txt",v);

    return 0;
}