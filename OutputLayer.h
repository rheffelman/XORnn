#include<vector>
#include<cmath>
#include<random>
#include"Neuron.h"
using namespace std;

class OutputLayer
{
public:
    OutputLayer(int numNodes, int numInputs)
    {
        for (int i = 0; i < numNodes; i++)
        {
            Neuron * temp = new Neuron(i * 33, numInputs);
            outputNodes.push_back(temp);
        }
    }
    vector<Neuron*> outputNodes;
};