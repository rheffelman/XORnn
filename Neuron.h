#pragma once
#include<iostream>
#include<vector>
#include<cmath>
#include<random>
using namespace std;

class Neuron
{
public:
    Neuron(int seed, int numWeights)
    {
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<> dis(-1, 1);
        for (int i = 0; i < numWeights; i++)
        {
            weights.push_back(dis(gen));
        }
        bias = dis(gen);
    }
    double bias;
    vector<double> weights;
    double brightness;
    double z;
};