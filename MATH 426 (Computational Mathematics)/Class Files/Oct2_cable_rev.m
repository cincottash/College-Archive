N = 5;
L = 100;
h = L/(N-1);

%Naive construction.

A = zeros(N,N);

A(1,1) = 1;
A(N,N) = 1;

for j = 2:N-1
    A(j,j) = -2;
    A(j,j-1) = 1;
    A(j,j+1) = 1;
end

%Proper vectorized way to create A.

A = diag(-2*ones(N,1))+diag(ones(N-1,1),1) + diag(ones(N-1,1),-1);

A(1,1) = 1;
A(1,2) = 0;
A(end,end) = 1;
A(end,end-1) = 0;

b = ones(N,1);
b(1) = 0;
b(end) = 0;

g = 9.8; 
T = 1000;

b = g*h^2/T*b;

q = A\b;

x = linspace(0,L,N);

plot(x,q,'-ro');

tic
lu(A);
toc

tic
lu(sparse(A));
toc
