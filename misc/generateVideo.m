% Read data from files
clear all;

% Create video handle
v = VideoWriter('ConwayGOL.avi');
v.FrameRate = 10;
open(v);

cd output_data;
% Number of steps
nSteps = 200; 
% Read files
delimiterIn = ' ';
headerlinesIn = 0;
for n = 1:nSteps
    filename = strcat('Matrix', int2str(n),'.dat');
    matrix{n} = importdata(filename, delimiterIn, headerlinesIn);
    writeVideo(v,matrix{n});
end


close(v);
cd ..;
