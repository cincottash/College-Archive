%4.2.4
clear;
clc;

g=@(x) x.^2 -4*x + 3.5;

x1 = 1;
x2 = g(x1);

iterations = 0;

ezplot(g,[-10,10]);
hold on 
ezplot('x',[[-10,10]])
hold off
while (abs(x2-x1) > 1e-5 && iterations<100)
    plot([x1 x1], [x1 x2], 'k-')
    plot([x1 x2], [x2 x2], 'k--')
    iterations = iterations + 1;
    x1 = x2;
    x2 = g(x1);
end
iterations 
[x1 x2] 




