#include "DDOS.hpp"

DDOS::DDOS(/* args */)
{
    _alert = false;
    EntThre.resize(2);
}

// for updating Sketch List Threhold
void DDOS::caculateEntropy()
{
    for (size_t l = 0; l < ListLength; l++)
    {
        if (!_DDoSSketch._sketchL[l]._sketchisempty)
        {
            Sketch cursketch = _DDoSSketch._sketchL[l];
            int hcount = cursketch.getHashCount();
            int kcount = cursketch.getKmemoryCount();
            int sketchSum = 0;
            for (size_t h = 0; h < hcount; h++)
            {
                for (size_t k = 0; k < kcount; k++)
                {
                    sketchSum += cursketch.getNij();
                }
            }

            double entropy_l;
            for (size_t h = 0; h < hcount; h++)
            {
                for (size_t k = 0; k < kcount; k++)
                {
                    double pij = cursketch.getNij() / sketchSum;
                    entropy_l += pij * log(pij);
                }
            }
            entropy_l = -entropy_l;
            cursketch.setEntropy(entropy_l);
        }
    }
}
// update Sketch List Entropy threhold
void DDOS::updateEntropyThre()
{
    caculateEntropy();
    EntThre.clear();
    EntThre.shrink_to_fit();

    int listentropySum = 0;
    for (size_t l = 0; l < ListLength; l++)
    {
        if (!_DDoSSketch._sketchL[l]._sketchisempty)
        {
            listentropySum += _DDoSSketch._sketchL[l].getEntropy();
        }
    }
    double listentropyAve = (listentropySum * 1.0) / ListLength;

    double diffsqu = 0.0;
    for (size_t l = 0; l < ListLength; l++)
    {
        if (!_DDoSSketch._sketchL[l]._sketchisempty)
        {
            diffsqu += pow((_DDoSSketch._sketchL[l].getEntropy() - listentropyAve), 2);
        }
    }
    double delta = sqrt(diffsqu / (ListLength - 1));

    EntThre.push_back(listentropyAve - 3 * delta);
    EntThre.push_back(listentropyAve + 3 * delta);
}
// caculate current sketch entropy, 
double DDOS::caculateCurSketchEntropy(Sketch cursketch)
{
    int hcount = cursketch.getHashCount();
    int kcount = cursketch.getKmemoryCount();
    int sketchSum = 0;
    for (size_t h = 0; h < hcount; h++)
    {
        for (size_t k = 0; k < kcount; k++)
        {
            sketchSum += cursketch.getNij();
        }
    }

    double entropy_l;
    for (size_t h = 0; h < hcount; h++)
    {
        for (size_t k = 0; k < kcount; k++)
        {
            double pij = cursketch.getNij() / sketchSum;
            entropy_l += pij * log(pij);
        }
    }
    return -entropy_l;
}

// if current sketch entropy is not in the range of Threhold, Alert!
void DDOS::doDetect(Sketch cursketch)
{
    double curSketchEnt = caculateCurSketchEntropy(cursketch);
    assert(EntThre.size() == 2);
    if (curSketchEnt < EntThre[0] || curSketchEnt > EntThre[1])
    {
        _alert = true;
    }
}