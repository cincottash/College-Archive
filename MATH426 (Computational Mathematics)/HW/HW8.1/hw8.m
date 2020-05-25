%% 5.6.1a
f = @(x) x.*log(1+x);
a = 0;
b =  1;
error = zeros(1,10);
results = zeros(1,10);
for k=1:10
    T = trapezoid(f,a,b,10.*2^k);
    results(k) = T;
    error(k) = results(k) - integral(f,a,b);
end
loglog(error);



%% 5.6.1b
f = @(x) x.^2.*atan(x);
a = 0;
b =  1;
error = zeros(1,10);
results = zeros(1,10);
for k=1:10
    T = trapezoid(f,a,b,10.*2^k);
    results(k) = T;
    error(k) = results(k) - integral(f,a,b);
end
loglog(error);


%% 5.6.1c
f = @(x) exp(x).*cos(x);
a = 0;
b =  pi/2;
error = zeros(1,10);
results = zeros(1,10);
for k=1:10
    T = trapezoid(f,a,b,10.*2^k);
    results(k) = T;
    error(k) = results(k) - integral(f,a,b);
end

loglog(error);



%% 5.6.1d
f = @(x) sqrt(x).*log(x);
a = eps(0);
b =  1;
error = zeros(1,10);
results = zeros(1,10);
for k=1:10
    T = trapezoid(f,a,b,10.*2^k);
    results(k) = T;
    error(k) = results(k) - integral(f,a,b);
end
loglog(error);




%% 5.6.1e
f = @(x) sqrt(1-x.^2);
a = 0;
b =  1;
error = zeros(1,10);
results = zeros(1,10);
for k=1:10
    T = trapezoid(f,a,b,10.*2^k);
    results(k) = T;
    error(k) = results(k) - integral(f,a,b);
end
loglog(error);



%% 6.1.5
k=1;
s=1;
m=0.25;
tspan=[0 10];
x0=[0.9*m 1.1*m 1.5*m 0.9*s 1.1*s 3*s];
for i=1:6
    [t,x] = ode45(@(t,x) k*(s-x)*(x-m),tspan,x0(i));
    hold on
    plot(t,x,'linewidth', 2)
    lgnd{i}=sprintf('for x0=%2.4f', x0(i));
end
ylim([0 3.5]);
legend(lgnd, 'location','best')
xlabel('time')
ylabel('x(t)')
title('plotting of x(t) vs time')
box on
grid on



%% 6.1.8
tspan1=[0 12];
tspan2=[13 25];
v0=0;
g=9.8;
k1=0.4875;
k2=29.16;
m=62;
[t1,v1] = ode45(@(t1,v) -g+(k1/m).*v.^2,tspan1,v0);
%t1
%v1
hold off
plot(t1,v1)

[t2,v2] = ode45(@(t1,v) -g+(k2/m).*v.^2,tspan2,v1(end));
%t
%v2
%t1
t=cat(1,t1,t2);
v=cat(1,v1,v2);

plot(t,v)
xlabel('time')
ylabel('v(t)')
title('plotting of v(t) vs time')
box on
grid on

t2=size(t);
fallDistance=1200;
groundTime=0;
distanceFallen=0;
for i=1:1:170-1
    h=(size(t(1:i)-size(t(i+1))));
    distanceFallen =((h(1)/3)*(4*(v(1) + v(i) + v(i+1))));
    if( fallDistance+((h(1)/3)*(4*(v(1) + v(i) + v(i+1))))< 0)
        groundTime=t(i);
        
        break
    end
end
hold off




%% 6.2.2.a
dudt=@(t,u)(-2*u*t);%define du/dt
u0=2;%initial condition
tspan=[0 2];%endpoint for t interval
n=320;%number of grid points
[t,u]=eulerivp(dudt,tspan,u0,n);
figure(1)
plot(t,u);%plot
xlabel('t');
ylabel('u');

k=2:10;
n=10.*2.^k;
uexact=@(t)(2*exp(-t.^2));
err=zeros(1,length(k));
figure(2)
for i=2:10
    [t,u]=eulerivp(dudt,tspan,u0,n(i-1));
    err(i-1)=abs(u(end)-uexact(2));
end
hold off
loglog(n, err);
hold on
loglog(n, 0.05*(n/n(1)).^(-1), '--');
xlabel('n');
ylabel('error');



%% 6.2.2.b

%THIS IS BROKE

dudt=@(t,u)((t.^2)/(u*(1+t.^3)) );%define du/dt
u0=1;%initial condition
tspan=[0 3/x];%endpoint for t interval
n=320;%number of grid points
[t,u]=eulerivp(dudt,tspan,u0,n);
figure(1)
plot(t,u);%plot
xlabel('t');
ylabel('u');

k=2:10;
n=10.*2.^k;
uexact=@(t, x)((1 + (2/3) * ln(1+x*t.^3) ).^(1/2));
err=zeros(1,length(k));
figure(2)
for i=2:10
    [t,u]=eulerivp(dudt,tspan,u0,n(i-1));
    err(i-1)=abs(u(end)-uexact(2));
end
hold off
loglog(n, err);
hold on
loglog(n, 0.05*(n/n(1)).^(-1), '--');
xlabel('n');
ylabel('error');


%% 6.3.3.a
% number of nodes
n=100;
tspan=[0 2*pi];
u0=[1; 1] ;% initial condition
dudt=@(t,u)[u(2,:); (4*t)-4*(u(1,:))]; % function
% exact solution
y=@(t)(t+cos(2*t));
% function calling
[t,u]=eulersys(dudt,tspan,u0,n);
u = u.';
% Error
err=abs(y(t)-u(1,:)');
yt = u(1,:);
y_t = u(2,:);
% plots y(t) and y'(t)
hold off
figure(1)
plot(t,yt,t, y_t)
legend('y','y^{\prime}')
xlabel('t')
ylabel('y and y^{\prime}')
%plot for the error in each as function of time
figure(2)
plot(t,err)
xlabel('t')
ylabel('Error')



%% 6.3.3.b
% number of nodes
n=100;
tspan=[0 2*pi];
u0=[2; 1] ;% initial condition
dudt=@(t,u)[u(2,:); sin(2*t)-9*(u(1,:))]; % function
% exact solution
y=@(t)((1/5)*sin(3*t))+(2*cos(3*t))+((1/5)*sin(2*t));
% function calling
[t,u]=eulersys(dudt,tspan,u0,n);
u = u.';
% Error
err=abs(y(t)-u(1,:)');
yt = u(1,:);
y_t = u(2,:);
% plots y(t) and y'(t)
hold off
figure(1)
plot(t,yt,t, y_t)
legend('y','y^{\prime}')
xlabel('t')
ylabel('y and y^{\prime}')
%plot for the error in each as function of time
figure(2)
plot(t,err)
xlabel('t')
ylabel('Error')




%%
function [T, t, y] = trapezoid(f, a, b, n)
h = (b-a)/n;
t = a + h*(0:n)';
y = f(t);
T = h * (sum(y(2:n)) + 0.5*(y(1) +y(n+1)));
end

%%
function [t,u] = eulerivp(dudt, tspan, u0, n)
a = tspan(1); b=tspan(2);
h= (b-a)/n;
t = a + (0:n)'*h;
u=zeros(n+1, 1);
u(1) = u0;
for i=1:n
    u(i+1) = u(i) + h*dudt(t(i), u(i));
end
end
%%
function [t,u] = eulersys(dudt, tspan, u0, n)
a=tspan(1);
b=tspan(2);
h=(b-a)/n;
t=a+(0:n)'*h;
m=length(u0);
u=zeros(m,n+1);
u(:,1)=u0(:);

for i=1:n
    u(:,i+1) = u(:,i) + h*dudt(t(i), u(:,i));
end
u=u';
end