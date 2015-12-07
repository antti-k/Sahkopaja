%% Setup
clear all
a = arduino('/dev/tty.usbmodem411','uno')
%% I2C Setup
pd = i2cdev(a,'0x23')
write(pd, 1, 'uint8');
write(pd, 16, 'uint8');

%% Plot
data = zeros(100,1);
for i = 1:100
    value = read(pd, 2,'uint8');
    data(i) = uint16(bitshift(uint16(value(1)),8)) + uint16(value(2));
    pause(0.2)
    plot(data)
end


%% Testi1
data = zeros(25,1);
writePosition(s,0.7)
for i = 1:25
    value = read(pd, 2,'uint8');
    data(i) = uint16(bitshift(uint16(value(1)),8)) + uint16(value(2));
    pause(0.5)
    plot(data)
    writePosition(s,(0.7+i*0.01))
end