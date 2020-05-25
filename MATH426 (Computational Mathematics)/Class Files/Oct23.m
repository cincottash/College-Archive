f = @(x) log(x)+ x.^2;
fp = @(x) 1./x + 2*x;

x = linspace(0.01,4,1000);
plot(x,f(x)); 
hold on;

r = fzero(f,1);
plot(r,f(r),'kx');

xn = [0.1];

for k = 1:4

    xn(end+1) = xn(end) - f(xn(end))/fp(xn(end));

end

plot(xn,f(xn),'ro');
grid on;

hold off;
hold off;
