#ifndef _FRAME_STREAM_H_
#define _FRAME_STREAM_H_

#include <ostream>
#include <streambuf>
#include <string>
#include <vector>
#include <androidfw/ZipFileRO.h>
#include <androidfw/Asset.h>
#include <android/log.h>

using namespace std;
using namespace android;

namespace frame_animation {

class fpstream : public ostream {
	fpstream& log_priority (android_LogPriority pri);
public:
	fpstream ();
	fpstream& I() { return log_priority(ANDROID_LOG_INFO);  }
	fpstream& E() { return log_priority(ANDROID_LOG_ERROR); }
	fpstream& D() { return log_priority(ANDROID_LOG_DEBUG); }
	fpstream& W() { return log_priority(ANDROID_LOG_WARN);  }
};

extern fpstream FPLog;

// ------------------------------------------------------
class ResStreamBuf : public streambuf {
	shared_ptr<Asset> asset;
	char *buf;
public:
	ResStreamBuf (shared_ptr<Asset> asset);

	virtual int underflow();
	virtual int uflow();
};

class ZipStreamBuf : public streambuf {
	shared_ptr<ZipFileRO> zip_file;
	string file_name;
	unique_ptr<FileMap> file_map;
	int length;
public:
	ZipStreamBuf (shared_ptr<ZipFileRO>, string);

	virtual int underflow() override;
protected:
	virtual pos_type seekoff(off_type off, ios_base::seekdir way, ios_base::openmode which) override;
};

}; //namespace frame_animation

#endif
