%% Setup
clear all
a = arduino('/dev/tty.usbmodem411','uno')

%% Servo setup
s = servo(a,'D4')
%%
for i = 0:0.01:0.9
    writePosition(s,i);
    pause(1);
end
