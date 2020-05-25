S = [-1 1 2 1 -0.5; 0 2 1 -1 -1.5];

S(:,end+1) = S(:,1);


R = [cos(7*pi/4) -sin(7*pi/4); sin(7*pi/4) cos(7*pi/4)];

newS = R*S;

plot(S(1,:),S(2,:),'r');
pbaspect([1 1 1]);

hold on;
plot(newS(1,:),newS(2,:),'b');
grid on;
hold off;

DE = delaware();

