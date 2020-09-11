%(1) Name : Zhiwei Deng
%(2) USC ID Number : 3669230452
%(3) USC Email : zhiweide@usc.edu
%(4) Submission Date : 02/16/2020

%Use the SE toolbox to Evaluate the Results
function run_evaluate(filetype, edgetype, thrs)
    clc;
    height = 321;
    width = 481;
    if (filetype == "dogs")
        GroundTruth = "Images/Dogs_GT.mat";
        filename = "Images/Dogs_";
    end
    if (filetype == "gallery")
        GroundTruth = "Images/Gallery_GT.mat";
        filename = "Images/Gallery_";
    end
    %Sobel Kernel
    if (edgetype == "SB")
        filename = filename + "SB_Map.raw";
        map = double(readraw(filename, height, width, 1)) / 255;
        %imshow(map);
    end
    %Canny Kernel
    if (edgetype == "CA")
        filename = filename + "CA_Map.raw";
        map = 1 - double(readraw(filename, height, width, 1)) / 255;
        imshow(map);
    end
    %Structured Edge
    if (edgetype == "SE")
        filename = filename + "SE_Map.raw";
        %Read Files
        map = 1 - readmap(filename, height, width);
        imshow(map);
    end
    %Store the R P F Thresholds
    thresh = zeros(5, thrs);
    cntR = zeros(5, thrs); sumR = zeros(5, thrs);
    cntP = zeros(5, thrs); sumP = zeros(5, thrs);
    P = zeros(5, thrs); R = zeros(5, thrs); F = zeros(5, thrs);
    GT = load(GroundTruth);
    %Seperate Each GroundTruth Files
    seperate(GT, filetype);
    params = {'out', '', 'thrs', thrs, 'maxDist', .0075, 'thin', 1};
    for i = 1 : 5
        string = "Images/" + filetype + num2str(i) + ".mat";
        [T, CR, SR, CP, SP, V] = edgesEvalImg(map, string, params);
        thresh(i,:) = T'; cntR(i,:) = CR'; sumR(i,:) = SR';
        cntP(i,:) = CP'; sumP(i,:) = SP';
        %Compute P,R,F
        [R(i,:), P(i,:), F(i,:)] = computeRPF(cntR(i,:),sumR(i,:),cntP(i,:),sumP(i,:));
        [R_mean, P_mean, F_mean] = mean_thresh(R(i,:), P(i,:));
        disp(['GroudTruth ' num2str(i) ' R_mean = ' num2str(R_mean) ' P_mean = ' num2str(P_mean) ' F_mean = ' num2str(F_mean)]);
    end
    
    %Mean of GroundTruths
    Pre_mean = (P(1,:) + P(2,:) + P(3,:) + P(4,:) + P(5,:)) / 5;
    Rec_mean = (R(1,:) + R(2,:) + R(3,:) + R(4,:) + R(5,:)) / 5;
    Fsc_mean = 2 * Pre_mean .* Rec_mean ./ max(eps, Pre_mean+Rec_mean);
    [F_score, index] = max(Fsc_mean)
    Pre_mean(index)
    Rec_mean(index)
    %plot(thresh(1,:), Fsc_mean);
    %title("Mean F-measure to Thresh")
end

%Threshold Means
function [R_mean, P_mean, F_mean] = mean_thresh(R1, P1)
    R_mean = mean(R1);
    P_mean = mean(P1);
    F_mean = 2 * P_mean * R_mean / max(eps,P_mean+R_mean);
end

%Seperate the GT
function seperate(GT, filetype)
    for i = 1 : 5
        cell = GT.groundTruth{i};
        groundTruth{1} = cell;
        string = "Images/" + filetype + num2str(i) + ".mat";
        save(string,'groundTruth');
    end
end

%Compute the Recall, Precision, F-Score
function [R,P,F] = computeRPF(cntR,sumR,cntP,sumP)
    R= cntR ./ max(eps,sumR);
    P= cntP ./ max(eps,sumP);
    F= 2 * P .* R ./ max(eps,P+R);
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

