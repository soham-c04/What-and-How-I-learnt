% SYMBOLIC EXPRESSIONS AND NUMERICAL INTEGRATION IN MATLAB

%1)
help syms;

%2)
syms t;
func=sin(2*pi*t);

%3)
%{
Two variables are are stored in workspace with the name
func:- with value 1*1 sym
and 
t:- with 1*1 sym
%}

%4)
help subs;

%5)
t=-1:0.01:1;
y=subs(func,t);
disp(y);

%6)
help int;
h1=int(func);
h2=int(func*func);
y1=subs(h1,1)-subs(h1,0);
y2=subs(h2,1)-subs(h2,0);
disp(y1);
disp(y2);

%FOURIER SERIES ANALYSIS
%1)
syms t;
w0=100*pi;
T0=2*pi/w0;
K=-5:5;

%2)
x1=cos(w0*t);
[Ak1,w1]=FourierAnalysis(x1,T0,K);

x2=sin(w0*t);
[Ak2,w2]=FourierAnalysis(x2,T0,K);

disp(Ak1);
disp(Ak2);

%3)
syms t;
t=-5:0.01:5;
xs=(abs(mod(t,1))<=0.25)+(mod(t,1)~=0).*(abs(mod(-t,1))<=0.25);
y=subs(xs);
plot(t,y);

%4)
syms t;
T0=1;
K=-10:10;
Xs=1;   
[Ak,W]=FourierAnalysis2(Xs,T0,K);
disp(Ak);
disp(W);
%All the Ak's are real.

%5)
stem(W,abs(Ak));

%6)
%{
The output is verified to be correct, but only after some neccesary changes
to the FourierAnalysis() function because otherwise, since the function is
define as a piecewise function it can't be integrated using the int()
function. Hence FourierAnalysis2() is designed.
%}

%FOURIER SERIES SYNTHESIS EQUATION AND GIBB'S PHENOMENON

%1)
t1=-2:0.01:2;
subplot(231);
plot(t1,X(1));
subplot(232);
plot(t1,X(5));
subplot(233);
plot(t1,X(10));
subplot(234);
plot(t1,X(25));
subplot(235);
plot(t1,X(50));
subplot(111);

%2)
%{
Observation:-
a) From the plot we observe that the maximum overshoot is:-

                max(xN(t))              Percentage Overshoot
N=1             1.13662                 13.662%
N=5             1.09332                 9.332%
N=10            1.09116                 9.116%
N=25            1.08996                 8.996%
N=50            1.08956                 8.956%

b) For each value of N we observe that the amplitude of intersection 
   point is 0.5.

c) For each value of N we observe that the time difference is 0.8.
%}

%3)
%{
N=1 and N=5 are not in conformity with Gibb's phenomenon as they are 
highly deviated from a square wave. N=10 is somewhat in conformity as it
tends to be a square wave.N=25 and N=50 almost satisfies Gibb's 
phenomenon as they are almost fully square waves.
%}



%FUNCTION FourierAnalysis()

function [Ak,w]=FourierAnalysis(x,T0,K)
    Ak=K;
    w=K;
    syms t;
    for i=1:length(K)
        k=K(i);
        w0=k*2*pi/T0;
        w(i)=w0;
        func=int(x*exp(-(1i)*w0*t))/T0;
        Ak(i)=subs(func,T0)-subs(func,0);
    end
end

function [Ak,w]=FourierAnalysis2(x,T0,K)
    Ak=K;
    w=K;
    syms t;
    for i=1:length(K)
        k=K(i);
        w0=k*2*pi/T0;
        w(i)=w0;
        func=int(x*exp(-(1i)*w0*t))/T0;
        Ak(i)=subs(func,T0/4)-subs(func,-T0/4);
    end
end

function x=X(N)
    syms t;
    xs=1;
    K=-N:N;
    [Ak,W]=FourierAnalysis2(xs,1,K);
    t1=-2:0.01:2;
    x=t1*0;
    for y=1:length(K)
        ak=Ak(y);
        w=W(y);
        x=x+ak*exp((1i)*w*t1);
    end
end