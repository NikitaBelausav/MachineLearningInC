#include <stdio.h>
#include <string.h>
#include <stdlib.h>

double** matrixMultiplication(double** x, int rows1, int columns1, double** y, int rows2, int columns2);
double** matrixTranspose(double** x, int rows1, int cols1);
double** inverseMatrix(double** x, int rows);
void freeMatrix(double** x, int rows);


int main(int argc, char* argv[])
{

	char* p = argv[1];
	FILE* fp = fopen(p, "r");
	int columns;
	fscanf(fp, "%d", &columns);
	columns++;
	int rows;
	fscanf(fp, "%d", &rows);

	double** y = malloc(rows * sizeof(double*));
	for (int i = 0; i < rows; i++) {
		y[i] = malloc(1 * sizeof(double));
	}

	double** arr2d = malloc(rows * sizeof(double*));
	for (int i = 0; i < rows; i++) {
		arr2d[i] = malloc(columns * sizeof(double));
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j <= columns; j++) {
			if (j != 0 && j != columns) {
			

				fscanf(fp, "%lf", &arr2d[i][j]);
				fscanf(fp, ",");
				
			}
			else if(j==0) {
				arr2d[i][j] = 1;
				
			}
			else {
				fscanf(fp, "%lf", &y[i][0]);
				fscanf(fp, ",");
				 
			}
		}
		  
	}
	fclose(fp);
	char* t = argv[2];
	fp = fopen(t, "r");
	int newRows = 0;
	fscanf(fp, "%d", &newRows);
	double** arr2d2 = malloc(newRows * sizeof(double*));
	for (int i = 0; i < newRows; i++) {
		arr2d2[i] = malloc(columns * sizeof(double));
	}
	for (int i = 0; i < newRows; i++) {
		for (int j = 0; j < columns; j++) {
			if (j != 0) {


				fscanf(fp, "%lf", &arr2d2[i][j]);
				fscanf(fp, ",");
				
				
			}
			else {
				arr2d2[i][j] = 1;
				
			}
		}
	 
	}
	fclose(fp);
	double** transpose = matrixTranspose(arr2d, rows, columns);
	double** product1 = matrixMultiplication(transpose, columns, rows, arr2d, rows, columns);
	
	double** inverse = inverseMatrix(product1, columns);
	
	double** product2 = matrixMultiplication(inverse, columns, columns, transpose, columns, rows);
	
	double** result = matrixMultiplication(product2, columns, rows, y, rows, 1);
	
	double** frResult = matrixMultiplication(arr2d2, newRows, columns, result, columns, 1);
	
	for (int i = 0; i < newRows; i++) {
		printf("%0.0lf\n", frResult[i][0]);
	}
	
	freeMatrix(arr2d, rows);
	freeMatrix(arr2d2, newRows);
	freeMatrix(y, rows);
	freeMatrix(transpose, columns);
	freeMatrix(product1, columns);
	freeMatrix(inverse, columns);
	freeMatrix(product2, columns);
	freeMatrix(result, columns);
	freeMatrix(frResult, newRows);
	

}
double** matrixMultiplication(double** x, int rows1, int columns1, double** y, int rows2, int columns2) {

	double** z = malloc(rows1 * sizeof(double*));
	for (int i = 0; i < rows1; i++) {
		z[i] = malloc(columns2 * sizeof(double));
	}
	for (int i = 0; i < rows1; i++) {
		for (int j = 0; j < columns2; j++) {
			double sum = 0;
			for (int k = 0; k < columns1; k++) {
				sum += (x[i][k] * y[k][j]);
			}
			z[i][j] = sum;
		}
	}
	return z;
}
double** matrixTranspose(double** x, int rows1, int cols1) {
	double** y = malloc(cols1* sizeof(double*));
	for (int i = 0; i < cols1; i++) {
		y[i] = malloc(rows1* sizeof(double));
	}
	
	for (int i = 0; i < cols1; i++)
		for (int j = 0; j < rows1; j++)
			y[i][j] = x[j][i];
	return y;
}
double** inverseMatrix(double** x, int rows) {
	double** z = malloc(rows * sizeof(double*));
	for (int i = 0; i < rows; i++) {
		z[i] = malloc(rows * sizeof(double));
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < rows; j++) {
			z[i][j] = x[i][j];
		}
	}
	double** y = malloc(rows * sizeof(double*));
	for (int i = 0; i < rows; i++) {
		y[i] = malloc(rows * sizeof(double));
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < rows; j++) {
			if (i == j) {
				y[i][j] = 1;
			}
			else {
				y[i][j] = 0;
			}
		}
	}
	for (int i = 0; i < rows; i++) {
		double f = z[i][i];
		for (int j = 0; j < rows; j++) {
			z[i][j] /= f;
			y[i][j] /= f;
		}
		for (int j = i + 1; j < rows; j++) {
			f = z[j][i];
			for (int k = 0; k < rows; k++) {
				z[j][k] -= (f * z[i][k]);
				y[j][k] -= (f * y[i][k]);
			}
		}
	}
	for (int p = rows - 1; p >= 0; p--) {
		for (int i = p - 1; i >= 0; i--) {
			double f = z[i][p];
			for (int k = 0; k < rows; k++) {
				z[i][k] -= (f * z[p][k]);
				y[i][k] -= (f * y[p][k]);
			}

		}
	}
	freeMatrix(z, rows);
	return y;
}
void freeMatrix(double** x, int rows) {
	for (int i = 0; i < rows; i++)
		free(x[i]);
	free(x);
}
