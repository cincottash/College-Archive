
optime = [];
probsize = [];
for n = 100*(2.^(1:8))
    probsize(end+1) = n;
    A = randn(n,n);
    x = randn(n,1);

    tic
    for k = 1:10
        A*x;
    end
    optime(end+1) = toc/10;
end
loglog(probsize,optime,'o-');
grid on;
xlabel('n'); ylabel('time');