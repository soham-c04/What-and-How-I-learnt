syms t a;
x=exp(-a*t)*heaviside(t);
X=fourier(x,t);
disp(X);