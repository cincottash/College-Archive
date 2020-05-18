%~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
%%

%4.1.1
syms x

fplot(exp(-x), [-2,2]);hold on
fplot(x^2, [-2,2]);hold off

y1 = @(x) exp(-x)-x^2;
fzero(y1, 0.7);



%~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
%%
%4.1.2

syms x
fplot(2*x, [-0.2,1.4]);hold on
fplot(tan(x), [-0.2,1.4]);hold off

y2 = @(x) 2*x-tan(x);
fzero(y2,0);
fzero(y2,1.15);

%~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
%%
%4.1.4
n=300;

table_func = @(P,r) (12.*P./r)*((1+r./12).^n-1); 

fprintf('Deposit (P) \t rate(r)\n')

for p=500:50:1000
fun = @(r) (table_func(p,r)-1000000); 
%find the 0 of the function with an initial guess of 0.1
x = fzero(fun,0.1);

fprintf('\t %d \t \t %f \n',p,x)

end

%~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
%%

%4.1.5
%x = linspace(0,1.761);
syms t
for t=0:0.01761:1.761
    
    fun = @(y) y-0.223*sin(y)-2*pi*t./1.761;
    y=fzero(fun,0);
    %my theta should be continous instead of jumping around like this
    theta=2*atan(sqrt(1.223/0.777)*tan(y./2));
    plot(t, theta, '.');hold on
  
end

