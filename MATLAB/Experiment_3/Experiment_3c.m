dt=0.001;
t=-5:dt:5;
x= X(t);
h= H(t);

subplot(221);
plot(t,x,'Linewidth',3,'color','r');

subplot(222);
plot(t,h,'linewidth',3,'color','b');

subplot(223);
%disp(ans);
T=t;
ans=T;
for i=1:length(T)
    h2=H(T(1,i)-t);
    
    dot=x.*h2;
    sm=sum(dot);
    ans(1,i)=sm*dt;
end
plot(T,ans,'linewidth',3,'color','g');

function v=H(t)
    v=(t)<=1 & (t)>=0;

end

function v=X(t)
    v= t<=2 & t>=0;
end