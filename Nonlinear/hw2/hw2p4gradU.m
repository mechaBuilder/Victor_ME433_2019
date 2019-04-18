syms m1 m2 g L1 L2 th1 th2 
U = (m1 + m2)*g*L1*(1 - cos(th1)) + m2*g*L2*(1 - cos(th1 + th2));
gradU = [gradient(U,th1); gradient(U,th2)]