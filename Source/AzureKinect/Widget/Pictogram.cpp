// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Pictogram.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"

#define Err_Range 0.1

SelectLevel UPictogram::Level = SelectLevel::Low;
Select_Button UPictogram::Button = Select_Button::None;

UPictogram::UPictogram(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	Low_pictogram1.Init(NULL, 0);
	Low_pictogram2.Init(NULL, 0);
	Low_pictogram3.Init(NULL, 0);
	Low_pictogram4.Init(NULL, 0);
	Low_pictogram5.Init(NULL, 0);
	Middle_pictogram1.Init(NULL, 0);
	Middle_pictogram2.Init(NULL, 0);
	Middle_pictogram3.Init(NULL, 0);
	Middle_pictogram4.Init(NULL, 0);
	Middle_pictogram5.Init(NULL, 0);
	High_pictogram1.Init(NULL, 0);
	High_pictogram2.Init(NULL, 0);
	High_pictogram3.Init(NULL, 0);
	High_pictogram4.Init(NULL, 0);
	High_pictogram5.Init(NULL, 0);

	FString prepath = FString(TEXT("Texture2D'/Game/"));
	FString Texturepath = FString(TEXT("Widget/Texture_new_/Pictogram"));
	FString step1 = FString(TEXT("초급동작_0"));
	FString step2 = FString(TEXT("중급동작_0"));
	FString step3 = FString(TEXT("고급동작_0"));
	FString str1 = FString(TEXT("_정면_"));
	FString str2 = FString(TEXT("_면"));


	IFileManager& FileManager = IFileManager::Get();

	for (int k = 0; k < SelectLevel::Level_None; k++) //난이도별(Level)
	{
		switch ((SelectLevel)k)
		{
			case SelectLevel::Low:
				for (int i = 1; i <= 5; i++) // 난이도별 5개의 춤(Button)
				{
					FString ButtonNum = FString::FromInt(i);

					//파일개수 찾기
					FString FMpath = FPaths::ProjectContentDir() + Texturepath + "/Low" + "/" + ButtonNum;
					TArray<FString> FileNames;
					const TCHAR* cPath = *FMpath;
					FString Dot = ".uasset";
					const TCHAR* dot = *Dot;
					FileManager.FindFiles(FileNames, cPath, dot);

					for (int j = FileNames.Num(); j > 0; j--) //경로의 파일 개수 (Pictogram 개수)
					{
						FString order = FString::FromInt(j);

						if (j < 10)
						{
							order = FString(TEXT("0")) + order;
						}

						FString temp = prepath + Texturepath + "/Low" + "/" + ButtonNum + "/" + step1 + ButtonNum + str1 + order + str2 + FString(TEXT("."))
							+ step1 + ButtonNum + str1 + order + str2 + FString(TEXT("'"));
						const TCHAR* ch = *temp;

						ConstructorHelpers::FObjectFinder<UTexture2D> texture(ch);
						if (texture.Succeeded())
						{
							switch (i)
							{
							case 1:
								Low_pictogram1.AddUnique(texture.Object);
								break;
							case 2:
								Low_pictogram2.AddUnique(texture.Object);
								break;
							case 3:
								Low_pictogram3.AddUnique(texture.Object);
								break;
							case 4:
								Low_pictogram4.AddUnique(texture.Object);
								break;
							case 5:
								Low_pictogram5.AddUnique(texture.Object);
								break;
							}
						}
					}
				}
				break;
			case SelectLevel::Middle:
				for (int i = 1; i <= 5; i++) // 난이도별 5개의 춤(Button)
				{
					FString ButtonNum = FString::FromInt(i);

					//파일개수 찾기
					FString FMpath = FPaths::ProjectContentDir() + Texturepath + "/Middle" + "/" + ButtonNum;
					TArray<FString> FileNames;
					const TCHAR* cPath = *FMpath;
					FString Dot = ".uasset";
					const TCHAR* dot = *Dot;
					FileManager.FindFiles(FileNames, cPath, dot);

					for (int j = FileNames.Num(); j > 0; j--) //경로의 파일 개수 (Pictogram 개수)
					{
						FString order = FString::FromInt(j);

						if (j < 10)
						{
							order = FString(TEXT("0")) + order;
						}

						FString temp = prepath + Texturepath + "/Middle" + "/" + ButtonNum + "/" + step2 + ButtonNum + str1 + order + str2 + FString(TEXT("."))
							+ step2 + ButtonNum + str1 + order + str2 + FString(TEXT("'"));
						const TCHAR* ch = *temp;

						ConstructorHelpers::FObjectFinder<UTexture2D> texture(ch);
						if (texture.Succeeded())
						{
							switch (i)
							{
							case 1:
								Middle_pictogram1.AddUnique(texture.Object);
								break;
							case 2:
								Middle_pictogram2.AddUnique(texture.Object);
								break;
							case 3:
								Middle_pictogram3.AddUnique(texture.Object);
								break;
							case 4:
								Middle_pictogram4.AddUnique(texture.Object);
								break;
							case 5:
								Middle_pictogram5.AddUnique(texture.Object);
								break;
							}
						}
					}
				}
				break;
			case SelectLevel::High:
				for (int i = 1; i <= 5; i++) // 난이도별 5개의 춤(Button)
				{
					FString ButtonNum = FString::FromInt(i);

					//파일개수 찾기
					FString FMpath = FPaths::ProjectContentDir() + Texturepath + "/High" + "/" + ButtonNum;
					TArray<FString> FileNames;
					const TCHAR* cPath = *FMpath;
					FString Dot = ".uasset";
					const TCHAR* dot = *Dot;
					FileManager.FindFiles(FileNames, cPath, dot);

					for (int j = FileNames.Num(); j > 0; j--) //경로의 파일 개수 (Pictogram 개수)
					{
						FString order = FString::FromInt(j);

						if (j < 10)
						{
							order = FString(TEXT("0")) + order;
						}

						FString temp = prepath + Texturepath + "/High" + "/" + ButtonNum + "/" + step3 + ButtonNum + str1 + order + str2 + FString(TEXT("."))
							+ step3 + ButtonNum + str1 + order + str2 + FString(TEXT("'"));
						const TCHAR* ch = *temp;

						ConstructorHelpers::FObjectFinder<UTexture2D> texture(ch);
						if (texture.Succeeded())
						{
							switch (i)
							{
							case 1:
								High_pictogram1.AddUnique(texture.Object);
								break;
							case 2:
								High_pictogram2.AddUnique(texture.Object);
								break;
							case 3:
								High_pictogram3.AddUnique(texture.Object);
								break;
							case 4:
								High_pictogram4.AddUnique(texture.Object);
								break;
							case 5:
								High_pictogram5.AddUnique(texture.Object);
								break;
							}
						}
					}
				}
				break;
		}
	}

	level = Level;
	button = Button;
}

void UPictogram::NativeConstruct()
{
	Super::NativeConstruct();

	Timing.Init(NULL, 0);
	pictogram.Init(NULL, 0);

	switch (Level)
	{
	case SelectLevel::Low :
		switch (Button)
		{
		case Select_Button::Button_1 :
			pictogram = Low_pictogram1;
			break;
		case Select_Button::Button_2:
			pictogram = Low_pictogram2;
			break;
		case Select_Button::Button_3:
			pictogram = Low_pictogram3;
			break;
		case Select_Button::Button_4:
			pictogram = Low_pictogram4;
			break;
		case Select_Button::Button_5:
			pictogram = Low_pictogram5;
			break;
		}
		break;
	case SelectLevel::Middle:
		switch (Button)
		{
		case Select_Button::Button_1:
			pictogram = Middle_pictogram1;
			break;
		case Select_Button::Button_2:
			pictogram = Middle_pictogram2;
			break;
		case Select_Button::Button_3:
			pictogram = Middle_pictogram3;
			break;
		case Select_Button::Button_4:
			pictogram = Middle_pictogram4;
			break;
		case Select_Button::Button_5:
			pictogram = Middle_pictogram5;
			break;
		}
		break;
	case SelectLevel::High:
		switch (Button)
		{
		case Select_Button::Button_1:
			pictogram = High_pictogram1;
			break;
		case Select_Button::Button_2:
			pictogram = High_pictogram2;
			break;
		case Select_Button::Button_3:
			pictogram = High_pictogram3;
			break;
		case Select_Button::Button_4:
			pictogram = High_pictogram4;
			break;
		case Select_Button::Button_5:
			pictogram = High_pictogram5;
			break;
		}
		break;
	}

	GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Red, FString::Printf(TEXT("pictogram.Num() : %d"), pictogram.Num()));

	Init();
}

void UPictogram::NativeDestruct()
{
	this->ConditionalBeginDestroy();
}

void UPictogram::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	if (MediaPlayer != NULL)
	{
		//MediaPlayer 값이 유효함을 확인함.
		double VideoTime = MediaPlayer->GetTime().GetTotalSeconds();

		if (Timing.IsValidIndex(Timing.Num()-1))//Timing.Top()의 인덱스가 유효한지 체크.
		{
			GEngine->AddOnScreenDebugMessage(3, 0.5, FColor::Red, FString::Printf(TEXT("Timing.Top() : %f"), Timing.Top()));
			if (abs(VideoTime - Timing.Top()) < Err_Range)
			{
				Timing.Pop();
				SpawnPictogram();
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(4, 0.5, FColor::Red, FString::Printf(TEXT("Timing is Empty, Num() : %d"), Timing.Num()));
		}
	}
}

void UPictogram::Init()
{
	FString Json_String;
	FString FilePath = FPaths::ProjectDir() + TEXT("UserData/PictogramTiming/");
	switch (Level)
	{
	case SelectLevel::Low:
		switch (Button)
		{
		case Select_Button::Button_1:
			FilePath = FilePath + TEXT("Picto_01.json");
			break;
		case Select_Button::Button_2:
			FilePath = FilePath + TEXT("Picto_02.json");
			break;
		case Select_Button::Button_3:
			FilePath = FilePath + TEXT("Picto_03.json");
			break;
		case Select_Button::Button_4:
			FilePath = FilePath + TEXT("Picto_04.json");
			break;
		case Select_Button::Button_5:
			FilePath = FilePath + TEXT("Picto_05.json");
			break;
		}
		break;
	case SelectLevel::Middle:
		switch (Button)
		{
		case Select_Button::Button_1:
			FilePath = FilePath + TEXT("Picto_06.json");
			break;
		case Select_Button::Button_2:
			FilePath = FilePath + TEXT("Picto_07.json");
			break;
		case Select_Button::Button_3:
			FilePath = FilePath + TEXT("Picto_08.json");
			break;
		case Select_Button::Button_4:
			FilePath = FilePath + TEXT("Picto_09.json");
			break;
		case Select_Button::Button_5:
			FilePath = FilePath + TEXT("Picto_10.json");
			break;
		}
		break;
	case SelectLevel::High:
		switch (Button)
		{
		case Select_Button::Button_1:
			FilePath = FilePath + TEXT("Picto_11.json");
			break;
		case Select_Button::Button_2:
			FilePath = FilePath + TEXT("Picto_12.json");
			break;
		case Select_Button::Button_3:
			FilePath = FilePath + TEXT("Picto_13.json");
			break;
		case Select_Button::Button_4:
			FilePath = FilePath + TEXT("Picto_14.json");
			break;
		case Select_Button::Button_5:
			FilePath = FilePath + TEXT("Picto_15.json");
			break;
		}
		break;
	}
	LoadFileToString(Json_String, *FilePath);

	TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<TCHAR>::Create(Json_String);
	TSharedPtr<FJsonObject> jsonObj = MakeShareable(new FJsonObject());
	FJsonSerializer::Deserialize(Reader, jsonObj);

	int32 total;

	if (!jsonObj->TryGetNumberField(FString(TEXT("Total")), total))
	{
		GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Red, TEXT("Fail UPictogram::Init()"));
	}

	for (int i = total; i > 0; i--)
	{
		auto temp = jsonObj->GetNumberField(FString::FromInt(i)) - 2.0;
		Timing.Add(temp);
	}
}

void UPictogram::SpawnPictogram()
{
	if (IsValid(pictogram.Top()))
	{
		UImage* TempImage = NewObject<UImage>(this, UImage::StaticClass());
		CanvasPanel_0->AddChild(TempImage);

		TempImage->SetBrushFromTexture(pictogram.Pop());
		TempImage->SetVisibility(ESlateVisibility::Visible);

		UCanvasPanelSlot* imageSlot = Cast<UCanvasPanelSlot>(TempImage->Slot);
		imageSlot->SetSize(FVector2D(110.0f, 120.0f));
		imageSlot->SetPosition(FVector2D(600.0f, 20.0f));

		MovePictogram(TempImage);
	}
	

	/*Image_0->SetBrushFromTexture(Cast<UTexture2D>(Image_1->Brush.GetResourceObject()));
	Image_1->SetBrushFromTexture(Cast<UTexture2D>(Image_2->Brush.GetResourceObject()));
	Image_2->SetBrushFromTexture(Cast<UTexture2D>(Image_3->Brush.GetResourceObject()));
	Image_3->SetBrushFromTexture(Cast<UTexture2D>(Image_4->Brush.GetResourceObject()));*/

	/*if(pictogram.IsValidIndex(0))
		Image_4->SetBrushFromTexture(pictogram.Pop());
	else
		Image_4->SetBrushFromTexture(Zero_opacity);*/
}

void UPictogram::MovePictogram(UImage* image)
{
	UCanvasPanelSlot* imageSlot = Cast<UCanvasPanelSlot>(image->Slot);
	double posi = imageSlot->GetPosition().X - 6.0;
	imageSlot->SetPosition(FVector2D(posi, 0.0f));


	if (FMath::IsNearlyEqual(posi, 0.0) || posi < 0.0)
	{
		image->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		FTimerDelegate TimerDel;

		FTimerHandle TimerHandle;

		TimerDel.BindUObject(this, &UPictogram::MovePictogram, image);
		//TimerDel.BindUFunction(this, FName("MovePictogram"), image);

		//0.01초로 설정하면 타이밍이 어긋남. 델리게이트 생성하는데 일정 시간이 필요해 밀리는 것으로 추정.
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDel, 0.02f, false);
	}


}

void UPictogram::LoadFileToString(FString& Result, const TCHAR* Filename)
{
	if (!FFileHelper::LoadFileToString(Result, Filename))
	{
		GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Red, TEXT("Fail LoadFileToString()"));

		LoadFileToString(Result, Filename);
	}
}
