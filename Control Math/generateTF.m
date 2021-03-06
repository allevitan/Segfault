function [ VtoWs, VtoU, VtoTheta ] = generateTF( k, R, L, rp, mp, Ip );
%GENERATETF Outputs transfer functions for the plant
%   INPUTS
%   k: The motor constant, in V*s/rad (or N/A)
%   R: The motor resistance, in Ohms
%   L: The motor inductance, in Ohms
%   rp: The distance between the angle and the platform + person CM, in m
%   mp: The mass of the platform + person, in kg
%   I: The moment of inertia of the platform+person about their CM, in
%        kg*m^2
%   
%   OUTPUTS
%   VtoWs: Transfer function from motor voltage (V) to angular velocity of
%   the wheel with respect to the platform (rad/s)
%   VtoU: Transfer function from motor voltage (V) to ground speed (m/s)
%   VtoTheta: Transfer function from motor voltage (V) to angle (rad).

% Defining some constants we're pretty sure about
g = 9.8; %m/s
n = 5; % Gear ratio from motor shaft to wheel
rw = 0.1; % radius of wheel [m]
mw = 0.75; % mass of wheel [kg]  [approximation but it won't matter]
Iw = 0.004; % moment of inertia of wheel [kg*m^2], [approximation but again it won't matter]
ke = k; % electric constant [volt*s] This is true
kt = k; % torque constant [N-m/amp] This is also true


s = sym('s');
mymat = [mw + Iw/rw^2 + mp, mp*rp; ...
    mp*rp, Ip+mp*rp^2] * s^2 - ...
    [0,0;0, g*mp*rp];

Plant = sym2tf(inv(mymat) * [1/rw;-1]);
s = tf('s');
TtoU = minreal(s*Plant(1));  %Transfer function from torque to ground speed [N-m] - [m/s]
TtoTheta = minreal(Plant(2)); %Transfer function from torque to angle of pendulum [N-m] - [rad]
TtoWs = minreal(TtoU/rw - s*TtoTheta); %RTransfer function from torque to angular speed of wheels wrt pendlum [N-m] - [rad/s]

VetoT = kt/(L*s+R) * 2 * n; %TF from V_in-V_backemf to Torque
VtoT = minreal(VetoT / (1 + ke*VetoT*TtoWs)); % TF from V_in to tow

VtoWs = minreal(VtoT * TtoWs);
VtoU = (VtoT * TtoU);
VtoTheta = minreal(VtoT * TtoTheta);

end

