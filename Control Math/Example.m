%These constants are for the segway by itself
rp0 = .03; %m
mp0 = 10; %kg
Ip0 = 0.274; %kg*m^2

% These are reasonable constants for a heavy person
rp = .5; %m
mp = 70; %kg
Ip = 50; %kg*m^2


k = 0.06; %V*s/rad
R = 0.22; %Ohms
L = 0; %Henries

s = tf('s');
[VtoWs, VtoU, VtoTheta] = generateTF(k,R,L,rp0,mp0,Ip0); %unloaded
%[VtoWs, VtoU, VtoTheta] = generateTF(k,R,L,rp,mp,Ip); %loaded