t = 1988:10:2018;
CO2 = [350.4,365.95,384.09,406.99];

A = zeros(4,4);

for k=1:4
    A(k,:) = [1, t(k), t(k)^2, t(k)^3];
end

c = A\(CO2');

tt = linspace(1988,2018,100);

plot(t,CO2,'ro');
hold on;
plot(tt,c(1)*(0*tt+1) + c(2)*tt + c(3)*tt.^2 + c(4)*tt.^3)
hold off