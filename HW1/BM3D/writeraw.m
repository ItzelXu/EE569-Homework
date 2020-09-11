%(1) Name : Zhiwei Deng
%(2) USC ID Number : 3669230452
%(3) USC Email : zhiweide@usc.edu
%(4) Submission Date : 01/28/2020

function writeraw(I, filename)
%writeraw - write RAW format grey scale image file 
% Usage :	writeraw(G, filename)
% G:		input image matrix
% filename: file name of the file to write to disk
% count:	return value, the elements written to file

	disp(['Write image into '  filename ' ...']);

	% Get file ID
	id = fopen(filename,'wb');

	% Write and close file
    fwrite(id, I, 'uint8');
	fclose(id);
end %function