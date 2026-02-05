% LTI SYSTEMS

%Q1)

%A)
n=-15:15;
subplot(221);
M=2;
h1a=hS1(M,n);
stem(n,h1a,'LineWidth',2);

subplot(222);
M=10;
h1b=hS1(M,n);
stem(n,h1b,'LineWidth',2);

%B)
subplot(223);
h2=n;
for i=1:length(n)
    h2(i)=delta(n(i))-delta(n(i)-1);
end
stem(n,h2,'LineWidth',2);

%C)
subplot(224);
n=0:20;
h3=n;
for i=1:length(n)
    h3(i)=4*sinc((n(i)-10)/20);
end
stem(n,h3,'LineWidth',2);
%input("");

%Q2)
help sin;
subplot(111);
t=0:0.001:0.2;
c=sin(2*pi*10*t)+sin(2*pi*100*t);

%Q3)
plot(t,c,'LineWidth',2);
%input("");

%Q5)
n=-15:15;
y1a=n*0;
M=2;
for i=1:length(n)
    for k=0:M-1
        y1a(i)=y1a(i)+C(n(i)-k)/M;
    end
end

y1b=n*0;
M=10;
for i=1:length(n)
    for k=0:M-1
        y1b(i)=y1b(i)+C(n(i)-k)/M;
    end
end
n=0:20;
for i=2:length(n)
    y2(i)=C(n(i))-C(n(i-1));
end

y3=conv(h3,c);

subplot(221);
plot(y1a);
subplot(222);
plot(y1b);
subplot(223);
plot(y2);
subplot(224);
plot(y3);
%input("");

%Q7)
% conv is used to calculate the convolution between the vectors h and c to
% get the output, which is later plotted.
y1a=conv(c,h1a,'valid');
y1b=conv(c,h1b,'valid');
y2=conv(c,h2,'valid');
y3=conv(c,h3,'valid');

subplot(221);
plot(y1a);
subplot(222);
plot(y1b);
subplot(223);
plot(y2);
subplot(224);
plot(y3);
%input("");
    
% PROPERTIES OF LTI SYSTEMS

%Q1)

f1=conv(c,conv(h1b,h2));
f2=conv(conv(c,h1b),h2);
f3=conv(conv(c,h2),h1b);
f4=conv(conv(h1b,c),h2);

subplot(221);
plot(f1);
subplot(222);
plot(f2);
subplot(223);
plot(f3);
subplot(224);
plot(f4);
%input("");

%Q2)
%{
Explanation:-
After potting all 4 of the resuslts we find that all of them are equal,
hence it can be concluded that convolution is associate as well as
commutative between 2 vectors.
%}

%Q3)
subplot(221);
f5=conv(c,h1a+h2);
plot(f5);
subplot(222);
f6=conv(c,h1a)+conv(c,h2);
plot(f6);

%Q4)
subplot(223);
f7=conv(c,h1b+h2);
plot(f7);
subplot(224);
f8=conv(c,h1b)+conv(c,h2);
plot(f8);
%input("");

%FUNCTIONS

function gc=C(t)
    gc=sin(2*pi*10*t)+sin(2*pi*100*t);
end

function h=hS1(M,n)
    h=n*0;
    for i=1:length(n)
        for k=0:M-1
            h(i)=h(i)+delta(n(i)-k);
        end
        h(i)=h(i)/M;
    end
end

function del=delta(k)
    del=k==0;
end

