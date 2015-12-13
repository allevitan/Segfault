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

Kv = 10;

VctoWs = minreal(VtoWs / (1+Kv*VtoWs)); 
VctoU = minreal(VtoU / (1+Kv*VtoWs));
VctoTheta = minreal(VtoTheta / (1+Kv*VtoWs));

Compensator = (s+3)/s;
rlocus(Compensator*-VctoTheta);

Kloop = 100;

System = minreal(-Kloop*Compensator*VctoTheta/(1-Kloop*Compensator*VctoTheta));

step(System);
