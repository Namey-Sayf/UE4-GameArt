#pragma once

template <class InElementType>
class MArray
{
	InElementType** ArrayElemtn;

	int32 Opacity;
	int32 Count;

public:
	MArray() : MArray(10)
	{
	}

	MArray(int32 opacity) : Opacity(opacity), Count(0)
	{
		check(opacity > 0);

		ArrayElemtn = new InElementType*[opacity];
	}

	~MArray()
	{
		delete[] ArrayElemtn;
	}

	void Add(InElementType* element)
	{
		AddImpl(*element);
	}

	void Add(InElementType& element)
	{
		AddImpl(element);
	}

	void Add(InElementType&& element)
	{
		AddImpl(element);
	}

	InElementType* operator [](int32 index)
	{
		return Find(index);
	}

	const InElementType* operator [](int32 index) const
	{
		return Find(index);
	}

	InElementType* Find(int32 index) const
	{
		check(index >= 0 && index < Count);

		return ArrayElemtn[index];
	}

	int32 Num()
	{
		return Count;
	}

private:
	FORCEINLINE InElementType& AddImpl(InElementType& element)
	{
		if (Count >= Opacity)
		{
			Resize();
		}

		ArrayElemtn[Count] = &element;

		Count++;

		return element;
	}

	FORCEINLINE void Resize()
	{
		InElementType** NewArrayElemtn = new InElementType*[Opacity * 2];

		CopyTo(NewArrayElemtn, ArrayElemtn, Count);

		Opacity *= 2;

		delete[] ArrayElemtn;

		ArrayElemtn = NewArrayElemtn;
	}

	FORCEINLINE void CopyTo(InElementType** NewArrayElemtn, InElementType** OldArrayElemtn, int32 count)
	{
		for (int32 i = 0; i < count; i++)
		{
			NewArrayElemtn[i] = (OldArrayElemtn[i]);
		}
	}
};
