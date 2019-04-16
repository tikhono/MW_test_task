//
// Created by tadir on 15/04/19.
//

#ifndef TEST_TASK_WRITEFILE_H
#define TEST_TASK_WRITEFILE_H

#include <fstream>
#include <vector>

class WriteFile
{
	public:
		void 	static to(	const std::string &skinFileName,
							const unsigned long &nx,
						   	const unsigned long &ny,
						   	const unsigned long &nz,
						   	const double &delta,
						   	const std::vector<std::vector <unsigned long> > &skin);
};


#endif //TEST_TASK_WRITEFILE_H
