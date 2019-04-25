clear; clc;
q11 = 1;
q12 = 0.01;
q21 = 0.01;
q22 = 100;
Q = [q11 q12; q21 q22];
syms x1 x2 
xdot = [x1 - x1^3 + x2; 3*x1 - x2];
xe = [2; 6]; %equalibrium (x1,x2) = (2,6)
A = double(subs(jacobian(xdot,[x1;x2]),{x1,x2},{xe(1),xe(2)}));
P = lyap(transpose(A),Q)
denomA = sqrt(det(P))
c = 1;
Area = pi*c/denomA