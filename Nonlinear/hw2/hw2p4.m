%EECS 495: Nonlinear Control
%hw2
%Problem 4
clear,clc
K = 50; 
%Simulation
tspan = [0 1000];     %10 seconds
x0 = zeros(4,1);
x0(1) = pi/2; %pi/4; %-2*pi + rand*(2*pi - (-2*pi));  %IC: theta - chosen at random from interval [-pi, pi]
x0(2) = pi; %pi/8; %-2*pi + rand*(2*pi - (-2*pi));
x0(3) = 0;  %IC: theta_dot -  [0, 0]
x0(4) = 0;
motor = 1;
%[dxdt, E] = dPendSS(t, x, K, motor);
options = odeset('RelTol',1e-6, 'AbsTol', 1e-6);%,'Stats','on','OutputFcn',@odeplot)
[t, x] = ode45(@(t,x) dPendSS(t,x,K, motor), tspan, x0, options); 
%Energy Calc
m1 = 1; m2 = 1; L1 = 0.5; L2 = 0.5; g = 9.81;
M = cell(size(x,1),1);
for i = 1:size(x,1)
M11(i) = (m1 + m2)*L1^2 + m2*L2^2 + 2*m2*L1*L2*cos(x(i,2));
M12(i) = m2*L2^2 + m2*L1*L2*cos(x(i,2));
M21(i) = m2*L2^2 + m2*L1*L2*cos(x(i,2));
M22(i) = m2*L2^2;
M{i} = [M11(i), M12(i); M21(i), M22(i)];
U(i) = (m1 + m2)*g*L1*(1 - cos(x(i,1))) + m2*g*L2*(1 - cos(x(i,1) + x(i,2)));
E(i) = (1/2)*[x(i,3), x(i,4)]*M{i}*[x(i,3); x(i,4)] + U(i);
end
%dt = (tspan(2)-tspan(1))/size(x,1);
%time = linspace(tspan(1),tspan(2),size(x,1));
%th_r = th_r*ones(size(x,1),1);
semilogy(t,E,'-o');
xlabel('time (sec.)');
ylabel('Energy');
%legend('theta', 'theta dot', 'theta_r');
%title('Problem 4, K = 35, th_r = 1 rad, u = K*sin(th_r - th)');

