%%
f = @(x) cos(x)-1/2;

g = @(x) x-f(x);

s = linspace(-pi,pi,1000);
plot(s,g(s)); 
hold on;
plot(s,s);

x = 0.2;

r = fzero(f,-1);
err = [];

% Adjust these iterations to your heart's content.
for k = 1:10

    err(end+1) = x-r;
    
    y = g(x);

    plot([x x],[x y],'ro-');
    plot([x y],[y y],'bo-');

    x = y;
end

hold off;
%%

semilogy(err,'o');
grid on;