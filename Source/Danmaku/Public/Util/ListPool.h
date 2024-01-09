// © 2024, Huy Phan. All rights reserved.

#pragma once


template <typename T>
class DANMAKU_API TListPool
{
public:
	static void Add(TArray<T> List)
	{
		List.Empty();
		Stack.Push(List);
	}
	
	static TArray<T> Get()
	{
		if (Stack.Num() > 0)
		{
			return Stack.Pop();
		}
		return TArray<T>();
	}
	
private:
	static TArray<TArray<T>> Stack;
};
