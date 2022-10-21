// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "MainGameInstanceSubsystem.generated.h"

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCreateSessionComplete, FName, bool);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnUpdateSessionComplete, FName, bool);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnStartSessionComplete, FName, bool);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnDestroySessionComplete, FName, bool);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnFindSessionsComplete, bool);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnJoinSessionComplete, FName, EOnJoinSessionCompleteResult::Type);

UCLASS()
class AZUREKINECT_API UMainGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UMainGameInstanceSubsystem();
	virtual void Deinitialize() override;

	void CreateSession(int32 NumPublicConnections, bool IsLANMatch);
	void UpdateSession();
	void StartSession();
	void DestroySession();
	void FindSessions(int32 MaxSearchResults, bool IsLANQuery);
	void JoinGameSession(const FOnlineSessionSearchResult& SessionResult);

	FOnlineSessionSearchResult GetSearchResult();

	FOnCreateSessionComplete OnCreateSessionCompleteEvent;
	FOnUpdateSessionComplete OnUpdateSessionCompleteEvent;
	FOnStartSessionComplete OnStartSessionCompleteEvent;
	FOnDestroySessionComplete OnDestroySessionCompleteEvent;
	FOnFindSessionsComplete OnFindSessionsCompleteEvent;
	FOnJoinSessionComplete OnJoinGameSessionCompleteEvent;

protected:
	void OnCreateSessionCompleted(FName SessionName, bool Successful);
	void OnUpdateSessionCompleted(FName SessionName, bool Successful);
	void OnStartSessionCompleted(FName SessionName, bool Successful);
	void OnDestroySessionCompleted(FName SessionName, bool Successful);
	void OnFindSessionsCompleted(bool Successful);

	void OnJoinSessionCompleted(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	bool TryTravelToCurrentSession();

private:
	TSharedPtr<FOnlineSessionSettings> LastSessionSettings;

	FOnCreateSessionCompleteDelegate CreateSessionCompleteDelegate;
	FDelegateHandle CreateSessionCompleteDelegateHandle;

	FOnUpdateSessionCompleteDelegate UpdateSessionCompleteDelegate;
	FDelegateHandle UpdateSessionCompleteDelegateHandle;

	FOnStartSessionCompleteDelegate StartSessionCompleteDelegate;
	FDelegateHandle StartSessionCompleteDelegateHandle;

	FOnDestroySessionCompleteDelegate DestroySessionCompleteDelegate;
	FDelegateHandle DestroySessionCompleteDelegateHandle;

	FOnFindSessionsCompleteDelegate FindSessionsCompleteDelegate;
	FDelegateHandle FindSessionsCompleteDelegateHandle;

	TSharedPtr<FOnlineSessionSearch> LastSessionSearch;

	FOnJoinSessionCompleteDelegate JoinSessionCompleteDelegate;
	FDelegateHandle JoinSessionCompleteDelegateHandle;
};
