%Define the x-axis
x = 1 : 160;

%The Histogram By Morphological Method
figure(1);
data1 = load('StarHistogram2.txt');
bar(x, data1(1:160), 'r');
title('The Histogram By Morphological Method');
xlabel('Star Size(Pixel Numbers)');
ylabel('Number of Stars');
disp('Paused. Press Any Key to Show Next Graph.');
pause;

%The Histogram By Connected Component Labeling
figure(2);
data2 = load('StarHistogram.txt');
bar(x, data2(1:160), 'b');
title('The Histogram By Connected Component Labeling');
xlabel('Star Size(Pixel Numbers)');
ylabel('Number of Stars');
disp('Paused. Press Any Key to Show Next Graph.');
pause;