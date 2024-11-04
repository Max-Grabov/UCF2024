#include <iostream>
#include <cstdlib>
#include <math.h>
using namespace std;

int main(){
    int dim, numBase;

    cout << "Enter number of dimensions and number of bases:" << endl;
    cin >> dim >> numBase;

    double **vectors = (double**)malloc(sizeof(double*) * (numBase + 1));
    for(int i = 0; i < dim; i++){
        vectors[i] = (double*)malloc(sizeof(double) * dim);
    }

    double t;
    cout << "Enter vector to project:" << endl;

    for(int i = 0; i < dim; i++){
        cin >> t;
        vectors[0][i] = t;
    }

    cout << "Enter basis:" << endl;

    for(int i = 0; i < numBase; i++){
        for(int j = 0; j < dim; j++){
            cin >> t;
            vectors[i+1][j] = t;
        }
        cout << "-------------------" << endl;
    }

    cout << "Calculating" << endl;

    double dotYU, dotUU;

    double *hold = (double*)calloc(dim, sizeof(double));

    for(int i = 0; i < numBase; i++){
        dotUU = 0;
        dotYU = 0;

        for(int j = 0; j < dim; j++){
            dotUU += vectors[i+1][j] * vectors[i+1][j];
            dotYU += vectors[0][j] * vectors[i+1][j];
        }

        //cout << dotUU << " " << dotYU << endl;
        for(int j = 0; j < dim; j++){
            hold[j] += vectors[i+1][j] * (dotYU / dotUU);
            //cout << vectors[i+1][j] * (dotYU / dotUU) << endl;
        }
    }

    for(int i = 0; i < dim; i++){
        cout << hold[i] << endl;
    }

    int choice;
    cout << "Do you want z (2) or distance (1)?" << endl;

    cin >> choice;

    if(choice == 1){
        double sum = 0;

        for(int i = 0; i < dim; i++){
            sum += pow((vectors[0][i] - hold[i]), 2);
        }

        cout << pow(sum, 0.5) << endl;
    }

    else if(choice == 2){
         double *zV = (double*)malloc(sizeof(double) * dim);

        for(int i = 0; i < dim; i++){
            zV[i] = vectors[0][i] - hold[i];
        }

        cout << "z Vector is: " << endl;

        for(int i = 0; i < dim; i++){
            cout << zV[i] << endl;
        }

        free(zV);
    }

    free(hold);
    for(int i = 0; i < numBase + 1; i++){
        free(vectors[i]);
    }
    free(vectors);
    return 0;
}