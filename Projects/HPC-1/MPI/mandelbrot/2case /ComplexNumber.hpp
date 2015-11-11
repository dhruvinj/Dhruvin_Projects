#ifndef COMPLEXNUMBERHEADERDEF
#define COMPLEXNUMBERHEADERDEF

#include <iostream>


class ComplexNumber
{
private:
double mRealPart;
double mImaginaryPart;
public:
ComplexNumber()
{
mRealPart = 0.0;
mImaginaryPart = 0.0;
}

ComplexNumber(double x, double y)
{
mRealPart = x;
mImaginaryPart = y;
}

double CalculateModulus() const
{
return sqrt(mRealPart*mRealPart+
mImaginaryPart*mImaginaryPart);
}

double CalculateArgument() const
{
return atan2(mImaginaryPart, mRealPart);
}
ComplexNumber CalculatePower(double n) const
{
double modulus = CalculateModulus();
double argument = CalculateArgument();
double mod_of_result = pow(modulus, n);
double arg_of_result = argument*n;
double real_part = mod_of_result*cos(arg_of_result);
double imag_part = mod_of_result*sin(arg_of_result);
ComplexNumber z(real_part, imag_part);
return z;
}
ComplexNumber operator=(const ComplexNumber z)
{
mRealPart = z.mRealPart;
mImaginaryPart = z.mImaginaryPart;
return * this;
}

ComplexNumber operator+(const ComplexNumber& z) const
{
ComplexNumber w;
w.mRealPart = mRealPart + z.mRealPart;
w.mImaginaryPart = mImaginaryPart + z.mImaginaryPart;
return w;
}

};

#endif



















