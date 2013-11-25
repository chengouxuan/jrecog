/*
 * Recog.h
 *
 *  Created on: 2013-11-25
 *      Author: chengouxuan
 */

#ifndef RECOG_H_
#define RECOG_H_

namespace Recog {

#include <string>

class Recog {
public:
	~Recog();
	Recog();

	std::string recognize(Jpeg::Decoder *jpegDecoder);
};

} /* namespace gx6 */
#endif /* RECOG_H_ */
