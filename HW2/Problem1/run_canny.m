%(1) Name : Zhiwei Deng
%(2) USC ID Number : 3669230452
%(3) USC Email : zhiweide@usc.edu
%(4) Submission Date : 02/16/2020

function run_canny(filename, output, height, width, lower, upper)
    im = imread(filename);
    temp = canny(im, lower, upper);
    result = zeros(height, width);
    for i = 1 : height
        for j = 1 : width
            if (temp(i,j) == 1)
                result(i,j) = 0;
            else
                result(i,j) = 255;
            end
        end
    end
    imshow(result)
    writeraw(result, output);
end


function result = canny(image, lower, upper)
    bpp = size(image, 3);
    %Check Input Image
    if (bpp == 3)
        image = color2gray(image);
    end
    
    result = edge(image, 'canny', [lower, upper]);
end

function gray = color2gray(image)
    height = size(image, 1);
    width = size(image, 2);
    bpp = size(image, 3);
    r = image(:, :, 1);
    g = image(:, :, 2);
    b = image(:, :, 3);
    
    %Check Input Image
    if (bpp ~= 3)
        disp('The Input Image is Not Colorful.');
    end
    disp('Grayscale Completed.');
    %Construct the Gray Image
    gray = zeros(height, width);
    
    %Loop the pixels
    for i = 1 : height * width
        gray(i) = uint8(r(i) * 0.2989 + g(i) * 0.5870 + b(i) * 0.1140);
    end
end

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

%Write Raw Image Function
function writeraw(I, filename)
	disp(['Write image into '  filename ' ...']);

	% Get file ID
	id = fopen(filename,'wb');
    
	% Write and close file
    fwrite(id, I', 'uint8');
	fclose(id);
end