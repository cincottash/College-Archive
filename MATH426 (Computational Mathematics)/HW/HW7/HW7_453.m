%4.5.3

clear all
close all
syms u v
%functions for which intersection have to find
f(u,v)=u.*log(u)+v.*log(v)+0.3;
g(u,v)=u.^4+v.^2-1;
%Displaying the equation
fprintf('The equations are\n')
disp(f)
disp(g)
%creating Jacobian matrix
f_u(u,v)=diff(f,u);
f_v(u,v)=diff(f,v);
g_u(u,v)=diff(g,u);
g_v(u,v)=diff(g,v);
%Jacobian matrix
jac1=[f_u f_v; g_u g_v];
%displaying the Jacobian Matrix
fprintf('\tThe Jacobian Matrix is \n\n')
disp(jac1)
u1=1;v1=0.1;


%loop for Newton iterations
err=1;k=0;
fprintf('For initial condition u=%f and v=%f \n',u1,v1)
while err>10^-10

jac=[f_u(u1,v1) f_v(u1,v1);g_u(u1,v1) g_v(u1,v1)];
ijac=inv(jac);
uu=double([u1;v1]-ijac*[f(u1,v1);g(u1,v1)]);
err=norm(uu-[u1;v1]);
u1=double(uu(1));
v1=double(uu(2));
end
fprintf('\tThe intersection occured at u=%f, v=%f\n\n',u1,v1)

clear all
syms u v
%functions for which intersection have to find
f(u,v)=u.*log(u)+v.*log(v)+0.3;
g(u,v)=u.^4+v.^2-1;
%creating Jacobian matrix
f_u(u,v)=diff(f,u);
f_v(u,v)=diff(f,v);
g_u(u,v)=diff(g,u);
g_v(u,v)=diff(g,v);
%Jacobian matrix
jac1=[f_u f_v; g_u g_v];
%displaying the Jacobian Matrix
fprintf('\tThe Jacobian Matrix is \n')
disp(jac1)
u1=0.1;v1=1;


%loop for Newton iterations
err=1;k=0;
fprintf('\n\tFor initial condition u=%f and v=%f \n',u1,v1)
while err>10^-10

jac=[f_u(u1,v1) f_v(u1,v1);g_u(u1,v1) g_v(u1,v1)];
ijac=inv(jac);
uu=double([u1;v1]-ijac*[f(u1,v1);g(u1,v1)]);
err=norm(uu-[u1;v1]);
u1=double(uu(1));
v1=double(uu(2));
end
fprintf('\n\tThe intersection occured at u=%f, v=%f \n',u1,v1)