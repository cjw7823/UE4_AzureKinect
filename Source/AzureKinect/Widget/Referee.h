// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomEnum.h"

/**
 * 
 */
class AMainPlayerController;
class AZUREKINECT_API Referee
{
private:
	double Find_Duration_MC(SelectLevel level, Select_Button button);
	double Find_Duration_Video(SelectLevel level, Select_Button button);
	void Load_ScoreSheet(SelectLevel level, Select_Button button);
	void GetUserJointRotation();
	void GetMCJointRotation(SelectLevel level, Select_Button button);
	void CompareRotation();
	void AveragePartsScore();
	void LoadFileToString(FString& Result, const TCHAR* Filename);

	bool SHOULDER_LEFT_Equals(const FRotator& L, const FRotator& R, float Tolerance);
	bool SHOULDER_RIGHT_Equals(const FRotator& L, const FRotator& R, float Tolerance);
	bool ELBOW_LEFT_Equals(const FRotator& L, const FRotator& R, float Tolerance);
	bool ELBOW_RIGHT_Equals(const FRotator& L, const FRotator& R, float Tolerance);
	bool HIP_LEFT_Equals(const FRotator& L, const FRotator& R, float Tolerance);
	bool HIP_RIGHT_Equals(const FRotator& L, const FRotator& R, float Tolerance);
	bool KNEE_LEFT_Equals(const FRotator& L, const FRotator& R, float Tolerance);
	bool KNEE_RIGHT_Equals(const FRotator& L, const FRotator& R, float Tolerance);

	double duration_MC; //모캡 최대길이
	double duration_video; // 코칭 비디오 최대길이

	UPROPERTY()
		FString FilePath;
	UPROPERTY()
		FString Json_String;
	UPROPERTY()
		TArray<double> ratios_MC; // 채점 타이밍
	UPROPERTY()
		TArray<double> ratios_video; // 채점 타이밍
	UPROPERTY()
		TArray<FRotator> Rotation_MC; // 최대길이 * 채점 타이밍
	UPROPERTY()
		TArray<FRotator> Rotation_Video; // 최대길이 * 채점 타이밍
	UPROPERTY()
		TArray<int32> UserFrames; //

	UPROPERTY()
		TArray<int32> SHOULDER_LEFT;
	UPROPERTY()
		TArray<int32> SHOULDER_RIGHT;
	UPROPERTY()
		TArray<int32> ELBOW_LEFT;
	UPROPERTY()
		TArray<int32> ELBOW_RIGHT;
	UPROPERTY()
		TArray<int32> HIP_LEFT;
	UPROPERTY()
		TArray<int32> HIP_RIGHT;
	UPROPERTY()
		TArray<int32> KNEE_LEFT;
	UPROPERTY()
		TArray<int32> KNEE_RIGHT;

	UPROPERTY()
		TArray<int32> leftarm;
	UPROPERTY()
		TArray<int32> rightarm;
	UPROPERTY()
		TArray<int32> leftleg;
	UPROPERTY()
		TArray<int32> rightleg;
	
	int32 TotalScore;

	static Referee* Instance;
public:
	Referee();
	~Referee();

	void Scoring();
	void Init();
	static Referee* Create();
	
	inline const int32 GetTotalScore() { return TotalScore; };
	inline const TArray<int32> GetUserFrames() { return UserFrames; };

	TArray<int32> Getleftarm();
	TArray<int32> Getrightarm();
	TArray<int32> Getleftleg();
	TArray<int32> Getrightleg();

	bool Done_Scoring;

	static SelectLevel Referee_Level;
	static Select_Button Referee_Button;
};
