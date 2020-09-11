%(1) Name : Zhiwei Deng
%(2) USC ID Number : 3669230452
%(3) USC Email : zhiweide@usc.edu
%(4) Submission Date : 01/28/2020

%Read Raw Image Function
function I = readraw(filename, height, width)
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
    I = zeros(height, width);
    
    %Construct the Image Matrix
    I(1:height * width) = pixels(1:height * width);
end