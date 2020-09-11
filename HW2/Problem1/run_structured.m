%(1) Name : Zhiwei Deng
%(2) USC ID Number : 3669230452
%(3) USC Email : zhiweide@usc.edu
%(4) Submission Date : 02/16/2020

%Use the SE toolbox to Detect Edges
function edges = run_structured(filename, output, mapfile, height, width, thresh)
    clc;
    im = imread(filename);
    %imshow(im)
    tic, edges = SE_Detector(im); toc
    map = 1 - edges;
    %imshow(map)
    result = round(map * 255);
    outfile = binarize(result, thresh);
    imshow(outfile)
    %Back to Previous Folder
    cd ../;
    writemap(map, mapfile);
    writeraw(outfile, output);
    disp('Structured Edges Detection Completed.');
end

%-------------------------------%
%                               %
%       Accessary Functions     %
%                               %
%-------------------------------%

%Set the Running Environment
function setTools()
    %SE Software Toolbox Path
    EDGE_MASTER = './edges-master/';
    addpath(genpath(EDGE_MASTER));
    %Piotr's Computer Vision Matlab Toolbox Path
    TOOL_MASTER = './toolbox-master/';
    addpath(genpath(TOOL_MASTER));
    %Image Path
    IMAGE_PATHS = './Images/';
    addpath(genpath(IMAGE_PATHS));
    %savepath;
    disp('Paths Added Successfuly.');
end

%Structured Edges Detector
function Edges = SE_Detector(image)
    setTools();
    %Set Opts for Training (see edgesTrain.m)
    opts=edgesTrain();                % default options (good settings)
    opts.modelDir='models/';          % model will be in models/forest
    opts.modelFnm='modelBsds';        % model name
    opts.nPos=5e5; opts.nNeg=5e5;     % decrease to speedup training
    opts.useParfor=0;                 % parallelize if sufficient memory
    %Train Edge Detector (~20m/8Gb per tree, proportional to nPos/nNeg)
    tic, model=edgesTrain(opts); toc; % will load model if already trained
    %Set Detection Parameters (can set after training)
    model.opts.multiscale=1;          % for top accuracy set multiscale=1
    model.opts.sharpen=2;             % for top speed set sharpen=0
    model.opts.nTreesEval=10;          % for top speed set nTreesEval=1
    model.opts.nThreads=4;            % max number threads for evaluation
    model.opts.nms=1;                 % set to true to enable nms
    Edges = edgesDetect(image, model);
end

%Binarize Function
function image = binarize(image, thresh)
    length = size(image, 1) * size(image, 2);
    for i = 1 : length
        if (image(i) < thresh)
            image(i) = 0;
        else
            image(i) = 255;
        end
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
	id = fopen(filename, 'wb');
	% Write and close file
    fwrite(id, I', 'uint8');
	fclose(id);
end

%Write Map Image Function
function writemap(I, filename)
	disp(['Write map into '  filename ' ...']);
	% Get file ID
	id = fopen(filename, 'wb');
	% Write and close file
    fwrite(id, I', 'double');
	fclose(id);
end

%Read Map Image Function
function I = readmap(filename, height, width)
    disp(['Reading Image ' filename ' ... ']);
    %Check File ID Exists or Not
    id = fopen(filename, 'rb');
    if (id == -1)
        disp('The File Dose Not Exist. Press CTRL-C.');
        pause;
    end
    %Get the Image Data From the File
    pixels = fread(id, inf, 'double');
    %Close File
    fclose(id);
    %Initialize the Matrix
    I = zeros(height, width);
    %Construct the Image Matrix
    for i = 1 : height
        for j = 1 : width
            I(i, j) = pixels(width * (i - 1) + j);
        end
    end
    I = double(I);
end