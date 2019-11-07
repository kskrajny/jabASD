#include <iostream>
#include <cstdio>
#define gc getchar_unlocked
using namespace std;

#define STALA 1000000000
static int n;
static int d;
static int brak = 0; // ile galezi brakuje do poziomu d
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
    int ltab[n]; // i-ty elem to lewy syn i+1-tej galezi
    int ptab[n]; // i-ty elem to prawy syn i+1-tej galezi
    int suma[n+1]; // i-ty elem, to liczba galezi w drzewie o korzeniu i
    int previous[n+1]; // i-ty elem, to ilosc "0" od "i" w odleglosci s-1
    int current[n+1]; // i-ty elem, to ilosc "0" od "i" w odleglosci s
    // prev i curr beda modyfikowane dynamicznie
    int odlZer[d-2]; // i-ty elem, to ilosc "0" odleglych od "n" o i+1;
    int *pom;
    pre = previous;
    curr = current;
    suma[0] = 1;
    previous[0] = 0;
    current[0] = 0;

    for(int i=0;i<d-2;i++){
        odlZer[i] = 0;
    }

    for(int i=0;i<n;i++) {
        scanint(ltab[i]);
        scanint(ptab[i]);
        previous[i+1] = 0;
        if(ltab[i] == 0){
            previous[i+1]++;
        } // ustalamy ile, jakie elem w odl 1 od "0"
        if(ptab[i] == 0){
            previous[i+1]++;
        } // ustalamy ile, jakie elem w odl 1 od "0"
        current[i+1] = 0;
        suma[i+1] = suma[ltab[i]] + suma[ptab[i]] + 1;
        suma[i+1] = suma[i+1]%STALA;
        // liczymy dynamicznie ilosc galezi
    }
    //cout << "wczytanie, sumy " << obliczSekundy(clock()) << endl;
    if(ltab[n-1] == 0){
        odlZer[0]++;
    } // ustalamy czy jest "0" w odl 1 od "n"

    if(ptab[n-1] == 0){
        odlZer[0]++;
    } // ustalamy czy jest "0" w odl 1 od "n"

    for(int i=2;i<d-1;i++){
        for(int j=i;j<n+1;j++){
            *(curr+j) = (*(pre+ltab[j-1]) + *(pre+ptab[j-1]))%STALA;
        }
        odlZer[i-1] = *(curr+n);
        pom = pre;
        pre = curr;
        curr = pom;
        for(int j=i-1;j<n;j++){
            *(curr+j) = 0;
        }
    }

    //cout << "ileZer " << obliczSekundy(clock()) << endl;

    for(int i=0;i<d-2;i++){
        if(odlZer[i] != 0){
            for(int j=0;j<odlZer[i];j++){
                suma[n] += (tab[d-i-1]-2);
                suma[n] = suma[n]%STALA;
            }
        }
    }
    suma[n] = (suma[n]+STALA-tab[d]+1)%STALA;
    //cout << "koniec " << obliczSekundy(clock()) << endl;
    cout << suma[n];
    return 0;
}
