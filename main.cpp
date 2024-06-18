#include<iostream>
#include<vector>
#include<cmath>
#include<random>
#include"Network.h"
using namespace std;


int main()
{
    Network net;
    vector<pair<pair<int, int>, int>> trainingData = 
    {
        {{0, 0}, 0},
        {{0, 1}, 1},
        {{1, 0}, 1},
        {{1, 1}, 0}
    };

    net.train(trainingData, 100000);

    printf("Predictions:\n");
    for (int i = 0; i < trainingData.size(); i++)
    {
        printf("%d XOR %d: %.2f\n", trainingData[i].first.first, trainingData[i].first.second, net.predict(trainingData[i].first.first, trainingData[i].first.second));
    }
}