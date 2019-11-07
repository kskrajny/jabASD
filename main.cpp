#include <iostream>
#include <cstdio>
#define gc getchar_unlocked
using namespace std;

#define STALA 1000000000
static int n;
static int d;
static int *pre;
static int *curr;

namespace {
    int tab[101];
    bool potegi(){
        tab[0] = 1;
        for(int i=1;i<101;i++){
            tab[i] = (tab[i-1]*2)%STALA;
        }
        return true;
    }
    bool done = potegi();
}
/*
double obliczSekundy( clock_t czas )
{
    return static_cast < double >( czas ) / CLOCKS_PER_SEC;
}
*/
void scanint(int &x)
{
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}

int main() {
    ios::sync_with_stdio(false);
    scanint(n);
    scanint(d);
    if(d > n){
        cout << "0";
        return 0;
    }

    int *ltab = new int[n]; // i-ty elem to lewy syn i+1-tej galezi
    int *ptab = new int[n]; // i-ty elem to prawy syn i+1-tej galezi
    //cout << "input" << endl;
    int *suma = new int[n+1]; // i-ty elem, to liczba galezi w drzewie o korzeniu i
    //cout << "all n" << endl;
    int odlZer[d-2]; // i-ty elem, to ilosc "0" odleglych od "n" o i+1;
    int *pom;
    suma[0] = 1;
    int max;

    for(int i=0;i<d-2;i++){
        odlZer[i] = 0;
    }

    //cout << "pamiec " << (sizeof(ltab)+sizeof(ptab)+sizeof(suma)+sizeof(odlZer))/1048576 << endl;

    for(int i=0;i<n;i++) {
        scanint(ltab[i]);
        scanint(ptab[i]);
        suma[i+1] = suma[ltab[i]] + suma[ptab[i]] + 1;
        suma[i+1] = suma[i+1]%STALA;
        // liczymy dynamicznie ilosc galezi
    }

    max = suma[n];
    suma[0] = 0; // tablica posluzy nam do innych rzeczy
    curr = suma;  // i-ty elem, to ilosc "0" od "i" w odleglosci s

    //cout << "wczytanie, sumy " << obliczSekundy(clock()) << endl;

    if(ltab[n-1] == 0){
        odlZer[0]++;
    } // ustalamy czy jest "0" w odl 1 od "n"

    if(ptab[n-1] == 0){
        odlZer[0]++;
    } // ustalamy czy jest "0" w odl 1 od "n"

    for(int i=0;i<n;i++){
        (*(curr+i+1)) = 0;
        if(ltab[i] == 0){
            (*(curr+i+1))++;
        } // ustalamy ile, jakie elem w odl 1 od "0"
        if(ptab[i] == 0){
            (*(curr+i+1))++;
        } // ustalamy ile, jakie elem w odl 1 od "0"
    }

    for(int i=2;i<d-1;i++){
        // w iteracji i, obliczamy ile jest "0" od "n" w odl i
        ltab[i-2] = 0;
        ptab[i-2] = 0;
        for(int j=n;j>i-1;j--){
            *(curr+j) = (*(curr+ltab[j-1]) + *(curr+ptab[j-1]))%STALA;
        }
        odlZer[i-1] = *(curr+n);
    }

    //cout << "ileZer " << obliczSekundy(clock()) << endl;

    for(int i=0;i<d-2;i++){
        if(odlZer[i] != 0){
            for(int j=0;j<odlZer[i];j++){
                max += (tab[d-i-1]-2);
                max = max%STALA;
            }
        }
    }
    max = (max+STALA-tab[d]+1)%STALA;
    //cout << "koniec " << obliczSekundy(clock()) << endl;
    cout << max;
    delete [] suma;
    delete [] ltab;
    delete [] ptab;
    return 0;
}
