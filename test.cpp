#include <bits/stdc++.h>
using namespace std;
int main() {
    freopen("test.sh", "w", stdout);
    freopen("./Dataset/deezer/deezer_processed.txt", "r", stdin);
    string a,b,c;
    int d;
    cin >> a >> b >> c >> d;
    // cerr << a << b << c << d;
    for(int i = 1;i <= 100;i++) {
        int x, y;
        cin >> x >> y;
        cout << "./main deezer 6 " << x << " 2 1\n";//./main butterfly 10 50 10 1
        cout << "./main deezer 8 " << x << " 2 1\n";//./main butterfly 10 50 10 1
        cout << "./main deezer 10 " << x << " 2 1\n";//./main butterfly 10 50 10 1
        cout << "./main deezer 12 " << x << " 2 1\n";//./main butterfly 10 50 10 1
        cout << "./main deezer 14 " << x << " 2 1\n";//./main butterfly 10 50 10 1
        
        cout << "./main deezer 6 " << x << " 2 20\n";//./main butterfly 10 50 10 1
        cout << "./main deezer 8 " << x << " 2 20\n";//./main butterfly 10 50 10 1
        cout << "./main deezer 10 " << x << " 2 20\n";//./main butterfly 10 50 10 1
        cout << "./main deezer 12 " << x << " 2 20\n";//./main butterfly 10 50 10 1
        cout << "./main deezer 14 " << x << " 2 20\n";//./main butterfly 10 50 10 1
    }


    // freopen("./Dataset/facebook_A4/facebook_A4_processed.txt", "r", stdin);

    // cin >> a >> b >> c >> d;
    // // cerr << a << b << c << d;
    // for(int i = 1;i <= 18;i++) {
    //     int x, y;
    //     cin >> x >> y;
    //     cout << "./main facebook_A4 6 " << x << " 6 1\n";//./main butterfly 10 50 10 1
    //     cout << "./main facebook_A4 8 " << x << " 6 1\n";//./main butterfly 10 50 10 1
    //     cout << "./main facebook_A4 10 " << x << " 6 1\n";//./main butterfly 10 50 10 1
    //     cout << "./main facebook_A4 12 " << x << " 6 1\n";//./main butterfly 10 50 10 1
    //     cout << "./main facebook_A4 14 " << x << " 6 1\n";//./main butterfly 10 50 10 1
        
    //     cout << "./main facebook_A4 6 " << x << " 6 20\n";//./main butterfly 10 50 10 1
    //     cout << "./main facebook_A4 8 " << x << " 6 20\n";//./main butterfly 10 50 10 1
    //     cout << "./main facebook_A4 10 " << x << " 6 20\n";//./main butterfly 10 50 10 1
    //     cout << "./main facebook_A4 12 " << x << " 6 20\n";//./main butterfly 10 50 10 1
    //     cout << "./main facebook_A4 14 " << x << " 6 20\n";//./main butterfly 10 50 10 1
    // }

    return 0;
}