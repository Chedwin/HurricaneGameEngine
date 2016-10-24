//*******************************//
//
// Name:			ResourceManager.h
// Description:		A basic description of the header goes here.
//
// Author:			Edwin Chen
// Created:			Oct 01, 2016
// Last updated:	Oct 14, 2016
//
//*******************************//

#pragma once


#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "Macro.h"
#include "DebugLog.h"

template <class ResourceType> 
class ResourceHandle
{
public:
	hINT index;

	ResourceHandle() : index(-1) {}
	ResourceHandle(hINT ind) : index(ind) {}

	inline hBOOL IsNull() 
	{
		return index == -1;
	}

	inline void Nullify() 
	{
		index = -1;
	}

	inline hINT GetIndex() const 
	{
		return index;
	}
};





template <class ResourceType>
class ResourceManager 
{
public:
	VECTOR(ResourceType*) resourceVector;
	MAP(STRING, ResourceHandle<ResourceType>)* resourceMap;

	ResourceManager()
	{
		resourceMap = new MAP(STRING, ResourceHandle<ResourceType>);
	}

	~ResourceManager()
	{
		EmptyResourceMap();
		delete resourceMap;
		resourceMap = nullptr;
	}

	// CLEAR EVERYTHING
	void EmptyResourceMap() 
	{
		MAP(STRING, ResourceHandle<ResourceType>)::iterator iter = resourceMap->begin();

		if (resourceMap->size() > 0)
		{
			for (iter = resourceMap->begin(); iter != resourceMap->end(); iter++)
			{
				ResourceHandle<ResourceType> rm = iter->second;
				hINT t = rm.GetIndex();

				delete resourceVector[t];
				resourceVector[t] = NULL;
			}
		}

		resourceVector.clear();
		resourceMap->clear();
	}

	// ADD A RESOURCE
	ResourceHandle<ResourceType> Add(const STRING& name, ResourceType* res)
	{
		MAP(STRING, ResourceHandle<ResourceType>)::iterator iter = resourceMap->begin();

		if (resourceMap->size() > 0) 
		{
			for (iter = resourceMap->begin(); iter != resourceMap->end(); iter++)
			{
				if (iter->first == name)
				{
					LOG->ConsoleError("\"" + name + "\" resource already exists");
					return iter->second;
				}
			}
		}

		hINT rListSize = resourceVector.size(); // should start at 0
		resourceVector.push_back(res);
		ResourceHandle<ResourceType> handle(rListSize);
		resourceMap->insert(iter, PAIR(STRING, hINT)(name, handle.index) );

		return handle.index;
	}

	// REMOVE A RESOURCE BY NAME
	void Remove(const STRING& name) 
	{
		MAP(STRING, ResourceHandle<ResourceType>)::iterator iter = resourceMap->begin();

		for (iter = resourceMap->begin(); iter != resourceMap->end(); iter++)
		{
			if (iter->first == name)
			{
				ResourceHandle<ResourceType> rm = iter->second;
				hINT t = rm.GetIndex();

				delete resourceVector[t];
				resourceVector[t] = NULL;
				resourceMap->erase(name);
				return;
			}
		}
		LOG->ConsoleError("Resource failed to be removed: \n\"" + name + "\" resource does not exist");
	}

	// GET (overload 1)
	// Return generic type pointer
	ResourceType* Get(ResourceHandle<ResourceType> &handle) const
	{
		hINT idx = handle.GetIndex();
		ResourceType *result = NULL;

		if (idx >= 0 && idx < hINT(resourceVector.size()))
		{
			result = resourceVector[idx];
		}
		return result;
	}

	// GET (overload 2)
	// Return resource handle (index of handle)
	ResourceHandle<ResourceType> Get(const STRING &name) const
	{
		MAP(STRING, ResourceHandle<ResourceType>)::iterator iter = resourceMap->begin();

		hBOOL b = false;

		for (iter = resourceMap->begin(); iter != resourceMap->end(); iter++)
		{
			if (iter->first == name)
			{
				return iter->second;
			}

		}
		return ResourceHandle<ResourceType>();
	}
};

#endif