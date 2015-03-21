#ifndef BinModel_h
#define BinModel_h
class BinModel {
private:
    int N;
    double S0;
    double U;
    double D;
    double R;
    double time_to_maturity;
    double interest_rate;
    double volatility;
public:
    double RiskNeutProb();
    double S(int n, int i);
    int GetInputData();
    double GetR();
    int GetN();
    double GetS0() {return S0;}
    double GetT() {return time_to_maturity;}
    double GetV() {return volatility;}
    void SetS0(double S0_){S0 = S0_;}
    void Setr(double r_){interest_rate = r_;}
    void SetV(double V_){volatility = V_;}
    void SetT(double T_){time_to_maturity = T_;}
    void SetN(int N_){N = N_;}
    
};
#endif
