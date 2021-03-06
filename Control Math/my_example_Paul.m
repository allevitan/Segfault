clear all
%These constants are for the segway by itself
rp0 = .03; %m
mp0 = 10; %kg
Ip0 = 0.274; %kg*m^2

rp = .5; %m
mp = 70 ; %kg
Ip = 40; %kg*m^2


k = 0.06; %V*s/rad
R = 0.22; %Ohms
L = 0; %Henries

s = tf('s');

[VtoWs, VtoU, VtoTheta] = generateTF(k,R,L,rp0,mp0,Ip0);
%[VtoWs, VtoU, VtoTheta] = generateTF(k,R,L,rp,mp,Ip);

Kv = .6;

VctoWs = minreal(Kv*VtoWs / (1+Kv*VtoWs));
VctoU = minreal(Kv*VtoU / (1+Kv*VtoWs));
VctoTheta = minreal(Kv*VtoTheta / (1+Kv*VtoWs));

%rlocus(VtoWs);

%pzmap(VctoTheta);

%Kv2 = 10;





%VcctoWs = minreal(Kv2*VctoWs/ (1+Kv2*VctoTheta*s));
%VcctoU = minreal(Kv2*VctoU/ (1+Kv2*VctoTheta*s));
%VcctoTheta = minreal(Kv2*VctoTheta/ (1+Kv2*VctoTheta*s));

%rlocus(VctoTheta*s)

%pzmap(VcctoTheta);

Kloop = 500;

Compensator = 1*(1/2.3*s+1)/((2*s-1))%
%Compensator = 1*(.2*s+1)*(.5*s+1)/((2*s-1))%b
%Compensator = 1*(.2*s+1)*(.5*s+1)*(.25*s+1)/((2*s-1))%

%Compensator = (s+3)/(s);
%rlocus(-Compensator*VctoTheta);


system = -VctoTheta;
systemPIDL = -VctoTheta;
systemCompL = -Compensator*VctoTheta;

systemPID = minreal(-Kloop*VctoTheta/(1-Kloop*VctoTheta));
systemComp = minreal(Kloop*systemCompL/(1+Kloop*systemCompL));%minreal(-Kloop*Compensator*VctoTheta/(1-Kloop*Compensator*VctoTheta));

%System = minreal(-Kloop*Compensator*VctoTheta/(1-Kloop*Compensator*VctoTheta));
%System = minreal(-Kloop*Compensator*VcctoTheta/(1-Kloop*Compensator*VcctoTheta));

t = linspace(0,10,1000);
u = [1,1, zeros(1,length(t)-2)];

figure(1)
rlocus(system);
title('Plant Root Locus Plot')
figure(2);
rlocus(systemCompL);
title('Compenstated System Root Locus Plot')
figure(3);
pzmap(systemComp);
title('Closed Loop System Pole-Zero Map')
figure(4);
step(systemComp);
figure(5);
lsim(systemComp,u,t,1);
figure(6);
margin(systemCompL);

%%
%convert to z plane

systemZ = c2d(Kloop*Compensator,.02);





