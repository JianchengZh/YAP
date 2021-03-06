#pragma once

#ifndef YapImplement_h_20160831
#define YapImplement_h_20160831

#include "ContainerImpl.h"

#define BEGIN_DECL_PROCESSORS extern "C" {\
	__declspec(dllexport) IProcessorContainer * GetProcessorManager()\
	{\
		static Yap::SmartPtr<ContainerImpl<IProcessor>> processor_manager;\
		if (processor_manager)\
			return processor_manager.get();\
		processor_manager = Yap::YapShared(new (std::nothrow) ContainerImpl<IProcessor>);\
		if (!processor_manager) return nullptr;

#define ADD_PROCESSOR(class_name) auto * my##class_name = new class_name; \
if (!my##class_name->Init())\
{\
	return nullptr;\
}\
processor_manager->Add(my##class_name->GetClassId(), my##class_name);

#define ADD(a, b) auto pb = b; if (!pb->Init())\
{\
	return nullptr;\
}\
processor_manager->Add((a), pb);

#define END_DECL_PROCESSORS return processor_manager.get();\
}\
} //end extern "C"

#endif