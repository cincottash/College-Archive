f = @(x1,x2) [x1.^2 + x2.^2/pi-1 ; (x1-1/2).^2 - x2];

J = @(x1,x2) [2.*x1 2*x2./pi ; 2*(x1-1/2) -1];

xn = [1;1/2];

for k = 1:5
    A = J(xn(1,end),xn(2,end));
    
    h = -A\f(xn(1,end),xn(2,end));
    xn(:,end+1) = xn(:,end) + h;
    
    disp(norm(f(xn(1,end),xn(2,end))));
end