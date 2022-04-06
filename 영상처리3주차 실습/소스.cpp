#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <math.h>
int main() {
	BITMAPFILEHEADER bmpFile;
	BITMAPINFOHEADER bmpInfo;
	FILE* inputFIle1 = NULL;
	inputFIle1 = fopen("HeOriginal.bmp", "rb");
	fread(&bmpFile, sizeof(BITMAPFILEHEADER), 1, inputFIle1);
	fread(&bmpInfo, sizeof(BITMAPINFOHEADER), 1, inputFIle1);
	FILE* inputFIle2 = NULL;
	inputFIle2 = fopen("AICenterY_Noise.bmp", "rb");
	fread(&bmpFile, sizeof(BITMAPFILEHEADER), 1, inputFIle2);
	fread(&bmpInfo, sizeof(BITMAPINFOHEADER), 1, inputFIle2);
	int width = bmpInfo.biWidth;
	int height = bmpInfo.biHeight;
	int size = bmpInfo.biSizeImage;
	int bitCnt = bmpInfo.biBitCount;
	int stride = (((bitCnt / 8) * width) + 3) / 4 * 4;




	unsigned char* inputImg1 = NULL, * outputImg = NULL, * inputImg2 = NULL;
	unsigned char* HeImg = NULL, * HeImgHisto = NULL, * OriginHisto = NULL;
	inputImg1 = (unsigned char*)calloc(size, sizeof(unsigned char));
	inputImg2 = (unsigned char*)calloc(size, sizeof(unsigned char));
	outputImg = (unsigned char*)calloc(size, sizeof(unsigned char));
	HeImg = (unsigned char*)calloc(size, sizeof(unsigned char));
	HeImgHisto = (unsigned char*)calloc(size, sizeof(unsigned char));
	OriginHisto = (unsigned char*)calloc(size, sizeof(unsigned char));
	fread(inputImg1, sizeof(unsigned char), size, inputFIle1);
	fread(inputImg2, sizeof(unsigned char), size, inputFIle2);
	unsigned char* Y = NULL;
	Y = (unsigned char*)calloc(size, sizeof(unsigned char));
	

	double hist[256] = { 0 };
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			Y[j * width + i] = inputImg1[j * stride + 3 * i + 0];
			hist[Y[j * width + i]] ++;
			outputImg[j * stride + 3 * i + 0] = Y[j * width + i];
			outputImg[j * stride + 3 * i + 1] = Y[j * width + i];
			outputImg[j * stride + 3 * i + 2] = Y[j * width + i];
		
		}
	}

	double outhist[512] = { 0 };
	double sumhist[256] = { 0 };
	double sumouthist[512] = { 0 };
	double sum = 0;
	for (int i = 0; i < 256; i++) {
		sum = sum + hist[i];
		sumhist[i] = sum;
	}

	for (int j = 0; j < height; j = j + 2) {
		outhist[j] = hist[j / 2] / 20;
		outhist[j + 1] = hist[j / 2] / 20;
		sumouthist[j] = sumhist[j/2]/512;
		sumouthist[j + 1] = sumhist[j/2]/512;
	}
	for (int i = 0; i < 256; i++) {
	printf("sumhist[%d] = %2.lf\n",i, sumhist[i]);
}

	///////////////////////////////////////////////////////
	unsigned char* Y1 = NULL;
	Y1 = (unsigned char*)calloc(size, sizeof(unsigned char));
	unsigned char* Y3 = NULL;
	Y3 = (unsigned char*)calloc(size, sizeof(unsigned char));

	double hist2[256] = { 0 };
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			Y1[j * width + i] = inputImg1[j * stride + 3 * i + 0];
			Y3[j * width + i] = 255 * sumhist[Y1[j * width + i]] / (width * height);
			hist2[Y3[j * width + i]] ++;

			HeImg[j * stride + 3 * i + 0] = Y3[j * width + i];
			HeImg[j * stride + 3 * i + 1] = Y3[j * width + i];
			HeImg[j * stride + 3 * i + 2] = Y3[j * width + i];
		}
	}

	for (int i = 0; i < 256; i++) {
		printf("hist2[%d] = %2.lf\n", i, hist2[i]);
	}

	double outhist2[512] = { 0 };
	double sumhist2[256] = { 0 };
	double sumouthist2[512] = { 0 };
	double sum2 = 0;
	for (int i = 0; i < 256; i++) {
		sum2 = sum2 + hist2[i];
		sumhist2[i] = sum2;
	}

	for (int j = 0; j < height; j = j + 2) {
		outhist2[j] = hist2[j / 2] / 20;
		outhist2[j + 1] = hist2[j / 2] / 20;
		sumouthist2[j] = sumhist2[j / 2] / 512;
		sumouthist2[j + 1] = sumhist2[j / 2] / 512;
	}

	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			if (j <= outhist[i]) {
				OriginHisto[j * stride + 3 * i + 0] = 0;
				OriginHisto[j * stride + 3 * i + 1] = 0;
				OriginHisto[j * stride + 3 * i + 2] = 0;
			}
			if (j >= outhist[i]) {
				OriginHisto[j * stride + 3 * i + 0] = 255;
				OriginHisto[j * stride + 3 * i + 1] = 255;
				OriginHisto[j * stride + 3 * i + 2] = 255;
			}
		}
	}
	
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			if (j <= outhist2[i]) {
				HeImgHisto[j * stride + 3 * i + 0] = 0;
				HeImgHisto[j * stride + 3 * i + 1] = 0;
				HeImgHisto[j * stride + 3 * i + 2] = 0;
			}
			if (j >= outhist2[i]) {
				HeImgHisto[j * stride + 3 * i + 0] = 255;
				HeImgHisto[j * stride + 3 * i + 1] = 255;
				HeImgHisto[j * stride + 3 * i + 2] = 255;
			}
		}
	}




	
	FILE* outputFile = fopen("Output.bmp", "wb");
	fwrite(&bmpFile, sizeof(BITMAPFILEHEADER), 1, outputFile);
	fwrite(&bmpInfo, sizeof(BITMAPINFOHEADER), 1, outputFile);
	fwrite(outputImg, sizeof(unsigned char), size, outputFile);

	FILE* outputFile1 = fopen("HeImg.bmp", "wb");
	fwrite(&bmpFile, sizeof(BITMAPFILEHEADER), 1, outputFile1);
	fwrite(&bmpInfo, sizeof(BITMAPINFOHEADER), 1, outputFile1);
	fwrite(HeImg, sizeof(unsigned char), size, outputFile1);

	FILE* outputFile2 = fopen("HeImgHisto.bmp", "wb");
	fwrite(&bmpFile, sizeof(BITMAPFILEHEADER), 1, outputFile2);
	fwrite(&bmpInfo, sizeof(BITMAPINFOHEADER), 1, outputFile2);
	fwrite(HeImgHisto, sizeof(unsigned char), size, outputFile2);

	FILE* outputFile3 = fopen("OriginHisto.bmp", "wb");
	fwrite(&bmpFile, sizeof(BITMAPFILEHEADER), 1, outputFile3);
	fwrite(&bmpInfo, sizeof(BITMAPINFOHEADER), 1, outputFile3);
	fwrite(OriginHisto, sizeof(unsigned char), size, outputFile3);


	free(outputImg);
	fclose(outputFile);

	free(inputImg1);
	fclose(inputFIle1);
	free(inputImg2);
	fclose(inputFIle2);
	return 0;
}