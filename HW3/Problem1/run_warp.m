%(1) Name : Zhiwei Deng
%(2) USC ID Number : 3669230452
%(3) USC Email : zhiweide@usc.edu
%(4) Submission Date : 03/03/2020

bb8 = readraw('Images/bb8.raw', 512, 512, 3);
hedwig = readraw('Images/hedwig.raw', 512, 512, 3);
raccoon = readraw('Images/raccoon.raw', 512, 512, 3);

warp_img0 = warp(bb8);
rcvr_img0 = inverse(warp_img0);
warp_img1 = warp(hedwig);
rcvr_img1 = inverse(warp_img1);
warp_img2 = warp(raccoon);
rcvr_img2 = inverse(warp_img2);

%imshow(warp_img);
imwrite(warp_img0,'bb8warpr.jpg');
imwrite(warp_img1,'hedwigwarpr.jpg');
imwrite(warp_img2,'raccoonwarpr.jpg');
imwrite(rcvr_img0,'bb8rcvr.jpg');
imwrite(rcvr_img1,'hedwigrcvr.jpg');
imwrite(rcvr_img2,'raccoonrcvr.jpg');

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