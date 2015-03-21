#include "BinLattice02.h"
#include "BinModel02.h"
#include "Options09.h"
#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ofstream fout;
    fout.open("Result.txt");
    
    double S0=106.0;
    double r=0.058;
    double sigma=0.46;
    double T=(double)9/12;
    double K=100.0;
    int N=8;
    
    BinModel Model;
    
    Model.SetS0(S0);
    Model.Setr(r);
    Model.SetV(sigma);
    Model.SetT(T);
    Model.SetN(N);
    
    if (Model.GetInputData() == 1)
        return 1;
    
    Put Option;
    Option.SetK(K);
    //Option.GetInputData();
    
    
    BinLattice<double> PriceTree;
    BinLattice<bool> StoppingTree;
    Option.PriceBySnell(Model, PriceTree, StoppingTree);
    fout << "S0 = " << Model.GetS0() << endl;
    fout << "T = " << Model.GetT() << endl;
    fout << "R = " << Model.GetR() << endl;
    fout << "V = " << Model.GetV() << endl;
    fout << "N = " << Model.GetN() << endl;
    fout << "K = " << Option.GetK() << endl;
    fout << "American put prices:" << endl << endl;
    PriceTree.Display(fout);
    fout << "American put exercise policy:" << endl << endl;
    StoppingTree.Display(fout);
    
    cout << "The output is in the 'Result.txt'. " << endl;
    fout.close();
    return 0;
}

