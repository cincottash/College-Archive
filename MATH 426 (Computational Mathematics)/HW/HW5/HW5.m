%%
%2.8.1
clear all
clc

for n=2:16
    fprintf('n=%d, condition number is %.4e and norm is %f\n',n,cond(hilb(n)), norm(hilb(n),2))
end
