#ifndef _DDOS_
#define _DDOS_
#include <cmath>
#include <vector>
#include <assert.h>
#include "Sketch.hpp"
using namespace std;

class DDOS
{
private:
    SketchList _DDoSSketch;
    bool _alert;
    vector<double> EntThre;
    void caculateEntropy();
public:
    DDOS(/* args */);
    ~DDOS();
    double caculateCurSketchEntropy(Sketch);
    void updateEntropyThre();
    void doDetect(Sketch);
};

#endif