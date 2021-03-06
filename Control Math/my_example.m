%These constants are for the segway by itself
rp0 = .03; %m
mp0 = 10; %kg
Ip0 = 0.274; %kg*m^2

rp = .5; %m
mp = 70; %kg
Ip = 40; %kg*m^2


k = 0.06; %V*s/rad
R = 0.22; %Ohms
L = 0; %Henries

s = tf('s');

[VtoWs, VtoU, VtoTheta] = generateTF(k,R,L,rp0,mp0,Ip0);
%[VtoWs, VtoU, VtoTheta] = generateTF(k,R,L,rp,mp,Ip);

Kv = 1;

VctoWs = minreal(Kv*VtoWs/ (1+Kv*VtoWs));
VctoU = minreal(Kv*VtoU/ (1+Kv*VtoWs));
VctoTheta = minreal(Kv*VtoTheta/ (1+Kv*VtoWs));

%rlocus(VtoWs);

%pzmap(VctoTheta);

%rlocus(VctoTheta*s)

Compensator = (s+2.5)/(s);
rlocus(-Compensator*VctoTheta);
%rlocus(-VctoTheta);

Kloop = 7;

System = minreal(-Kloop*Compensator*VctoTheta/(1-Kloop*Compensator*VctoTheta));
%System = minreal(-Kloop*Compensator*VcctoTheta/(1-Kloop*Compensator*VcctoTheta));

c2d(Kloop*Compensator,0.02,'tustin')

t = linspace(0,10,1000);
u = [1,1, zeros(1,length(t)-2)];
lsim(System,u,t,1);
