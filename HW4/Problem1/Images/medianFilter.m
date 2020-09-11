im = imread("result_14D_41.jpg");
k=medfilt2(im,[15,15]);
imshow(k);
imwrite(k, 'median_27.jpg');