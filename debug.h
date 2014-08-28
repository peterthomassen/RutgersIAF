#pragma once

#include <iostream>

#define DEBUG(message) \
( \
	(std::cerr << "Debug: " << (message) << " at " << __PRETTY_FUNCTION__ << " in " << __FILE__ << ":" << __LINE__ << std::endl), \
	(void)0 \
)
