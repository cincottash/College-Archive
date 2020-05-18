
roots = root_finder(1/5,1/5,-1);
roots

%roots = root_finder(1,1,-1);
%roots


function roots = root_finder(A,B,C)
   
    true_roots = [];
    roots_temp = [];
    roots = [];
    

    
    f = @(t) A*cos(2*pi*t) + B*sin(2*pi*t) + C*t;
    dfdt = @(t) (-2*A*pi)*sin(2*pi*t) + (2*B*pi)*cos(2*pi*t) + C;
    
    %The initial guesses begin at the minimum value and stop at the maximum
    %value of f
    initialGuessStart = -abs(A./C)-abs(B./C);
    initialGuessEnd = abs(A./C)+abs(B./C);
    
    %Calculating the roots using fzero to test my results against
    for k=initialGuessStart:.5:initialGuessEnd
        true_roots(end+1) = fzero(f, k);
    end
    
    %Rounding the roots
    for g=1:length(true_roots)
        true_roots(g) = round(true_roots(g), 3);
    end
    
    %Deleting duplicate roots
    true_roots = unique(true_roots);
    true_roots
    
    %Calculating roots via newtons method at various initial guesses
    %This is the same newton method code I used in my last HW(7)
    for k=initialGuessStart:.5:initialGuessEnd
        results = newton(f, dfdt, k);
        roots_temp(end+1) = round(results(end),3);
    end
    
    %Again rounding the roots
    roots_temp = unique(roots_temp);

    %Sometimes it detects small numbers such as -1 & 1 to be roots, I don't
    %think these are close enough to zero to be considered a root.  This
    %code deletes any root whose magnitude is greater than 1  Thus it is
    %guarenteed that every root will be sufficiently close to 0.
    for o=1:length(roots_temp)
        if abs(f(roots_temp(o))) < 1
            roots(end+1) = roots_temp(o);
        end
    end
    
end
    
function t = newton(f, dfdt, t1)
   
funtol = 50*eps; ttol = 50*eps; maxiter=8;
t = t1;
y = f(t1);
dt = Inf;
k =1;
while(abs(dt) > ttol)&&(abs(y) > funtol)&&(k < maxiter)
    dydt = dfdt(t(k));
    dt = -y/dydt;
    t(k+1) = t(k) + dt;
    k = k+1;
    y=f(t(k));
end
end