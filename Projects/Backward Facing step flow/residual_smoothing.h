#include<iostream>
#include<cmath>
#include<string>
#include<cassert>
#include<fstream>
#include<cstdlib>


void tdma(int ibeg , int iend, double* aa, double* bb, double* cc, double* dd);

void residual_smoothing(int nodes, double** R_ca, double** R_cu, double** R_cv,double res)
{

  double U_ca[nodes][nodes];
  double U_cu[nodes][nodes];
  double U_cv[nodes][nodes];


  double* aa = new double[nodes];
  double* bb = new double[nodes];
  double* cc = new double[nodes];
  double* dd = new double[nodes];

  for(int j = 0; j<nodes; j++)
    {
      
      aa[0] = 0;
      bb[0] = 1+2*res;
      cc[0] = -res;
      dd[0] = R_ca[0][j];
      for(int i = 1; i < nodes-1; i++)
	{
	  aa[i] = -res;
	  bb[i] = 1+2*res;
	  cc[i] = -res;
	  dd[i] = R_ca[i][j];
	}
      aa[nodes-1] = -res;
      bb[nodes-1] = 1+2*res;
      cc[nodes-1] = 0;
      dd[nodes-1] = R_ca[nodes-1][j];


      tdma(0,nodes-1, aa, bb, cc, dd);

      for(int i=0;i< nodes;i++)
	{
	  U_ca[i][j] = dd[i];
	}

    }



  for(int j = 0; j<nodes; j++)
    {
      
      aa[0] = 0;
      bb[0] = 1+2*res;
      cc[0] = -res;
      dd[0] = R_cu[0][j];
      for(int i = 1; i < nodes-1; i++)
	{
	  aa[i] = -res;
	  bb[i] = 1+2*res;
	  cc[i] = -res;
	  dd[i] = R_cu[i][j];
	}
      aa[nodes-1] = -res;
      bb[nodes-1] = 1+2*res;
      cc[nodes-1] = 0;
      dd[nodes-1] = R_cu[nodes-1][j];


      tdma(0,nodes-1, aa, bb, cc, dd);

      for(int i=0;i< nodes;i++)
	{
	  U_cu[i][j] = dd[i];
	}

    }



  for(int j = 0; j<nodes; j++)
    {
      
      aa[0] = 0;
      bb[0] = 1+2*res;
      cc[0] = -res;
      dd[0] = R_cv[0][j];
      for(int i = 1; i < nodes-1; i++)
	{
	  aa[i] = -res;
	  bb[i] = 1+2*res;
	  cc[i] = -res;
	  dd[i] = R_cv[i][j];
	}
      aa[nodes-1] = -res;
      bb[nodes-1] = 1+2*res;
      cc[nodes-1] = 0;
      dd[nodes-1] = R_cv[nodes-1][j];


      tdma(0,nodes-1, aa, bb, cc, dd);

      for(int i=0;i< nodes;i++)
	{
	  U_cv[i][j] = dd[i];
	}

    }



  for(int i = 0; i<nodes; i++)
    {

      aa[0] = 0;
      bb[0] = 1+2*res;
      cc[0] = -res;
      dd[0] = U_ca[i][0];
      for(int j = 1; j < nodes-1; j++)
	{
	  aa[j] = -res;
	  bb[j] = 1+2*res;
	  cc[j] = -res;
	  dd[j] = U_ca[i][j];
	}
      aa[nodes-1] = -res;
      bb[nodes-1] = 1+2*res;
      cc[nodes-1] = 0;
      dd[nodes-1] = U_ca[i][nodes-1];
	
     
      tdma(0,nodes-1, aa, bb, cc, dd);

      for(int j=0;j< nodes;j++)
	{
	  R_ca[i][j] = dd[j];
	}

    }




  for(int i = 0; i<nodes; i++)
       {

      aa[0] = 0;
      bb[0] = 1+2*res;
      cc[0] = -res;
      dd[0] = U_cu[i][0];
      for(int j = 1; j < nodes-1; j++)
	{
	  aa[j] = -res;
	  bb[j] = 1+2*res;
	  cc[j] = -res;
	  dd[j] = U_cu[i][j];
	}
      aa[nodes-1] = -res;
      bb[nodes-1] = 1+2*res;
      cc[nodes-1] = 0;
      dd[nodes-1] = U_cu[i][nodes-1];
	
     
      tdma(0,nodes-1, aa, bb, cc, dd);

      for(int j=0;j< nodes;j++)
	{
	  R_cu[i][j] = dd[j];
	}

    }



  for(int i = 0; i<nodes; i++)
      {

      aa[0] = 0;
      bb[0] = 1+2*res;
      cc[0] = -res;
      dd[0] = U_cv[i][0];
      for(int j = 1; j < nodes-1; j++)
	{
	  aa[j] = -res;
	  bb[j] = 1+2*res;
	  cc[j] = -res;
	  dd[j] = U_cv[i][j];
	}
      aa[nodes-1] = -res;
      bb[nodes-1] = 1+2*res;
      cc[nodes-1] = 0;
      dd[nodes-1] = U_cv[i][nodes-1];
	
     
      tdma(0,nodes-1, aa, bb, cc, dd);

      for(int j=0;j< nodes;j++)
	{
	  R_cv[i][j] = dd[j];
	}

    }

  delete[] aa;
  delete[] bb;
  delete[] cc;
  delete[] dd;

}




void tdma(int ibeg , int iend, double* aa, double* bb, double* cc, double* dd)
{
  double r;
  for (int i = ibeg+1; i< iend +1; i++)
    {

      r = aa[i]/bb[i-1];
      bb[i] = bb[i] - r*cc[i-1];
      dd[i] = dd[i]-r*dd[i-1];
    }

  dd[iend] = dd[iend]/bb[iend];

  //back substitution

  for(int i = iend -1; i > ibeg-1; i--)
    {

      dd[i] = (dd[i]-cc[i]*dd[i+1])/bb[i];

    }


}
