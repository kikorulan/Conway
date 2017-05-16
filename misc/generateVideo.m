% Read data from files
clear all;

% Read files
delimiterIn = ' ';
headerlinesIn = 0;
% Import data
filenameData = 'CGOL.dat';
matrix = importdata(filenameData, delimiterIn, headerlinesIn);
% Import dimensions
filenameDimensions = 'dimensions.dat';
dim = importdata(filenameDimensions, delimiterIn, headerlinesIn);
dimX = dim(1);
dimY = dim(2);
nSteps = dim(3);

% Create video handle
v = VideoWriter('ConwayGOL.avi');
v.FrameRate = 30;
open(v);


% Generate video
for n = 0:nSteps
    writeVideo(v,matrix(1+n*dimX:(n+1)*dimX, :));
end


close(v);

