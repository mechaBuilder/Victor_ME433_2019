%EECS495: Nonlinear Control
%hw3
%Problem 4

%Questions:
    %(1) How large can you make the area of the resulting estimate by
            %adjusting Q?

clear; clc;
a = 200;
b = 0.2;
d = 0.3;
Q = [a b; b d]
syms x1 x2 
xdot = [x1 - x1^3 + x2; 3*x1 - x2];
xe = [2; 6] %equalibrium (x1,x2) = (2,6)
A = double(subs(jacobian(xdot,[x1;x2]),{x1,x2},{xe(1),xe(2)}))
P = lyap(transpose(A),Q)
x = [x1; x2]; 
Vsyms = transpose(x - xe)*P*(x - xe);
LfVsyms = diff(Vsyms,x1)*xdot(1) + diff(Vsyms,x2)* xdot(2);
x1n = linspace(-10,10,50);
x2n = linspace(-10,10,50);
[X,Y] = meshgrid(x1n,x2n);
Vnum = double(subs(Vsyms, {x1,x2}, {X,Y}));
LfVnum = double(subs(LfVsyms, {x1,x2},{X,Y}));
hold on
contourf(X,Y,LfVnum,[0,0],'ShowText','on')
scatter(2,6,'*b') %represents equalibriam pt.

%plotmatrix(Vnum,'--r')

contour(X,Y,Vnum, [0,1.8],'--r','ShowText','on')
contour(X,Y,Vnum, [0,0.5],'--r','ShowText','on')
contour(X,Y,Vnum, [0,0.25],'--r','ShowText','on')
contour(X,Y,Vnum, [0,10],'--r','ShowText','on')
contour(X,Y,Vnum, [0,100],'ShowText','on')
hold off
legend('LfV<0','Equalibrium', 'c=0.5','c=0.25','c=0.15','c=0.12', 'V=c')
title('Boundaries of LfV and V')
xlabel('x1');
ylabel('x2');
c = 100;
Area = (pi*c)/sqrt(det(P))