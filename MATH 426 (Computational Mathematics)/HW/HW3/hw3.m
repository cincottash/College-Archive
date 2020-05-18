%1.3.3
clc

clear all

x = [1 1 -1 -1]

y = [-1 1 1 -1]

A = polyarea(x,y)

x = [0 1 -1]

y = [2 0 0]

A = polyarea(x,y)
%The question asks for an equilater triangle but I could not figure out how
%to represent that with integer coordinates(of which our function requires)

function A = polyarea(x,y)
    n = size(x,2)

    x(n+1) = x(1)

    y(n+1) = y(1)
    
    sum = 0
    
    for i =1:n
        sum = sum + x(i)*y(i+1)-x(i+1)*y(i)
    end 
    
    A = abs(sum)/2
                  
    
end


