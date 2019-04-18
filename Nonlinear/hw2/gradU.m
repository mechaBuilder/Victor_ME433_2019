syms m1 m2 g L1 L2 th1 th2 
U = (m1 + m2)*g*L1*(1 - cos(x(i,1))) + m2*g*L2*(1 - cos(x(i,1) + x(i,2)));
gradU = [gradient(U,th1); gradient(U,th2)]