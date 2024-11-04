#include <iostream>
#include <cstdlib>
#include <math.h>
using namespace std;

int main(){
    int dim, numBase;

    cout << "Enter number of dimensions and number of bases:" << endl;
    cin >> dim >> numBase;

    double **vectors = (double**)malloc(sizeof(double*) * (numBase));
    double **ans = (double**)malloc(sizeof(double*) * (numBase));
    for(int i = 0; i < dim; i++){
        vectors[i] = (double*)malloc(sizeof(double) * dim);
        ans[i] = (double*)malloc(sizeof(double) * dim);
    }

    double t;
    cout << "Enter basis:" << endl;

    for(int i = 0; i < numBase; i++){
        for(int j = 0; j < dim; j++){
            cin >> t;
            vectors[i][j] = t;
        }
        cout << "-------------------" << endl;
    }

    cout << "Calculating" << endl;

    double dotYU, dotUU;

    double *hold = (double*)calloc(dim, sizeof(double));

    for(int j = 0; j < numBase; j++){

        if(j == 0){
            for(int n = 0; n < dim; n++){
                ans[j][n] = vectors[j][n];
            }
            continue;
        }

        for(int k = j - 1; k >= 0; k--){
            dotUU = 0;
            dotYU = 0;
            for(int n = 0; n < dim; n++){
                dotUU += ans[k][n] * ans[k][n];
                dotYU += vectors[j][n] * ans[k][n];
            }

            for(int n = 0; n < dim; n++){
                hold[n] += (dotYU / dotUU) * ans[k][n];
            }
        }

        for(int n = 0; n < dim; n++){
            ans[j][n] = vectors[j][n] - hold[n];
            hold[n] = 0;
        }
    }

    for(int i = 0; i < dim; i++){
        for(int j = 0; j < numBase; j++){
            cout << ans[j][i] << " ";
        }
        cout << endl;
    }
    return 0;
}
