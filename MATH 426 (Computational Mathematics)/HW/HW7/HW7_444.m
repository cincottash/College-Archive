%4.4.4
x = linspace(0.5, 4*pi, 100);
y = x.^(-2)-sin(x);
plot(x,y)

f=@(x) x^(-2)-sin(x);
t=[0.5,1.5]; %starting points as t=0 and 1.5
kmax=50; %max iterations
tol=1*10^(-8); %tolerance
for j=length(t)+1:(kmax+length(t))
    t(j)=t(j-1)-f(t(j-1))*(t(j-1)-t(j-2))/(f(t(j-1))-f(t(j-2))); %next estimate
    if abs(f(t(j)))<tol %if error is within tolerance level
        disp(['The root is: t=',num2str(t(j)),' found after ',num2str(j),' iterations']) %return the element
        return
    end
end
disp(['The root is : ',num2str(t(end)),' found after ',kmax,' iterations']) %return the root found after max iterations