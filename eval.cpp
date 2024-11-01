#include <bits/stdc++.h>
using namespace std;

int main() {
    int q[4] = {364788, 409642};
    int gamma = 1, F = 10;
    for(int R = 2;R <= 10;R += 2) {
        // if(F == 10) continue;
        double kk = 0, diamm = 0, tt = 0, kkm = 11110;
        for(int i = 0;i < 2;i++) {
            string path = "./output/1030/dataset_wiki_A4_F_" + 
                to_string(F) + 
                "_q_" + to_string(q[i]) + 
                "_R_" + to_string(R) + 
                "_gamma_" + to_string(gamma) + ".txt"; 
            freopen(path.c_str(), "r", stdin);
            // cout << path << endl;
            double k, diam, t;
            scanf("k : %lf\nOverall running time: %lfs.\ndiameter : %lf", &k, &t, &diam);
            kk += k;
            diamm += diam;
            tt += t;
            kkm = min(kkm, k);
        }
        kk /= 2;
        diamm /= 2;
        tt /= 2;
        cout << "R : " << R <<", time : " << tt  << ", diameter : " << diamm <<  ", k : " << kk << ", kmin : " << kkm << endl;
    }
    return 0;
}

