#include<vector>
#include<cmath>
#include<random>
#include"Neuron.h"
using namespace std;

class HiddenLayer
{
public:
    HiddenLayer(int numNodes, int numInputs)
    {
        for (int i = 0; i < numNodes; i++)
        {
            Neuron * temp = new Neuron(i * 33, numInputs);
            hiddenNodes.push_back(temp);
        }
    }
    vector<Neuron*> hiddenNodes;
};