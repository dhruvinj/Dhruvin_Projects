#include<iostream>
#include<cmath>
#include<string>
#include<cassert>
#include<fstream>
#include<cstdlib>

#ifndef GETDATAHEADERDEF
#define GETDATAHEADERDEF

class Getdata
{

 public:
  /*
    Getdata(double re, double res, double cfl, double vn, double episilon);
    double GetRe();
    double Getres() ;
    double GetCFL();
    double GetVN() ;
    double Getepisilon() ;
  */
  Getdata(double re, double rs, double cfl, double vn, double ep)
    {
      Re = re;
      res = rs;
      CFL = cfl;
      VN = vn;
      episilon = ep;
    }
  double GetRe()
  {
    //Re = 100;
    return Re;
  }




  double GetCFL() 
  {
    //CFL=0.01;
    return CFL;
  }


  double GetVN() 
  {
    //VN=0.01;
    return VN;
  }




  double Getres() 
  {
    //res = 0.001;
    return res;
  }



  double Getepisilon() 
  {
    //episilon=0.001;
    return episilon;
  }
 private:
  double Re;
  double res;
  double CFL;
  double VN;
  double episilon;
};

#endif
