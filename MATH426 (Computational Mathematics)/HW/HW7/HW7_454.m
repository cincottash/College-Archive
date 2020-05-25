x1 = @(t) -5+10*cos(t);
y1 = @(t) 6*sin(t);
clf, fplot(x1,y1,[0 2*pi])
x2 = @(t) 8*cos(t);
y2 = @(t) 1+12*sin(t);
hold on, fplot(x2,y2, [0 2*pi])
f = zeros(2,1);



function x = newtonsys(f, x1)
funtol = 100*eps; xtol=100*eps; maxiter=40;
x = x1(:);
[y, J] = f(x1);
dx = Inf;
k = 1;

while(norm(dx) > xtol) && (norm(y) > funtol) && (k < maxiter)
    dx = -(J\y);
    x(:,k+1) = x(:,k) + dx;
    k = k+1;
    [y,J] = f(x(:,k));
end
end

