#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> Mcostos_sub(26,vector<int>(26));
vector<vector<int>> Mcostos_trans(26,vector<int>(26));
vector<int> Lcostos_ins(26);
vector<int> Lcostos_del(26);

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

int DMDEE(const string& A, const string& B, int N, int M) {

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
        int costoSub = DMDEE(A,B,N-1,M-1) + costo_sub(A[N-1],B[M-1]);
        int costoDel = DMDEE(A,B,N-1,M) + costo_del(A[N-1]);
        int costoIns = DMDEE(A,B,N,M-1) + costo_ins(B[M-1]);
        //Caso existe transposición
        if(N > 1 && M > 1 && A[N-1] == B[M-2] && A[N-2] == B[M-1]) {
            int costoTrans = DMDEE(A,B,N-2,M-2) + costo_trans(A[N-1],B[M-1]);
            return min(min(costoTrans,costoSub),min(costoDel,costoIns));
        //Caso no existe transposición
        } else {
            return min(costoSub,min(costoDel,costoIns));
        }      
    }
}

int main() {
    //Obtención de costos para el Algoritmo
    fstream del("cost_delete2.txt");
    fstream ins("cost_insert2.txt");
    fstream sub("cost_replace2.txt");
    fstream trans("cost_transpose2.txt");
    
    for(int i = 0; i < 26; ++i){
        del >> Lcostos_del[i];
        ins >> Lcostos_ins[i];
        for(int j = 0; j < 26; ++j){
            sub >> Mcostos_sub[i][j];
            trans >> Mcostos_trans[i][j];
        }
    }
    
    //Obtencion de Dataset y aplicación del Algoritmo
    fstream data("data5.txt");
    string S1, S2;
    int N;
    data >> N;
    for(int i = 0; i < N; ++i){
        data >> S1;
        data >> S2;
        if(S1 == "0") S1 = "";
        if(S2 == "0") S2 = "";
        cout << "'" << S1 << "' -------------> '" << S2 << "'" << endl;
        int Distancia;
        
        auto start = chrono::high_resolution_clock::now();
        for(int j = 0; j < 5; ++j){
            Distancia = DMDEE(S1,S2,S1.size(),S2.size());
        }
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = end - start;

        cout << "Distancia de edición Extendida: --> " << Distancia << " <-- " << endl;
        cout << "Tiempo promedio en segundos: " << (duration.count())/5 << "\n" << endl;
        
    }
    data.close();
	return 0;
}