function dxdt = ssp1(t, x, K)
u = K*x(2);
dxdt = zeros(2,1);
dxdt(1) = x(1) - x(1)^3 + x(2);
dxdt(2) = 3*x(1) - x(2) + u;
end 