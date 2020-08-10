#include "Func.hpp"
#include "Error.hpp"
#include <windows.h>

////-----------------------------------------------------------------
sf::Texture LoadTextureFromResource(const char* const name){

	HRSRC rsrcData = FindResource(NULL, name, RT_RCDATA);
	if (!rsrcData) throw ErrSys("RESORUCES find resoruce.");

	DWORD rsrcDataSize = SizeofResource(NULL, rsrcData);
	if (rsrcDataSize <= 0) throw ErrSys("RESORUCES Size is 0.");

	HGLOBAL grsrcData = LoadResource(NULL, rsrcData);
	if (!grsrcData) throw ErrSys("RESORUCES load resuroce.");

	LPVOID firstByte = LockResource(grsrcData);
	if (!firstByte) throw ErrSys("RESORUCES lock resoruce.");

	sf::Texture texture;
	if (!texture.loadFromMemory(firstByte, rsrcDataSize))
		throw ErrSys("RESORUCES load texture form memory.");

	return texture;
}

////-----------------------------------------------------------------
sf::Font LoadFontFromResource(const char* const name){

	HRSRC rsrcData = FindResource(NULL, name, RT_RCDATA);
	if (!rsrcData) throw ErrSys("RESORUCES find resoruce.");

	DWORD rsrcDataSize = SizeofResource(NULL, rsrcData);
	if (rsrcDataSize <= 0) throw ErrSys("RESORUCES Size of is 0.");

	HGLOBAL grsrcData = LoadResource(NULL, rsrcData);
	if (!grsrcData) throw ErrSys("RESORUCES load resuroce.");

	LPVOID firstByte = LockResource(grsrcData);
	if (!firstByte) throw ErrSys("RESORUCES lock resoruce.");

	sf::Font font;
	if (!font.loadFromMemory(firstByte, rsrcDataSize))
		throw ErrSys("RESORUCES load font form memory.");

	return font;
}