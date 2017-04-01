
% Read data from files

filename = 'myfile01.txt';
delimiterIn = ' ';
headerlinesIn = 0;
A = importdata(filename,delimiterIn,headerlinesIn);

v = VideoWriter('newfile.avi');
open(v)
writeVideo(v,rand(300))
