#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <math.h>
int main() {
	BITMAPFILEHEADER bmpFile;
	BITMAPINFOHEADER bmpInfo;
	FILE* inputFIle1 = NULL;
	inputFIle1 = fopen("AIcenterY.bmp", "rb");
	fread(&bmpFile, sizeof(BITMAPFILEHEADER), 1, inputFIle1);
	fread(&bmpInfo, sizeof(BITMAPINFOHEADER), 1, inputFIle1);


	int width = bmpInfo.biWidth;
	int height = bmpInfo.biHeight;
	int size = bmpInfo.biSizeImage;
	int bitCnt = bmpInfo.biBitCount;
	int stride = (((bitCnt / 8) * width) + 3) / 4 * 4;
	printf("W: %d(%d)\nH: %d\nS: %d\nD: %d\n", width, stride, height, size, bitCnt);

	int ratio2 = 2;
	int width2_2 = bmpInfo.biWidth << ratio2;
	int height2_2 = bmpInfo.biHeight << ratio2;
	int stride2_2 = (((bitCnt / 8) * width2_2) + 3) / 4 * 4;
	int size2_2 = stride2_2 * height2_2;
	printf("W: %d(%d)\nH: %d\nS: %d\nD: \n", width2_2, stride2_2, height2_2, size2_2);

	unsigned char* inputImg1 = NULL, * outputImg2 = NULL;
	inputImg1 = (unsigned char*)calloc(size, sizeof(unsigned char));
	fread(inputImg1, sizeof(unsigned char), size, inputFIle1);

	outputImg2 = (unsigned char*)calloc(size2_2, sizeof(unsigned char));
	


	unsigned char* Y1_2 = NULL;
	Y1_2 = (unsigned char*)calloc(size, sizeof(unsigned char));

	unsigned char* Y2_2 = NULL;
	Y2_2 = (unsigned char*)calloc(size2_2, sizeof(unsigned char));


	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			Y1_2[j * width + i] = inputImg1[j * stride + 3 * i + 0];

			for (int a = 0; a < 4; a++) {
				for (int b = 0; b < 4; b++) {
					outputImg2[(4 * j + a)  * stride2_2 + 3 * (4 * i + b) + 0] = Y1_2[j * width + i];
					outputImg2[(4 * j + a)  * stride2_2 + 3 * (4 * i + b) + 1] = Y1_2[j * width + i];
					outputImg2[(4 * j + a)  * stride2_2 + 3 * (4 * i + b) + 2] = Y1_2[j * width + i];
				}
			}
			
			/*
			outputImg2[2 * j * stride2_2 + 3 * 2 * i + 0] = Y1_2[j * width + i];
			outputImg2[2 * j * stride2_2 + 3 * 2 * i + 1] = Y1_2[j * width + i];
			outputImg2[2 * j * stride2_2 + 3 * 2 * i + 2] = Y1_2[j * width + i];

			outputImg2[(2 * j + 1) * stride2_2 + 3 * 2 * i + 0] = Y1_2[j * width + i];
			outputImg2[(2 * j + 1) * stride2_2 + 3 * 2 * i + 1] = Y1_2[j * width + i];
			outputImg2[(2 * j + 1) * stride2_2 + 3 * 2 * i + 2] = Y1_2[j * width + i];

			outputImg2[2 * j * stride2_2 + 3 * (2 * i + 1) + 0] = Y1_2[j * width + i];
			outputImg2[2 * j * stride2_2 + 3 * (2 * i + 1) + 1] = Y1_2[j * width + i];
			outputImg2[2 * j * stride2_2 + 3 * (2 * i + 1) + 2] = Y1_2[j * width + i];

			outputImg2[(2 * j + 1) * stride2_2 + 3 * (2 * i + 1) + 0] = Y1_2[j * width + i];
			outputImg2[(2 * j + 1) * stride2_2 + 3 * (2 * i + 1) + 1] = Y1_2[j * width + i];
			outputImg2[(2 * j + 1) * stride2_2 + 3 * (2 * i + 1) + 2] = Y1_2[j * width + i];
			*/
		}
	}

	FILE* outputFile2 = fopen("upsampling.bmp", "wb");
	bmpInfo.biWidth = width2_2;
	bmpInfo.biHeight = height2_2;
	bmpInfo.biSizeImage = size2_2;
	bmpFile.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + size2_2;
	fwrite(&bmpFile, sizeof(BITMAPFILEHEADER), 1, outputFile2);
	fwrite(&bmpInfo, sizeof(BITMAPINFOHEADER), 1, outputFile2);
	fwrite(outputImg2, sizeof(unsigned char), size2_2, outputFile2);

	free(outputImg2);
	fclose(outputFile2);
	free(inputImg1);
	fclose(inputFIle1);
	return 0;
}