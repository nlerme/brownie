#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <string>
#include "config.h"
#include "color.h"
#include "window.h"


namespace CConfig
{
	static const EWindowType WindowType  = WT_SOFTWARE;
	static const std::string WindowTitle = "Brownie";
	static const int WindowWidth         = 1024;
	static const int WindowHeight        = 768;
	static const std::string LogFilename = "output.log";
	static const float VSync             = 1.0f/50.0f;
	static const color4f BackgroundColor = color4f(color3f::light_gray, 1.0f);
};

#endif //__CONFIG_H__
