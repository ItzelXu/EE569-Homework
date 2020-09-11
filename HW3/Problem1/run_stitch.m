%(1) Name : Zhiwei Deng
%(2) USC ID Number : 3669230452
%(3) USC Email : zhiweide@usc.edu
%(4) Submission Date : 03/03/2020

%Left Image
im1 = readraw('Images/left.raw', 720, 480, 3);
%Middle Image
im2 = readraw('Images/middle.raw', 720, 480, 3);
%Right Image
im3 = readraw('Images/right.raw', 720, 480, 3);

grayImage1 = rgb2gray(im1);
grayImage2 = rgb2gray(im2);
grayImage3 = rgb2gray(im3);

%Feature Extractions
points1 = detectSURFFeatures(grayImage1);
points2 = detectSURFFeatures(grayImage2);
points3 = detectSURFFeatures(grayImage3);
[features1, points1] = extractFeatures(grayImage1, points1);
[features2, points2] = extractFeatures(grayImage2, points2);
[features3, points3] = extractFeatures(grayImage3, points3);

%Left and Middle
indexPairs1 = matchFeatures(features2, features1, 'Unique', true);
%Middle and Right
indexPairs2 = matchFeatures(features3, features2, 'Unique', true);

matchedPoints1 = points1(indexPairs1(:,2), :);
matchedPoints2 = points2(indexPairs1(:,1), :);
matchedPoints3 = points2(indexPairs2(:,2), :);
matchedPoints4 = points3(indexPairs2(:,1), :);

%The set of Control Points
CtrlPoint1 = 10; CtrlPoint5 = 6;
CtrlPoint2 = 12; CtrlPoint6 = 24;
CtrlPoint3 = 23; CtrlPoint7 = 52;
CtrlPoint4 = 61; CtrlPoint8 = 62;

%Choose the Control Points of Left Image
leftCtrlPt1 = matchedPoints1.Location(CtrlPoint1, :);
leftCtrlPt2 = matchedPoints1.Location(CtrlPoint2, :);
leftCtrlPt3 = matchedPoints1.Location(CtrlPoint3, :);
leftCtrlPt4 = matchedPoints1.Location(CtrlPoint4, :);
%Choose the Control Points of Middle Image - With Left
middCtrlPt1 = matchedPoints2.Location(CtrlPoint1, :);
middCtrlPt2 = matchedPoints2.Location(CtrlPoint2, :);
middCtrlPt3 = matchedPoints2.Location(CtrlPoint3, :);
middCtrlPt4 = matchedPoints2.Location(CtrlPoint4, :);
%Choose the Control Points of Middle Image - With Right
middCtrlPt5 = matchedPoints3.Location(CtrlPoint5, :);
middCtrlPt6 = matchedPoints3.Location(CtrlPoint6, :);
middCtrlPt7 = matchedPoints3.Location(CtrlPoint7, :);
middCtrlPt8 = matchedPoints3.Location(CtrlPoint8, :);
%Choose the Control Points of Right Image
rigtCtrlPt1 = matchedPoints4.Location(CtrlPoint5, :);
rigtCtrlPt2 = matchedPoints4.Location(CtrlPoint6, :);
rigtCtrlPt3 = matchedPoints4.Location(CtrlPoint7, :);
rigtCtrlPt4 = matchedPoints4.Location(CtrlPoint8, :);

%Show the Control Points with Local Positions
originLocalx1 = leftCtrlPt1(1,1); originLocaly1 = leftCtrlPt1(1,2);
originLocalx2 = leftCtrlPt2(1,1); originLocaly2 = leftCtrlPt2(1,2);
originLocalx3 = leftCtrlPt3(1,1); originLocaly3 = leftCtrlPt3(1,2);
originLocalx4 = leftCtrlPt4(1,1); originLocaly4 = leftCtrlPt4(1,2);
originLocalx5 = rigtCtrlPt1(1,1); originLocaly5 = rigtCtrlPt1(1,2);
originLocalx6 = rigtCtrlPt2(1,1); originLocaly6 = rigtCtrlPt2(1,2);
originLocalx7 = rigtCtrlPt3(1,1); originLocaly7 = rigtCtrlPt3(1,2);
originLocalx8 = rigtCtrlPt4(1,1); originLocaly8 = rigtCtrlPt4(1,2);

targetLocalx1 = middCtrlPt1(1,1); targetLocaly1 = middCtrlPt1(1,2);
targetLocalx2 = middCtrlPt2(1,1); targetLocaly2 = middCtrlPt2(1,2);
targetLocalx3 = middCtrlPt3(1,1); targetLocaly3 = middCtrlPt3(1,2);
targetLocalx4 = middCtrlPt4(1,1); targetLocaly4 = middCtrlPt4(1,2);
targetLocalx5 = middCtrlPt5(1,1); targetLocaly5 = middCtrlPt5(1,2);
targetLocalx6 = middCtrlPt6(1,1); targetLocaly6 = middCtrlPt6(1,2);
targetLocalx7 = middCtrlPt7(1,1); targetLocaly7 = middCtrlPt7(1,2);
targetLocalx8 = middCtrlPt8(1,1); targetLocaly8 = middCtrlPt8(1,2);
%{

im2(round(middCtrlPt5(2)), round(middCtrlPt5(1)), :) = [255, 0, 0];
im2(round(middCtrlPt5(2))-1, round(middCtrlPt5(1)), :) = [255, 0, 0];
im2(round(middCtrlPt5(2)), round(middCtrlPt5(1))-1, :) = [255, 0, 0];
im2(round(middCtrlPt5(2))+1, round(middCtrlPt5(1)), :) = [255, 0, 0];
im2(round(middCtrlPt5(2)), round(middCtrlPt5(1))+1, :) = [255, 0, 0];

im2(round(middCtrlPt6(2)), round(middCtrlPt6(1)), :) = [255, 0, 0];
im2(round(middCtrlPt6(2))-1, round(middCtrlPt6(1)), :) = [255, 0, 0];
im2(round(middCtrlPt6(2)), round(middCtrlPt6(1))-1, :) = [255, 0, 0];
im2(round(middCtrlPt6(2))+1, round(middCtrlPt6(1)), :) = [255, 0, 0];
im2(round(middCtrlPt6(2)), round(middCtrlPt6(1))+1, :) = [255, 0, 0];

im2(round(middCtrlPt7(2)), round(middCtrlPt7(1)), :) = [255, 0, 0];
im2(round(middCtrlPt7(2))-1, round(middCtrlPt7(1)), :) = [255, 0, 0];
im2(round(middCtrlPt7(2)), round(middCtrlPt7(1))-1, :) = [255, 0, 0];
im2(round(middCtrlPt7(2))+1, round(middCtrlPt7(1)), :) = [255, 0, 0];
im2(round(middCtrlPt7(2)), round(middCtrlPt7(1))+1, :) = [255, 0, 0];

im2(round(middCtrlPt8(2)), round(middCtrlPt8(1)), :) = [255, 0, 0];
im2(round(middCtrlPt8(2))-1, round(middCtrlPt8(1)), :) = [255, 0, 0];
im2(round(middCtrlPt8(2)), round(middCtrlPt8(1))-1, :) = [255, 0, 0];
im2(round(middCtrlPt8(2))+1, round(middCtrlPt8(1)), :) = [255, 0, 0];
im2(round(middCtrlPt8(2)), round(middCtrlPt8(1))+1, :) = [255, 0, 0];

imshow(im2);
%}

%Ceate Canvas
canvas = uint8(zeros(2000, 2000, 3));

%Copy the Imges onto Canvas
for i = 1:720
    for j = 1:480
        canvas(i+640, j, :) = im1(i, j, :);
        canvas(i+640, j+760, :) = im2(i, j, :);
        canvas(i+640, j+1520, :) = im3(i, j, :);
    end
end

%Get the Canvas Coordinates
originCanvasx1 = originLocalx1; originCanvasy1 = originLocaly1 + 640;
originCanvasx2 = originLocalx2; originCanvasy2 = originLocaly2 + 640;
originCanvasx3 = originLocalx3; originCanvasy3 = originLocaly3 + 640;
originCanvasx4 = originLocalx4; originCanvasy4 = originLocaly4 + 640;
originCanvasx5 = originLocalx5 + 1520; originCanvasy5 = originLocaly5 + 640;
originCanvasx6 = originLocalx6 + 1520; originCanvasy6 = originLocaly6 + 640;
originCanvasx7 = originLocalx7 + 1520; originCanvasy7 = originLocaly7 + 640;
originCanvasx8 = originLocalx8 + 1520; originCanvasy8 = originLocaly8 + 640;

targetCanvasx1 = targetLocalx1 + 760; targetCanvasy1 = targetLocaly1 + 640;
targetCanvasx2 = targetLocalx2 + 760; targetCanvasy2 = targetLocaly2 + 640;
targetCanvasx3 = targetLocalx3 + 760; targetCanvasy3 = targetLocaly3 + 640;
targetCanvasx4 = targetLocalx4 + 760; targetCanvasy4 = targetLocaly4 + 640;
targetCanvasx5 = targetLocalx5 + 760; targetCanvasy5 = targetLocaly5 + 640;
targetCanvasx6 = targetLocalx6 + 760; targetCanvasy6 = targetLocaly6 + 640;
targetCanvasx7 = targetLocalx7 + 760; targetCanvasy7 = targetLocaly7 + 640;
targetCanvasx8 = targetLocalx8 + 760; targetCanvasy8 = targetLocaly8 + 640;

%Get the Cartisian Coordinates
%{
originCartisianx1 = originCanvasx1; originCartisiany1 = 2000 - originCanvasy1;
originCartisianx2 = originCanvasx2; originCartisiany2 = 2000 - originCanvasy2;
originCartisianx3 = originCanvasx3; originCartisiany3 = 2000 - originCanvasy3;
originCartisianx4 = originCanvasx4; originCartisiany4 = 2000 - originCanvasy4;

targetCartisianx1 = targetCanvasx1; targetCartisiany1 = 2000 - targetCanvasy1; 
targetCartisianx2 = targetCanvasx2; targetCartisiany2 = 2000 - targetCanvasy2;
targetCartisianx3 = targetCanvasx3; targetCartisiany3 = 2000 - targetCanvasy3; 
targetCartisianx4 = targetCanvasx4; targetCartisiany4 = 2000 - targetCanvasy4;


%Show the Control Points in Canvas
canvas(round(originCanvasy1), round(originCanvasx1), :) = [255, 0, 0];
canvas(round(originCanvasy2), round(originCanvasx2), :) = [255, 0, 0];
canvas(round(originCanvasy3), round(originCanvasx3), :) = [255, 0, 0];
canvas(round(originCanvasy4), round(originCanvasx4), :) = [255, 0, 0];
canvas(round(originCanvasy5), round(originCanvasx5), :) = [255, 0, 0];
canvas(round(originCanvasy6), round(originCanvasx6), :) = [255, 0, 0];
canvas(round(originCanvasy7), round(originCanvasx7), :) = [255, 0, 0];
canvas(round(originCanvasy8), round(originCanvasx8), :) = [255, 0, 0];
canvas(round(targetCanvasy1), round(targetCanvasx1), :) = [255, 0, 0];
canvas(round(targetCanvasy2), round(targetCanvasx2), :) = [255, 0, 0];
canvas(round(targetCanvasy3), round(targetCanvasx3), :) = [255, 0, 0];
canvas(round(targetCanvasy4), round(targetCanvasx4), :) = [255, 0, 0];
canvas(round(targetCanvasy5), round(targetCanvasx5), :) = [255, 0, 0];
canvas(round(targetCanvasy6), round(targetCanvasx6), :) = [255, 0, 0];
canvas(round(targetCanvasy7), round(targetCanvasx7), :) = [255, 0, 0];
canvas(round(targetCanvasy8), round(targetCanvasx8), :) = [255, 0, 0];

%imshow(canvas);
%}

%Construct the Matrix
%Left Matrix
originCtrlPt1 = [originCanvasx1, originCanvasy1, 1, 0, 0, 0, -originCanvasx1*targetCanvasx1, -originCanvasy1*targetCanvasx1; 
                 0, 0, 0, originCanvasx1, originCanvasy1, 1, -originCanvasx1*targetCanvasy1, -originCanvasy1*targetCanvasy1];
originCtrlPt2 = [originCanvasx2, originCanvasy2, 1, 0, 0, 0, -originCanvasx2*targetCanvasx2, -originCanvasy2*targetCanvasx2; 
                 0, 0, 0, originCanvasx2, originCanvasy2, 1, -originCanvasx2*targetCanvasy2, -originCanvasy2*targetCanvasy2];
originCtrlPt3 = [originCanvasx3, originCanvasy3, 1, 0, 0, 0, -originCanvasx3*targetCanvasx3, -originCanvasy3*targetCanvasx3; 
                 0, 0, 0, originCanvasx3, originCanvasy3, 1, -originCanvasx3*targetCanvasy3, -originCanvasy3*targetCanvasy3];
originCtrlPt4 = [originCanvasx4, originCanvasy4, 1, 0, 0, 0, -originCanvasx4*targetCanvasx4, -originCanvasy4*targetCanvasx4; 
                 0, 0, 0, originCanvasx4, originCanvasy4, 1, -originCanvasx4*targetCanvasy4, -originCanvasy4*targetCanvasy4];
%Right Matrix
originCtrlPt5 = [originCanvasx5, originCanvasy5, 1, 0, 0, 0, -originCanvasx5*targetCanvasx5, -originCanvasy5*targetCanvasx5; 
                 0, 0, 0, originCanvasx5, originCanvasy5, 1, -originCanvasx5*targetCanvasy5, -originCanvasy5*targetCanvasy5];
originCtrlPt6 = [originCanvasx6, originCanvasy6, 1, 0, 0, 0, -originCanvasx6*targetCanvasx6, -originCanvasy6*targetCanvasx6; 
                 0, 0, 0, originCanvasx6, originCanvasy6, 1, -originCanvasx6*targetCanvasy6, -originCanvasy6*targetCanvasy6];
originCtrlPt7 = [originCanvasx7, originCanvasy7, 1, 0, 0, 0, -originCanvasx7*targetCanvasx7, -originCanvasy7*targetCanvasx7; 
                 0, 0, 0, originCanvasx7, originCanvasy7, 1, -originCanvasx7*targetCanvasy7, -originCanvasy7*targetCanvasy7];
originCtrlPt8 = [originCanvasx8, originCanvasy8, 1, 0, 0, 0, -originCanvasx8*targetCanvasx8, -originCanvasy8*targetCanvasx8; 
                 0, 0, 0, originCanvasx8, originCanvasy8, 1, -originCanvasx8*targetCanvasy8, -originCanvasy8*targetCanvasy8];
%Middle Matrix
targetCtrlPt1 = [targetCanvasx1; targetCanvasy1];
targetCtrlPt2 = [targetCanvasx2; targetCanvasy2];
targetCtrlPt3 = [targetCanvasx3; targetCanvasy3];
targetCtrlPt4 = [targetCanvasx4; targetCanvasy4];
targetCtrlPt5 = [targetCanvasx5; targetCanvasy5];
targetCtrlPt6 = [targetCanvasx6; targetCanvasy6];
targetCtrlPt7 = [targetCanvasx7; targetCanvasy7];
targetCtrlPt8 = [targetCanvasx8; targetCanvasy8];

%Construct Matrix
leftOriginMatrix = double([originCtrlPt1; originCtrlPt2; originCtrlPt3; originCtrlPt4]);
rigtOriginMatrix = double([originCtrlPt5; originCtrlPt6; originCtrlPt7; originCtrlPt8]);
targetMatrix1 = double([targetCtrlPt1; targetCtrlPt2; targetCtrlPt3; targetCtrlPt4]);
targetMatrix2 = double([targetCtrlPt5; targetCtrlPt6; targetCtrlPt7; targetCtrlPt8]);

%Compute the Transform Matrix
transformMatrix1 = double(reshape([multi(inv(leftOriginMatrix), targetMatrix1); 1], [3,3]))';
transformMatrix2 = double(reshape([multi(inv(rigtOriginMatrix), targetMatrix2); 1], [3,3]))';

Result = uint8(zeros(2000, 2000, 3));

%Get the four Corners of Left Image
leftupp1 = multi(transformMatrix1, [1; 641; 1]);
leftdwn1 = multi(transformMatrix1, [1; 1360; 1]);
rightup1 = multi(transformMatrix1, [480; 641; 1]);
rightdw1 = multi(transformMatrix1, [480; 1360; 1]);
leftuppx1 = round(abs(leftupp1(1) / leftupp1(3)));
leftuppy1 = round(abs(leftupp1(2) / leftupp1(3)));
leftdwnx1 = round(abs(leftdwn1(1) / leftdwn1(3)));
leftdwny1 = round(abs(leftdwn1(2) / leftdwn1(3)));
rightupx1 = round(abs(rightup1(1) / rightup1(3)));
rightupy1 = round(abs(rightup1(2) / rightup1(3)));
rightdwx1 = round(abs(rightdw1(1) / rightdw1(3)));
rightdwy1 = round(abs(rightdw1(2) / rightdw1(3)));
%Get the four Corners of Right Image
leftupp2 = multi(transformMatrix2, [1521; 641; 1]);
leftdwn2 = multi(transformMatrix2, [1521; 1360; 1]);
rightup2 = multi(transformMatrix2, [2000; 641; 1]);
rightdw2 = multi(transformMatrix2, [2000; 1360; 1]);
leftuppx2 = round(abs(leftupp2(1) / leftupp2(3)));
leftuppy2 = round(abs(leftupp2(2) / leftupp2(3)));
leftdwnx2 = round(abs(leftdwn2(1) / leftdwn2(3)));
leftdwny2 = round(abs(leftdwn2(2) / leftdwn2(3)));
rightupx2 = round(abs(rightup2(1) / rightup2(3)));
rightupy2 = round(abs(rightup2(2) / rightup2(3)));
rightdwx2 = round(abs(rightdw2(1) / rightdw2(3)));
rightdwy2 = round(abs(rightdw2(2) / rightdw2(3)));

%Inverse Mapping Left Image
for i = leftuppy1:leftdwny1 + 10
    for j = leftuppx1:rightdwx1
        newpos = multi(inv(transformMatrix1), [j; i; 1]);
        newi = round(abs(newpos(2) / newpos(3)));
        newj = round(abs(newpos(1) / newpos(3)));
        if (newi < 1), newi = 1; end
        if (newj < 1), newj = 1; end
        Result(i, j, :) = canvas(newi, newj, :);
    end
end


%Inverse Mapping Right Image
for i = rightupy2:rightdwy2
    for j = leftuppx2:rightdwx2
        newpos = multi(inv(transformMatrix2), [j; i; 1]);
        newi = round(abs(newpos(2) / newpos(3)));
        newj = round(abs(newpos(1) / newpos(3)));
        if (newi < 1), newi = 1; end
        if (newj < 1), newj = 1; end
        Result(i, j, :) = canvas(newi, newj, :);
    end
end

%The Middle Image Averaging


for i = 641:1360
    for j = 761:1240
        if (Result(i, j, 1) == 0 && Result(i, j, 2) == 0 && Result(i, j, 3) == 0)
            Result(i, j, :) = canvas(i, j, :);
        else
            Result(i, j, :) = uint8((canvas(i, j, :) + Result(i, j, :)) / 2);
        end
    end
end



%The middle Image Paste
%{
for i = 641:1360
    for j = 761:1240
        Result(i, j, :) = canvas(i, j, :);
    end
end
%}
imshow(Result);
imwrite(Result,'average.jpg');

%Read Raw Image Function
function I = readraw(filename, height, width, bpp)
    disp(['Reading Image ' filename ' ... ']);
    %Check File ID Exists or Not
    id = fopen(filename, 'rb');
    if (id == -1)
        disp('The File Dose Not Exist. Press CTRL-C.');
        pause;  
    end
    
    %Get the Image Data From the File
    pixels = fread(id, inf, 'uchar');
    
    %Close File
    fclose(id);
    
    %Initialize the Matrix
    I = zeros(height, width, bpp);
    
    %Construct the Image Matrix
    for i = 1 : height
        for j = 1 : width
            for k = 1 : bpp
                I(i, j, k) = pixels((width * (i - 1) + (j - 1)) * bpp + k);
            end
        end
    end
    I = uint8(I);
end

%Element Wise Multiplication
function c = multi(a, b)
    [p, q] = size(b);
    c = zeros(p, q);
    [m, n] = size(a);
    for i = 1:m
        sum = 0;
        for j = 1:n
            sum = sum + a(i, j) * b(j);
        end
        c(i) = sum;
    end
end
