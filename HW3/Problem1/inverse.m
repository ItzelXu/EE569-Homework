%(1) Name : Zhiwei Deng
%(2) USC ID Number : 3669230452
%(3) USC Email : zhiweide@usc.edu
%(4) Submission Date : 03/03/2020

function rcvr_img = inverse(im)
    rcvr_img = uint8(zeros(512, 512, 3));
    %Warping
    for i = 1:512
        for j = 1:512
            %Check the Distance of the Pixels
            dist = sqrt((i-256)^2+(j-256)^2);
            %Get the Region and Transformed Coordinate
            region = getRegion(i, j);
            [x, y] = getCoord(region, i, j);
            %Compute the Angle Cosine and Sine
            c_theta = x / dist;
            s_theta = y / dist;
            %Compute the New Locations
            [new_x, new_y] = computeLocation(c_theta, s_theta, x, y, region);
            %Do the Bilinear Interpolation
            value = bilinear(new_x, new_y, region, im);
            rcvr_img(j,i,:) = value;
        end
    end
    %Boundaries
    for i = 1:511
        rcvr_img(i,511,:) = rcvr_img(i,510,:);
        rcvr_img(i,512,:) = rcvr_img(i,510,:);
    end
    for j = 1:511
        rcvr_img(511,j,:) = rcvr_img(510,j,:);
        rcvr_img(512,j,:) = rcvr_img(510,j,:);
    end
end

%Get the Region of the Pixels
function region = getRegion(i, j)
    %Cross Lines
    if (i == 256 || j == 256), region = 0; end
    %Left Upper Corner
    if (i < 256 && j < 256), region = 1; end
    %Right Upper Corner
    if (i < 256 && j > 256), region = 2; end
    %Left Down Corner
    if (i > 256 && j < 256), region = 3; end
    %Right Down Corner
    if (i > 256 && j > 256), region = 4; end
    return;
end

%Get the Coordinates
function [x, y] = getCoord(region, i, j)
    %Cross Lines
    if (region == 0)
        x = i;
        y = j;
    end
    %Left Upper Corner
    if (region == 1)
        x = 256 - i;
        y = 256 - j;
    end
    %Right Upper Corner
    if (region == 2)
        x = 256 - i;
        y = j - 256;
    end
    %Left Down Corner
    if (region == 3)
        x = i - 256;
        y = 256 - j;
    end
    %Right Down Corner
    if (region == 4)
        x = i - 256;
        y = j - 256;
    end
    return;
end

%Get the New Location
function [new_x, new_y] = computeLocation(c_theta, s_theta, x, y, region)
    if (c_theta > sqrt(2)/2)
        total = 256 / c_theta;
        new_x = x * 256 / total;
        new_y = y * 256 / total;
    else
        total = 256 / s_theta;
        new_x = x * 256 / total;
        new_y = y * 256 / total;
    end
    %Get the Original Coordinate
    %Left Upper
    if (region == 0)
        new_x = x;
        new_y = y;
    end
    if (region == 1)
        new_x = 256 - new_x;
        new_y = 256 - new_y;
    end
    %Right Upper
    if (region == 2)
        new_x = 256 - new_x;
        new_y = new_y + 256;
    end
    %Left Down
    if (region == 3)
        new_x = new_x + 256;
        new_y = 256 - new_y;
    end
    %Right Down
    if (region == 4)
        new_x = new_x + 256;
        new_y = new_y + 256;
    end
    %Bound
    if (new_x < 1), new_x = 1; end
    if (new_y < 1), new_y = 1; end
    if (new_x > 512), new_x = 512; end
    if (new_y > 512), new_y = 512; end
end

%Blinear Interpolation
function value = bilinear(src_x, src_y, region, im)
    if (region == 0)
        value = im(src_y, src_x, :);
        return;
    end
    floor_x = floor(src_x);
	floor_y = floor(src_y);
	top_x = min(floor_x + 1, 512);
	top_y = min(floor_y + 1, 512);
    value0 = (top_x - src_x) * im(floor_y, floor_x, :) + (src_x - floor_x) * im(floor_y, top_x, :);
	value1 = (top_x - src_x) * im(top_y, floor_x, :) + (src_x - floor_x) * im(top_y, top_x, :);
    value = int64((top_y - src_y) * value0 + (src_y - floor_y) * value1);
end