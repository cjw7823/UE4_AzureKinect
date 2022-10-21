// Fill out your copyright notice in the Description page of Project Settings.

#include "Referee.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

SelectLevel Referee::Referee_Level = SelectLevel::Low;
Select_Button Referee::Referee_Button = Select_Button::Button_2;
Referee* Referee::Instance = nullptr;

double Referee::Find_Duration_MC(SelectLevel level, Select_Button button)
{
	FilePath = FPaths::ProjectDir() + TEXT("UserData/") + TEXT("Duration.json");
	LoadFileToString(Json_String, *FilePath);
	TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<TCHAR>::Create(Json_String);
	TSharedPtr<FJsonObject> jsonObj = MakeShareable(new FJsonObject());
	FJsonSerializer::Deserialize(Reader, jsonObj);

	TSharedPtr<FJsonObject> JsonObject;

	JsonObject = jsonObj->GetObjectField(TEXT("MotionCapture"));

	if (JsonObject != nullptr)
	{
		if (level == SelectLevel::Low)
		{
			if (button == Select_Button::Button_1)
				return JsonObject->GetNumberField(FString(TEXT("MC_01")));
			else if (button == Select_Button::Button_2)
				return JsonObject->GetNumberField(FString(TEXT("MC_02")));
			else if (button == Select_Button::Button_3)
				return JsonObject->GetNumberField(FString(TEXT("MC_03")));
			else if (button == Select_Button::Button_4)
				return JsonObject->GetNumberField(FString(TEXT("MC_04")));
			else if (button == Select_Button::Button_5)
				return JsonObject->GetNumberField(FString(TEXT("MC_05")));
		}
		else if (level == SelectLevel::Middle)
		{
			if (button == Select_Button::Button_1)
				return JsonObject->GetNumberField(FString(TEXT("MC_06")));
			else if (button == Select_Button::Button_2)
				return JsonObject->GetNumberField(FString(TEXT("MC_07")));
			else if (button == Select_Button::Button_3)
				return JsonObject->GetNumberField(FString(TEXT("MC_08")));
			else if (button == Select_Button::Button_4)
				return JsonObject->GetNumberField(FString(TEXT("MC_09")));
			else if (button == Select_Button::Button_5)
				return JsonObject->GetNumberField(FString(TEXT("MC_10")));
		}
		else if (level == SelectLevel::High)
		{
			if (button == Select_Button::Button_1)
				return JsonObject->GetNumberField(FString(TEXT("MC_11")));
			else if (button == Select_Button::Button_2)
				return JsonObject->GetNumberField(FString(TEXT("MC_12")));
			else if (button == Select_Button::Button_3)
				return JsonObject->GetNumberField(FString(TEXT("MC_13")));
			else if (button == Select_Button::Button_4)
				return JsonObject->GetNumberField(FString(TEXT("MC_14")));
			else if (button == Select_Button::Button_5)
				return JsonObject->GetNumberField(FString(TEXT("MC_15")));
		}
	}

	return 0.0;
}

double Referee::Find_Duration_Video(SelectLevel level, Select_Button button)
{
	FilePath = FPaths::ProjectDir() + TEXT("UserData/") + TEXT("Duration.json");
	LoadFileToString(Json_String, *FilePath);
	TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<TCHAR>::Create(Json_String);
	TSharedPtr<FJsonObject> jsonObj = MakeShareable(new FJsonObject());
	FJsonSerializer::Deserialize(Reader, jsonObj);

	TSharedPtr<FJsonObject> JsonObject;

	JsonObject = jsonObj->GetObjectField(TEXT("Video"));

	if (JsonObject != nullptr)
	{
		if (level == SelectLevel::Low)
		{
			if (button == Select_Button::Button_1)
				return JsonObject->GetNumberField(FString(TEXT("Video_01")));
			else if (button == Select_Button::Button_2)
				return JsonObject->GetNumberField(FString(TEXT("Video_02")));
			else if (button == Select_Button::Button_3)
				return JsonObject->GetNumberField(FString(TEXT("Video_03")));
			else if (button == Select_Button::Button_4)
				return JsonObject->GetNumberField(FString(TEXT("Video_04")));
			else if (button == Select_Button::Button_5)
				return JsonObject->GetNumberField(FString(TEXT("Video_05")));
		}
		else if (level == SelectLevel::Middle)
		{
			if (button == Select_Button::Button_1)
				return JsonObject->GetNumberField(FString(TEXT("Video_06")));
			else if (button == Select_Button::Button_2)
				return JsonObject->GetNumberField(FString(TEXT("Video_07")));
			else if (button == Select_Button::Button_3)
				return JsonObject->GetNumberField(FString(TEXT("Video_08")));
			else if (button == Select_Button::Button_4)
				return JsonObject->GetNumberField(FString(TEXT("Video_09")));
			else if (button == Select_Button::Button_5)
				return JsonObject->GetNumberField(FString(TEXT("Video_10")));
		}
		else if (level == SelectLevel::High)
		{
			if (button == Select_Button::Button_1)
				return JsonObject->GetNumberField(FString(TEXT("Video_11")));
			else if (button == Select_Button::Button_2)
				return JsonObject->GetNumberField(FString(TEXT("Video_12")));
			else if (button == Select_Button::Button_3)
				return JsonObject->GetNumberField(FString(TEXT("Video_13")));
			else if (button == Select_Button::Button_4)
				return JsonObject->GetNumberField(FString(TEXT("Video_14")));
			else if (button == Select_Button::Button_5)
				return JsonObject->GetNumberField(FString(TEXT("Video_15")));
		}
	}

	return 0.0;
}

void Referee::Load_ScoreSheet(SelectLevel level, Select_Button button)
{
	FilePath = FPaths::ProjectDir() + TEXT("UserData/Score_Sheet/");

	if (level == SelectLevel::Low)
	{
		if (button == Select_Button::Button_1)
			FilePath = FilePath + TEXT("Score_01.json");
		else if (button == Select_Button::Button_2)
			FilePath = FilePath + TEXT("Score_02.json");
		else if (button == Select_Button::Button_3)
			FilePath = FilePath + TEXT("Score_03.json");
		else if (button == Select_Button::Button_4)
			FilePath = FilePath + TEXT("Score_04.json");
		else if (button == Select_Button::Button_5)
			FilePath = FilePath + TEXT("Score_05.json");
	}
	else if (level == SelectLevel::Middle)
	{
		if (button == Select_Button::Button_1)
			FilePath = FilePath + TEXT("Score_06.json");
		else if (button == Select_Button::Button_2)
			FilePath = FilePath + TEXT("Score_07.json");
		else if (button == Select_Button::Button_3)
			FilePath = FilePath + TEXT("Score_08.json");
		else if (button == Select_Button::Button_4)
			FilePath = FilePath + TEXT("Score_09.json");
		else if (button == Select_Button::Button_5)
			FilePath = FilePath + TEXT("Score_10.json");
	}
	else if (level == SelectLevel::High)
	{
		if (button == Select_Button::Button_1)
			FilePath = FilePath + TEXT("Score_11.json");
		else if (button == Select_Button::Button_2)
			FilePath = FilePath + TEXT("Score_12.json");
		else if (button == Select_Button::Button_3)
			FilePath = FilePath + TEXT("Score_13.json");
		else if (button == Select_Button::Button_4)
			FilePath = FilePath + TEXT("Score_14.json");
		else if (button == Select_Button::Button_5)
			FilePath = FilePath + TEXT("Score_15.json");
	}

	LoadFileToString(Json_String, *FilePath);

	TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<TCHAR>::Create(Json_String);
	TSharedPtr<FJsonObject> jsonObj = MakeShareable(new FJsonObject());
	FJsonSerializer::Deserialize(Reader, jsonObj);

	TSharedPtr<FJsonObject> JsonObject1;

	JsonObject1 = jsonObj->GetObjectField(TEXT("MotionCapture"));
	if(JsonObject1 == nullptr)
		GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Red, TEXT("Fail Load_ScoreSheet() : JsonObject == nullptr"));


	auto total1 = JsonObject1->GetNumberField(FString(TEXT("Total")));
	if(total1 ==0)
		GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Red, TEXT("Fail Load_ScoreSheet()"));

	for (int i = 1; i <= total1; i++)
	{
		auto ratio_MC = (JsonObject1->GetNumberField(FString::FromInt(i))) / duration_MC;
		ratios_MC.Add(ratio_MC);
	}

	TSharedPtr<FJsonObject> JsonObject2;
	JsonObject2 = jsonObj->GetObjectField(TEXT("Video"));
	if (JsonObject2 == nullptr)
		GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Red, TEXT("Fail Load_ScoreSheet() : JsonObject == nullptr"));

	auto total2 = JsonObject2->GetNumberField(FString(TEXT("Total")));
	if (total2 == 0)
		GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Red, TEXT("Fail Load_ScoreSheet()"));

	for (int i = 1; i <= total2; i++)
	{
		auto ratio_video = (JsonObject2->GetNumberField(FString::FromInt(i))) / duration_video;
		ratios_video.Add(ratio_video);
	}
}

void Referee::GetUserJointRotation()
{
	FilePath = FPaths::ProjectDir() + TEXT("UserData/") + TEXT("User_Data.json");
	LoadFileToString(Json_String, *FilePath);

	TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<TCHAR>::Create(Json_String);
	TSharedPtr<FJsonObject> jsonObj = MakeShareable(new FJsonObject());
	FJsonSerializer::Deserialize(Reader, jsonObj);

	int32 total_frame;
	//total_frame:
	if (!jsonObj->TryGetNumberField(FString(TEXT("TOTAL_FRAME")), total_frame))
	{
		GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Red, TEXT("Fail GetUserJointRotation() : TryGetNumberField-TOTAL_FRAME"));
		//goto total_frame;
	}

	//GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Yellow, FString::Printf(TEXT("user_frame : %d"), user_frame));
	for (int i = 0; i < ratios_video.Num(); i++)
	{
		double ratio = total_frame * ratios_video[i];
		
		UserFrames.Add(ratio);
		TSharedPtr<FJsonObject> JsonObject;

		//ratio:
		JsonObject = jsonObj->GetObjectField(FString::FromInt((int32)ratio));
		if (JsonObject == nullptr)
		{
			ratio++;
			GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Red, TEXT("Fail GetUserJointRotation() : GetObjectField-ratio"));
			//goto ratio;
		}
		const UEnum* CharStateEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("ScoringJoints"), true);

		for (uint8 j = 0; j < (uint8)ScoringJoints::COUNT; j++)
		{
			const FString EnumToName = CharStateEnum->GetNameStringByValue(j);
			TSharedPtr<FJsonObject> EachJoint = JsonObject->GetObjectField(EnumToName);
			float Pitch = EachJoint->GetNumberField(TEXT("Pitch"));
			float Yaw = EachJoint->GetNumberField(TEXT("Yaw"));
			float Roll = EachJoint->GetNumberField(TEXT("Roll"));
			//이 데이터와 비교해야 함.
			Rotation_Video.Add(FRotator(Pitch, Yaw, Roll));
		}
	}

	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Purple, FString::Printf(TEXT("UserFrames : %d"), UserFrames.Num()));
}

void Referee::GetMCJointRotation(SelectLevel level, Select_Button button)
{
	FilePath = FPaths::ProjectDir() + TEXT("UserData/MC_Data/");

	if (level == SelectLevel::Low)
	{
		if (button == Select_Button::Button_1)
			FilePath = FilePath + TEXT("MC_01.json");
		else if (button == Select_Button::Button_2)
			FilePath = FilePath + TEXT("MC_02.json");
		else if (button == Select_Button::Button_3)
			FilePath = FilePath + TEXT("MC_03.json");
		else if (button == Select_Button::Button_4)
			FilePath = FilePath + TEXT("MC_04.json");
		else if (button == Select_Button::Button_5)
			FilePath = FilePath + TEXT("MC_05.json");
	}
	else if (level == SelectLevel::Middle)
	{
		if (button == Select_Button::Button_1)
			FilePath = FilePath + TEXT("MC_06.json");
		else if (button == Select_Button::Button_2)
			FilePath = FilePath + TEXT("MC_07.json");
		else if (button == Select_Button::Button_3)
			FilePath = FilePath + TEXT("MC_08.json");
		else if (button == Select_Button::Button_4)
			FilePath = FilePath + TEXT("MC_09.json");
		else if (button == Select_Button::Button_5)
			FilePath = FilePath + TEXT("MC_10.json");
	}
	else if (level == SelectLevel::High)
	{
		if (button == Select_Button::Button_1)
			FilePath = FilePath + TEXT("MC_11.json");
		else if (button == Select_Button::Button_2)
			FilePath = FilePath + TEXT("MC_12.json");
		else if (button == Select_Button::Button_3)
			FilePath = FilePath + TEXT("MC_13.json");
		else if (button == Select_Button::Button_4)
			FilePath = FilePath + TEXT("MC_14.json");
		else if (button == Select_Button::Button_5)
			FilePath = FilePath + TEXT("MC_15.json");
	}

	LoadFileToString(Json_String, *FilePath);

	TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<TCHAR>::Create(Json_String);
	TSharedPtr<FJsonObject> jsonObj = MakeShareable(new FJsonObject());
	FJsonSerializer::Deserialize(Reader, jsonObj);

	int32 user_frame;
	//user_frame:
	if (!jsonObj->TryGetNumberField(FString(TEXT("TOTAL_FRAME")), user_frame))
	{
		GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Red, TEXT("Fail GetMCJointRotation() : TryGetNumberField-TOTAL_FRAME"));
		//goto user_frame;
	}

	for (int i = 0; i < ratios_video.Num(); i++)
	{
		auto ratio = user_frame * ratios_MC[i];

		TSharedPtr<FJsonObject> JsonObject;

		//ratio1:
		JsonObject = jsonObj->GetObjectField(FString::FromInt((int32)ratio));
		if (JsonObject == nullptr)
		{
			ratio++;
			GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Red, TEXT("Fail GetMCJointRotation() : GetObjectField-ratio"));
			//goto ratio1;
		}

		const UEnum* CharStateEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("ScoringJoints"), true);

		for (uint8 j = 0; j < (uint8)ScoringJoints::COUNT; j++)
		{
			const FString EnumToName = CharStateEnum->GetNameStringByValue(j);
			TSharedPtr<FJsonObject> EachJoint = JsonObject->GetObjectField(EnumToName);
			float Pitch = EachJoint->GetNumberField(TEXT("Pitch"));
			float Yaw = EachJoint->GetNumberField(TEXT("Yaw"));
			float Roll = EachJoint->GetNumberField(TEXT("Roll"));
			//이 데이터와 비교해야 함.
			Rotation_MC.Add(FRotator(Pitch, Yaw, Roll));
		}
	}
}

void Referee::CompareRotation()
{
	int32 Maxindex = Rotation_Video.Num();
	if (Maxindex == 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Red, TEXT("Fail CompareRotation() : Maxindex == 0"));
		Maxindex = 1;
	}

	GEngine->AddOnScreenDebugMessage(30, 100, FColor::Purple, FString::Printf(TEXT("Maxindex : %d"), Maxindex));

	float tolerance1 = 40.f;
	float tolerance2 = 60.f;

	for (int i = 0; i < Maxindex; i++)
	{
		int temp = i % (int)ScoringJoints::COUNT;

		const UEnum* CharStateEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("ScoringJoints"), true);
		const FString EnumToName = CharStateEnum->GetNameStringByValue(temp);

		auto _MC = FRotator(Rotation_MC[i].Pitch, Rotation_MC[i].Yaw, Rotation_MC[i].Roll);
		auto _Video = FRotator(Rotation_Video[i].Pitch, Rotation_Video[i].Yaw, Rotation_Video[i].Roll);

		if (true)
		{
			UE_LOG(LogTemp, Warning, TEXT("Rotation_MC-%s : %f, %f, %f"), *EnumToName, _MC.Pitch, _MC.Yaw, _MC.Roll);
			UE_LOG(LogTemp, Warning, TEXT("Rotation_Video-%s : %f, %f, %f \n --------"), *EnumToName, _Video.Pitch, _Video.Yaw, _Video.Roll);
		}

		
		if (temp == (int)ScoringJoints::SHOULDER_LEFT)
		{
			if (SHOULDER_LEFT_Equals(_MC, _Video, tolerance1))
			{
				TotalScore += 100;
				SHOULDER_LEFT.Add(100);
			}
			else if (SHOULDER_LEFT_Equals(_MC, _Video, tolerance2))
			{
				TotalScore += 50;
				SHOULDER_LEFT.Add(50);
			}
			else
			{
				TotalScore += 25;
				SHOULDER_LEFT.Add(25);
			}
		}
		else if (temp == (int)ScoringJoints::SHOULDER_RIGHT)
		{
			if (SHOULDER_RIGHT_Equals(_MC, _Video, tolerance1))
			{
				TotalScore += 100;
				SHOULDER_RIGHT.Add(100);
			}
			else if (SHOULDER_RIGHT_Equals(_MC, _Video, tolerance2))
			{
				TotalScore += 50;
				SHOULDER_RIGHT.Add(50);
			}
			else
			{
				TotalScore += 25;
				SHOULDER_RIGHT.Add(25);
			}
		}
		else if (temp == (int)ScoringJoints::ELBOW_LEFT)
		{
			if (ELBOW_LEFT_Equals(_MC, _Video, tolerance1))
			{
				TotalScore += 100;
				ELBOW_LEFT.Add(100);
			}
			else if (ELBOW_LEFT_Equals(_MC, _Video, tolerance2))
			{
				TotalScore += 50;
				ELBOW_LEFT.Add(50);
			}
			else
			{
				TotalScore += 25;
				ELBOW_LEFT.Add(25);
			}
		}
		else if (temp == (int)ScoringJoints::ELBOW_RIGHT)
		{
			if (ELBOW_RIGHT_Equals(_MC, _Video, tolerance1))
			{
				TotalScore += 100;
				ELBOW_RIGHT.Add(100);
			}
			else if (ELBOW_RIGHT_Equals(_MC, _Video, tolerance2))
			{
				TotalScore += 50;
				ELBOW_RIGHT.Add(50);
			}
			else
			{
				TotalScore += 25;
				ELBOW_RIGHT.Add(25);
			}
		}
		else if (temp == (int)ScoringJoints::HIP_LEFT)
		{
			if (HIP_LEFT_Equals(_MC, _Video, tolerance1))
			{
				TotalScore += 100;
				HIP_LEFT.Add(100);
			}
			else if (HIP_LEFT_Equals(_MC, _Video, tolerance2))
			{
				TotalScore += 50;
				HIP_LEFT.Add(50);
			}
			else
			{
				TotalScore += 25;
				HIP_LEFT.Add(25);
			}
		}
		else if (temp == (int)ScoringJoints::HIP_RIGHT)
		{
			if (HIP_RIGHT_Equals(_MC, _Video, tolerance1))
			{
				TotalScore += 100;
				HIP_RIGHT.Add(100);
			}
			else if (HIP_RIGHT_Equals(_MC, _Video, tolerance2))
			{
				TotalScore += 50;
				HIP_RIGHT.Add(50);
			}
			else
			{
				TotalScore += 25;
				HIP_RIGHT.Add(25);
			}
		}
		else if (temp == (int)ScoringJoints::KNEE_LEFT)
		{
			if (KNEE_LEFT_Equals(_MC, _Video, tolerance1))
			{
				TotalScore += 100;
				KNEE_LEFT.Add(100);
			}
			else if (KNEE_LEFT_Equals(_MC, _Video, tolerance2))
			{
				TotalScore += 50;
				KNEE_LEFT.Add(50);
			}
			else
			{
				TotalScore += 25;
				KNEE_LEFT.Add(25);
			}
		}
		else if (temp == (int)ScoringJoints::KNEE_RIGHT)
		{
			if (KNEE_RIGHT_Equals(_MC, _Video, tolerance1))
			{
				TotalScore += 100;
				KNEE_RIGHT.Add(100);
			}
			else if (KNEE_RIGHT_Equals(_MC, _Video, tolerance1))
			{
				TotalScore += 50;
				KNEE_RIGHT.Add(50);
			}
			else
			{
				TotalScore += 25;
				KNEE_RIGHT.Add(25);
			}
		}

	}

	int32 temp = FMath::DivideAndRoundNearest(TotalScore, Maxindex);

	TotalScore = (int32)temp;
	
}

void Referee::AveragePartsScore()
{
	for (int i = 0; i < SHOULDER_LEFT.Num(); i++)
	{
		leftarm.Add((SHOULDER_LEFT[i] + ELBOW_LEFT[i]) / 2);
		rightarm.Add((SHOULDER_RIGHT[i] + ELBOW_RIGHT[i])/2);
		leftleg.Add((HIP_LEFT[i] + KNEE_LEFT[i]) / 2);
		rightleg.Add((HIP_RIGHT[i] + KNEE_RIGHT[i]) / 2);
	}
	//GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Blue, FString::Printf(TEXT("%d"), leftarm.Num()));
}

void Referee::LoadFileToString(FString& Result, const TCHAR* Filename)
{
	if (!FFileHelper::LoadFileToString(Result, Filename))
	{
		GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Red, TEXT("Fail LoadFileToString()"));

		LoadFileToString(Result, Filename);
	}
}

bool Referee::SHOULDER_LEFT_Equals(const FRotator& L, const FRotator& R, float Tolerance)
{
	FRotator MC_correction = FRotator(1.44, 90.74, 1.95);
	FRotator User_correction = FRotator(-3.8, 1.8, -95.0);
	
	FRotator left = UKismetMathLibrary::NormalizedDeltaRotator(MC_correction, L);
	FRotator Right = UKismetMathLibrary::NormalizedDeltaRotator(User_correction, R);

	//GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Red, left.ToString());

	return (FMath::Abs(FRotator::NormalizeAxis(left.Pitch - Right.Pitch)) <= Tolerance)
		&& (FMath::Abs(FRotator::NormalizeAxis(left.Yaw - Right.Yaw)) <= Tolerance)
		&& (FMath::Abs(FRotator::NormalizeAxis(left.Roll - Right.Roll)) <= Tolerance);
}

bool Referee::SHOULDER_RIGHT_Equals(const FRotator& L, const FRotator& R, float Tolerance)
{
	FRotator MC_correction = FRotator(1.24, 89.91, -177.57);
	FRotator User_correction = FRotator(10.6, -8.6, 86.0);

	FRotator left = UKismetMathLibrary::NormalizedDeltaRotator(MC_correction, L);
	FRotator Right = UKismetMathLibrary::NormalizedDeltaRotator(User_correction, R);

	return (FMath::Abs(FRotator::NormalizeAxis(left.Pitch - Right.Pitch)) <= Tolerance)
		&& (FMath::Abs(FRotator::NormalizeAxis(left.Yaw - Right.Yaw)) <= Tolerance)
		&& (FMath::Abs(FRotator::NormalizeAxis(left.Roll - Right.Roll)) <= Tolerance);
}

bool Referee::ELBOW_LEFT_Equals(const FRotator& L, const FRotator& R, float Tolerance)
{
	FRotator MC_correction = FRotator(-0.19, 89.6, 3.2);
	FRotator User_correction = FRotator(22.0, -10.0, -106.0);

	FRotator left = UKismetMathLibrary::NormalizedDeltaRotator(MC_correction, L);
	FRotator Right = UKismetMathLibrary::NormalizedDeltaRotator(User_correction, R);

	return (FMath::Abs(FRotator::NormalizeAxis(left.Pitch - Right.Pitch)) <= Tolerance)
		&& (FMath::Abs(FRotator::NormalizeAxis(left.Yaw - Right.Yaw)) <= Tolerance)
		&& (FMath::Abs(FRotator::NormalizeAxis(left.Roll - Right.Roll)) <= Tolerance);
}

bool Referee::ELBOW_RIGHT_Equals(const FRotator& L, const FRotator& R, float Tolerance)
{
	FRotator MC_correction = FRotator(0.45, 89.87, -176.6);
	FRotator User_correction = FRotator(-1.1, 1.6, 90.3);

	FRotator left = UKismetMathLibrary::NormalizedDeltaRotator(MC_correction, L);
	FRotator Right = UKismetMathLibrary::NormalizedDeltaRotator(User_correction, R);

	return (FMath::Abs(FRotator::NormalizeAxis(left.Pitch - Right.Pitch)) <= Tolerance)
		&& (FMath::Abs(FRotator::NormalizeAxis(left.Yaw - Right.Yaw)) <= Tolerance)
		&& (FMath::Abs(FRotator::NormalizeAxis(left.Roll - Right.Roll)) <= Tolerance);
}

bool Referee::HIP_LEFT_Equals(const FRotator& L, const FRotator& R, float Tolerance)
{
	FRotator MC_correction = FRotator(88.55, -54.16, -142.48);
	FRotator User_correction = FRotator(7.1, -89.1, -73.5);

	FRotator left = UKismetMathLibrary::NormalizedDeltaRotator(MC_correction, L);
	FRotator Right = UKismetMathLibrary::NormalizedDeltaRotator(User_correction, R);

	return (FMath::Abs(FRotator::NormalizeAxis(left.Pitch - Right.Pitch)) <= Tolerance)
		&& (FMath::Abs(FRotator::NormalizeAxis(left.Yaw - Right.Yaw)) <= Tolerance)
		&& (FMath::Abs(FRotator::NormalizeAxis(left.Roll - Right.Roll)) <= Tolerance);
}

bool Referee::HIP_RIGHT_Equals(const FRotator& L, const FRotator& R, float Tolerance)
{
	FRotator MC_correction = FRotator(-87.76, -143.94, 57.02);
	FRotator User_correction = FRotator(-7.9, 89.3, 98.1);

	FRotator left = UKismetMathLibrary::NormalizedDeltaRotator(MC_correction, L);
	FRotator Right = UKismetMathLibrary::NormalizedDeltaRotator(User_correction, R);

	return (FMath::Abs(FRotator::NormalizeAxis(left.Pitch - Right.Pitch)) <= Tolerance)
		&& (FMath::Abs(FRotator::NormalizeAxis(left.Yaw - Right.Yaw)) <= Tolerance)
		&& (FMath::Abs(FRotator::NormalizeAxis(left.Roll - Right.Roll)) <= Tolerance);
}

bool Referee::KNEE_LEFT_Equals(const FRotator& L, const FRotator& R, float Tolerance)
{
	FRotator MC_correction = FRotator(77.46, 177.93, 84.08);
	FRotator User_correction = FRotator(15.3, -87.5, -80.8);

	FRotator left = UKismetMathLibrary::NormalizedDeltaRotator(MC_correction, L);
	FRotator Right = UKismetMathLibrary::NormalizedDeltaRotator(User_correction, R);

	return (FMath::Abs(FRotator::NormalizeAxis(left.Pitch - Right.Pitch)) <= Tolerance)
		&& (FMath::Abs(FRotator::NormalizeAxis(left.Yaw - Right.Yaw)) <= Tolerance)
		&& (FMath::Abs(FRotator::NormalizeAxis(left.Roll - Right.Roll)) <= Tolerance);
}

bool Referee::KNEE_RIGHT_Equals(const FRotator& L, const FRotator& R, float Tolerance)
{
	FRotator MC_correction = FRotator(-77.88, 2.9, -95.36);
	FRotator User_correction = FRotator(-23.3, 88.5, 98.0);

	FRotator left = UKismetMathLibrary::NormalizedDeltaRotator(MC_correction, L);
	FRotator Right = UKismetMathLibrary::NormalizedDeltaRotator(User_correction, R);

	return (FMath::Abs(FRotator::NormalizeAxis(left.Pitch - Right.Pitch)) <= Tolerance)
		&& (FMath::Abs(FRotator::NormalizeAxis(left.Yaw - Right.Yaw)) <= Tolerance)
		&& (FMath::Abs(FRotator::NormalizeAxis(left.Roll - Right.Roll)) <= Tolerance);
}

Referee::Referee()
{
	Init();
}

Referee::~Referee()
{
}

void Referee::Scoring()
{
	Init();

	//Video와 MotionCapture의 최대 길이를 구함.
	duration_MC = Find_Duration_MC(Referee_Level, Referee_Button);
	if (duration_MC == 0.0)
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, TEXT("duration_MC == 0.0"));// exit(-1);

	duration_video = Find_Duration_Video(Referee_Level, Referee_Button);
	if (duration_video == 0.0)
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, TEXT("duration_video == 0.0"));// exit(-1);

	//위에서 구한 최대 길이를 사용해 채점 타이밍의 비율을 구함. ratios_MC, ratios_video
	Load_ScoreSheet(Referee_Level, Referee_Button);

	//Rotation_MC, Rotation_Video
	GetUserJointRotation();
	GetMCJointRotation(Referee_Level, Referee_Button);

	//두 각도 집합 비교. 실 채점이 진행.
	CompareRotation();

	AveragePartsScore();

	Done_Scoring = true;
}

void Referee::Init()
{
	Done_Scoring = false;

	TotalScore = 0;
	duration_MC = 0.0;
	duration_video = 0.0;
	FilePath = NULL;
	Json_String = NULL;
	ratios_MC.Init(NULL, 0);
	ratios_video.Init(NULL, 0);
	Rotation_MC.Init(FRotator(), 0);
	Rotation_Video.Init(FRotator(), 0);
	UserFrames.Init(NULL, 0);
	SHOULDER_LEFT.Init(NULL, 0);
	SHOULDER_RIGHT.Init(NULL, 0);
	ELBOW_LEFT.Init(NULL, 0);
	ELBOW_RIGHT.Init(NULL, 0);
	HIP_LEFT.Init(NULL, 0);
	HIP_RIGHT.Init(NULL, 0);
	KNEE_LEFT.Init(NULL, 0);
	KNEE_RIGHT.Init(NULL, 0);
	leftarm.Init(NULL, 0);
	leftleg.Init(NULL, 0);
	rightarm.Init(NULL, 0);
	rightleg.Init(NULL, 0);
}

Referee* Referee::Create()
{
	if (Instance == nullptr)
		Instance = new Referee();

	return Instance;
}

TArray<int32> Referee::Getleftarm()
{
	return leftarm;
}

TArray<int32> Referee::Getrightarm()
{
	return rightarm;
}

TArray<int32> Referee::Getleftleg()
{
	return leftleg;
}

TArray<int32> Referee::Getrightleg()
{
	return rightleg;
}
