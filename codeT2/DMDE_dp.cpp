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

    //Creación de memoria para el guardado de subproblemas
    vector<vector<int>> memo(N+1,vector<int>(M+1));

    for(int i = 0; i < N+1; ++i){
        for(int j = 0; j < M+1; ++j){

            //Caso base
            if(i == 0 && j == 0) memo[i][j] = 0;
            else if(i == 0) memo[i][j] = memo[i][j-1] + costo_ins(B[j-1]);
            else if(j == 0) memo[i][j] = memo[i-1][j] + costo_del(A[i-1]);

            //Caso general
            else {
                int costoSub = memo[i-1][j-1] + costo_sub(A[i-1],B[j-1]);
                int costoDel = memo[i-1][j] + costo_del(A[i-1]);
                int costoIns = memo[i][j-1] + costo_ins(B[j-1]);
                //Caso existe transposición
                if(i > 1 && j > 1 && A[i-1] == B[j-2] && A[i-2] == B[j-1]) {    
                    int costoTrans = memo[i-2][j-2] + costo_trans(A[i-1],B[j-1]);                 
                    memo[i][j] = min(min(costoTrans,costoSub),min(costoDel,costoIns));
                //Caso no existe transposición
                } else {
                    memo[i][j] = min(costoSub,min(costoDel,costoIns));
                }
            }
        }
    }

    return memo[N][M];
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
    fstream data("dataset1.txt");
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