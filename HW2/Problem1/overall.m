%(1) Name : Zhiwei Deng
%(2) USC ID Number : 3669230452
%(3) USC Email : zhiweide@usc.edu
%(4) Submission Date : 02/16/2020
im =  readraw('Images/020_030.raw', 321, 481, 1);
ed = 1 - im / 255;
params = {'out', '', 'thrs', 1, 'maxDist', .0075, 'thin', 1};
[T, CR, SR, CP, SP, V] = edgesEvalImg(ed, 'Images/Gallery_GT.mat', params);
P = CP ./ max(eps,SP);
R = CR ./ max(eps,SR);
F = 2 * P .* R ./ max(eps, P+R);
[F_score, index] = max(F)

function seperate(GT, filetype)
    for i = 1 : 5
        cell = GT.groundTruth{i};
        groundTruth{1} = cell;
        string = "Images/" + filetype + num2str(i) + ".mat";
        save(string,'groundTruth');
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