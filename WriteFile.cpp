//
// Created by tadir on 15/04/19.
//

#include "WriteFile.hpp"
#include "mwTPoint3d.hpp"

void WriteFile::to(	const std::string &skinFileName,
					const unsigned long &nx,
					const unsigned long &ny,
				   	const unsigned long &nz,
				   	const double &delta,
				   	const std::vector<std::vector <unsigned long> > &skin)
{
	std::ofstream	ofs;
	ofs.open(skinFileName);
	for (unsigned long i = 0; i < nx; i++)
		for (unsigned long j = 0; j < ny; j++)
			ofs << i * delta << ' ' << j * delta << ' ' << skin[i][j] * delta << std::endl;
	ofs.close();
}
