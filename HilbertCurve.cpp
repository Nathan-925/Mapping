/*
 * HilbertCurve.cpp
 *
 *  Created on: Aug 3, 2023
 *      Author: Nathan
 */
#include "HilbertCurve.h"

using namespace std;

namespace priori{

	std::pair<int, int> getHilbertPosition(unsigned int position, int order){
		auto out = std::make_pair(0, 0);
		for(int i = 0; i < order; i++){
			int orderSize = pow(2, i);
			int orderPos = position&3;

			switch(orderPos){
			case 2:
				out.first += orderSize;
				//no break
			case 1:
				out.second += orderSize;
				break;
			case 3:
				out.first = orderSize-1-out.first;
				out.second = 2*orderSize-1-out.second;
				//no break
			case 0:
				std::swap(out.first, out.second);
			}
			position >>= 2;
		}

		return out;
	}

}
