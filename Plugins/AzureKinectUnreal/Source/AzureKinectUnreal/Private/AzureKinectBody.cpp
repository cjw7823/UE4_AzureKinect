// Fill out your copyright notice in the Description page of Project Settings.


#include "AzureKinectBody.h"

UAzureKinectBody::UAzureKinectBody() :
	Id(0)
{
	Joints.SetNum(JointCount);
	for (uint32 i = 0; i < JointCount; i++)
	{
		Joints[i].Index = i;
	}

	bIsMirrored = false;
	bIsTracked = false;
}

UAzureKinectBody::~UAzureKinectBody()
{
	Joints.Empty();
}

int32 UAzureKinectBody::GetId() const
{
	return Id;
}

TArray<FAzureKinectJoint> UAzureKinectBody::GetJoints() const
{
	return Joints;
}

FAzureKinectJoint UAzureKinectBody::GetJoint(int32 index) const
{
	if (index < 0 || index >= Joints.Num()) return Joints[0];
	return Joints[index];
}

void UAzureKinectBody::UpdateBodyWithKinectInfo()
{
	if (!bIsTracked) return;

	Id = NativeBody.id;

	for (uint32 i = 0; i < JointCount; i++)
	{
		Joints[i].UpdateFromNativeJoint(NativeBody.skeleton.joints[i], bIsMirrored);
	}
}
