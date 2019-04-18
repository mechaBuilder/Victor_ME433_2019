%EECS 495: Nonlinear Control
%hw2
%Problem 4
%This function is the state space representation of equation (1)
%Inputs:    t = time vector
%           x = state variable vector
%           K = proportional gain
%           motor = position of the motor - either 1 or 2
%                   used in control, u, vector

%Output:    dxdt

function dxdt = dPendSS(t, x, K, motor)
%syms m1 m2 g L1 L2 th1 th2 
%U = -(m1 + m2)*g*L1*cos(th1) - m2*g*L2*cos(th1 + th2);
%gradU = [gradient(U,th1); gradient(U,th2)]

m1 = 1; m2 = 1; L1 = 0.5; L2 = 0.5; g = 9.81;

M = zeros(2,2);
M(1,1) = (m1 + m2)*L1^2 + m2*L2^2 + 2*m2*L1*L2*cos(x(2));
M(1,2) = m2*L2^2 + m2*L1*L2*cos(x(2));
M(2,1) = m2*L2^2 + m2*L1*L2*cos(x(2));
M(2,2) = m2*L2^2;

C = zeros(2,2);
C(1,1) = m2*L1*L2*sin(x(2))*(-x(4));
C(1,2) = m2*L1*L2*sin(x(2))*(-x(3)- x(4));
C(2,1) = m2*L1*L2*sin(x(2))*(x(3));
C(2,2) = 0;

gradU = zeros(2,1);

%L1*g*sin(th1)*(m1 + m2) + L2*g*m2*sin(th1 + th2)
%L2*g*m2*sin(th1 + th2)
gradU(1) = L1*g*sin(x(1))*(m1 + m2) + L2*g*m2*sin(x(1) + x(2));
gradU(2) = L2*g*m2*sin(x(1) + x(2));

dxdt = zeros(4,1); 
%x(1) = th1; 
%x(2) = th2;
%x(3) = th1dot;
%x(4) = th2dot;

u = zeros(2,1);

control = -K*x(motor+2);               %Saturation limits: [-0.2 0.2]
if control > 0.2
    u(motor) = 0.2;
elseif u < -0.2
    u(motor) = -0.2;
else
    
end

%u = zeros(2,1);

dxdt(1) = x(3);
dxdt(2) = x(4);
dxdt(3:4) = M\(u - C*[x(3); x(4)] - gradU);

end 