#pragma once

enum ServerWidgetIndex : uint8
{
	ServerWidget_1_1 = 0,
	ServerWidget_2_1, //Helper widget
	ServerWidget_2_2,
	ServerWidget_2_3,
	ServerWidget_3_1,
	ServerWidget_3_2,
	ServerWidget_3_3,
	ServerWidget_4_1,
	ServerWidget_4_2,
	ServerWidget_4_3,
	ServerWidget_5_1,
	ServerWidget_5_2,
	NextCoachingVideo,
};

enum ClientWidgetIndex : uint8
{
	ClientWidget_1_1 = 0,
	ClientWidget_2_1, //Helper widget
	ClientWidget_2_2,
	ClientWidget_2_3,
	ClientWidget_3_1,
	ClientWidget_3_2,
	ClientWidget_3_3,
	ClientWidget_4_1,
	ClientWidget_4_2,
	ClientWidget_4_3,
	ClientWidget_5_1,
	ClientWidget_5_2,
};

enum SelectLevel :uint8
{
	Low = 0,
	Middle,
	High,
	Level_None,
};

enum Select_Button : uint8
{
	None = 0,
	Button_1 = 1,
	Button_2 = 2,
	Button_3 = 3,
	Button_4 = 4,
	Button_5 = 5,
};

UENUM(BlueprintType)
enum class ScoringJoints : uint8
{
	SHOULDER_LEFT = 0,
	ELBOW_LEFT,
	SHOULDER_RIGHT,
	ELBOW_RIGHT,
	HIP_LEFT,
	KNEE_LEFT,
	HIP_RIGHT,
	KNEE_RIGHT,
	COUNT,
};
