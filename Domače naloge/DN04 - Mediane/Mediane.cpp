#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Z bisekcijo vstavljamo v urejen seznam in izpisujemo mediane.

int main(){
    int N, x, min, max, polovica;
    cin >> N;
    //int *arr = (int*)malloc(N*sizeof(int));
    vector <int> arr(N);
    cin >> x;
    arr[0] = x;
    cout << arr[0] << "\n";

    for (int i = 1; i < N; i++){
        cin >> x;
        min = 0;
        max = i-1;
        if (x >= arr[i-1]){
            arr[i] = x;
        }
        else if (x < arr[0]){
            arr.insert(arr.begin(), x);
        }
        else{
            while (max > min){
                polovica = (min + max) / 2;
                if (arr[polovica] < x){
                    min = polovica+1;
                }
                else{
                    max = polovica;
                }
            }
            /*for (int j = i; j > max; j--){
                arr[j] = arr[j-1];
            }
            arr[max] = x;*/
            arr.insert(arr.begin()+max, x);
        }
        
        cout << arr[i/2] << "\n";
    }
    

    return 0;
}