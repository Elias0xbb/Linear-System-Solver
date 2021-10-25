#include <iostream>
#include <iomanip>
#include <cmath>

class GaussMatrix
{
private:
	std::uint32_t nColumns;
	std::uint32_t nRows;
	double **matrix;

	// subtracts row a scaled by k from row b
	void subRowAkFromB(std::uint32_t b, std::uint32_t a, double k);
	void swapRows(std::uint32_t a, std::uint32_t b);
	void scaleRow(std::uint32_t row, double k);

public:
	GaussMatrix() = delete;
	GaussMatrix(std::uint32_t nRows, std::uint32_t nColumns);
	GaussMatrix(const GaussMatrix &g): GaussMatrix(g.nRows, g.nColumns)
	{
		for(int r = 0; r < nRows; ++r)
			for(int c = 0; c < nColumns; ++c)
				matrix[r][c] = g.matrix[r][c];
	}


	~GaussMatrix()
	{
		// deallocate matrix memory
		for(int i = 0; i < nRows; ++i) delete[] matrix[i];
		delete[] matrix;
	}

	std::uint32_t getNColumns() const { return nColumns; }
	std::uint32_t getNRows() const { return nRows; }

	double get(std::uint32_t row, std::uint32_t column) const;
	void set(std::uint32_t row, std::uint32_t column, double value);
	void set(double **matrix)
	{
		for(std::uint32_t r = 0; r < nRows; ++r)
			for(std::uint32_t c = 0; c < nColumns; ++c)
				this->matrix[r][c] = matrix[r][c];
	}

	void solve();
	void print() const;
};
