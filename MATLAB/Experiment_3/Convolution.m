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