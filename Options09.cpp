#include "BinLattice02.h"
#include "BinModel02.h"
#include "Options09.h"
#include <iostream>
#include <cmath>
using namespace std;

double EurOption::PriceByCRR(BinModel Model, BinLattice<double>& PriceTree,
                             BinLattice<double>& StockTree, BinLattice<double>&MoneyTree) {
    //double q = Model.RiskNeutProb();
    int N = GetN();
    PriceTree.SetN(N);
    StockTree.SetN(N - 1);
    MoneyTree.SetN(N - 1);
    for (int i = 0; i <= N; ++i) {
        PriceTree.SetNode(N, i, Payoff(Model.S(N, i)));
    }
    for (int i = N - 1; i >= 0; --i) {
        for (int j = 0; j <= i; ++j) {
            double P0 = PriceTree.GetNode(i + 1, j), P1 = PriceTree.GetNode(i + 1, j + 1);
            double S0 = Model.S(i + 1, j), S1 = Model.S(i + 1, j + 1);
            double delta = (P1 - P0) / (S1 - S0);
            double bond  = (P0 * S1 - P1 * S0) / (S1 - S0) / (1 + Model.GetR());
            StockTree.SetNode(i, j, delta);
            MoneyTree.SetNode(i, j, bond);
            PriceTree.SetNode(i, j, delta * Model.S(i, j) + bond);
        }
    }
    
    return PriceTree.GetNode(0, 0);
}

double AmOption::PriceBySnell(BinModel Model, BinLattice<double>& PriceTree,
                              BinLattice<bool>& StoppingTree) {
    double q = Model.RiskNeutProb();
    int N = Model.GetN();
    PriceTree.SetN(N);
    StoppingTree.SetN(N);
    double ContVal;
    
    for (int i = 0; i<= N; ++i) {
        PriceTree.SetNode(N, i, Payoff(Model.S(N, i)));
        StoppingTree.SetNode(N, i, 1);
    }
    
    for (int n = N - 1; n >= 0; --n) {
        for (int i = 0; i <= n; ++i) {
            ContVal = (q * PriceTree.GetNode(n + 1, i + 1) + (1 - q)
                       * PriceTree.GetNode(n + 1, i)) / (1 + Model.GetR());
            PriceTree.SetNode(n, i, Payoff(Model.S(n, i)));
            StoppingTree.SetNode(n, i, 1);
            if (ContVal > PriceTree.GetNode(n, i)) {
                PriceTree.SetNode(n, i, ContVal);
                StoppingTree.SetNode(n, i, 0);
            }
            else if (PriceTree.GetNode(n, i) == 0.0) {
                StoppingTree.SetNode(n, i, 0);
            }
        }
    }
    return PriceTree.GetNode(0, 0);
}


int Call::GetInputData() {
    cout << "Enter call option data  : " << endl;
    int N;
    cout << "Enter steps to expiry N : ";
    cin >> N;
    SetN(N);
    cout << "Enter strike price K    : ";
    cin >> K;
    cout << endl;
    return 0;
}

double Call::Payoff(double z) {
    if (z > K)
        return z - K;
    return 0.0;
}

int Put::GetInputData() {
    cout << "Enter put option data   : " << endl;
    int N;
    cout << "Enter steps to expiry N : ";
    cin >> N;
    SetN(N);
    cout << "Enter strike price K    : ";
    cin >> K;
    cout << endl;
    return 0;
}

double Put::Payoff(double z) {
    if (z < K)
        return K - z;
    return 0.0;
}
