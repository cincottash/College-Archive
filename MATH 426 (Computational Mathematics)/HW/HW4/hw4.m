
%%
%2.6.3.b n=4
clc;
clear all;
n=4;
a=0;
b=1;
h=(b-a)/n;
x=0:h:1;
tau=10;
g=-9.8;

A(1,1)=2*n*tau;
A(1,2)=-n*tau;
for i=2:n-2
    A(i,i-1)=-n*tau;
    A(i,i)=2*n*tau;
    A(i,i+1)=-n*tau;
end
A(n-1,n-2)=-n*tau;
A(n-1,n-1)=2*n*tau;

for i=1:n-1
    f(i)=(1/(10*n))*g;
end

q1=(A)\f';

q(1)=0;
for i=1:n-1
    q(i+1)=q1(i);
end
q(n+1)=0;
q'
plot(x,q,'linewidth',2)
xlabel('x')
ylabel('q')

%%
%2.6.3.b n=40
clc;
clear all;
n=40;
a=0;
b=1;
h=(b-a)/n;
x=0:h:1;
tau=10;
g=-9.8;

A(1,1)=2*n*tau;
A(1,2)=-n*tau;
for i=2:n-2
A(i,i-1)=-n*tau;
A(i,i)=2*n*tau;
A(i,i+1)=-n*tau;
end
A(n-1,n-2)=-n*tau;
A(n-1,n-1)=2*n*tau;

for i=1:n-1
f(i)=(1/(10*n))*g;
end

q1=(A)\f';

q(1)=0;
for i=1:n-1
q(i+1)=q1(i);
end
q(n+1)=0;
q'
plot(x,q,'linewidth',2)
xlabel('x')
ylabel('q')

%%
%2.6.3.c n=4
clc;
clear all;
n=4;
a=0;
b=1;
h=(b-a)/n;
x=0:h:1;
tau=10;
g=-9.8;

A(1,1)=2*n*tau;
A(1,2)=-n*tau;
for i=2:n-2
A(i,i-1)=-n*tau;
A(i,i)=2*n*tau;
A(i,i+1)=-n*tau;
end
A(n-1,n-2)=-n*tau;
A(n-1,n-1)=2*n*tau;

for i=1:n-1
f(i)=(i/(5*n^2))*g;
end

q1=(A)\f';

q(1)=0;
for i=1:n-1
q(i+1)=q1(i);
end
q(n+1)=0;
q'
plot(x,q,'linewidth',2)
xlabel('x')
ylabel('q')


%%
%2.6.3.c n=40
clc;
clear all;
n=40;
a=0;
b=1;
h=(b-a)/n;
x=0:h:1;
tau=10;
g=-9.8;

A(1,1)=2*n*tau;
A(1,2)=-n*tau;
for i=2:n-2
A(i,i-1)=-n*tau;
A(i,i)=2*n*tau;
A(i,i+1)=-n*tau;
end
A(n-1,n-2)=-n*tau;
A(n-1,n-1)=2*n*tau;

for i=1:n-1
f(i)=(i/(5*n^2))*g;
end

q1=(A)\f';

q(1)=0;
for i=1:n-1
q(i+1)=q1(i);
end
q(n+1)=0;
q'
plot(x,q,'linewidth',2)
xlabel('x')
ylabel('q')

%%
%2.8.1
clear all
clc

for n=2:16
    fprintf('n=%d, condition number is %.4e and norm is %f\n',n,cond(hilb(n)), norm(hilb(n),2))
end
