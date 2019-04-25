%EECS495: Nonlinear Control
%hw3
%Problem 3
clear; clc;
Q = eye(2)
syms x1 x2 
xdot = [x1 - x1^3 + x2; 3*x1 - x2];
xe = [2; 6] %equalibrium (x1,x2) = (2,6)
A = double(subs(jacobian(xdot,[x1;x2]),{x1,x2},{xe(1),xe(2)}))
P = lyap(transpose(A),Q)
x = [x1; x2]; 
Vsyms = transpose(x - xe)*P*(x - xe);
LfVsyms = diff(Vsyms,x1)*xdot(1) + diff(Vsyms,x2)* xdot(2);
x1n = linspace(-2,8,50);
x2n = linspace(2,8,50);
[X,Y] = meshgrid(x1n,x2n);
Vnum = double(subs(Vsyms, {x1,x2}, {X,Y}));
LfVnum = double(subs(LfVsyms, {x1,x2},{X,Y}));
hold on
contourf(X,Y,LfVnum,[0,0],'ShowText','on')
scatter(2,6,'*b') %represents equalibriam pt.

%plotmatrix(Vnum,'--r')

contour(X,Y,Vnum, [0,1],'--r','ShowText','on')
contour(X,Y,Vnum, [0,0.5],'--r','ShowText','on')
contour(X,Y,Vnum, [0,0.25],'--r','ShowText','on')
contour(X,Y,Vnum, [0,0.15],'--r','ShowText','on')
contour(X,Y,Vnum, [0,0.12],'ShowText','on')
hold off
legend('LfV<0','Equalibrium', 'c=0.5','c=0.25','c=0.15','c=0.12', 'V=c')
title('Boundaries of LfV and V for 50x50 matrix of x0')
xlabel('x1');
ylabel('x2');
c = 0.12;
Area = (pi*c)/sqrt(det(P))