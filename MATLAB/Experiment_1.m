% VECTOR OPERATIONS

%Q1
disp("Q1");
v1=[1 2 3 4 10];
v2=[-1 -2 -3 -4 -10];
disp(v1);
disp(v2);

%Q2
disp("Q2");
v3=[v1 v2];
disp(v3);

%Q3
disp("Q3");
help ones;
help zeros;
v4=zeros(1,20);
v5=ones(1,20);
help size;
sz=size(v5);
len=length(v5);
fprintf("Size of v5 is %d\n",sz);
fprintf("Length of v5 is %d\n",len);


%Q4
disp("Q4");
v6=5*ones(1,20);
disp(v6);

%Q5
disp("Q5");
v7=v1+v2;
disp(v7);

%6
disp("Q6");
v7=v7+5;
disp(v7);

%7
disp("Q7");
v8=1:2:10;
fprintf("v8 is:");
disp(v8);

%8
disp("Q8");
fprintf("%d %d %d\n",v1(3),v1(5),v1(1));
v8=1:1:10;
v9=25:-5:-20;
disp(v8);
disp(v9);

%9
disp("Q9");
v10=v1;
v10(3)=[];
disp(v10);

%10
disp("Q10");
v11=v1(1:2:length(v1));
disp(v11);

%11
disp("Q11");
v1t=v1';
disp(v1t);

%12
disp("Q12");
vtt1=v1t*v1;
v1tt=v1*v1t;
disp(vtt1);
disp(v1tt);

%13
disp("Q13");
vq=v1.*v1;
disp(vq);
vmul=v1.^2;
disp(vmul);
vdiv=v1./v2;
disp(vdiv);

%14
disp("Q14");
s=sum(v1);
disp(s);

%15
disp("Q15");
avg=mean(v1);
disp(avg);

%16
disp("Q16");
k=v1==3;
disp(k);

%17
disp("Q17");
k=v1>=4;
disp(k);

%18
disp("Q18");
vprod=ones(length(v9),1)*v9;
disp(vprod);
vv=vprod+vprod';
vans=vv>=15;
disp(vans);

vgreater=(v9>=15).*v9;
ss=sum(vgreater);
disp(vgreater);
disp(ss);

%MATRIX OPERATIONS

%1
disp("Q1");
A = [1 2 3 4; 5 6 7 8; 9 10 11 12];
disp(A);

%2
disp("Q2");
disp(A(2,:));
disp(A(:,3));

%3
disp("Q3");
disp([A(:,1) A(:,3)]);

%4
disp("Q4");
help repmat;
B=repmat(A,[4,3]);
disp(B);

%5
disp("Q5");
help reshape;
A2=reshape(A,[2,6]);
disp(A2);

%6
disp("Q6");
C=zeros(3,4);
D=ones(3,4);
disp(C);
disp(D);

%7
disp("Q7");
help horzcat;
disp(horzcat(A,C));
disp(vertcat(A,D));

%8
disp("Q8");
help eye;
I=eye(4);
disp(I);

%9
disp("Q9");
dia=diag(B);
disp(dia);

%10
disp("Q10");
help tril;
help triu;
disp(tril(A));
disp(triu(A));

%11
disp("Q11");
disp(A);
disp(sum(A));
disp(sum(A'));
disp(sum(A(:)));

%12
disp("Q12");
E=ones(4);
disp(E);
disp(E*E);
disp(E.*E);

%RANDOM MATRICES GENERATION

%1
disp("Q1");
help rand;
R=rand([3,4]);
disp(R);

%2
disp("Q2");
R1=randi([5,10],[3,4]);
disp(R1);

%3
disp("Q3");
R2=randi([-5,5],4);
disp(R2);

%4
disp("Q4");
R3=randn(4);
disp(R3);

%5
disp("Q5");
help randn;
R4=10+2.*randn(4);
disp(R4);
avg=mean(R4(:));
disp(avg);

%6
disp("Q6");
R5=10+raylrnd(2,4);
disp(R5);
avg=mean(R5(:));
disp(avg);
R6=10+exprnd(2,4);
disp(R6);
avg=mean(R6(:));
disp(avg);

% SAVING AND LOADING

%1
disp("Q1");
varA='VARIABLE';
varB='vari_B';
save("savefile.m.mat",'varA');
save("savefile.m.mat",'varB');

%2
disp("Q2");
app=ones(5,5);
save("savefile.m.mat","app","-append");

%3
disp("Q3");
var=load("savefile.m.mat","app");
disp(var);

%4
disp("Q4");
name=["Alice" "Bob" "Chef"];
age=[16 17 18];
writematrix(name,"savexcel.xlsx");
writematrix(age,"savexcel.xlsx",'Writemode','append');

%5
disp("Q5");
final=readmatrix("savexcel.xlsx");
disp(final);
avrg=mean(final);
disp(avrg);

%6
disp("Q6");
song=randi([1,2],[1,1]);
disp(song);
filename='yes';
if(song==1)
    filename='DBS OP1.mp3';
else
    filename='DBS OP2.mp3';
end
[y,Fs] = audioread(filename);
sound(y,Fs);

%7
disp("Q7");
audiowrite("DBnew.mp3",y,Fs);
clear y Fs;

%8
disp("Q8");
F=imread("goku 00.jpg");

%9
disp("Q9");
image(F);

%10
disp("Q10");
G=F;
F(:,:,1)=0;
image(F);
inp=input("");
F=G;
F(:,:,2)=0;
image(F);
inp=input("");
F=G;
F(:,:,3)=0;
image(F);
inp=input("");
F=G;

% LOOPS AND FUNCTIONS

%1
disp("Q1");
K=randi([1,10],[100,100]);
sm=0;
for i=1:100
    for j=1:100
        sm=sm+K(i,j)*K(i,j);
    end
end
disp(sm);

%2
disp("Q2");
K2=K.*K;
sm2=sum(K2(:));
disp(sm2);

%3
disp("Q3");
tic
sm=0;
for i=1:100
    for j=1:100
        sm=sm+K(i,j)*K(i,j);
    end
end
toc
tic
K2=K.*K;
sm2=sum(K2(:));
toc
K=randi([1,10],[100,100]);
 
%4
disp("Q4");
cnt=0;
for i=1:100
    for j=1:100
        if K(i,j)<3 || K(i,j)>5
            cnt=cnt+1;
        end
    end
end
disp(cnt);

%5
disp("Q5");
K3=K>5;
K4=K<3;
cnt1=sum(K3(:))+sum(K4(:));
disp(cnt1);

%6
disp("Q6");
ranb=randi([20,40]);
rana=randi([10,20]);
disp(ranb);
disp(rana);
while rem(ranb,rana)~=0
    temp=rem(ranb,rana);
    ranb=rana;
    rana=temp;

end
disp(rana);
 
%7
disp("Q7");
numb=input("Enter a number between 1 to 4: ");
switch(numb)
    case 1
        disp("You entered number 1");
    case 2
        disp("You entered number 2");
    case 3
        disp("You entered number 3");
    case 4
        disp("You entered numbe4 4");
    otherwise
        disp("You entered a big number");
end

%8
disp("Q8");
n=input("Enter the number for your factorial: ");
fact=factorial(n);
disp(fact);
function fac=factorial(n)
    if(n==0) 
        fac=1;
    else
        fac=n*(factorial(n-1));
    end
end









