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
	inputFIle2 = fopen("AIcenterY_Noise.bmp", "rb");
	fread(&bmpFile, sizeof(BITMAPFILEHEADER), 1, inputFIle2);
	fread(&bmpInfo, sizeof(BITMAPINFOHEADER), 1, inputFIle2);

	int width = bmpInfo.biWidth;
	int height = bmpInfo.biHeight;
	int size = bmpInfo.biSizeImage;
	int bitCnt = bmpInfo.biBitCount;
	int stride = (((bitCnt / 8) * width) + 3) / 4 * 4;
	/*printf("W: %d(%d)\nH: %d\nS: %d\nD: %d\n", width, stride, height, size, bitCnt);*/

	unsigned char* inputImg1 = NULL, * inputImg2 = NULL;
	unsigned char* Y1 = NULL, * Y2 = NULL;
	inputImg1 = (unsigned char*)calloc(size, sizeof(unsigned char));
	inputImg2 = (unsigned char*)calloc(size, sizeof(unsigned char));
	Y1 = (unsigned char*)calloc(size, sizeof(unsigned char));
	Y2 = (unsigned char*)calloc(size, sizeof(unsigned char));
	fread(inputImg1, sizeof(unsigned char), size, inputFIle1);
	fread(inputImg2, sizeof(unsigned char), size, inputFIle2);

	double mse = 0, psnr;
	int Err;

	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {


			Y1[j * width + i] = inputImg1[j * stride + 3 * i + 0];
			Y2[j * width + i] = inputImg2[j * stride + 3 * i + 0];



			mse += (double)((Y2[j * width + i] - Y1[j * width + i]) * (Y2[j * width + i] - Y1[j * width + i]));

		}
	}
	mse /= (width * height);
	psnr = mse != 0.0 ? 10.0 * log10(255 * 255 / mse) : 99.99;
	printf("MSE = %.2lf\nPSNR = %.2lf dB\n", mse, psnr);





;
	free(inputImg1);
	fclose(inputFIle1);
	free(inputImg2);
	fclose(inputFIle2);


	return 0;
}