%(1) Name : Zhiwei Deng
%(2) USC ID Number : 3669230452
%(3) USC Email : zhiweide@usc.edu
%(4) Submission Date : 01/28/2020

%Define the x-axis
x = 0 : 255;

%The R channel of Original Image
figure(1);
data1 = load('Data/Histogram_OR.txt');
bar(x, data1, 'r');
title('The R channel of Original Image.');
xlabel('Grayscale Values');
ylabel('Pixel Numbers');
disp('Paused. Press Any Key to Show Next Graph.');
pause;

%The G channel of Original Image
figure(2);
data2 = load('Data/Histogram_OG.txt');
bar(x, data2, 'g');
title('The G channel of Original Image.');
xlabel('Grayscale Values');
ylabel('Pixel Numbers');
disp('Paused. Press Any Key to Show Next Graph.');
pause;

%The B channel of Original Image
figure(3);
data3 = load('Data/Histogram_OB.txt');
bar(x, data3, 'b');
title('The B channel of Original Image.');
xlabel('Grayscale Values');
ylabel('Pixel Numbers');
disp('Paused. Press Any Key to Show Next Graph.');
pause;

%The R channel of Method A Image
figure(4);
data4 = load('Data/Histogram_AR.txt');
bar(x, data4, 'r');
title('The R channel of Method A Image.');
xlabel('Grayscale Values');
ylabel('Pixel Numbers');
disp('Paused. Press Any Key to Show Next Graph.');
pause;

%The G channel of Method A Image
figure(5);
data5 = load('Data/Histogram_AG.txt');
bar(x, data5, 'g');
title('The G channel of Method A Image.');
xlabel('Grayscale Values');
ylabel('Pixel Numbers');
disp('Paused. Press Any Key to Show Next Graph.');
pause;

%The B channel of Method A Image
figure(6);
data6 = load('Data/Histogram_AB.txt');
bar(x, data5, 'b');
title('The B channel of Method A Image.');
xlabel('Grayscale Values');
ylabel('Pixel Numbers');
disp('Paused. Press Any Key to Show Next Graph.');
pause;

%The R channel of Method B Image
figure(7);
data7 = load('Data/Histogram_BR.txt');
bar(x, data7, 'r');
title('The R channel of Method B Image.');
xlabel('Grayscale Values');
ylabel('Pixel Numbers');
disp('Paused. Press Any Key to Show Next Graph.');
pause;

%The G channel of Method B Image
figure(8);
data8 = load('Data/Histogram_BR.txt');
bar(x, data8, 'g');
title('The G channel of Method B Image.');
xlabel('Grayscale Values');
ylabel('Pixel Numbers');
disp('Paused. Press Any Key to Show Next Graph.');
pause;

%The B channel of Method B Image
figure(9);
data9 = load('Data/Histogram_BB.txt');
bar(x, data9, 'b');
title('The B channel of Method B Image.');
xlabel('Grayscale Values');
ylabel('Pixel Numbers');
disp('Paused. Press Any Key to Show Next Graph.');
pause;

%The R channel of Transfer Function
figure(10);
data10 = load('Data/Transfer_R.txt');
data10 = data10 / 255;
bar(x, data10, 'r');
title('The R channel of Transfer Function.');
xlabel('Old Grayscale Values');
ylabel('New Grayscale Values');
disp('Paused. Press Any Key to Show Next Graph.');
pause;

%The G channel of Transfer Function
figure(11);
data11 = load('Data/Transfer_G.txt');
data11 = data11 / 255;
bar(x, data11, 'g');
title('The G channel of Transfer Function.');
xlabel('Old Grayscale Values');
ylabel('New Grayscale Values');
disp('Paused. Press Any Key to Show Next Graph.');
pause;

%The B channel of Transfer Function
figure(12);
data12 = load('Data/Transfer_B.txt');
data12 = data12 / 255;
bar(x, data12, 'b');
title('The B channel of Transfer Function.');
xlabel('Old Grayscale Values');
ylabel('New Grayscale Values');
disp('Paused. Press Any Key to Show Next Graph.');
pause;

%The R channel of Cumulative Histogram
figure(13);
data13 = load('Data/Cumulative_R.txt');
bar(x, data13, 'r');
title('The R channel of Cumulative Histogram.');
xlabel('Old Grayscale Values');
ylabel('Pixel Numbers');
disp('Paused. Press Any Key to Show Next Graph.');
pause;

%The G channel of Cumulative Histogram
figure(14);
data14 = load('Data/Cumulative_G.txt');
bar(x, data14, 'g');
title('The G channel of Cumulative Histogram.');
xlabel('Old Grayscale Values');
ylabel('Pixel Numbers');
disp('Paused. Press Any Key to Show Next Graph.');
pause;

%The B channel of Cumulative Histogram
figure(15);
data15 = load('Data/Cumulative_B.txt');
bar(x, data15, 'b');
title('The B channel of Cumulative Histogram.');
xlabel('Old Grayscale Values');
ylabel('Pixel Numbers');
disp('Paused. Press Any Key to Show Next Graph.');
pause;