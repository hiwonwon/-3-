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
	inputFIle2 = fopen("HSI_result.bmp", "rb");
	fread(&bmpFile, sizeof(BITMAPFILEHEADER), 1, inputFIle2);
	fread(&bmpInfo, sizeof(BITMAPINFOHEADER), 1, inputFIle2);

	int width = bmpInfo.biWidth;
	int height = bmpInfo.biHeight;
	int size = bmpInfo.biSizeImage;
	int bitCnt = bmpInfo.biBitCount;
	int stride = (((bitCnt / 8) * width) + 3) / 4 * 4;
	printf("W: %d(%d)\nH: %d\nS: %d\nD: %d\n", width, stride, height, size, bitCnt);
	//printf("W: %d(%d)\nH: %d\nS: %d\nD: %d\n", width, stride, height, size, bitCnt);

	unsigned char* inputImg1 = NULL, * outputImg = NULL, * inputImg2 = NULL;
	unsigned char* Y1 = NULL, * Y2 = NULL;
	inputImg1 = (unsigned char*)calloc(size, sizeof(unsigned char));
	inputImg2 = (unsigned char*)calloc(size, sizeof(unsigned char));
	outputImg = (unsigned char*)calloc(size, sizeof(unsigned char));
	Y1 = (unsigned char*)calloc(size, sizeof(unsigned char));
	Y2 = (unsigned char*)calloc(size, sizeof(unsigned char));

	outputImg = (unsigned char*)calloc(size, sizeof(unsigned char));
	fread(inputImg1, sizeof(unsigned char), size, inputFIle1);
	fread(inputImg2, sizeof(unsigned char), size, inputFIle2);

	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {

			/*unsigned char I = (unsigned char)((inputImg1[j * stride + 3 * i + 2] + inputImg1[j * stride + 3 * i + 1] + inputImg1[j * stride + 3 * i + 0]) / 3);*/

			unsigned char Diff_Y = (inputImg1[j * stride + 3 * i + 2] - inputImg2[j * stride + 3 * i + 2]) * (inputImg1[j * stride + 3 * i + 2] - inputImg2[j * stride + 3 * i + 2]);
			outputImg[j * stride + 3 * i + 0] = (unsigned char)(Diff_Y > 255 ? 255 : (Diff_Y < 0 ? 0 : Diff_Y));
			outputImg[j * stride + 3 * i + 1] = (unsigned char)(Diff_Y > 255 ? 255 : (Diff_Y < 0 ? 0 : Diff_Y));
			outputImg[j * stride + 3 * i + 2] = (unsigned char)(Diff_Y > 255 ? 255 : (Diff_Y < 0 ? 0 : Diff_Y));

		}
	}
	FILE* outputFile = fopen("Difference.bmp", "wb");
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