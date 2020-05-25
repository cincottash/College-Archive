%Created by Shane Cincotta 9/5/19

clear
x = linspace(-1,1,1000); % Generate 10 evenly spaced points between 5 and 20
y1 = (exp(x)-1)/x;

output1 = zeros(1, 1000);
output2 = zeros(1, 1000);

for n = 1:1000
   output1(n) = (exp(x(n))-1)/x(n)
end

for n = 1:1000
   output2(n) = (1 + (x(n))/factorial(2)+ (x(n))^2/factorial(3)+ (x(n))^3/factorial(4)+ (x(n))^4/factorial(5)+ (x(n))^5/factorial(6)+ (x(n))^6/factorial(7)+ (x(n))^7/factorial(8)+ (x(n))^8/factorial(9)+ (x(n))^9/factorial(10)+ (x(n))^10/factorial(11) + (x(n))^11/factorial(12)+ (x(n))^12/factorial(13)+ (x(n))^13/factorial(14)+ (x(n))^14/factorial(15)+ (x(n))^15/factorial(16)+ (x(n))^16/factorial(17)+ (x(n))^17/factorial(18))
end

for n = 1:1000
   difference = abs(output1(n) - output2(n))
   plot(difference(0:1/100:1)), hold on
    
end
%Based on my two different algorithms, I believe that the 2nd algorithm is
%more accurate because it has a higher degree of precision due to how a
%taylor series is derived.  A taylor series is derived by using a series of
%derivates at a certain point, which increases the number of sig figs in
%our result