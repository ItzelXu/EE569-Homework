%(1) Name : Zhiwei Deng
%(2) USC ID Number : 3669230452
%(3) USC Email : zhiweide@usc.edu
%(4) Submission Date : 01/28/2020

%The BM3D function and deopendencies are from Online Source
%http://www.cs.tut.fi/~foi/GCF-BM3D/ Website

%Run the BM3D Algorithm
function run_BM3D(filename, height, width, sigma)
    addpath('Lib')
    y = readraw(filename, height, width) / 255;
    y_ori = readraw('Images/Corn_gray.raw', 320, 320) / 255;
    y_est = BM3D(y, sigma);
    y_int = uint8(y_est * 255);
    output = 'Images/Corn_BM3D.raw';
    writeraw(y_int, output);
    PSNR = getPSNR(y_ori, y_est)
end