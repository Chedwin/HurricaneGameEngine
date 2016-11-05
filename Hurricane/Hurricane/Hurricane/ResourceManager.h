//*******************************//
//
// Name:			ResourceManager.h
// Description:		A basic description of the header goes here.
//
// Author:			Edwin Chen
// Created:			Oct 01, 2016
// Last updated:	Oct 24, 2016
//
//*******************************//

#pragma once


#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "Macro.h"
#include "Debug.h"

template <class Type> 
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





template <class Type>
class ResourceManager 
{
public:
	VECTOR(Type*) resourceVector;
	MAP(STRING, ResourceHandle<Type>)* resourceMap;

	ResourceManager()
	{
		resourceMap = new MAP(STRING, ResourceHandle<Type>);
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
		MAP(STRING, ResourceHandle<Type>)::iterator iter = resourceMap->begin();

		if (resourceMap->size() > 0)
		{
			for (iter = resourceMap->begin(); iter != resourceMap->end(); iter++)
			{
				ResourceHandle<Type> rm = iter->second;
				hINT t = rm.GetIndex();

				delete resourceVector[t];
				resourceVector[t] = NULL;
			}
		}

		resourceVector.clear();
		resourceMap->clear();
	}

	// ADD A RESOURCE
	ResourceHandle<Type> Add(const STRING& name, Type* res)
	{
		MAP(STRING, ResourceHandle<Type>)::iterator iter = resourceMap->begin();

		if (resourceMap->size() > 0) 
		{
			for (iter = resourceMap->begin(); iter != resourceMap->end(); iter++)
			{
				if (iter->first == name)
				{
					Debug::ConsoleError("\"" + name + "\" resource already exists");
					return iter->second;
				}
			}
		}

		hINT rListSize = resourceVector.size(); // should start at 0
		resourceVector.push_back(res);
		ResourceHandle<Type> handle(rListSize);
		resourceMap->insert(iter, PAIR(STRING, hINT)(name, handle.index) );

		return handle.index;
	}

	// REMOVE A RESOURCE BY NAME
	void Remove(const STRING& name) 
	{
		MAP(STRING, ResourceHandle<Type>)::iterator iter = resourceMap->begin();

		for (iter = resourceMap->begin(); iter != resourceMap->end(); iter++)
		{
			if (iter->first == name)
			{
				ResourceHandle<Type> rm = iter->second;
				hINT t = rm.GetIndex();

				delete resourceVector[t];
				resourceVector[t] = NULL;
				resourceMap->erase(name);
				return;
			}
		}
		Debug::ConsoleError("Resource failed to be removed: \n\"" + name + "\" resource does not exist");
	}

	// GET (overload 1)
	// Return generic type pointer
	Type* Get(ResourceHandle<Type> &handle) const
	{
		hINT idx = handle.GetIndex();
		Type *result = NULL;

		if (idx >= 0 && idx < hINT(resourceVector.size()))
		{
			result = resourceVector[idx];
		}
		return result;
	}

	// GET (overload 2)
	// Return resource handle (index of handle)
	ResourceHandle<Type> Get(const STRING &name) const
	{
		MAP(STRING, ResourceHandle<Type>)::iterator iter = resourceMap->begin();

		ResourceHandle<Type> result(-1);

		for (iter = resourceMap->begin(); iter != resourceMap->end(); iter++)
		{
			if (iter->first == name)
			{
				result = iter->second;
				return iter->second;
			}

		}
		return result;
	}
};

#endif