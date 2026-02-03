n=input("Number of rows or columns: ");
fprintf("\n");
A=zeros(n,n);
adjA=zeros(n,n);
invA=zeros(n,n);
for i=1:n
    for j=1:n
       fprintf('Enter the elements (%d,%d): ',i,j);
       A(i,j)=input("");
    end
end
determinant=dett(A,n);
%
fprintf('Determinant is %d\n',determinant);
for i=1:n
    for j=1:n
        B=zeros(n-1,n-1);
        for y=1:i-1
            for x=1:j-1
                B(x,y)=A(x,y);
            end
        end
        for y=i+1:n
            for x=1:j-1
                B(x,y-1)=A(x,y);
            end
        end
        for y=1:i-1
            for x=j+1:n
                B(x-1,y)=A(x,y);
            end
        end
        for y=i+1:n
            for x=j+1:n
                B(x-1,y-1)=A(x,y);
            end
        end
        %disp("B");
        %disp(B);
        c=0;
        if rem(i+j,2)==0
            c=1;
        else
            c=-1;
        end
        adjA(i,j)=c*dett(B,n-1);
    end
end
invA=adjA/determinant;
disp("Adjoint of the matrix is: -");
disp(adjA);
disp("Inverse of the matrix is: -");
disp(invA);
%
function det=dett(A,s)
    if s==2
        det=A(1,1)*A(2,2)-A(1,2)*A(2,1);
    else
        val=0;
        B=zeros(s-1,s-1);
        for i=1:s
            for j=2:s
                for k=1:i-1
                    B(j-1,k)=A(j,k);
                end
                for k=i+1:s
                    B(j-1,k-1)=A(j,k);
                end
            end
            % disp("B");
            % disp(B);
            if rem(i,2)==0 
                val=val-A(1,i)*dett(B,s-1);
            else
                val=val+A(1,i)*dett(B,s-1);
            end
        end
        det=val;
    end
end

