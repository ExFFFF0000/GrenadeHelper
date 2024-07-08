#pragma once

namespace GrenadeHelper {

	struct GrenadePoint 
	{
		std::string name;
		vec3 pos;
		vec3 angle;
	};

	enum class GrenadeType : int
	{
		flashbang,
		smokegrenade,
		hegrenade,
		incgrenade,
	};

	static bool bRender = false;

	static std::vector<GrenadePoint> FlashPoints, SmokePoints,HePoints,IncPoints;

	void InitMapPoint(std::string mapname);
	
	namespace setting {
		inline bool flashbang;
		inline bool smokegrenade;
		inline bool hegrenade;
		inline bool incgrenade;

		inline int   length = 3000;
		inline float range = 300;
	}


	void AddPoint(std::string name,int type);

	void SavePoint();

	void Clear();

	void Render();

}