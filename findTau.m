function tau = findTau(dataFile,loopTime)
'TauData/step_data5_lt25.csv'
rawDataStep = csvread(dataFile);

%loopTime = 25; %amount of time that the encoders are counting over. Read from csv file name ltXX
voltageCmdStep = rawDataStep(:,2)*24/127;
motorSpeedStep = rawDataStep(:,3:4)/100*2*pi / (loopTime)*5;
tStepRightShark = rawDataStep(:,1)-rawDataStep(min(find(rawDataStep(:,3)>0))-1,1);
tStepLeftShark = rawDataStep(:,1)-rawDataStep(min(find(rawDataStep(:,4)>0))-1,1);

%RightShark Motor tau
%Determines the point at which the signal reaches 63, 586,95 and 98 percent
%and then compares them
timeConstantValues = [.37,.135,.05,.018];
rightSharkStepEnd = mean(motorSpeedStep(end-8:end,1));
leftSharkStepEnd = mean(motorSpeedStep(end-8:end,2));
for i = 1:4
    tau(1,i) = tStepRightShark(max(find(abs(motorSpeedStep(:,1)-rightSharkStepEnd)>=timeConstantValues(i)*rightSharkStepEnd)))/i;
    tau(2,i) = tStepLeftShark(max(find(abs(motorSpeedStep(:,1)-leftSharkStepEnd)>=timeConstantValues(i)*leftSharkStepEnd)))/i;
end
tau
end
