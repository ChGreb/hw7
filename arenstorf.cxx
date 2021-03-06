//////////////////////////////////
//  Christian Greb	2030036	//
//  Homework7	Dormand-Prince	//
//////////////////////////////////

#include<cmath>
#include<fstream>

using namespace std;

void fxy(double y0, double y1, double y2, double y3, double* const ki);
void RK45(double& dt, double* const y, double* const y5);
void timestep(double& dt, double* const y, double* const y5);

int main(){
  double T = 0, Tend = 17.065216560157;
  const double mu = 0.012277471;
  double y[4], y5[4];
  double dt = 1E-4;
  y[0] = 0.994;
  y[1] = 0;
  y[2] = 0;
  y[3] = -2.00158510637908;
  
  ofstream out("data.txt");
  out << T << "\t" << dt << "\t" << y[0] << "\t" << y[1] << "\t" << y[2] << "\t" << y[3] << endl;
  
  while(T<Tend){
    RK45(dt, y, y5);
    T += dt;
    out << T << "\t" << dt << "\t" << y[0] << "\t" << y[1] << "\t" << y[2] << "\t" << y[3] << endl;
    timestep(dt, y, y5);
  }
    
  out.close();
  return 0;
}

void fxy(double y0, double y1, double y2, double y3, double* const ki){
  const double mu = 0.012277471;  
  double r = sqrt((y0+mu)*(y0+mu)+y2*y2);
  double s = sqrt((y0-1+mu)*(y0-1+mu)+y2*y2);
  
  ki[0] = y1;
  ki[1] = y0+2*y3-((1-mu)*(y0+mu))/(pow(r,3))-(mu*(y0-1+mu))/(pow(s,3));
  ki[2] = y3;
  ki[3] = y2-2*y1-((1-mu)*y2)/(pow(r,3))-(mu*y2)/(pow(s,3));
  
}

void RK45(double& dt, double* const y, double* const y5){
  double k1[4], k2[4], k3[4], k4[4], k5[4], k6[4], k7[4];
  
    fxy(y[0], y[1], y[2], y[3], k1);
    fxy(y[0]+dt*1./5*k1[0], 
        y[1]+dt*1./5*k1[1], 
        y[2]+dt*1./5*k1[2], 
        y[3]+dt*1./5*k1[3], k2);
    fxy(y[0]+dt*(3./40.*k1[0]+9./40.*k2[0]), 
        y[1]+dt*(3./40.*k1[1]+9./40.*k2[1]), 
        y[2]+dt*(3./40.*k1[2]+9./40.*k2[2]), 
        y[3]+dt*(3./40.*k1[3]+9./40.*k2[3]), k3);
    fxy(y[0]+dt*(44./45.*k1[0]-56./15.*k2[0]+32./9.*k3[0]), 
        y[1]+dt*(44./45.*k1[1]-56./15.*k2[1]+32./9.*k3[1]), 
        y[2]+dt*(44./45.*k1[2]-56./15.*k2[2]+32./9.*k3[2]), 
        y[3]+dt*(44./45.*k1[3]-56./15.*k2[3]+32./9.*k3[3]), k4);
    fxy(y[0]+dt*(19372./6561.*k1[0]-25360./2187.*k2[0]+64448./6561.*k3[0]-212./729.*k4[0]), 
        y[1]+dt*(19372./6561.*k1[1]-25360./2187.*k2[1]+64448./6561.*k3[1]-212./729.*k4[1]), 
        y[2]+dt*(19372./6561.*k1[2]-25360./2187.*k2[2]+64448./6561.*k3[2]-212./729.*k4[2]), 
        y[3]+dt*(19372./6561.*k1[3]-25360./2187.*k2[3]+64448./6561.*k3[3]-212./729.*k4[3]), k5);
    fxy(y[0]+dt*(9017./3168.*k1[0]-355./33.*k2[0]+46732./5247.*k3[0]+49./176.*k4[0]-5103./18656.*k5[0]), 
        y[1]+dt*(9017./3168.*k1[1]-355./33.*k2[1]+46732./5247.*k3[1]+49./176.*k4[1]-5103./18656.*k5[1]), 
        y[2]+dt*(9017./3168.*k1[2]-355./33.*k2[2]+46732./5247.*k3[2]+49./176.*k4[2]-5103./18656.*k5[2]), 
        y[3]+dt*(9017./3168.*k1[3]-355./33.*k2[3]+46732./5247.*k3[3]+49./176.*k4[3]-5103./18656.*k5[3]), k6);
    fxy(y[0]+dt*(35./384.*k1[0]+500./1113.*k3[0]+125./192.*k4[0]-2187./6784.*k5[0]+11./84.*k6[0]), 
        y[1]+dt*(35./384.*k1[1]+500./1113.*k3[1]+125./192.*k4[1]-2187./6784.*k5[1]+11./84.*k6[1]), 
        y[2]+dt*(35./384.*k1[2]+500./1113.*k3[2]+125./192.*k4[2]-2187./6784.*k5[2]+11./84.*k6[2]), 
        y[3]+dt*(35./384.*k1[3]+500./1113.*k3[3]+125./192.*k4[3]-2187./6784.*k5[3]+11./84.*k6[3]), k7);
    
    for(int i=0; i<4; i++){
      y5[i] = y[i] + dt*(35./384.*k1[i]+500./1113.*k3[i]+125./192.*k4[i]-2187./6784.*k5[i]+11./84.*k6[i]);		//RK5
       y[i] += dt*(5179./57600.*k1[i]+7571./16695.*k3[i]+393./640.*k4[i]-92097./339200.*k5[i]+187./2100.*k6[i]+1./40.*k7[i]);		//RK4
    } 
}

void timestep(double& dt, double* const y, double* const y5){
  double xi = 0, tol = 1E-8;
  
  for(int i=0; i<4; i++){
    double v = abs(y[i]-y5[i]);
    
    if(v>xi){	
      xi = v;
      }  
  }
  dt *= pow((tol/xi), 0.2);
}




