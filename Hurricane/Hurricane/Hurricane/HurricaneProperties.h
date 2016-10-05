//*******************************//
//
// Name:			HurricaneProperties.h
// Description:		This class reads an XML file to verify all the properties to engine needs for the game.
//					Utilizes TinyXML to read XML files.
//
// Author:			Edwin Chen, Mathieu Violette, James Sholdice, & Nathan Senter
// Created:			Sep 18, 2016
// Last updated:	Sep 21, 2016
//
//*******************************//

#pragma once

#ifndef HURRICANE_PROPERTIES_H
#define HURRICANE_PROPERTIES_H

#include "Macro.h"
#include "tinyxml2.h"

#define H_PROPERTIES HurricaneProperties::GetHurricaneProperties()

// Abstract Properties struct
struct Properties {
	//Reads video property values from the xml and assigns
	virtual void ReadValues() = 0;
	//Writes changed values to xml
	virtual void WriteValues() = 0;
};

// Engine properties loaded and read by TinyXML
class HurricaneProperties {
protected:
	HurricaneProperties();
public:
	~HurricaneProperties();
	static HurricaneProperties* GetHurricaneProperties();

	// GENERAL PROPERTIES
	// i.e. game name, author, etc.
	struct GeneralProperties : public Properties {
		STRING gameName;
		STRING author;

		void ReadValues();
		void WriteValues();
	};

	inline static GeneralProperties* GetGeneralProperties() {
		return _genProp;
	}

	// AUDIO PROPERTIES
	struct AudioProperties : public Properties {
		hFLOAT masterVolume;
		hFLOAT musicVolume;
		hFLOAT soundVolume;

		void ReadValues();
		void WriteValues();
	};

	inline static AudioProperties* GetAudioProperties() {
		return _audioProp;
	}

	// VIDEO PROPERTIES
	struct VideoProperties : public Properties {
		hINT screenWidth;
		hINT screenHeight;
		hUINT fullScreen;

		void ReadValues();
		void WriteValues();
		hFLOAT AspectRatio();
	};

	inline static VideoProperties* GetVideoProperties() {
		return _videoProp;
	}

	//Called when you click the _audioPropply after changing some settings
	//Writes current values to the xml and saves it
	static void ApplyChanges();

protected:
	static UNIQUE_PTR(HurricaneProperties) _HurricaneProperties;
	friend DEFAULT_DELETE(HurricaneProperties);

	static GeneralProperties* _genProp;
	static AudioProperties* _audioProp;
	static VideoProperties* _videoProp;

	static tinyxml2::XMLDocument _xml_doc;
};

#endif