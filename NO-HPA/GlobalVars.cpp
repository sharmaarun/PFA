#include "GlobalVars.h"

CSettings::CSettings()
{
	this->FileOpenFlag = false;	
	this->FileSaveFlag  = false;
	this->destNodeSelected = false;
	this->findingPath = false;
	this->helpFlag = false;
	this->sFlag=false;
}

void CSettings::setFileToOpen(irr::core::stringw t_fileToOpen)
{

	this->fileToOpen = t_fileToOpen;

}

irr::core::stringw* CSettings::getFileToOpen()
{
	return &this->fileToOpen;
}


void CSettings::setFileToSave(irr::core::stringw t_fileToSave)
{

	this->fileToSave = t_fileToSave;

}

irr::core::stringw* CSettings::getFileToSave()
{
	return &this->fileToSave;
}

void CSettings::setFileOpenFlag(bool flag)
{
	this->FileOpenFlag = flag;
}

bool CSettings::getFileOpenFlag()
{
	return this->FileOpenFlag;
}

void CSettings::setFileSaveFlag(bool flag)
{
	this->FileSaveFlag = flag;
}

bool CSettings::getFileSaveFlag()
{
	return this->FileSaveFlag;
}

void CSettings::setDestSelFlag(bool flag)
{
	this->destNodeSelected = flag;
}

bool CSettings::getDestSelFlag()
{
	return this->destNodeSelected;
}

void CSettings::setFindingPathFlag(bool flag)
{
	this->findingPath = flag;
}

bool CSettings::getFindingPathFlag()
{
	return this->findingPath;
}

void CSettings::setHelpFlag(bool flag)
{
	this->helpFlag = flag;
}
bool CSettings::getHelpFlag()
{
	return this->helpFlag;
}

void CSettings::setSFlag(bool flag)
{
	this->sFlag = flag;
}
bool CSettings::getSFlag()
{
	return this->sFlag;
}