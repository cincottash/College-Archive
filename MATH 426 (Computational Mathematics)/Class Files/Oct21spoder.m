f = @(x) cos(4*x)-1/2;

g = @(x) x-f(x);

s = linspace(-pi,pi,1000);
plot(s,g(s)); 
hold on;
plot(s,s);

x = 0.1;

for k = 1:10

    y = g(x);

    plot([x x],[x y],'ro-');
    plot([x y],[y y],'bo-');

    x = y;
end

hold off;
