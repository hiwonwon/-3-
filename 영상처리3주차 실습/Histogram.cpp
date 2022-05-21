#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <math.h>
int main() {
	BITMAPFILEHEADER bmpFile;
	BITMAPINFOHEADER bmpInfo;
	FILE* inputFIle1 = NULL;
	inputFIle1 = fopen("AICenterY.bmp", "rb");
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
	inputImg1 = (unsigned char*)calloc(size, sizeof(unsigned char));
	inputImg2 = (unsigned char*)calloc(size, sizeof(unsigned char));
	outputImg = (unsigned char*)calloc(size, sizeof(unsigned char));
	fread(inputImg1, sizeof(unsigned char), size, inputFIle1);
	fread(inputImg2, sizeof(unsigned char), size, inputFIle2);
	unsigned char* Y = NULL;
	Y = (unsigned char*)calloc(size, sizeof(unsigned char));
	double hist[256] = { 0 };
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			Y[j * width + i] = inputImg1[j * stride + 3 * i + 0];
			hist[Y[j * width + i]] ++;
		}
	}

	double outhist[512] = { 0 };
	double sumhist[512] = { 0 };
	double sum = 0;
	for (int j = 0; j < height; j = j + 2) {
		outhist[j] = hist[j] / 20;
		outhist[j + 1] = hist[j] / 20;
		//printf("%.2lf %.2lf\n", outhist[j], outhist[j + 1]);
		outhist[j] = hist[j / 2] / 20;
		outhist[j + 1] = hist[j / 2] / 20;
		sum += sum + outhist[j];
		sumhist[j] = sum / 512;
		sumhist[j + 1] = sum / 512;


	}
	for (int j = 0; j < height; j++) {
		printf("%.2lf\n", outhist[j]);
	}


	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			if (j <= outhist[i]) {
				outputImg[j * stride + 3 * i + 0] = 0;
				outputImg[j * stride + 3 * i + 1] = 0;
				outputImg[j * stride + 3 * i + 2] = 0;
			}
			if (j >= outhist[i]) {
				outputImg[j * stride + 3 * i + 0] = 255;
				outputImg[j * stride + 3 * i + 1] = 255;
				outputImg[j * stride + 3 * i + 2] = 255;
			}
		}
	}
	FILE* outputFile = fopen("Output.bmp", "wb");
	fwrite(&bmpFile, sizeof(BITMAPFILEHEADER), 1, outputFile);
	fwrite(&bmpInfo, sizeof(BITMAPINFOHEADER), 1, outputFile);
	fwrite(outputImg, sizeof(unsigned char), size, outputFile);
	free(outputImg);
	free(inputImg1);
	fclose(inputFIle1);
	free(inputImg2);
	fclose(inputFIle2);
	fclose(outputFile);
	return 0;
}