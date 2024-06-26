#include <math.h>
#include <stdio.h>

// Function to convert CCT (Correlated Color Temperature) to CIE 1931 xy values
void CCT_to_xy(int CCT, double *x, double *y)
{
	double X, Y, Z;
	double x_temp, y_temp;

	if (CCT <= 4000)
		x_temp = -0.2661239 * pow(10, 9) / pow(CCT, 3) - 0.2343589 * pow(10, 6) / pow(CCT, 2) + 0.8776956 * pow(10, 3) / CCT + 0.179910;
	else
		x_temp = -3.0258469 * pow(10, 9) / pow(CCT, 3) + 2.1070379 * pow(10, 6) / pow(CCT, 2) + 0.2226347 * pow(10, 3) / CCT + 0.240390;

	if (CCT <= 2222)
		y_temp = -1.1063814 * pow(x_temp, 3) - 1.34811020 * pow(x_temp, 2) + 2.18555832 * x_temp - 0.20219683;
	else if (CCT <= 4000)
		y_temp = -0.9549476 * pow(x_temp, 3) - 1.37418593 * pow(x_temp, 2) + 2.09137015 * x_temp - 0.16748867;
	else
		y_temp = 3.0817580 * pow(x_temp, 3) - 5.87338670 * pow(x_temp, 2) + 3.75112997 * x_temp - 0.37001483;

	// Assuming Y (luminance) = 1 for simplicity
	Y = 1.0;
	X = Y / y_temp * x_temp;
	Z = Y / y_temp * (1 - x_temp - y_temp);

	// Convert XYZ to xy
	*x = X / (X + Y + Z);
	*y = Y / (X + Y + Z);
}

/**
 * @brief main func for test the CCT to xy function generated by Cursor 
 * compare result to https://www.waveformlighting.com/tech/calculate-cie-1931-xy-coordinates-from-cct/
 *
 * @return 
 */
int main()
{
	double x, y;

	CCT_to_xy(3000, &x, &y);
	printf("x: %f, y: %f\n", x, y);

	return 0;
}
