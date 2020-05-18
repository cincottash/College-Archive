%2.4.5
A = [2, 0, 4, 3,; -4, 5, -7, -10; 1, 15, 2, -4.5; -2, 0, 2, -13];

[L,U] = lufact2(A)


function [L, U] = lufact2(A)
    n = length(A);
    L = eye(n);
    
    for j = 1:n-1
        for i = j+1:n
            L(i,j) = A(1,j) / A(j,j);
            A(i,j:n) = A(i,j:n) - L(i,j)*A(j,j:n);
        end
    end
U = triu(A)
end

