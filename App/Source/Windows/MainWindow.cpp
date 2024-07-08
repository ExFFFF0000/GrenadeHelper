#include "../Global.h"
char PointNameField[128];

void MainWindow::Render()
{
    Manager::SetNextSize(300.0f, 300.0f);
	const ImVec2 windowSize = ImGui::GetWindowSize();
	ImGui::Checkbox("flashbang", &GrenadeHelper::setting::flashbang);
	ImGui::SameLine();
	ImGui::Checkbox("smokegrenade", &GrenadeHelper::setting::smokegrenade);
	ImGui::Checkbox("hegrenade", &GrenadeHelper::setting::hegrenade);
	ImGui::SameLine();
	ImGui::Checkbox("incgrenade", &GrenadeHelper::setting::incgrenade);
    ImGui::SliderFloat("Range", &GrenadeHelper::setting::range, 10, 3000);
	ImGui::SliderInt("Length", &GrenadeHelper::setting::length, 10, 3000);
	ImGui::InputTextWithHint("##PointName", "PointName", PointNameField, IM_ARRAYSIZE(PointNameField));
	static int type = 0;
	ImGui::Combo("Type", &type, "flashbang\0smokegrenade\0hegrenade\0incgrenade\0");
	if (ImGui::Button("AddPoint")) {
		GrenadeHelper::AddPoint(PointNameField,type);
	}
	ImGui::SameLine();
	if (ImGui::Button("SavePoint")) {
		GrenadeHelper::SavePoint();
	}

}