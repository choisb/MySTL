#pragma once
#include <iostream>

#define TEST_LOG_FOMAT(pred) std::string("line: ") + std::to_string(__LINE__) + std::string(" [") + std::string(#pred) + std::string("] ")

#define TEST_CODE(pred) if(pred == false) \
							std::cout << TEST_LOG_FOMAT(pred) << std::string("failed") << std::endl; \
						else \
							std::cout << TEST_LOG_FOMAT(pred) << std::string("succeeded") << std::endl; \