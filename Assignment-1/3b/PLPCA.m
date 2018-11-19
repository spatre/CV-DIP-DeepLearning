%% Initialization
%
%
clear all
close all

sigma=25;
randn('seed', 2);
%ima = double(imread('data/house.png'));

	% Get file ID for file
	fid=fopen('house.raw','rb');

	% Check if file exists
	if (fid == -1)
	  	error('can not open input image file press CTRL-C to exit \n');
	  	pause
	end

	% Get all the pixels from the image
	pixel = fread(fid, inf, 'uchar');

	% Close file
	fclose(fid);

	% Calculate length/width, assuming image is square
	[Y X]=size(pixel);
	Size=(Y*X);
	N=sqrt(Size);

	% Construct matrix
	ima = zeros(N,N);

	% Write pixels into matrix
	ima(1:Size) = pixel(1:Size);

	% Transpose matrix, to orient it properly
	ima = ima';
   
%ima_nse = readraw(House_noisy.raw);

	

	% Get file ID for file
	fid=fopen('House_noisy.raw','rb');

	% Check if file exists
	if (fid == -1)
	  	error('can not open input image file press CTRL-C to exit \n');
	  	pause
	end

	% Get all the pixels from the image
	pixel = fread(fid, inf, 'uchar');

	% Close file
	fclose(fid);

	% Calculate length/width, assuming image is square
	[Y X]=size(pixel);
	Size=(Y*X);
	N=sqrt(Size);

	% Construct matrix
	ima_nse = zeros(N,N);

	% Write pixels into matrix
	ima_nse(1:Size) = pixel(1:Size);

	% Transpose matrix, to orient it properly
	ima_nse = ima_nse';


figure('Position',[100 100  800 800]);
plotimage(ima_nse);
title(sprintf('Noisy: \n  PSNR %.2f', psnr(ima, ima_nse)));
set(get(gca,'Title'),'FontSize',12);

%% LOCAL VERSION: PLPCA.m
[WP factor_thr hW] = PLPCA_best_params(sigma);
threshold = factor_thr * sigma;
% Shift/Redudancy  parameter for the searching zone.
delta = hW; %< 2*hW+WP;
func_thresholding = @(ima_ppca) ...
    hardthresholding(ima_ppca, threshold, sigma);
local_time=tic;
%% Patchization step 
ima_patchs = spatial_patchization(ima_nse, WP);
%% Local PCA denoising step
ima_patchs_fil = PLPCA_denoising(ima_patchs, func_thresholding, ...
                                 hW, delta);
%% Uniform reprojection step
ima_fil_PLPCA = reprojection_UWA(ima_patchs_fil);
local_time=toc(local_time);
%% Display

figure('Position',[100 100  800 800])
plotimage(ima_fil_PLPCA);
title(sprintf('PLPCA: \n  PSNR %.2f', psnr(ima, ima_fil_PLPCA)));
set(get(gca,'Title'),'FontSize',12);

sprintf('PLPCA:\n PSNR: %.2f dB \n Computing Time: %.2f s.', ...
    psnr(ima, ima_fil_PLPCA),local_time)