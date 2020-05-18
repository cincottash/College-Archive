data = csvread('McGuireAFB.csv',1,0);
dates = data(:,1);

formatteddates = datetime(string(dates),'InputFormat','yyyyMMdd');

%DaysSinceDay0
x = days(formatteddates-formatteddates(1));
%Temperature will be the y variable
%20309 this is the total elements
%2130 is 2130 days = 6 years
temperatures = data(:,2);
%All temperatures from 'McGuireAFB.csv'
hold on;
scatter(x, temperatures, 'filled')
%Getting all scattered points, and show all of them with xlabels and
%ylabels, and then a sinusoidal curve and a trend curve will be plotted
hold on;
title('Temperature vs Time')
xlabel('Time')
ylabel('Temperature')
%Begin to onstruct the normal matrix to fit a line and a curve fitting to the data.

%x_0+x_1*x+x_2*cos(2?d/365.25)+ x_3*sin(2?d/365.25) and x_0+x_1*x

%A1'*A1*x = A1'*temperatures is the function of normal matrix, and x is the
%coefficient matrix. Temperatures is is an n*1 matrix, A1 is the n-by-m design matrix
%for the model and the model equatioin should be
%x_0+x_1*x+x_2*cos(2?d/365.25)+ x_3*sin(2?d/365.25).
A1= [0*x+1 x cos(2*pi*x/365) sin(2*pi*x/365)];
%A1'*A1; left side of normal equation except x.
normal = A1'*A1;
%A1'*temperatures right side of normal equation.
B1 = A1'*temperatures;
coefficient = normal\B1
%coefficient = 52.765458965605170    0.000102721893022  -19.253762945587109
% -10.173298885938818



X = linspace(1, 20309, 20309);
plot(X, 1.7*coefficient(4)*sin(2*pi*X/365.25)+1.7*coefficient(3)*cos(2*pi*X/365.25)+coefficient(2)*X-6+coefficient(1), 'y');
hold on;
%plot of sinusoid curve.


plot(x, coefficient(2)*x-6+coefficient(1), 'b');
%plot of trend curve.