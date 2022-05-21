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


	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {

			unsigned char Y = 0.299 * inputImg1[j * stride + 3 * i + 2] + 0.587 * inputImg1[j * stride + 3 * i + 1] + 0.114 * inputImg1[j * stride + 3 * i + 0];
			/*unsigned char Cb = -0.169 * inputImg1[j * stride + 3 * i + 2] - 0.331 * inputImg1[j * stride + 3 * i + 1] + 0.500 * inputImg1[j * stride + 3 * i + 0];
			unsigned char Cr = 0.500 * inputImg1[j * stride + 3 * i + 2] - 0.419 * inputImg1[j * stride + 3 * i + 1] - 0.0813 * inputImg1[j * stride + 3 * i + 0];


			unsigned char R = (unsigned char)( Y + 1.402 * Cr);
			unsigned char G = (unsigned char)(Y - 0.714 * Cr - 0.344 * Cb);
			unsigned char B = (unsigned char)(Y + 1.772 * Cb);*/

			outputImg[j * stride + 3 * i + 0] = (unsigned char)(Y > 255 ? 255 : (Y < 0 ? 0 : Y));
			outputImg[j * stride + 3 * i + 1] = (unsigned char)(Y > 255 ? 255 : (Y < 0 ? 0 : Y));
			outputImg[j * stride + 3 * i + 2] = (unsigned char)(Y > 255 ? 255 : (Y < 0 ? 0 : Y));
			if (j < 100 && i < 100)
			{
				outputImg[j * stride + 3 * i + 0] = 0;
				outputImg[j * stride + 3 * i + 1] = 0;
				outputImg[j * stride + 3 * i + 2] = 0;
			}
			if (j > 400 && i >400)
			{
				outputImg[j * stride + 3 * i + 0] = 255;
				outputImg[j * stride + 3 * i + 1] = 255;
				outputImg[j * stride + 3 * i + 2] = 255;
			}



		}
	}





	FILE* outputFile = fopen("Result.bmp", "wb");
	fwrite(&bmpFile, sizeof(BITMAPFILEHEADER), 1, outputFile);
	fwrite(&bmpInfo, sizeof(BITMAPINFOHEADER), 1, outputFile);
	fwrite(outputImg, sizeof(unsigned char), size, outputFile);

	free(outputImg);
	free(inputImg1);
	fclose(inputFIle1);
	fclose(outputFile);



	return 0;
}