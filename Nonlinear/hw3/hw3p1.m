%Semi group property

x0 = zeros(2,1);
x0(1) = 10;
x0(2) = 20;
tspan = [0 100];     %10 seconds

[t, x] = ode45(@(t,x) ssp1(t,x),tspan, x0);
hold on
plot(t,x,'-o');
%xlabel('time (sec.)');
%ylabel('Energy (J)');
legend();
%title('Problem 4, Plot: Energy vs. time');
x0(1) = -10;
x0(2) = -20;
tspan = [0 100];     %10 seconds
[t, x] = ode45(@(t,x) ssp1(t,x),tspan, x0);
plot(t,x);
hold off

