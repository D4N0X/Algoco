#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> Mcostos_sub(25,vector<int>(25));
vector<vector<int>> Mcostos_trans(25,vector<int>(25));
vector<int> Lcostos_ins(25);
vector<int> Lcostos_del(25);

int costo_ins(char a){
    int costo;
    a = tolower(a);
    costo = Lcostos_ins[int(a)-97];
    return costo;
}

int costo_del(char a){
    int costo;
    a = tolower(a);
    costo = Lcostos_del[int(a)-97];
    return costo;
}

int costo_sub(char a, char b){
    int costo;
    a = tolower(a);
    b = tolower(b);
    costo = Mcostos_sub[int(a)-97][int(b)-97];
    return costo;
}

int costo_trans(char a, char b){
    int costo;
    a = tolower(a);
    b = tolower(b);
    costo = Mcostos_trans[int(a)-97][int(b)-97];
    return costo; 
}

int DMDE(const string& A, const string& B, int N, int M) {

    //Caso base
    if(N == 0) {
        int costo = 0;
        for(int j = 0; j < M; ++j) costo += costo_ins(B[j]);
        return costo;
    } else if(M == 0) {
        int costo = 0;
        for(int i = 0; i < N; ++i) costo += costo_del(A[i]);
        return costo;
    }

    //Caso general
    else {
        int costoSub = DMDE(A,B,N-1,M-1) + costo_sub(A[N-1],B[M-1]);
        int costoDel = DMDE(A,B,N-1,M) + costo_del(A[N-1]);
        int costoIns = DMDE(A,B,N,M-1) + costo_ins(B[M-1]);
        //Caso existe transposición
        if(N > 1 && M > 1 && A[N-1] == B[M-2] && A[N-2] == B[M-1]) {
            int costoTrans = DMDE(A,B,N-2,M-2) + costo_trans(A[N-1],B[M-1]);
            return min(min(costoTrans,costoSub),min(costoDel,costoIns));
        //Caso no existe transposición
        } else {
            return min(costoSub,min(costoDel,costoIns));
        }      
    }
}

int main() {
    //Obtención de costos para el Algoritmo
    fstream del("cost_delete1.txt");
    fstream ins("cost_insert1.txt");
    fstream sub("cost_replace1.txt");
    fstream trans("cost_transpose1.txt");
    
    for(int i = 0; i < 25; ++i){
        del >> Lcostos_del[i];
        ins >> Lcostos_ins[i];
        for(int j = 0; j < 25; ++j){
            sub >> Mcostos_sub[i][j];
            trans >> Mcostos_trans[i][j];
        }
    }
    
    //Obtencion de Dataset y aplicación del Algoritmo
    fstream data("dataset2.txt");
    string S1, S2, Trash;
    int N;
    data >> N;
    data.ignore();
    auto start = chrono::high_resolution_clock::now();
    for(int i = 0; i < N; ++i){
        getline(data,S1);
        getline(data,S2);
        getline(data,Trash);
        cout << "'" << S1 << "' -------------> '" << S2 << "'" << endl;

        int D = DMDE(S1,S2,S1.size(),S2.size());
        cout << "Distancia de edición Extendido: --> " << D << " <-- \n" << endl;

    }
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    cout << "\nTiempo en segundos: " << duration.count() << endl;
	return 0;
}