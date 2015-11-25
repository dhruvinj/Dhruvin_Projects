#include<iostream>
#include<cmath>
#include<string>
#include<cassert>
#include<fstream>
#include<cstdlib>
#include"metrics.h"
#include"gridgeneration.h"
#include "bcsuv.h"
#include "curvilinearrhs.h"
#include "bcsp.h"
#include "dissipation.h"
#include "Getdata.h"
#include "localtime.h"
#include "residualsmoothing.h"

void dissipation(int nodes, double** u, double** v, double** p, double** U, double** V, double** g_11, double** g_22, double** J, double** dis_1, double** dis_2, double** dis_3, double episilon);
void bcsp(int nodes, double** p,double** u,double** v);
void gridgeneration(int nodes, double r,double** x,double** y,double* dx,double* dy);

void bcsuv(int nodes, double** u,double** v,double** p);

void metrics(double** x,double** y,int nodes, double** eta, double** xita, double** G, double** J, double** xita_x, double** xita_y, double** eta_x, double** eta_y, double** x_xita, double** y_eta,double** x_eta,double** y_xita);


void curvilinearrhs(double** x,double** y,int nodes, double** eta, double** xita, double** G, double** J, double** xita_x, double** xita_y, double** eta_x, double** eta_y, double** x_xita, double** y_eta,double** x_eta,double** y_xita, double** u, double** v, double** p, double** R_ca, double** R_cu, double** R_cv, double** U, double** V, double** g_11, double** g_12, double** g_22, double*** dEs1,double*** dEs2,double*** dEv1,double*** dEv2, double Re);

void localtime(int nodes, double** U, double** V, double** g_11, double** g_22, double** J, double** dt,double Re, double CFL, double VN);

void residualsmoothing(int nodes, double** R_ca, double** R_cu, double** R_cv,double res);

//void tdma(int ibeg , int iend, double* aa, double* bb, double* cc, double* dd);
int main(int argc, char* argv[])
{
  double pi;
  pi= M_PI;

  const int nodes = 61;
  double r =1;

  double delta_t;
  delta_t = 0.001;
  double** x;
  double** y;
  double* dx;
  double* dy;
  double* errP = new double[6000000];
  double* errU = new double[6000000];
  double* errV = new double[6000000];

  double** eta;
  double** xita;
  double** G;
  double** J;
  double** xita_x;
  double** xita_y;
  double** eta_x;
  double** eta_y;
  double** x_xita;
  double** y_eta;
  double** x_eta;
  double** y_xita;
  double** uold;
  double** vold;
  double** pold;
  double** U;
  double** V;
  double** R_ca;
  double** R_cu;
  double** R_cv;
  double** g_11;
  double** g_12;
  double** g_22;

  double** dis_1;
  double** dis_2;
  double** dis_3;

  double** u1;
  double** v1;
  double** p1;

  double** u2;
  double** v2;
  double** p2;

  double** u3;
  double** v3;
  double** p3;

  double** unew;
  double** vnew;
  double** pnew;

  double** errp;
  double** erru;
  double** errv;
  double** dt;

  dx = new double;
  dy = new double;
  x = new double* [nodes];
  y = new double* [nodes];
  eta = new double* [nodes];
  xita = new double* [nodes];
  G = new double* [nodes];
  J = new double* [nodes];
  xita_x = new double* [nodes];
  xita_y = new double* [nodes];
  eta_x = new double* [nodes];
  eta_y = new double* [nodes];
  x_xita = new double* [nodes];
  y_eta = new double* [nodes];
  x_eta = new double* [nodes];
  y_xita = new double* [nodes];
  uold = new double* [nodes];
  vold = new double* [nodes];
  pold = new double* [nodes];

  u1 = new double* [nodes];
  v1 = new double* [nodes];
  p1 = new double* [nodes];

  u2 = new double* [nodes];
  v2 = new double* [nodes];
  p2 = new double* [nodes];

  u3 = new double* [nodes];
  v3 = new double* [nodes];
  p3 = new double* [nodes];

  unew = new double* [nodes];
  vnew = new double* [nodes];
  pnew = new double* [nodes];


  U = new double* [nodes];
  V = new double* [nodes];
  R_ca = new double* [nodes];
  R_cu = new double* [nodes];
  R_cv = new double* [nodes];
  g_11 = new double* [nodes];
  g_12 = new double* [nodes];
  g_22 = new double* [nodes];


  dis_1 = new double* [nodes];
  dis_2 = new double* [nodes];
  dis_3 = new double* [nodes];

  errp = new double* [nodes];
  erru = new double* [nodes];
  errv = new double* [nodes];
  dt = new double* [nodes];

  for (int i=0; i<nodes; i++)
    {
      x[i] = new double [nodes];
      y[i] = new double [nodes];
      eta[i] = new double [nodes];
      xita[i] = new double [nodes];
      G[i] = new double [nodes];
      J[i] = new double [nodes];
      xita_x[i] = new double [nodes];
      xita_y[i] = new double [nodes];
      eta_x[i] = new double [nodes];
      eta_y[i] = new double [nodes];
      x_xita[i] = new double [nodes];
      y_eta[i] = new double [nodes];
      x_eta[i] = new double [nodes];
      y_xita[i] = new double [nodes];
      uold[i] = new double [nodes];
      vold[i] = new double [nodes];
      pold[i] = new double [nodes];

      u1[i] = new double [nodes];
      v1[i] = new double [nodes];
      p1[i] = new double [nodes];


      u2[i] = new double [nodes];
      v2[i] = new double [nodes];
      p2[i] = new double [nodes];

      u3[i] = new double [nodes];
      v3[i] = new double [nodes];
      p3[i] = new double [nodes];

      unew[i] = new double [nodes];
      vnew[i] = new double [nodes];
      pnew[i] = new double [nodes];


      U[i] = new double [nodes];
      V[i] = new double [nodes];
      R_ca[i] = new double [nodes];
      R_cu[i] = new double [nodes];
      R_cv[i] = new double [nodes];
      g_11[i] = new double [nodes];
      g_12[i] = new double [nodes];
      g_22[i] = new double [nodes];

      dis_1[i] = new double [nodes];
      dis_2[i] = new double [nodes];
      dis_3[i] = new double [nodes];

      errp[i] = new double [nodes];
      erru[i] = new double [nodes];
      errv[i] = new double [nodes];

      dt[i] = new double [nodes];
    }

  double ***dEs1;
  double ***dEs2;
  double ***dEv1;
  double ***dEv2;

  // allocate memory
  dEs1 = new double** [3];  
  dEs2 = new double** [3];   
  dEv1 = new double** [3];   
  dEv2 = new double** [3];                 
  for(int i = 0; i < 3; i++){
    dEs1[i] = new double* [nodes];
    dEs2[i] = new double* [nodes];
    dEv1[i] = new double* [nodes];
    dEv2[i] = new double* [nodes];           
    for(int j = 0; j < nodes; j++){
      dEs1[i][j] = new double [nodes]; 
      dEs2[i][j] = new double [nodes];
      dEv1[i][j] = new double [nodes];
      dEv2[i][j] = new double [nodes];      
    }
  }

  gridgeneration(nodes, r, x , y, dx,dy);

  Getdata Data(400, 0.1, 0.01, 0.01, 0.01);

  double Reynold = Data.GetRe() ; 
  double residual = Data.Getres() ; 
  double CFLnum = Data.GetCFL() ; 
  double VNnum  = Data.GetVN() ; 
  double epi = Data.Getepisilon() ; 

  //double Re = Getdata::GetRe() ;
  /*
    std::cout << "The Reynolds Number = "<< Reynold << "\n";
    std::cout << "The Residual Smoothing Number = " << residual << "\n";
    std::cout << "The CFL Number = "<< CFLnum << "\n";
    std::cout << "The Von Neumann Number = " << VNnum << "\n";
    std::cout << "The dissipation smoothing Number = " << epi << "\n";
  */
  metrics(x, y,nodes, eta, xita, G, J,  xita_x,  xita_y,  eta_x,  eta_y,  x_xita,  y_eta,x_eta,y_xita);
 

  bcsuv(nodes,uold,vold,pold);


  int a=0;
  for(int t=0;t< 60000000;t++)
	
    {

      bcsuv(nodes,u1,v1,p1);
      curvilinearrhs(x, y, nodes,eta, xita, G, J, xita_x, xita_y, eta_x,  eta_y,  x_xita,  y_eta, x_eta, y_xita,  uold,  vold,  pold, R_ca, R_cu,  R_cv,  U,  V,  g_11,  g_12,  g_22,  dEs1,dEs2, dEv1,dEv2, Reynold);
      localtime( nodes, U, V,  g_11,  g_22, J, dt, Reynold, CFLnum,VNnum);
     // residualsmoothing(nodes,  R_ca,  R_cu, R_cv, residual);
      for(int i = 1; i < nodes-1; i++)
	{
	  for(int j = 1; j < nodes-1; j++){

	    p1[i][j] = pold[i][j] + double(1/4)*dt[i][j]*R_ca[i][j];
	    u1[i][j] = uold[i][j] + double(1/4)*dt[i][j]*R_cu[i][j];
	    v1[i][j] = vold[i][j] + double(1/4)*dt[i][j]*R_cv[i][j];
		
	  }
	}

      bcsp(nodes, p1,u1,v1);


      bcsuv(nodes,u2,v2,p2);
      curvilinearrhs(x, y, nodes,eta, xita, G, J, xita_x, xita_y, eta_x,  eta_y,  x_xita,  y_eta, x_eta, y_xita,  u1,  v1,  p1, R_ca, R_cu,  R_cv,  U,  V,  g_11,  g_12,  g_22,  dEs1,dEs2, dEv1,dEv2, Reynold);

      localtime( nodes, U, V,  g_11,  g_22, J, dt, Reynold, CFLnum,VNnum);
      //residualsmoothing(nodes,  R_ca,  R_cu, R_cv, residual);

      for(int i = 1; i < nodes-1; i++)
	{
	  for(int j = 1; j < nodes-1; j++){

	    p2[i][j] = pold[i][j] + double(1/3) * dt[i][j] * R_ca[i][j];
	    u2[i][j] = uold[i][j] + double(1/3) * dt[i][j] * R_cu[i][j];
	    v2[i][j] = vold[i][j] + double(1/3) * dt[i][j] * R_cv[i][j]; 
		
	  }
	}

      bcsp(nodes, p2,u2,v2);


      bcsuv(nodes,u3,v3,p3);
      curvilinearrhs(x, y, nodes,eta, xita, G, J, xita_x, xita_y, eta_x,  eta_y,  x_xita,  y_eta, x_eta, y_xita,  u2,  v2,  p2, R_ca, R_cu,  R_cv,  U,  V,  g_11,  g_12,  g_22,  dEs1,dEs2, dEv1,dEv2, Reynold);

      localtime( nodes, U, V,  g_11,  g_22, J, dt, Reynold, CFLnum,VNnum);
      //residualsmoothing(nodes,  R_ca,  R_cu, R_cv, residual);

      for(int i = 1; i < nodes-1; i++)
	{
	  for(int j = 1; j < nodes-1; j++){

	    p3[i][j] = pold[i][j] + double(1/2) * dt[i][j] * R_ca[i][j];
	    u3[i][j] = uold[i][j] + double(1/2) * dt[i][j] * R_cu[i][j];
	    v3[i][j] = vold[i][j] + double(1/2) * dt[i][j] * R_cv[i][j];
		
	  }
	}

      bcsp(nodes, p3,u3,v3);

      bcsuv(nodes,unew,vnew,pnew);
      curvilinearrhs(x, y, nodes,eta, xita, G, J, xita_x, xita_y, eta_x,  eta_y,  x_xita,  y_eta, x_eta, y_xita,  u3,  v3,  p3, R_ca, R_cu,  R_cv,  U,  V,  g_11,  g_12,  g_22,  dEs1,dEs2, dEv1,dEv2,Reynold);
      dissipation(nodes, u3, v3,  p3, U, V, g_11, g_22, J,dis_1,dis_2,dis_3,epi);
      localtime( nodes, U, V,  g_11,  g_22, J, dt, Reynold, CFLnum,VNnum);
     // residualsmoothing(nodes,  R_ca,  R_cu, R_cv, residual);

      for(int i = 1; i < nodes-1; i++)
	{
	  for(int j = 1; j < nodes-1; j++){

	    pnew[i][j] = pold[i][j] +  dt[i][j] * (R_ca[i][j] -J[i][j]*dis_1[i][j]);
	    unew[i][j] = uold[i][j] +  dt[i][j] * (R_cu[i][j] -J[i][j]*dis_2[i][j]);
	    vnew[i][j] = vold[i][j] +  dt[i][j] * (R_cv[i][j] -J[i][j]*dis_3[i][j]);
		
	  }
	}

      bcsp(nodes, pnew,unew,vnew);

      for(int i = 1; i < nodes-1; i++)
	{
	  for(int j = 1; j < nodes-1; j++){

	    errp[i][j] = pow(pnew[i][j] - pold[i][j],2);
	    erru[i][j] = pow(unew[i][j] - uold[i][j],2);
	    errv[i][j] = pow(vnew[i][j] - vold[i][j],2);
		
	  }
	}
      double sump=0.0;
      double sumu=0.0;
      double sumv=0.0;




      for(int i = 1; i < nodes-1; i++)
	{
	  for(int j = 1; j < nodes-1; j++){

	    sump +=  errp[i][j] ;
	    sumu += erru[i][j] ;
	    sumv += errv[i][j] ;
		
	  }
	}

      //std::cout << "Error in p = " << sump << "\n";
      //std::cout << "Error in v = " << sumu << "\n";
      //std::cout << "Error in u = " << sumv << "\n"; 

      errP[a] = sqrt(double(sump)/double(pow(nodes,2)));
      errU[a] = sqrt(double(sumu)/double(pow(nodes,2)));
      errV[a] = sqrt(double(sumv)/double(pow(nodes,2)));


      std::cout << "Error in p = " << errP[a] << "\n";
      std::cout << "Error in v = " << errU[a] << "\n";
      std::cout << "Error in u = " << errV[a] << "\n"; 

      if(errP[a] < 1.e-7)
	{
	  if(errU[a] < 1.e-7)
	    {
	      if(errV[a] < 1.e-7)
		{
		  std::cout << "the solution has converged" << "\n";
		  break;
		}			
	    }
	}

      for(int i = 0; i < nodes; i++)
	{
	  for(int j = 0; j < nodes; j++){

	    pold[i][j]=  pnew[i][j] ;
	    uold[i][j]=  unew[i][j] ;
	    vold[i][j]=  vnew[i][j] ;
		
	  }
	}

      a++;
    }

  
    std::ofstream writex("x.dat");
    // Write numbers as +x.<13digits>e+00 (width 20)
    writex.setf(std::ios::scientific);
    writex.precision(30);

    assert(writex.is_open());
    for (int i=0; i< nodes; i++)
    {
    for(int j=0; j< nodes; j++){
    writex << x[i][j] << " "; 
    }
    writex << "\n";
    }
    writex.close();

    std::ofstream writey("y.dat");
    // Write numbers as +x.<13digits>e+00 (width 20)
    writey.setf(std::ios::scientific);
    writey.precision(30);

    assert(writey.is_open());
    for (int i=0; i< nodes; i++)
    {
    for(int j=0; j< nodes; j++){
    writey << y[i][j] << " "; 
    }
    writey << "\n";
    }
    writey.close();





    std::ofstream write_file("u.dat");
    // Write numbers as +x.<13digits>e+00 (width 20)
    write_file.setf(std::ios::scientific);
    write_file.precision(30);

    assert(write_file.is_open());
    for (int i=0; i< nodes; i++)
    {
    for(int j=0; j< nodes; j++){
    write_file << unew[i][j] << " "; 
    }
    write_file << "\n";
    }
    write_file.close();


    std::ofstream write_v("v.dat");
    // Write numbers as +x.<13digits>e+00 (width 20)
    write_v.setf(std::ios::scientific);
    write_v.precision(30);

    assert(write_v.is_open());
    for (int i=0; i< nodes; i++)
    {
    for(int j=0; j< nodes; j++){
    write_v << vnew[i][j] << " "; 
    }
    write_v << "\n";
    }
    write_v.close();
  

  for (int i=0; i<nodes; i++)
    {


      delete[] x[i] ;
      delete[] y[i] ;
      delete[] eta[i];
      delete[] xita[i];
      delete[] G[i] ;
      delete[] J[i] ;
      delete[] xita_x[i];
      delete[] xita_y[i];
      delete[] eta_x[i];
      delete[] eta_y[i];
      delete[] x_xita[i];
      delete[] y_eta[i];
      delete[] x_eta[i];
      delete[] y_xita[i];
      delete[] uold[i];
      delete[] vold[i] ;
      delete[] pold[i];

      delete[] u1[i];
      delete[] v1[i];
      delete[] p1[i] ;


      delete[] u2[i];
      delete[] v2[i];
      delete[] p2[i];

      delete[] u3[i] ;
      delete[] v3[i] ;
      delete[] p3[i];

      delete[] unew[i];
      delete[] vnew[i] ;
      delete[] pnew[i] ;

      delete[] U[i] ;
      delete[] V[i];
      delete[] R_ca[i] ; 
      delete[] R_cu[i];
      delete[] R_cv[i];
      delete[] g_11[i];
      delete[] g_12[i];
      delete[] g_22[i];
 
      delete[] dis_1[i];
      delete[] dis_2[i];
      delete[] dis_3[i];

      delete[] errp[i];
      delete[] erru[i];
      delete[] errv[i];
      delete[] dt[i];
    }
  delete[] x ;
  delete[] y ;
  delete[] eta;
  delete[] xita;
  delete[] G ;
  delete[] J ;
  delete[] xita_x;
  delete[] xita_y;
  delete[] eta_x;
  delete[] eta_y;
  delete[] x_xita;
  delete[] y_eta;
  delete[] x_eta;
  delete[] y_xita;
  delete[] uold;
  delete[] vold ;
  delete[] pold;

  delete[] u1;
  delete[] v1;
  delete[] p1;


  delete[] u2;
  delete[] v2;
  delete[] p2;

  delete[] u3;
  delete[] v3;
  delete[] p3;

  delete[] unew;
  delete[] vnew;
  delete[] pnew;

  delete[] U ;
  delete[] V;
  delete[] R_ca; 
  delete[] R_cu;
  delete[] R_cv;
  delete[] g_11;
  delete[] g_12;
  delete[] g_22;
  delete[] dis_1;
  delete[] dis_2;
  delete[] dis_3;

  delete[] errp;
  delete[] erru;
  delete[] errv;
  delete[] dt;


  return 0;

}


