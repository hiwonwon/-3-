#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <math.h>
#include <cstdlib>
int main() {
	BITMAPFILEHEADER bmpFile;
	BITMAPINFOHEADER bmpInfo;

	FILE* inputFIle1 = NULL;
	inputFIle1 = fopen("AICenterY.bmp", "rb");
	fread(&bmpFile, sizeof(BITMAPFILEHEADER), 1, inputFIle1);
	fread(&bmpInfo, sizeof(BITMAPINFOHEADER), 1, inputFIle1);

	int width = bmpInfo.biWidth;
	int height = bmpInfo.biHeight;
	int size = bmpInfo.biSizeImage;
	int bitCnt = bmpInfo.biBitCount;
	int stride = (((bitCnt / 8) * width) + 3) / 4 * 4;
	printf("W: %d(%d)\nH: %d\nS: %d\nD: %d\n", width, stride, height, size, bitCnt);

	unsigned char* inputImg1 = NULL, * outputImg = NULL;
	inputImg1 = (unsigned char*)calloc(size, sizeof(unsigned char));
	outputImg = (unsigned char*)calloc(size, sizeof(unsigned char));
	fread(inputImg1, sizeof(unsigned char), size, inputFIle1);

	int prob = 55;
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {

			unsigned char Y = 0.299 * inputImg1[j * stride + 3 * i + 2] + 0.587 * inputImg1[j * stride + 3 * i + 1] + 0.114 * inputImg1[j * stride + 3 * i + 0];
			if ((rand() % prob) == 0)Y = 255;
			else if ((rand() % prob) == 1)Y = 0;
			else Y = Y;

			outputImg[j * stride + 3 * i + 0] = (unsigned char)(Y > 255 ? 255 : (Y < 0 ? 0 : Y));
			outputImg[j * stride + 3 * i + 1] = (unsigned char)(Y > 255 ? 255 : (Y < 0 ? 0 : Y));
			outputImg[j * stride + 3 * i + 2] = (unsigned char)(Y > 255 ? 255 : (Y < 0 ? 0 : Y));


		}
	}





	FILE* outputFile = fopen("saltPepper.bmp", "wb");
	fwrite(&bmpFile, sizeof(BITMAPFILEHEADER), 1, outputFile);
	fwrite(&bmpInfo, sizeof(BITMAPINFOHEADER), 1, outputFile);
	fwrite(outputImg, sizeof(unsigned char), size, outputFile);

	free(outputImg);
	free(inputImg1);
	fclose(inputFIle1);
	fclose(outputFile);



	return 0;
}