#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string.h>
using namespace std;

// Izračunamo najmanjšo razdaljo med dvema točkama. Če je xmin == 0 in ymin == 0, se prekrivata.

int main(){
    int T;
    cin >> T;
    int x1, y1, x2, y2, x3, y3, x4, y4;
    int x1min, y1min, x1max, y1max;
    int x2min, y2min, x2max, y2max;
    int xmin, ymin;
    double razdalja;
    int razdalja_pednji;

    for (int i = 0; i < T; i++){
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
        x1min = min(x1, x2);
        x1max = max(x1, x2);
        y1min = min(y1, y2);
        y1max = max(y1, y2);
        x2min = min(x3, x4);
        x2max = max(x3, x4);
        y2min = min(y3, y4);
        y2max = max(y3, y4);

        // Najmanjsa razdalja po x in y

        if (x1max >= x2max){
            if (x1min > x2max){
                xmin = x1min - x2max;
            }else{ // x1min <= x2max
                xmin = 0;
            }
        }else{
            if (x1max < x2min){
                xmin = x2min - x1max;
            }else{ // x1max >= x2min
                xmin = 0;
            }
        }

        if (y1max >= y2max){
            if (y1min > y2max){
                ymin = y1min - y2max;
            }else{ // y1min <= y2max
                ymin = 0;
            }
        }else{
            if (y1max < y2min){
                ymin = y2min - y1max;
            }else{ // y1max >= y2min
                ymin = 0;
            }
        }

        // ymin == 0 in xmin == 0 -> razdalja = 0 (se prekrivata)

        razdalja = sqrt(xmin*xmin + ymin*ymin);
        razdalja = razdalja * 8;
        razdalja_pednji = razdalja;
        if (razdalja_pednji < razdalja){
            razdalja_pednji++; // Zaokrozevanje navzgor
        }
        cout << razdalja_pednji << endl;
        
    }

    
    return 0;
}
