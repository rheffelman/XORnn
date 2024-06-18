#pragma once
#define eulers 2.71828
#include<iostream>
#include<vector>
#include<cmath>
#include<random>
#include"Neuron.h"
#include"HiddenLayer.h"
#include"OutputLayer.h"
using namespace std;

struct InputLayer
{
    int a = 0;
    int b = 0;
};

class Network
{
public:

    Network()
    {
        hl = new HiddenLayer(2, 2);
        ol = new OutputLayer(1, 2);
        learningRate = 0.1;
    }

    InputLayer il;
    HiddenLayer * hl = nullptr;
    OutputLayer * ol = nullptr;
    double learningRate;

    void feed(int data1, int data2)
    {
        il.a = data1;
        il.b = data2;

        for (int i = 0; i < hl->hiddenNodes.size(); i++)
        {
            hl->hiddenNodes[i]->z = ((il.a * hl->hiddenNodes[i]->weights[0]) + (il.b * hl->hiddenNodes[i]->weights[1])) + hl->hiddenNodes[i]->bias;
            hl->hiddenNodes[i]->brightness = sigmoid(hl->hiddenNodes[i]->z);
        }
        ol->outputNodes[0]->z = ((hl->hiddenNodes[0]->brightness * ol->outputNodes[0]->weights[0]) + (hl->hiddenNodes[1]->brightness * ol->outputNodes[0]->weights[1])) + ol->outputNodes[0]->bias;
        ol->outputNodes[0]->brightness = sigmoid(ol->outputNodes[0]->z);
    }

    void backpropagate(int target)
    {
        double output = ol->outputNodes[0]->brightness;
        double outputError = target - output;
        double outputDelta = outputError * sigmoidDerivative(ol->outputNodes[0]->z);

        vector<double> hiddenErrors(hl->hiddenNodes.size());
        vector<double> hiddenDeltas(hl->hiddenNodes.size());

        for (int i = 0; i < hl->hiddenNodes.size(); i++)
        {
            hiddenErrors[i] = outputDelta * ol->outputNodes[0]->weights[i];
            hiddenDeltas[i] = hiddenErrors[i] * sigmoidDerivative(hl->hiddenNodes[i]->z);
        }

        for (int i = 0; i < hl->hiddenNodes.size(); i++)
        {
            ol->outputNodes[0]->weights[i] += learningRate * outputDelta * hl->hiddenNodes[i]->brightness;
            ol->outputNodes[0]->bias += learningRate * outputDelta;
        }

        for (int i = 0; i < hl->hiddenNodes.size(); i++)
        {
            hl->hiddenNodes[i]->weights[0] += learningRate * hiddenDeltas[i] * il.a;
            hl->hiddenNodes[i]->weights[1] += learningRate * hiddenDeltas[i] * il.b;
            hl->hiddenNodes[i]->bias += learningRate * hiddenDeltas[i];
        }
    }

    void train(vector<pair<pair<int, int>, int>> data, int epochs)
    {
        for (int i = 0; i < epochs; i++)
        {
            for (auto &d : data)
            {
                feed(d.first.first, d.first.second);
                backpropagate(d.second);
            }
        }
    }

    double predict(int data1, int data2)
    {
        feed(data1, data2);
        return ol->outputNodes[0]->brightness;
    }

    double sigmoid(double x)
    {
        return 1.0 / (1 + pow(eulers, -x));
    }

    double sigmoidDerivative(double x)
    {
        return sigmoid(x) * (1 - sigmoid(x));
    }
};

