#include "HurricaneProperties.h"
#include "DebugLog.h"

/// STATIC DECLARATIONS
UNIQUE_PTR(HurricaneProperties) HurricaneProperties::_HurricaneProperties(nullptr);

HurricaneProperties::GeneralProperties*		HurricaneProperties::_genProp;   // General properties
HurricaneProperties::AudioProperties*		HurricaneProperties::_audioProp; // Audio properties
HurricaneProperties::VideoProperties*		HurricaneProperties::_videoProp; // Video properties

tinyxml2::XMLDocument HurricaneProperties::_xml_doc; // static tinyxml doc



HurricaneProperties* HurricaneProperties::GetHurricaneProperties() {
	if (_HurricaneProperties.get() == nullptr) {
		/// I originally set the unique_ptr to be null in the constructor - reset() sets the new address
		_HurricaneProperties.reset(new HurricaneProperties());
	}
	return _HurricaneProperties.get();
}


HurricaneProperties::HurricaneProperties()
{
	_genProp = new GeneralProperties();
	_audioProp = new AudioProperties();
	_videoProp = new VideoProperties();

	_xml_doc.LoadFile("properties.xml");

	_genProp->ReadValues();
	_audioProp->ReadValues();
	_videoProp->ReadValues();
}

HurricaneProperties::~HurricaneProperties()
{
	delete _genProp;
	delete _videoProp;
	delete _audioProp;

	_genProp = nullptr;
	_audioProp = nullptr;
	_videoProp = nullptr;
}

////// GENERAL PROPERTIES //////
void HurricaneProperties::GeneralProperties::ReadValues()
{
	tinyxml2::XMLElement* element = _xml_doc.RootElement()->FirstChildElement("GeneralProperty")->FirstChildElement("name");
	gameName = STRING(element->GetText());
	element = element->NextSiblingElement("author");
	author = STRING(element->GetText());
}

void HurricaneProperties::GeneralProperties::WriteValues()
{
	tinyxml2::XMLElement* element = _xml_doc.RootElement()->FirstChildElement("GeneralProperty")->FirstChildElement("name");
	element->SetText(gameName.c_str());
	element = element->NextSiblingElement("author");
	element->SetText(author.c_str());
}

////// AUDIO PROPERTIES //////
void HurricaneProperties::AudioProperties::ReadValues()
{
	tinyxml2::XMLElement* element = _xml_doc.RootElement()->FirstChildElement("AudioProperty")->FirstChildElement("master");
	masterVolume = STOI(element->GetText());
	element = element->NextSiblingElement("music");
	musicVolume = STOI(element->GetText());
	element = element->NextSiblingElement("soundfx");
	soundVolume = STOI(element->GetText());
}

void HurricaneProperties::AudioProperties::WriteValues()
{
	tinyxml2::XMLElement* element = _xml_doc.FirstChildElement("AudioProperty")->FirstChildElement("master");

	element->SetText(masterVolume);
	element = element->NextSiblingElement("music");
	element->SetText(musicVolume);
	element = element->NextSiblingElement("soundfx");
	element->SetText(soundVolume);
}

////// VIDEO PROPERTIES //////
void HurricaneProperties::VideoProperties::ReadValues()
{
	tinyxml2::XMLElement* element = _xml_doc.RootElement()->FirstChildElement("VideoProperty")->FirstChildElement("width");

	screenWidth = STOI(element->GetText());
	element = element->NextSiblingElement("height");
	screenHeight = STOI(element->GetText());
	element = element->NextSiblingElement("fullscreen");
	fullScreen = STOI(element->GetText());
}

void HurricaneProperties::VideoProperties::WriteValues()
{
	tinyxml2::XMLElement* element = _xml_doc.FirstChildElement("VideoProperty")->FirstChildElement("width");

	element->SetText(screenWidth);
	element = element->NextSiblingElement("height");
	element->SetText(screenHeight);
	element = element->NextSiblingElement("fullscreen");
	element->SetText(fullScreen);
}


hFLOAT HurricaneProperties::VideoProperties::AspectRatio()
{
	return screenWidth / (hFLOAT)screenHeight;
}


/// APPLY CHANGES ///
void HurricaneProperties::ApplyChanges()
{
	_videoProp->WriteValues();

	//A series of checks to ensure the volume values are between 0 and 1
	//May not be neccesary?
	if (_audioProp->masterVolume > 1)_audioProp->masterVolume = 1;
	if (_audioProp->masterVolume < 0)_audioProp->masterVolume = 0;

	if (_audioProp->musicVolume > 1)_audioProp->musicVolume = 1;
	if (_audioProp->musicVolume < 0)_audioProp->musicVolume = 0;

	if (_audioProp->soundVolume > 1)_audioProp->soundVolume = 1;
	if (_audioProp->soundVolume < 0)_audioProp->soundVolume = 0;

	_audioProp->WriteValues();

	_xml_doc.SaveFile("properties.xml");

	/*AudioManager * am = AudioManager::getInstance();
	am->setSoundVolume(_audioProp->soundVolume * _audioProp->masterVolume);
	am->setMusicVolume(_audioProp->musicVolume * _audioProp->masterVolume);*/
}