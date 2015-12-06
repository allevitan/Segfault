%Code to characterize motors using Serial data
clear all
rawDataLinear = csvread('raw_data.csv');
rawDataLinear = rawDataLinear(2:1921,:);
rawDataLinear = rawDataLinear(rawDataLinear(:,4)~=0,:);

%% Plot the data to get a value for Kt and Ke
clf
hold all
plot(rawDataLinear(:,2),rawDataLinear(:,3),'*');
plot(rawDataLinear(:,2),rawDataLinear(:,4),'*');
xlabel('Motor Command')
ylabel('Motor Speed')
legend('Right Shark','Left Shark');

loopTimeLinear = 100/1000; %time that encoder ticks are counted over [seconds]
encoderCounts = 100; %Number of lines the encoders have


voltageCmdLinear = rawDataLinear(:,2)*24/127;
motorSpeedLinear = rawDataLinear(:,3:4)/encoderCounts*2*pi / (loopTimeLinear)*5;



Kv1 = voltageCmdLinear./motorSpeedLinear(:,1);
meanKv1_bits = mean(rawDataLinear(:,2)./rawDataLinear(:,3));
meanKv1 = mean(Kv1);
medianKv1 = median(Kv1);


Kv2 = voltageCmdLinear./motorSpeedLinear(:,2);
meanKv2_bits = mean(rawDataLinear(:,2)./rawDataLinear(:,4));
meanKv2 = mean(Kv2);
medianDv2 = median(Kv2);

%% Get Time Constant Data

findTau('TauData/step_data5_lt25.csv',25); 

% rawDataStep = csvread('TauData/step_data5_lt25.csv');
% 
% loopTimeStep = 25; %amount of time that the encoders are counting over. Read from csv file name ltXX
% voltageCmdStep = rawDataStep(:,2)*24/127;
% motorSpeedStep = rawDataStep(:,3:4)/encoderCounts*2*pi / (loopTimeStep)*5;
% tStepRightShark = rawDataStep(:,1)-rawDataStep(min(find(rawDataStep(:,3)>0))-1,1);
% tStepLeftShark = rawDataStep(:,1)-rawDataStep(min(find(rawDataStep(:,4)>0))-1,1);
% 
% %RightShark Motor tau
% %Determines the point at which the signal reaches 63, 86,95 and 98 percent
% %and then compares them
% timeConstantValues = [.37,.135,.05,.018];
% rightSharkStepEnd = mean(motorSpeedStep(end-8:end,1));
% for i = 1:4
%     rightSharkTauI(i) = tStepRightShark(max(find(abs(motorSpeedStep(:,1)-rightSharkStepEnd)>=timeConstantValues(i)*rightSharkStepEnd)))/i;
% end
    






clf
plot(tStepRightShark,motorSpeedStep(:,1))

%yi=y(end)
%idx=max(find(abs(y-yi)>=0.37*yi))










