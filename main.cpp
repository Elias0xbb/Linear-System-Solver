#include <iostream>
#include "GaussMatrix.h"

int main()
{
	while(true)
	{
		uint32_t rows = 1, cols = 1;

		// get user input for rows and columns:
		try
		{
			std::string temp = "";
			std::cout << "Exit program? y:n\n";
			std::cin >> temp;
			if(temp[0] == 'y') return 0;

			std::cout << "Enter number of rows: ";
			std::cin >> temp;
			// convert to integer
			rows = (uint32_t)std::stoi(temp);
			std::cout << "\nEnter number of columns: ";
			std::cin >> temp;
			cols = (uint32_t)std::stoi(temp);

			std::cout << "M[" << rows << "][" << cols << "] y:n ?\n";
			std::cin >> temp;
			if(temp[0] != 'y') continue;
		}
		catch (std::exception e)
		{
			std::cout << e.what() << '\n';
			std::cout << "[Error] Invalid input, please input a positive integer\n";
			continue;
		}

		// init the matrix
		GaussMatrix g(rows, cols);

		for(std::uint32_t row = 0; row < g.getNRows(); ++row)
		{
			for(std::uint32_t col = 0; col < g.getNColumns(); ++col)
			{
				g.print();
				try
				{
					std::cout << "\nSET MATRIX[" << row << "][" << col << "] = ";
					std::string temp = "";
					std::cin >> temp;
					double value = std::stod(temp);
					g.set(row, col, value);
				}
				catch(std::exception e)
				{
					std::cout << e.what() << '\n';
				}
			}
		}

		std::cout << "Solving matrix....\n";
		g.solve();
		std::cout << '\n';
		g.print();
	}

	return 0;
}
