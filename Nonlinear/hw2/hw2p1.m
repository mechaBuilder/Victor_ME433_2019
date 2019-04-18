%EECS 495: Nonlinear Control
%hw2
%Problem 1
syms m1 m2 L1 L2 th1 th2
M = sym('M%d%d', [2 2]);                               %prefill 2x2 matrix
M(1,1) = (m1 + m2)*L1^2 + m2*L2^2 + 2*m2*L1*L2*cos(th2);
M(1,2) = m2*L2^2 + m2*L1*L2*cos(th2);
M(2,1) = m2*L2^2 + m2*L1*L2*cos(th2);
M(2,2) = m2*L2^2;
lambda = simplify(eig(M),'Steps',50)
%Now going to convert symbolic to double for m1 m2 L1 L2 to simplify
%further
%double(m1); double(m2); double(L1); double(L2); 
%m1 = 1; m2 = 1; L1 = 1; L2 = 1;


