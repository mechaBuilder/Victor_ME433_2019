function [position,isterminal,direction] = chaosEventsFcn(t,x)
% Locate when abs(phi) = 2*pi
phi = x(1) + x(2);
position = abs(phi) - 2*pi;     % Detect when abs(phi) = 2*pi
isterminal = 1;                 % Stop the integration
direction = 0;                  % the zero can be approached from any direction
end