f = @ (x) x.*(x-1).*(x+1) + 0.01*cos(15*x);

x = linspace(-2,2,1000);

n = 20;
xn = linspace(-1.5,1.5,n+1);

c = polyfit(xn,f(xn),n); %Find the coefficients.
p = @(x) polyval(c,x);   %Use the coefficients.

plot(x,f(x));
hold on;
plot(xn,f(xn),'ro');
plot(x,p(x),'g');
hold off;

%% Piecewise linear.

plot(x,f(x),'b');
hold on;
plot(xn,f(xn),'ro-');
hold off;