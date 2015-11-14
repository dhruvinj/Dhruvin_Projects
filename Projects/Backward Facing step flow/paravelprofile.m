clear all;close all; clc;

y= 0:0.00001:1;



myu = zeros(1,length(y));
value =300;
peak_T = 2000;
T0 = 300;
T1 = 1400;

W_O2_0 = 0.47;
W_O2_1 = 1.0;

W_O3_0 = 0.53;
W_O3_1 = 0.0;

U_0 = 3.65476;
U_1 = 23;
h = length(y)/2 +0.5 ;
for i=1:length(y)
    if y(i) < 0.5
        myu(i) = 0.0;
    else
   myu(i) =(1/0.06)*(y(i)-0.5)*(1-(y(i)));
    end
   
end
figure;plot(myu,y);