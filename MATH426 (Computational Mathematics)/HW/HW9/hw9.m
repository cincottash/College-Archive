%HW9 SHANE CINCOTTA

%%6.3.4

tspan = [0 100];
y0 = [0.95 0.05]; % Initial conditions
[t, y] = ode45(@(t, y) odefcn(t, y), tspan, y0); 
plot(t, y(:,1), '-', t, y(:,2), '-.')
legend('v(t)', 'w(t)', 'Location', 'northwest')
title('Solution of ODE')
xlabel('t')

function dydt = odefcn(t, y)
dydt = [0.2*(1 - y(1)) - 3*y(1)*y(2); (3*y(1) - 1)*y(2)];
end

%%6.4.11
function der2 = newode2(x, y)
der2 = [y(2); (y(1)-3*x*y(2))/(2*x*x)];
end
[Time, Fun] = RK4_Method(@newode2, [1, 16], [4, -1], 100);
real_f = @(x)2*(x.^0.5 + 1./x);

error = zeros(101, 1);

for i = 0:100
   error(i+1) = real_f(1+(15*i/100)) - Fun(i+1, 1); 
end

holder = zeros(10, 1);
for k = 1:10
   [ti, fun2] =RK4_Method(@newode2, [1, 16], [4, -1], 2.^(k+2));
   holder(k) = real_f(16) - fun2(end, 1);
end

temp_holder = zeros(10, 1);
temp_holder(1) = 4;
for k = 2:10
   temp_holder(k) = temp_holder(k-1)/4;
end

loglog(2.^(3:12), holder);
hold on;
loglog(2.^(3:12), temp_holder);
hold off;

holder

function [t, u] = RK4_Method(dudt, tspan, u0, n)
a = tspan(1); b = tspan(2);
h = (b-a)/n;
t = a + (0:n)'*h;

u = zeros(length(u0), n+1);
u(:,1)= u0(:);


for i = 1:n
   k1 = h*dudt(t(i), u(:,i));
   k2 = h*dudt(t(i)+(2*h/3), u(:,i)+2*k1/3);
   u(:,i+1)=u(:,i)+ (k1+3*k2)/4;
end

u=u';
end

