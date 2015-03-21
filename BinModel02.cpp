#include "BinModel02.h"
#include <iostream>
#include <cmath>
using namespace std;

double BinModel::RiskNeutProb() {
    return (R - D) / (U - D);
}

double BinModel::S(int n, int i) {
    return S0 * pow(1 + U, i) * pow(1 + D, n - i);
}

double BinModel::GetR() {
    return R;
}

int BinModel::GetN() {
    return N;
}

int BinModel::GetInputData() {
    /*
    cout << "Enter S0 : ";
    cin >> S0;
    cout << "Enter interest rate  r : ";
    cin >> interest_rate;
    cout << "Enter volatility v : ";
    cin >> volatility;
    cout << "Enter time to maturity T : ";
    cin >> time_to_maturity;
    cout << "Enter steps to expiry N : ";
    cin >> N;
    cout << endl;
    */
    
    double h = time_to_maturity / N;
    U = exp((interest_rate + volatility * volatility / 2) * h
            + volatility * sqrt(h)) - 1;
    D = exp((interest_rate + volatility * volatility / 2) * h
            - volatility * sqrt(h)) - 1;
    R = exp(interest_rate * h) - 1;
    
    if (S0 <= 0.0 || U <= -1.0 || D <= -1.0 || U <= D || R <= -1.0) {
        cout << "Illegal data ranges" << endl;
        cout << "Terminating program" << endl;
        return 1;
    }
    
    if (R >= U || R <= D) {
        cout << "Arbitrage exists" << endl;
        cout << "Terminating program" << endl;
        return 1;
    }
    
    cout << "Input data checked" << endl;
    cout << "There is no arbitrage" << endl << endl;
    
    return 0;
}
