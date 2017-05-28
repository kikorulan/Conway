%================================================
% Generate glider
%================================================
glider = ...
[0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0;
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 1 0 0 0 0 0 0 0 0 0 0 0 0;
0 0 0 0 0 0 0 0 0 0 0 0 0 1 1 0 0 0 0 0 0 1 1 0 0 0 0 0 0 0 0 0 0 0 0 1 1 0;
0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0 0 0 0 1 1 0 0 0 0 0 0 0 0 0 0 0 0 1 1 0;
0 1 1 0 0 0 0 0 0 0 0 1 0 0 0 0 0 1 0 0 0 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
0 1 1 0 0 0 0 0 0 0 0 1 0 0 0 1 0 1 1 0 0 0 0 1 0 1 0 0 0 0 0 0 0 0 0 0 0 0;
0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 1 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0;
0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
0 0 0 0 0 0 0 0 0 0 0 0 0 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0];

%================================================
% 100x50 domain
%================================================
% Domain dimensions
nrows = 100;
ncols = 50;
nsteps = 1000;
domain = zeros(nrows, ncols);
dimensions = [nrows ncols nsteps];
% Assign glider
domain(1:11, 1:38) = glider;
% Save domain
dlmwrite('Example1_dimensions.dat', dimensions, 'delimiter', ' ');
dlmwrite('Example1_domain.dat', domain, 'delimiter', ' ');

%================================================
% 100x100 domain
%================================================
% Domain dimensions
nrows = 100;
ncols = 100;
nsteps = 1000;
domain = zeros(nrows, ncols);
dimensions = [nrows ncols nsteps];
% Assign glider
domain(1:11, 1:38) = glider;

% Save domain
dlmwrite('Example2_dimensions.dat', dimensions, 'delimiter', ' ');
dlmwrite('Example2_domain.dat', domain, 'delimiter', ' ');

%================================================
% 100x200 domain
%================================================
% Domain dimensions
nrows = 100;
ncols = 200;
nsteps = 1000;
domain = zeros(nrows, ncols);
dimensions = [nrows ncols nsteps];
% Assign glider
domain(1:11, 1:38) = glider;

% Save domain
dlmwrite('Example3_dimensions.dat', dimensions, 'delimiter', ' ');
dlmwrite('Example3_domain.dat', domain, 'delimiter', ' ');

%================================================
% 100x400 domain
%================================================
% Domain dimensions
nrows = 100;
ncols = 400;
nsteps = 1000;
domain = zeros(nrows, ncols);
dimensions = [nrows ncols nsteps];
% Assign glider
domain(1:11, 1:38) = glider;

% Save domain
dlmwrite('Example4_dimensions.dat', dimensions, 'delimiter', ' ');
dlmwrite('Example4_domain.dat', domain, 'delimiter', ' ');

%================================================
% 100x800 domain
%================================================
% Domain dimensions
nrows = 100;
ncols = 800;
nsteps = 1000;
domain = zeros(nrows, ncols);
dimensions = [nrows ncols nsteps];
% Assign glider
domain(1:11, 1:38) = glider;

% Save domain
dlmwrite('Example5_dimensions.dat', dimensions, 'delimiter', ' ');
dlmwrite('Example5_domain.dat', domain, 'delimiter', ' ');

