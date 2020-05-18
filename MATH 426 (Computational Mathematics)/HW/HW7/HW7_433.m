%4.3.3
%b there is one root in the intervval
f = @(x) exp(x+1)-x-2;
dfdx = @(x) exp(x+1)-1;
fplot(f, [-2 2]);
%c
true_root = fzero(f, -1);
true_root
%d
results = newton(f, dfdx, 1);
root = results(end);
root
%e
xn = [-1];
e = [xn(1) - true_root];
for k =1:4
   xn(end+1) = xn(end) - f(xn(end))/dfdx(xn(end));
   e(end+1) = xn(end) - true_root;
end
e
function x = newton(f, dfdx, x1)
funtol = 100*eps; xtol = 100*eps; maxiter=40;
x = x1;
y = f(x1);
dx = Inf;
k =1;
while(abs(dx) > xtol)&&(abs(y) > funtol)&&(k < maxiter)
    dydx = dfdx(x(k));
    dx = -y/dydx;
    x(k+1) = x(k) + dx;
    k = k+1;
    y=f(x(k));
end
end


