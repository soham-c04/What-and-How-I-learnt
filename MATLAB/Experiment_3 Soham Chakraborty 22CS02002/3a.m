% CONVOLUTION USING MATRIX METHOD (Trick Method)

x=input("Enter vector x: ");
h=input("Enter vector h: ");
N1=input("Enter the value of N1: ");
N2=input("Enter the value of N2: ");

h=h';
n=length(x);
m=length(h);
nfinal=max(N1,N2)+max(n-N1,m-N2);   
nx=zeros(1,nfinal);
j=1-max(N1,N2);
for i=1:nfinal
    nx(1,i)=j;
    j=j+1;
end

X=zeros(1,nfinal);
H=zeros(1,nfinal);
h=h';
j=1;
for i=max(N1,N2)-N1+1:max(N1,N2)-N1+n
    X(1,i)=x(1,j);
    j=j+1;
end
j=1;
for i=max(N1,N2)-N2+1:max(N1,N2)-N2+m
    H(1,i)=h(1,j);
    j=j+1;
end

stem(nx,X,'Color','r','LineWidth',3); hold ON;
stem(nx,H,'Color','b','LineWidth',2); hold OFF;

[v,N]=Convolution(x,h,N1,N2);

nf=zeros(1,n+m-1);
j=1;
for i=1-N:-N+n+m-1
    nf(1,j)=i;
    j=j+1;
end
stem(nf,v,'Color','g','LineWidth',2);



function [v,N]=Convolution(x,h,N1,N2)
h=h';
n=length(x);
m=length(h);
v=zeros(1,n+m-1);
A=h*x;
for i=1:n
    for j=1:m
        v(1,i+j-1)=v(1,i+j-1)+A(j,i);
    end
end
N=N1+N2-1;
end