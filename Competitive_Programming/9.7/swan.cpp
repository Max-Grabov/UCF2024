#include <iostream>
#include <vector>
#include <math.h>
#define PI 3.1415926535897932384626433
using namespace std;
double ans = 99999999999999999;

void solve(vector<vector<double>> &dist, vector<bool> visited, vector<pair<double, double>> &loc, pair<double, double> &start, int numLocations, int currLocation, int index, double currDistance){
    if(index == numLocations){
        double dx = start.first - loc[currLocation].first;
        double dy = start.second - loc[currLocation].second;

        if(currDistance + sqrt(dx * dx + dy * dy) <= ans){
            ans = currDistance + sqrt(dx * dx + dy * dy);
        }
        return;
    }

    for(int i = 0; i < numLocations; i++){
        if(dist[currLocation][i] == 0) continue;
        if(visited[i]) continue;

        currDistance += dist[currLocation][i];
        visited[i] = true;

        if(currDistance >= ans){
            return;
        }
        //cout << currDistance << endl;
        solve(dist, visited, loc, start, numLocations, i, index + 1, currDistance);

        visited[i] = false;
        currDistance -= dist[currLocation][i];
    }
}

int main(){
    int n;
    int numLocations, degree, speed;
    int a, b;
    double dx, dy;

    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> numLocations >> degree >> speed;

        vector<pair<double, double>> loc;
        vector<vector<double>> dist(numLocations, vector<double>(numLocations));
        vector<bool> visited;
        pair<double, double> startPos = {1000*cos((PI*degree/180)), 1000*sin((PI*degree/180))};


        for(int j = 0; j < numLocations; j++){
            cin >> a >> b;
            loc.push_back({a*cos((PI*b/180)), a*sin((PI*b/180))});
            visited.push_back(false);
        }

        if(numLocations == 1){
            dx = startPos.first - loc[0].first;
            dy = startPos.second - loc[0].second;
            printf("%0.2lf\n", 2*(sqrt(dx * dx + dy * dy))/speed);
            continue;
        }

        for(int j = 0; j < numLocations; j++){
            for(int k = 0; k < numLocations; k++){
                dx = loc[j].first - loc[k].first;
                dy = loc[j].second - loc[k].second;
                dist[j][k] = sqrt(dx * dx + dy * dy);
            }
        }

        ans = 99999999999999;
        for(int j = 0; j < numLocations; j++){
            dx = startPos.first - loc[j].first;
            dy = startPos.second - loc[j].second;

            visited[j] = true;
            solve(dist, visited, loc, startPos, numLocations, j, 1, sqrt(dx * dx + dy * dy));
            visited[j] = false;
        }
        printf("%0.2lf\n", ans/speed);
        loc.clear();
        visited.clear();
    }
    return 0;
}