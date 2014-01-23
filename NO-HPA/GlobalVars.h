#ifndef _GLOBAL_VAR_
#define _GLOBAL_VAR_

#include "irrlicht.h"


//file 

	class CSettings
	{
	private:
		irr::core::stringw fileToOpen;
		irr::core::stringw fileToSave;

		bool FileOpenFlag;
		bool FileSaveFlag;

		bool destNodeSelected;
		bool findingPath;
		bool sFlag;

		bool helpFlag;

	public:
		CSettings();
		void setFileToOpen(irr::core::stringw t_fileToOpen);
		irr::core::stringw* getFileToOpen();

		void setFileToSave(irr::core::stringw t_fileToSave);
		irr::core::stringw* getFileToSave();

		void setFileOpenFlag(bool flag);
		bool getFileOpenFlag();
		void setFileSaveFlag(bool flag);
		bool getFileSaveFlag();
		void setDestSelFlag(bool flag);
		bool getDestSelFlag();
		void setFindingPathFlag(bool flag);
		bool getFindingPathFlag();
		void setHelpFlag(bool flag);
		bool getHelpFlag();	
		void setSFlag(bool flag);
		bool getSFlag();

	};

	enum EDITOR_CONTROLS
	{
		ID_FILE_OPEN_BUTTON = 200,
		ID_FILE_SAVE_BUTTON,
		ID_FILE_OPEN_WINDOW,
		ID_HELP_WINDOW
		
	};

	



#endif