clear all;
%%parameter
M0 = 4.0;
M1 = 0.36;
M = M0 + M1;
ls = 0.420;
theta = 0.08433;
Fr = 6.5;
C = 0.00652;
kA = 7.50;
g = 9.8;
R = (M1^2)*(ls^2) - M*theta;
%%isi matriks
a22 = (theta*Fr)/R;
a23 = ((M1^2)*(ls^2)*g)/R;
a24 = (-1*C*M1*ls)/R;
a42 = (-1*M1*ls*Fr)/R;
a43 = (-M*M1*ls*g)/R;
a44 = (C*M)/R;
b2 = (-1*theta)/R;
b4 = (M1*ls)/R;

A = [0 1 0 0;
     0 a22 a23 a24;
     0 0 0 1;
     0 a42 a43 a44];
B = [0;b2;0;b4];
C1 = [1 0 0 0;
    0 1 0 0];

D = [0];

Q = 1*eye(4);
R = 1*eye(1);

Q2 = 2*eye(4);
R2 = 1*eye(1);

Q3 = 100*eye(4);
R3 = 1*eye(1);

Cn = C1(1, :);
% lqr
[K,P,E] = lqr(A,B,Q,R);
[K2,P2,E2] = lqr(A,B,Q2,R2);
[K3,P3,E3] = lqr(A,B,Q3,R3);

Kr = inv(Cn*inv(-(A-B*K))*B)
Kr2 = inv(Cn*inv(-(A-B*K2))*B)
Kr3 = inv(Cn*inv(-(A-B*K3))*B)