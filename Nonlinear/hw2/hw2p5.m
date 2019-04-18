%EECS 495: Nonlinear Control
%hw2
%Problem 5
clear, clc
% Tflip = magic(100)
% s = pcolor(Tflip)
% s.FaceColor = 'interp';

x0(1) = -pi; %pi/4; %-2*pi + rand*(2*pi - (-2*pi));  %IC: theta - chosen at random from interval [-pi, pi]
x0(2) = pi/8; %pi/8; %-2*pi + rand*(2*pi - (-2*pi));
x0(3) = 0;  %IC: theta_dot -  [0, 0]
x0(4) = 0;
tspan = [0 20]; 
%[dxdt, E] = dPendSS(t, x, K, motor);
options = odeset('Events',@chaosEventsFcn,'RelTol',1e-6, 'AbsTol', 1e-6,'Stats','off','OutputFcn',@odeplot);
[t,x,te,ye,ie] = ode45(@(t,x) dPendSSp5(t,x), tspan, x0, options);
m1 = 1; m2 = 1; L1 = 0.5; L2 = 0.5; g = 9.81;
Ecrit = min(2*(m1 + m2)*g*L1, 2*m2*g*L2);

size = 20;                      % SPECIFY size of grid
Tflip = zeros(size,size);       % prefill Tflip matrix
th1Range = [pi/2 pi];
phiRange = [pi/2 pi];
th1pts = linspace(th1Range(1), th1Range(2), size);
phipts = linspace(phiRange(1), phiRange(2), size);

for i = 1:size
    x0(1) = th1pts(i);
    
    for j = 1:size
        x0(2) = phipts(j) - th1pts(i);
        %Checking the Ecrit value
        M11 = (m1 + m2)*L1^2 + m2*L2^2 + 2*m2*L1*L2*cos(x0(2));
        M12 = m2*L2^2 + m2*L1*L2*cos(x0(2));
        M21 = m2*L2^2 + m2*L1*L2*cos(x0(2));
        M22 = m2*L2^2;
        M   = [M11, M12; M21, M22];
        U   = (m1 + m2)*g*L1*(1 - cos(x0(1))) + m2*g*L2*(1 - cos(x0(1) + x0(2)));
        E   = (1/2)*[x0(3), x0(4)]*M*[x0(3); x0(4)] + U;

        if E <= Ecrit
            Tflip(i,j) = NaN;
        else
            [t,x,te,ye,ie] = ode45(@(t,x) dPendSSp5(t,x), tspan, x0, options);
            te
            if length(te) == 0
                 Tflip(i,j) = tspan(2);
             else
                 Tflip(i,j) = te;    
             end
        end
    end
end

s = pcolor(Tflip);
s.FaceColor = 'interp';
set(s, 'EdgeColor', 'none');