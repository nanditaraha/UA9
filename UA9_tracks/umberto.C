#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
int main()
{
    long double x1 = 0.34599586141601396;
    long double x2 = 0.93212039493814425;
    long double dx = 0.01953748445073767;
    long double me = 0.000511;
    long double me2 = me*me;
    long double mmu = 0.10566;
    long double mu2=mmu*mmu;
    long double Emu=150.;
    long double dxm = (x2 - x1)/30.;
    long double xvalue = x1; 
    cout << " input values x1  " << setprecision(17) << x1  << endl;
    cout << " input values x2  " << setprecision(17) << x2  << endl;
    cout << " input values dxm " << setprecision(17) << dxm << endl;
    for( int a = 0; a < 31; a = a + 1 ) 
    {   
      cout << "value of x: " << setprecision(17) << xvalue << endl;
      long double tt=xvalue*xvalue*mu2/(xvalue-1);
      long double Ee=(2*me2-tt)/2./me;
      long double r=sqrt(Emu*Emu-mu2)/(Emu+me);
      long double theta=acos(1./r*sqrt((Ee-me)/(Ee+me)));
      cout << a << "  " << xvalue << "  " << tt << "  " << Ee << "  " <<theta<<" \n";
      xvalue += dxm; 
    }   
    return 1;
    
}


