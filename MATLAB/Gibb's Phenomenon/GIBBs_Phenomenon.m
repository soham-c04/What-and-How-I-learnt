% GIBB'S PHENOMENON

% CONVOLUTION IN TIME DOMAIN
% Window-1
c=3;
[Range1,Final1]=Gibbs_Phenomenon_TIME(c);
subplot(231);
plot(Range1,Final1,'linewidth',2);
title('Window size = 3');

% Window-2
c=5;
[Range2,Final2]=Gibbs_Phenomenon_TIME(c);
subplot(232);
plot(Range2,Final2,'linewidth',2);
title('Window size = 5');

% Window-3
c=10;
[Range3,Final3]=Gibbs_Phenomenon_TIME(c);
subplot(233);
plot(Range3,Final3,'linewidth',2);
title('Window size = 10');

% Window-4
c=20;
[Range4,Final4]=Gibbs_Phenomenon_TIME(c);
subplot(234);
plot(Range4,Final4,'linewidth',2);
title('Window size = 20');

% Window-5
c=30;
[Range5,Final5]=Gibbs_Phenomenon_TIME(c);
subplot(235);
plot(Range5,Final5,'linewidth',2);
title('Window size = 30');

% Window-6
c=50;
[Range6,Final6]=Gibbs_Phenomenon_TIME(c);
subplot(236);
plot(Range6,Final6,'linewidth',2);
title('Window size = 50');

% MULTIPLY IN FREQUENCY DOMAIN MULTIPLICATION AND THEN INVERSE TO TIME
% DOMAIN

% Window-1
c=3;
[Range1,Final1]=Gibbs_Phenomenon(c);
subplot(231);
plot(Range1,Final1,'linewidth',2);
title('Window size = 3');

% Window-2
c=5;
[Range2,Final2]=Gibbs_Phenomenon(c);
subplot(232);
plot(Range2,Final2,'linewidth',2);
title('Window size = 5');

% Window-3
c=10;
[Range3,Final3]=Gibbs_Phenomenon(c);
subplot(233);
plot(Range3,Final3,'linewidth',2);
title('Window size = 10');

% Window-4
c=20;
[Range4,Final4]=Gibbs_Phenomenon(c);
subplot(234);
plot(Range4,Final4,'linewidth',2);
title('Window size = 20');

% Window-5
c=30;
[Range5,Final5]=Gibbs_Phenomenon(c);
subplot(235);
plot(Range5,Final5,'linewidth',2);
title('Window size = 30');

% Window-6
c=50;
[Range6,Final6]=Gibbs_Phenomenon(c);
subplot(236);
plot(Range6,Final6,'linewidth',2);
title('Window size = 50');
    
%{
In accordance with Gibb's Phenomenon we observe that as we increase the
value of c, i.e. the window size the final output tends to become more of a
square wave with a maximum overshoot of about 9%.
%}

%{
Certain breaks are observed in the output graphs, this is as a result of
taking lower intervals in Range, but since MATLAB takes a lot of time due
to it being too slow in calculations, intervals of 0.1 are taken, break
size decreases significantly on taking interval of 0.01, but it is not
possible to generate their graph for higher window length of about 50
because of large computational time required.
%}

function [Range,Final]=Gibbs_Phenomenon(c)
    syms w;
    sympref('HeavisideAtOrigin',1);
    filter=heaviside(w+c)-heaviside(w-c);
    Filter=fourier(filter);
    Range=-5*c:0.1:5*c;
    Range(5*c/0.1+1)=0.1;
    syms v;
    FW=heaviside(v+c)-heaviside(v-c);
    cut=FW*Filter;
    syms t;
    final=Inverse_DTFT(cut,t,v);
    Final=subs(final,Range);
end

function [Range,Final]=Gibbs_Phenomenon_TIME(c)
    syms t;
    sympref('HeavisideAtOrigin',1);
    rectangular_pulse = heaviside(t+c)-heaviside(t-c);
    sinc_wave = fourier(rectangular_pulse);
    Range = -5*c:0.1:5*c;
    Range(5*c/0.1+1)=0.1;
    rectangular_pulse_sub = subs(rectangular_pulse,Range);
    rectangle= find(impulse_pulse);
    sinc_wave_sub = subs(sinc_wave,Range);
    Final_one=convo(rectangular_pulse_sub,sinc_wave_sub);
    Final=Range;
    len=length(Range);
    ini=len-1-(len-1)/2+1;
    for i=ini:ini+len-1
        Final(i-ini+1)=Final_one(i);
    end
end

function v=convo(x,h)
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
end
    
function x=Inverse_DTFT(X,n,w)
    X1=X*exp((1i)*w*n);
    x=int(X1,0,2*pi)/(2*pi);  
end



