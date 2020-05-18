%%
M = csvread('BicycleDataset.csv ');
fcn = @(b,x) b(1).*x./(b(2)+x);
x = M(1:113, 2);
y = M(1:113, 1);


hold on
scatter(x, y, 'filled')
title('Speed vs Temperature')
xlabel('Temperature')
ylabel('Speed')



%Construct the normal matrix to fit a line to the data.  
%Create a plot of the data and your fit on the same graph.  
A = [ones(size(x)) x]; 
yfit = A*((A'*A)\(A'*y));
plot(x,yfit)

%%
%Construct the normal matrix to fit a parabola to the data
B0 = [50; 50];
B = fminsearch(@(b) norm(y - fcn(b,x)), B0);
s = fcn(B,x);
figure

plot(x, y, 'pg')
title('Speed vs Temperature')
xlabel('Temperature')
ylabel('Speed')


hold on
plot(x,s,'k')
