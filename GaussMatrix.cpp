#ifndef GAUSS_MATRIX
#define GAUSS_MATRIX

#include "GaussMatrix.h"

// Constructor
GaussMatrix::GaussMatrix(std::uint32_t nRows, std::uint32_t nColumns)
{
	// allocate memory for the matrix
	matrix = new double*[nRows];
	for(int i = 0; i < nRows; ++i) matrix[i] = new double[nColumns];

	this->nRows = nRows;
	this->nColumns = nColumns;
}

// private methods
void GaussMatrix::subRowAkFromB(std::uint32_t b, std::uint32_t a, double k)
{
	for(std::uint32_t col = 0; col < nColumns; ++col)
		matrix[b][col] -= k * matrix[a][col];
}

void GaussMatrix::swapRows(std::uint32_t a, std::uint32_t b)
{
	for(std::uint32_t col = 0; col < nColumns; ++col)
	{
		double temp = matrix[a][col];
		matrix[a][col] = matrix[b][col];
		matrix[b][col] = temp;
	}
}
void GaussMatrix::scaleRow(std::uint32_t row, double k)
{
	for(std::uint32_t col = 0; col < nColumns; ++col)
		matrix[row][col] *= k;
}

// public methods
double GaussMatrix::get(std::uint32_t row, std::uint32_t column) const
{
	return matrix[row][column];
}

void GaussMatrix::set(std::uint32_t row, std::uint32_t column, double value)
{
	matrix[row][column] = value;
}

void GaussMatrix::solve()
{
	// loop through all columns containing coefficients
	for(std::uint32_t col = 0; col < ( nColumns - 1 ); ++col)
	{
		std::cout << "COLUMN " << col << "\n\n";
		// find two rows a, b where matrix[a][col] and matrix[b][col] != 0
		while(1)
		{
			int a = -1, b = -1;

			// find two non-zero rows
			for(int row = col; row < nRows; ++row)
			{
				if(matrix[row][col] != 0)
				{
					// a will be set first
					if(a == -1) a = row;
					// if a is already set and the row is non-zero, set b
					else if(b == -1) b = row;
				}
			}
			// if b wasn't set, there aren't two non-zero rows -> continue with the next column
			if(b == -1) break;

			// k * m[a][c] = m[b][c]
			double k = matrix[b][col] / matrix[a][col];
			subRowAkFromB(b, a, k);
			if(matrix[b][col] != 0.0)
			{
				std::cout << "Matrix[" << b << "]" << "[" << col << "] = " << matrix[b][col] << '\n';
				matrix[b][col] = 0.0;
			}

			/*
			std::cout << "\nswapping...\n";
			print();
			swapRows(a, col);
			std::cout << "swapped " << a << " with " << col << '\n';
			print();
			*/

			// reset a and b
			a = -1;
			b = -1;
		}
		
		// / x x x \      / x 0 0 \
		// | 0 x x | ---> | 0 x 0 | 
		// \ 0 0 x /      \ 0 0 x / 
		for(std::uint32_t col = (nColumns - 2); col > 0; --col)
		{
			std::uint32_t lowestRow = col >= nRows ? nRows-1 : col;
			scaleRow(lowestRow, ( 1.0 / matrix[lowestRow][col] ));
			for(std::uint32_t row = 0; row < lowestRow; ++row)
			{
				double k = matrix[row][col] / matrix[lowestRow][col];
				subRowAkFromB(row, lowestRow, k);
				if(matrix[row][col] != 0)
				{
					std::cout << "Matrix[" << row << "][" << col << "] = " << matrix[row][col]
						<< " -> 0" << '\n';
					matrix[row][col] = 0;
				}
			}
		}

		// scale row 0
		scaleRow(0, 1.0 / matrix[0][0]);
	}
}

void GaussMatrix::print() const
{
	for(std::uint32_t r = 0; r < nRows; r++)
	{
		for(std::uint32_t c = 0; c < nColumns; c++)
		{
			if(c == nColumns - 1) std::cout << "| ";
			if(matrix[r][c] >= 0) std::cout << ' ';
			std::cout << std::fixed << std::setprecision(4) << matrix[r][c] << "  ";
		}
		std::cout << '\n';
	}
}

#endif
