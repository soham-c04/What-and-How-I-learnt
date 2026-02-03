% CONVOLUTION USING TRADITIONAL METHOD

x1=input("Enter vector x: ");
h1=input("Enter vector h: ");
N1=input("Enter the value of N1: ");
N2=input("Enter the value of N2: ");

sz=max(length(x1),length(h1));
T=-sz:sz;

x=T*0;
h=x;
origin=sz+1;
ox=origin+N1-1;
oh=origin+N2-1;

for i=1:length(x1)
    x(1,origin-N1+i)=x1(1,i);
end
for i=1:length(h1)
    h(1,origin-N2+i)=h1(1,i);
end
%disp(x);
%disp(T);

%stem(x,T,'linewidth',2);

convo=zeros(1,length(T));
for i=1:length(T)
    n=T(1,i)+origin;
    p=0;
    for k=1:n-1
        p=p+x(1,k)*h(1,n-k);
    end
    convo(1,i)=p;
end

stem(convo,T,'Color','g','LineWidth',2);


