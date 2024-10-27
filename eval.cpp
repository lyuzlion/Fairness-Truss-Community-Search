#include <bits/stdc++.h>
using namespace std;

int main() {
    int q[4] = {124, 135, 154, 509};
    int gamma = 1, R = 6;
    for(int F = 6;F <= 14;F += 2) {
        if(F == 10) continue;
        double kk = 0, diamm = 0, tt = 0;
        for(int i = 0;i < 4;i++) {
            string path = "./output/1028/dataset_amazon_A4_F_" + 
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
        }
        kk /= 4;
        diamm /= 4;
        tt /= 4;
        cout << "F : " << F <<", time : " << tt  << ", diameter : " << diamm <<  ", k : " << kk <<  endl;
    }
    return 0;
}

