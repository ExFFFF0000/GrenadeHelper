#include "Global.h"

void GrenadeHelper::InitMapPoint(std::string mapname)
{
	if (bRender)Clear();
	std::ifstream f(mapname + ".json");
	json data = json::parse(f);
	int count = data["infos"].size();
	for (int i = 0; i < count; i++) {
		json current = data["infos"].at(i);
		GrenadePoint point{};
		point.name = current["Name"]; 
		point.pos = { current["Position"][0],current["Position"][1],current["Position"][2] };
		point.angle = { current["Angle"][0],current["Angle"][1],0 };
		switch ((GrenadeType)current["Type"])
		{
		case GrenadeType::flashbang:
			FlashPoints.push_back(point);
			break;
		case GrenadeType::smokegrenade:
			SmokePoints.push_back(point);
			break;
		case  GrenadeType::hegrenade:
			HePoints.push_back(point);
			break;
		case GrenadeType::incgrenade:
			IncPoints.push_back(point);
			break;
		default:
			break;
		}
	}
	bRender = true;
}

void GrenadeHelper::AddPoint(std::string name,int type)
{
	GrenadePoint point{};
	point.name = name;
	auto LocalPlayer = proc->Read<uint64_t>(client + client_dll::dwLocalPlayerPawn);
	point.pos = proc->Read<vec3>(LocalPlayer + C_BasePlayerPawn::m_vOldOrigin);
	point.angle = proc->Read<vec3>(client + client_dll::dwViewAngles);
	switch ((GrenadeType)type)
	{
	case GrenadeType::flashbang:
		FlashPoints.push_back(point);
		break;
	case GrenadeType::smokegrenade:
		SmokePoints.push_back(point);
		break;
	case  GrenadeType::hegrenade:
		HePoints.push_back(point);
		break;
	case GrenadeType::incgrenade:
		IncPoints.push_back(point);
		break;
	default:
		break;
	}
}

void GrenadeHelper::SavePoint()
{

}

void GrenadeHelper::Clear()
{
	std::vector<GrenadePoint>().swap(FlashPoints);
	std::vector<GrenadePoint>().swap(SmokePoints);
	std::vector<GrenadePoint>().swap(HePoints);
	std::vector<GrenadePoint>().swap(IncPoints);
	bRender = false;
}

#define M_PI       3.14159265358979323846   // pi

vec2 screensize = { 1920,1080 };

vec3 local_pos;

static void DrawPoint(GrenadeHelper::GrenadePoint point, int index, ImColor Color) {
	
	std::string name = point.name + std::to_string(index);

	if(local_pos.distance(point.pos) > GrenadeHelper::setting::range)return;
	vec3 screenpos{};
	if (math::world_to_screen(screensize, point.pos, screenpos, matrix)) {
		ImGui::GetForegroundDrawList()->AddText({ screenpos.x,screenpos.y }, ImColor(255, 255, 255), name.c_str());
		ImGui::GetForegroundDrawList()->AddCircleFilled({ screenpos.x,screenpos.y }, 3, Color);
	}
	vec3 EndPos;
	float LineLength = cos(point.angle.x * M_PI / 180) * GrenadeHelper::setting::length;
	EndPos.x = local_pos.x + cos(point.angle.y * M_PI / 180) * LineLength;
	EndPos.y = local_pos.y + sin(point.angle.y * M_PI / 180) * LineLength;
	EndPos.z = local_pos.z - sin(point.angle.x * M_PI / 180) * GrenadeHelper::setting::length;

	if (math::world_to_screen(screensize, EndPos, screenpos, matrix)) {
		ImGui::GetForegroundDrawList()->AddText({ screenpos.x,screenpos.y }, ImColor(255, 255, 255), name.c_str());
		ImGui::GetForegroundDrawList()->AddCircleFilled({ screenpos.x,screenpos.y }, 3, Color);
	}
}


void GrenadeHelper::Render()
{
	if (!bRender)return;

	matrix = proc->Read<view_matrix_t>(client + client_dll::dwViewMatrix);
	auto LocalPlayer = proc->Read<uint64_t>(client + client_dll::dwLocalPlayerPawn);

	local_pos = proc->Read<vec3>(LocalPlayer + C_BasePlayerPawn::m_vOldOrigin);
	auto e_pos = proc->Read<float>(LocalPlayer + C_BaseModelEntity::m_vecViewOffset + 8);
	local_pos.z + e_pos;
	int index = 0;
	if (setting::flashbang) {
		for (auto& i : FlashPoints)
		{
			DrawPoint(i, index, ImColor(255, 0, 0));
			index++;
		}
	}

	if (setting::smokegrenade) {
		for (auto& i : SmokePoints)
		{
			DrawPoint(i, index, ImColor(0, 255, 0));
			index++;
		}
	}

	if (setting::hegrenade) {
		for (auto& i : HePoints)
		{
			DrawPoint(i, index, ImColor(0, 0, 255));
		}
	}

	if (setting::incgrenade) {
		for (auto& i : IncPoints)
		{
			DrawPoint(i, index, ImColor(255, 255, 0));
		}
	}

}
